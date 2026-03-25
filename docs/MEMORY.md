# CCS Workspace Memory

## Project
TI CC2640R2 BLE peripheral (SimplePeripheral) with SD card data logging via FatFS.
Root: `simple_peripheral_cc2640r2lp_app/`
Active branch: `Extended-Use-SD-Card`

## SDK & Toolchain
- SDK: `C:\ti\simplelink_cc2640r2_sdk_5_10_00_02`  (SimpleLink CC2640R2 SDK v5.10.0.02)
- Compiler: TI ARM Compiler 18.1.8.LTS (TMS470, Cortex-M3, Thumb, little-endian)
- IDE: TI Code Composer Studio (CCS), Eclipse-based (.cproject)
- Board file: `C:\ti\simplelink_cc2640r2_sdk_5_10_00_02\source\ti\boards\CC2640R2_LAUNCHXL\CC2640R2_LAUNCHXL.c`
  (standard LaunchPad board file — custom BACPAC PCB uses same file)

## Key Files
- `Sensors/DiskAccess.c` — Main SD/FatFS logic (session mgmt, read/write/commit)
- `Sensors/DiskAccess.h` — API + error codes
- `Sensors/Storage.c` — RTOS task + ring buffer wrapper around da_write/da_commit
- `Sensors/Storage.h` — Ring buffer API (Storage_push_frame, Storage_get_dropped_frames)
- `Sensors/sensors.c` — Sensors_init(), DACtimerCallback ISR, load_serializer()
- `Sensors/ff.c / ff.h / ffconf.h / diskio.c` — FatFS library (FFCONF_DEF 80386)
- `Application/simple_peripheral.c` — Calls Sensors_init() at line 478 inside SBP task
- `Startup/main.c` — Calls Storage_createTask() at line 220, then BIOS_start()

## Implementation Status — All 4 Fixes IMPLEMENTED (branch: Extended-Use-SD-Card)

### Fix 1 — f_open crash (DONE)
**Original bug:** `FA_CREATE_ALWAYS` on first SD write after cold boot caused FatFS hang.
Also `System_sprintf(..., "%lu", uint32_t)` with wrong format specifier corrupted filename buffer.
**Fix:**
- Removed `da_read_session_counter()` / `da_write_session_counter()` entirely
- `da_find_next_file()`: scans `data1.txt → data2.txt → ...` via `f_stat` until missing file found
  (f_stat calls also warm up the SD write path before f_open)
- `da_open_and_preallocate()`: uses `FA_CREATE_NEW` (never overwrites); retries on `FR_EXIST`
  (handles edge case where data1.txt + data3.txt exist → skips to data4.txt)
- `FR_DENIED` used for disk-full detection (this FatFS version has no `FR_NO_FREE_SPACE`)
- All `System_sprintf` replaced with `sprintf`
- `cur_sector_num` changed from `uint32_t` to `int32_t` (sentinel -1 for "no sector cached")

### Fix 2 — Ring buffer / ISR data loss (DONE)
**Original bug:** Single shared buffer + mutex; Storage task held mutex during entire
da_write()+da_commit() (50–150ms). ISR used BIOS_NO_WAIT → silently dropped 2–7 frames/cycle.
**Fix (Storage.c / Storage.h / sensors.c):**
- 16-slot ring buffer: `StorageRingSlot ring_buffer[16]`, each slot 128 bytes
- `ring_head` = `volatile uint8_t`, written by ISR only (atomic on Cortex-M3)
- `ring_tail` = `uint8_t`, written by Storage task only — no mutex needed
- `storage_buffer_mailbox` changed from BINARY to COUNTING semaphore (one count per frame)
- `Storage_push_frame(data, len)`: ISR-callable, returns 0 if ring full (graceful drop + counter)
- `load_serializer()` in sensors.c calls `Storage_push_frame()` instead of mutex+memcpy
- `dropped_frames` counter accessible via `Storage_get_dropped_frames()`

### Fix 3 — Deferred f_sync / NAND page alignment (DONE)
**Original bug:** `f_sync` called every 66-byte frame → ~32× NAND write amplification.
**Fix (DiskAccess.c):**
- `da_commit()` is now a SOFT commit by default: flushes dirty sector only, no metadata rewrite,
  no f_sync, does NOT reset `cur_sector_num` (eliminates unnecessary sector re-read)
