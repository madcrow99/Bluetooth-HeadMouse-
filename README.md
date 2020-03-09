# Bluetooth-HeadMouse-
Control mouse over Bluetooth with head movement. 

This project uses a RN-42 Bluetooth module (version 6.03 or later) to send HID (mouse pointer and button commands) reports to computer or phone. Mouse movements are related to the movement of an MPU6050 (gyroscope) placed on the side of the users head (e.g. respirator mask, headband, hat, eye glasses earpiece...). This has been tested on Android, Windows and Ubuntu.

Connect Arduino MEGA, RN-42 (use one module for each device) , 4 buttons and the MPU6050 as outlined in HeadMouse.fzz.

Run HID_Config.ino, to configure the rn-42. This sets the RN-42 to the combo(mouse and keyboard ) profile.

Pair RN-42 modules with devices (phone and computer). This step is simply pairing a Bluetooth device from the phone or computer.

Upload headMouse.ino

If the pointer moves while the MPU 6050 is stationary, run calibrate_gyro.ino with MPU6050 stationary. Update values of averageX and averageZ in headMouse.ino.

Included are step and stl files for power wheelchair button mounts (left and right, hand and head). 

![Headrest](https://user-images.githubusercontent.com/60524115/74993637-d3e9ae00-5408-11ea-90e8-a1750409c90b.jpg)
![Powerchair](https://user-images.githubusercontent.com/60524115/74993647-db10bc00-5408-11ea-8423-e0b95e2d7ee9.jpg)
