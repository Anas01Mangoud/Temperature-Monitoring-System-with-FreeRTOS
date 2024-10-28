# Temperature-Monitoring-System-with-FreeRTOS
Created a system using FreeRTOS to detect room temperature and display it on an LCD, using semaphores  for task



Project Overview
The Temperature Monitoring System is designed to detect and display room temperature using an LCD. It utilizes FreeRTOS for real-time task management and synchronization. The system effectively demonstrates how to manage concurrent tasks in an embedded environment.

Features
Real-time temperature monitoring
LCD display for temperature readings
Utilization of FreeRTOS for task management
Semaphore-based task synchronization for efficient resource sharing

Components Used
Microcontroller:STM32, ATmega32
RTOS: FreeRTOS
Temperature Sensor: LM35
Display: 16x2 LCD

Getting Started

Running the System
Compile the project.
Upload the code to the microcontroller.
Connect the temperature sensor and LCD as per the schematic.
Power on the system, and the temperature will be displayed on the LCD.

Code Structure
main.c: Main application file that initializes the system and starts the FreeRTOS scheduler.
temperature_task.c: Task for reading temperature data from the sensor.
display_task.c: Task for updating the LCD display with the temperature reading.
semphr.h: Header file for semaphore definitions and declarations.

Task Synchronization
The system uses semaphores for task synchronization between the temperature reading task and the display update task. This ensures that the temperature data is accurately read and displayed without conflicts.