- HARD commit (flush + metadata sector 0 rewrite + f_sync) triggered when
  `bytes_since_sync >= da_sync_threshold` (= `DA_SYNC_SECTORS × sector_size` = 16 × 512 = 8192 bytes)
- `da_flush_metadata()`: shared helper for hard commit logic
- Hard commit always runs on `da_close()` and on file rollover
- `da_sync_threshold` computed once in `da_initialize()` from actual sector size

### Fix 4 — 1MB file rollover (DONE)
**Fix (DiskAccess.c):**
- `bytes_written_to_file` counter tracks actual data bytes written per file (reset on da_load)
- Rollover triggered in `da_commit()` when `bytes_written_to_file >= DA_FILE_ROLLOVER_THRESHOLD` (1MB)
- `da_rollover()`: hard-commits current file → f_close → da_find_next_file() → da_open_and_preallocate()
- `DA_FILE_ROLLOVER_THRESHOLD = 1,048,576` bytes (~26 min at 660 bytes/sec)
- Power-fail data loss bounded to RAM buffers only (~1.5KB ring buffer + txn_buffer)

## DiskAccess Architecture (current, post-fix)
- File naming: `data1.txt`, `data2.txt`, ... (f_stat scan at POR and at rollover)
- File layout: sector 0 = metadata (`SESSION:N:write_pos:read_pos`), sectors 1..N = data
- File pre-allocated at open: `f_lseek(end) + f_write(1 byte) + f_sync`
  → FAT cluster chain committed at creation; subsequent sector writes go direct to NAND
- `da_initialize()` → f_mount, get sector geometry, malloc txn_buffer, compute da_sync_threshold
- `da_load()` → da_find_next_file() → da_open_and_preallocate() → write metadata → f_sync
- `da_write()` → byte-wise into txn_buffer; flushes sector when write_pos crosses sector boundary
- `da_commit()` → soft commit (sector flush only); hard commit every 8KB; rollover at 1MB
- `da_close()` → always hard commits before closing

## Buffer Chain (ISR → NAND)
```
DACtimerCallback ISR (~2.4 kHz)
  └─ load_serializer() → Storage_push_frame(frame_buf, 66 bytes)
       └─ ring_buffer[16 slots × 128 bytes] — max 15 frames buffered
            └─ Semaphore_post(storage_buffer_mailbox) [counting]
                 └─ Storage_taskFxn (priority 1) wakes
                      └─ da_write(ring_buffer[tail], len) → txn_buffer[512 bytes]
                           └─ da_commit() → f_write → disk_write → SPI DMA → SD NAND
```
- One serialized frame = 66 bytes (uint16_t timestamp + float[16] impedances)
- Data rate: ~660 bytes/sec at MUXFREQ=800 Hz, NUM_CYCLES_PER_OUTPUT=5
- Ring buffer holds ~1.5 sec of frames before dropping; Storage task drains in <5ms per frame

## Error Codes (DiskAccess.h)
| Code | Value | Meaning |
|------|-------|---------|
| DISK_SUCCESS | 1 | OK |
| DISK_NULL_HANDLE | -1 | SD driver handle is NULL |
| DISK_FAILED_INIT | -2 | f_mount or SD_open failed |
| DISK_FAILED_READ | -3 | Sector read error |
| DISK_FAILED_WRITE | -4 | Sector write error |
| DISK_LOCKED | -5 | Disk locked |
| DISK_NO_SPACE | -6 | SD card full (FR_DENIED from FatFS) |

`DISK_NO_SPACE` in `da_load()` → Sensors_init prints `"SD_FULL\r\n"` and continues
(device runs without SD logging). All other da_load errors → LED1 blink halt.

## RTOS Task Structure
| Task | Priority | Stack | Created in |
|------|----------|-------|------------|
| BLE Stack | 5 | — | ICall_createRemoteTasks() |
| GAPRole | 3 | — | GAPRole_createTask() |
| SimplePeripheral | 1 | 832 bytes | SimplePeripheral_createTask() |
| Storage | 1 | 448 bytes | Storage_createTask() |

- `Storage_createTask()` called from `main()` before `BIOS_start()`
- Storage task pends on `storage_init_complete` semaphore (binary) until `Sensors_init()` posts it
- `Sensors_init()` called at line 478 of `simple_peripheral.c` inside SimplePeripheral task body
- SimplePeripheral and Storage both priority 1 → cooperative at yield points (Task_sleep, Semaphore_pend)

