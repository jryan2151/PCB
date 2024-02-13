#ifndef SENSORS_H
#define SENSORS_H

void Sensors_init();
void Sensors_start_timers();
void Sensors_stop_timers();
void Sensors_serializer_output();
void Sensors_serializer_EMGIMP_EMG_output();
void Sensors_serializer_EMGIMP_IMP_output();
void increment_EMG_sensor();
void set_impedance();
void calibration_output();
void adc_read();
void check_cycle_count();
void adjust_pot_V_One_Three();
void adjust_pot_V_One_Two();
void load_serializer(uint16_t read_value);

void DA_get_status(int status_code, char* message);

void print();

#endif
