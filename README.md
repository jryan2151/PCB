# BACPAC PCB Code

I refactored and rewrote a lot of code to get the sensor code from before to run without issues in a Bluetooth project. Some files were renamed. Hopefully this readme will help make it possible to navigate the files.

## Sensors

All of the files that deals with reading input in from the sensors are now stored in the Sensor folder. `main_iter3.c` was renamed to `sensor.c`. Future changes to the sensor code should be written to this file.

I also created a `sensor.h` file, which holds the definition for the `Sensor_createTask` function and is called from the `main.c` file in the Include folder.

The Sensors folder also holds the DiskAccess files which make it easy to read from and write to the SD card.

## PROFILES

In the profiles folder you can find the `bacpac_service.c` and `bacpac_service.h` files which is where our bluetooth service is defined.