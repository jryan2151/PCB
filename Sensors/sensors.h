#ifndef SENSORS_H
#define SENSORS_H

//void Sensors_createTask(void);
void Sensors_init();
void Sensors_start_timers();
void Sensors_stop_timers();

void DA_get_status(int status_code, char* message);

void print();

#endif
