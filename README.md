# Bluetooth-HeadMouse-
Control mouse over Bluetooth with head movement. 

This project uses a RN-42 Bluetooth module (version 6.03 or later) to send HID (mouse pointer and button commands) reports to computer or phone. Mouse movements are related to the movement of an MPU6050 (gyroscope) placed on the side of the users head (e.g. respirator mask, headband, hat. eye glasses earpiece...). This has been tested on Android (Apple won't work ), Windows and Ubuntu.

Connect Arduino MEGA, RN-42 (use one module for each device) , 4 buttons and the MPU6050 as outlined in 
