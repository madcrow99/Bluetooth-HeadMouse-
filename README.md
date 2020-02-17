# Bluetooth-HeadMouse-
Control mouse over Bluetooth with head movement. 

This project uses a RN-42 Bluetooth module (version 6.03 or later) to send HID (mouse pointer and button commands) reports to computer or phone. Mouse movements are related to the movement of an MPU6050 (gyroscope) placed on the side of the users head (e.g. respirator mask, headband, hat, eye glasses earpiece...). This has been tested on Android (Apple phones won't work), Windows and Ubuntu.

Connect Arduino MEGA, RN-42 (use one module for each device) , 4 buttons and the MPU6050 as outlined in HeadMouse.fzz.

Run HID_Config.ino, to configure the rn-42. This sets the RN-42 to the combo(mouse and keyboard ) profile.

Upload headMouse.ino

If the pointer moves while the MPU 6050 is stationary, run calibrate_gyro.ino with MPU6050 stationary. Update values of averageX and averageZ in headMouse.ino.

Included are step and stl files for power wheelchair button mounts (left and right hand and head)
