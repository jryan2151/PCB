#ifndef STORAGE_H
#define STORAGE_H

#include <ti/sysbios/knl/Semaphore.h>
#include "DiskAccess.h"

/* -----------------------------------------------------------------------
 * Ring-buffer dimensions
 * --------------------------------------------------------------------- */
#define RING_BUFFER_SLOTS  16u    /* number of frame slots; max in-flight = 15 */
#define RING_SLOT_SIZE     128u   /* bytes per slot — fits any serializer frame */

/* -----------------------------------------------------------------------
 * Synchronisation handles (used by sensors.c / Storage_push_frame)
 * --------------------------------------------------------------------- */
extern Semaphore_Handle storage_buffer_mailbox;  /* counting semaphore */
extern Semaphore_Handle storage_init_complete;   /* binary semaphore   */

/* -----------------------------------------------------------------------
 * Public API
 * --------------------------------------------------------------------- */

/*
 * Storage_push_frame
 *
 * Called from ISR (DACtimerCallback → load_serializer) to enqueue one
 * serialised sensor frame into the ring buffer.
 *
 * Thread safety: ring_head written only by ISR; ring_tail read atomically
 * (uint8_t on Cortex-M3).  No mutex required.
 *
 * Returns 1 on success, 0 if the ring buffer was full (frame dropped).
 */
int Storage_push_frame(const char* data, uint8_t len);

/* Returns the number of frames dropped due to ring-buffer overflow. */
uint32_t Storage_get_dropped_frames(void);

/* Task creation (call once at startup) */
void Storage_init(void);
void Storage_createTask(void);

/* Status: 0 = last write OK, non-zero = error */
uint8_t getStatus(void);

/* Debug — do not use in production */
char* Storage_get_transaction_buffer(void);

#endif /* STORAGE_H */
