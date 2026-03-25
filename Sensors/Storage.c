#include "Storage.h"
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>
#include <ti/drivers/UART.h>
#include <string.h>
#include <stdint.h>

extern UART_Handle uart;

/* -----------------------------------------------------------------------
 * Task configuration
 * --------------------------------------------------------------------- */
#define STORAGE_TASK_PRIORITY   1
#define STORAGE_TASK_STACK_SIZE 448

/* -----------------------------------------------------------------------
 * Ring buffer
 *
 * ring_head — index of the NEXT slot to write (advanced by ISR only)
 * ring_tail — index of the NEXT slot to read  (advanced by task only)
 *
 * Empty condition : ring_head == ring_tail
 * Full  condition : (ring_head + 1) % RING_BUFFER_SLOTS == ring_tail
 *   → maximum capacity = RING_BUFFER_SLOTS - 1 = 15 frames
 *
 * Thread safety on Cortex-M3:
 *   uint8_t reads/writes are atomic.  ISR writes ring_head only;
 *   task writes ring_tail only.  No additional locking needed.
 * --------------------------------------------------------------------- */
typedef struct {
    char    data[RING_SLOT_SIZE];
    uint8_t len;
} StorageRingSlot;

static StorageRingSlot  ring_buffer[RING_BUFFER_SLOTS];
static volatile uint8_t ring_head = 0;   /* written by ISR only  */
static          uint8_t ring_tail = 0;   /* written by task only */

static volatile uint32_t dropped_frames = 0;

/* -----------------------------------------------------------------------
 * RTOS objects
 * --------------------------------------------------------------------- */
static Semaphore_Struct mailbox_struct;
static Semaphore_Struct init_struct;

Semaphore_Handle storage_buffer_mailbox;  /* counting — one count per frame */
Semaphore_Handle storage_init_complete;   /* binary   — posted by Sensors_init */

static uint8_t storage_status = 0;

static Task_Struct storageTask;
static Char        storageTaskStack[STORAGE_TASK_STACK_SIZE];

/* ======================================================================
 * ISR-callable API
 * ==================================================================== */

/*
 * Storage_push_frame
 * Safe to call from interrupt context.  Copies <len> bytes from <data>
 * into the next ring buffer slot and posts the counting semaphore so the
 * Storage task wakes for each frame.
 */
int Storage_push_frame(const char* data, uint8_t len)
{
    uint8_t next_head = (uint8_t)((ring_head + 1u) % RING_BUFFER_SLOTS);

    if (next_head == ring_tail) {
        /* Ring buffer full — drop this frame */
        dropped_frames++;
        return 0;
    }

    memcpy(ring_buffer[ring_head].data, data, len);
    ring_buffer[ring_head].len = len;

    /* Advance head atomically (uint8_t single-instruction write on M3) */
    ring_head = next_head;

    /* One semaphore count per frame — task wakes once per frame */
    Semaphore_post(storage_buffer_mailbox);
    return 1;
}

uint32_t Storage_get_dropped_frames(void)
{
    return dropped_frames;
}

uint8_t getStatus(void)
{
    return storage_status;
}

char* Storage_get_transaction_buffer(void)
{
    return da_get_transaction_buffer();
}

/* ======================================================================
 * Storage task
 * ==================================================================== */

static void Storage_taskFxn(UArg a0, UArg a1)
{
    /* Block until Sensors_init() completes and posts storage_init_complete */
    Semaphore_pend(storage_init_complete, BIOS_WAIT_FOREVER);
    UART_write(uart, "ST\r\n", 4);   /* Storage Task started */

    while (1) {
        /* Block until at least one frame is in the ring buffer */
        Semaphore_pend(storage_buffer_mailbox, BIOS_WAIT_FOREVER);
        storage_status = 0;

        UART_write(uart, "SW\r\n", 4);   /* Storage Write starting */

        /* Consume one frame from the tail — no mutex held during SD I/O */
        int wr = da_write(ring_buffer[ring_tail].data,
                          ring_buffer[ring_tail].len);

        /* Advance tail now that we have finished reading from this slot */
        ring_tail = (uint8_t)((ring_tail + 1u) % RING_BUFFER_SLOTS);

        if (wr != DISK_SUCCESS) {
            storage_status = 1;
            UART_write(uart, "WF\r\n", 4);   /* Write Failed */
        }

        /* da_commit: soft flush every call; hard flush + f_sync every
         * DA_SYNC_SECTORS sectors; rollover at DA_FILE_ROLLOVER_THRESHOLD */
        int cm = da_commit();
        if (cm != DISK_SUCCESS) {
            storage_status = 1;
            UART_write(uart, "CF\r\n", 4);   /* Commit Failed */
        }

        if (storage_status == 0) {
            UART_write(uart, "OK\r\n", 4);   /* Write OK */
        }
        /* NOTE: no Semaphore_post(mutex) — mutex has been removed */
    }
}

/* ======================================================================
 * Initialisation
 * ==================================================================== */

void Storage_init(void)
{
    Semaphore_Params mailParams;
    Semaphore_Params initParams;

    Semaphore_Params_init(&mailParams);
    Semaphore_Params_init(&initParams);

    /* COUNTING semaphore — one count per frame pushed into ring buffer */
    mailParams.mode = Semaphore_Mode_COUNTING;
    initParams.mode = Semaphore_Mode_BINARY;

    Semaphore_construct(&mailbox_struct, 0, &mailParams);
    Semaphore_construct(&init_struct,    0, &initParams);

    storage_buffer_mailbox = Semaphore_handle(&mailbox_struct);
    storage_init_complete  = Semaphore_handle(&init_struct);
}

void Storage_createTask(void)
{
    Task_Params taskParams;

    /* Initialise semaphores BEFORE creating the task */
    Storage_init();

    Task_Params_init(&taskParams);
    taskParams.stack     = storageTaskStack;
    taskParams.stackSize = STORAGE_TASK_STACK_SIZE;
    taskParams.priority  = STORAGE_TASK_PRIORITY;

    Task_construct(&storageTask, Storage_taskFxn, &taskParams, NULL);
}
