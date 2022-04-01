#ifndef SENSORS_H
#define SENSORS_H

//void Sensors_createTask(void);

void Sensors_init();
void Sensors_start_timers();
void Sensors_stop_timers();

void Sensors_write_test();
void Sensors_read_test();
void Sensors_size_test();
void Sensors_pos_test();
void Sensors_clear_test();
void Sensors_load_test();
void Sensors_close_test();
void Sensors_timer_test();
void DA_get_status(int status_code, char* message);

void hello_world();
void print();


#endif