## Timing Architecture
### Hardware Timer (DAC Timer) — `Sensors/sensors.c`
- Timer: GPTimerCC26XX (CC2640R2_LAUNCHXL_GPTIMER0A), periodic mode
- CPU clock: 48 MHz, MUXFREQ: 800 Hz, DACTIMER_CASE_COUNT: 3 states
- Load value: 48,000,000 / (800×3) = 20,000 cycles → ~0.417 ms per interrupt
- 3-state FSM: State0=ADC read, State1=serialize+push frame, State2=mux reset
- Every 5 reads per channel (NUM_CYCLES_PER_OUTPUT=5) → serializer full → Storage_push_frame()
- Started/stopped via Sensors_start_timers() / Sensors_stop_timers()

### BLE Periodic Clock — `Application/simple_peripheral.c`
- SBP_PERIODIC_EVT_PERIOD = 5000 ms (5 sec), software RTOS Clock
- Active only while BLE connected; drives housekeeping/connection param updates

### Key Constants
| Constant | Value | Purpose |
|---|---|---|
| MUXFREQ | 800 Hz | Sensor channels/sec |
| DACTIMER_CASE_COUNT | 3 | FSM states per sensor |
| Load value | 20,000 cycles | ~0.417 ms per interrupt |
| PERIOD_OF_TIME | 1.2522821 ms | Timestamp increment per FSM cycle |
| NUM_CYCLES_PER_OUTPUT | 5 | Reads averaged before serialize |
| DA_SYNC_SECTORS | 16 | Sectors between f_sync calls (8KB) |
| DA_FILE_ROLLOVER_THRESHOLD | 1,048,576 | Bytes per file before rollover (1MB) |
| RING_BUFFER_SLOTS | 16 | Ring buffer depth (max 15 frames in-flight) |
| RING_SLOT_SIZE | 128 | Bytes per ring slot |
| SBP_PERIODIC_EVT_PERIOD | 5000 ms | BLE housekeeping timer |

## Active Issue — No UART Output on PCB
**Status: Under investigation**
- Code compiles and links successfully (all 4 fixes in)
- Flashed to custom BACPAC PCB; no UART output seen on TeraTerm (tried COM3 and COM4)
- SD card confirmed empty after flash (da_load never ran, or ran silently)

**Debug code currently in sensors.c (TEMPORARY — remove before production):**
```c
// Baud rate temporarily reduced from 460800 to 115200
uartParams.baudRate = 115200;

// LED0 pulse immediately after UART_open — confirms Sensors_init is reached
GPIO_init();
GPIO_setConfig(Board_GPIO_LED0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
GPIO_write(Board_GPIO_LED0, 1);
Task_sleep(200);
GPIO_write(Board_GPIO_LED0, 0);

// UART checkpoints added: A (before peripheral init), B (after), C (SD_init done),
// D (after 500ms settle), E (da_initialize returned), F (before da_load),
// G (da_load returned), H (error handling passed), DONE (full init complete)
```

**Diagnosis plan:**
- If LED0 blinks → code reaches Sensors_init; issue is UART bridge or pin
- If LED0 does NOT blink → code never reaches Sensors_init (crash/hang before line 478 in SBP task)
- If LED blinks and output appears at 115200 → USB-to-UART bridge doesn't support 460800
- If LED blinks and no output at 115200 → UART TX pin (IOID_3) not wired to USB-UART on custom PCB
- Board file maps UART TX=IOID_3, RX=IOID_2 — verify these match custom PCB schematic

**To restore production settings after debugging:**
1. Remove LED pulse block (lines 255–260)
2. Remove UART checkpoint writes (A/B/C/D/E)
3. Change baudRate back to 460800
4. Keep F/G/H/DONE checkpoints (they were pre-existing)

## FatFS Notes
- Version: FFCONF_DEF 80386 (does NOT define `FR_NO_FREE_SPACE` — use `FR_DENIED` for disk full)
- `CTRL_SYNC` in diskio.c is a no-op (returns RES_OK immediately)
- GET_BLOCK_SIZE hardcoded to 1 in diskio.c (true AU size not queryable via TI SDK)
- f_sync forces FAT table + directory entry updates to NAND (needed for metadata consistency)
- Preallocation at file creation means cluster chain is in FAT before any data write
