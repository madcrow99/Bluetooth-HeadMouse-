//run to calculate drift offset
//if mouse pointer is not stationary at rest, the values may need to be updated
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>


MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int averageCount =0;
double averageX = 0;
double averageY = 0;
double averageZ = 0;

void setup() {
 

}

void loop() {
  if (averageCount < 100) {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    averageX = averageX + gx;
    averageY = averageY + gy;
    averageZ = averageZ + gz;
    averageCount ++;
    delay(20);
  }
  else if (averageCount == 100) {
    averageX = averageX / 100;
    averageY = averageY / 100;
    averageZ = averageZ / 100;
    averageCount ++;
    Serial.print("averageX: ");Serial.println(averageX);
    Serial.print("averageZ: ");Serial.println(averageZ);
  }

}
