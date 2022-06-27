#ifndef SENSORS_H
#define SENSORS_H

#include <ti/sysbios/knl/Semaphore.h>

//void Sensors_createTask(void);
extern Semaphore_Handle bacpac_channel_mutex;
extern Semaphore_Handle bacpac_channel_mailbox;
extern char streaming_buffer[];
extern uint8_t streaming_buffer_length;

void Sensors_init();
void Sensors_start_timers();
void Sensors_stop_timers();

void DA_get_status(int status_code, char* message);

void print();


#endif
