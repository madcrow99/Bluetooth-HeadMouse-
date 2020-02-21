#include <Bounce2.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>


MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;


int averageCount = 0;
double averageX = -20;//from calibrate_gyro.ino
double averageY = 0;
double averageZ = 52;//from calibrate_gyro.ino

#define NUM_BUTTONS 4
int BUTTON_PINS[NUM_BUTTONS] = { 2, 3, 4, 5};

Bounce * buttons = new Bounce[NUM_BUTTONS];

int buttonState = 0;
int device = 2;

bool lastButton1 = false;
bool lastButton2 = false;

long buttonTimer = 0;
long phoneTimer = 0;

long longPressTime = 500;
long phonePressTime = 1000;

boolean buttonActive = false;
boolean longPressActive = false;
boolean longPress2Active = false;

boolean phoneActive = false;
boolean phoneActiveLong = false;
boolean button0Active = false;
boolean button2Active = false;
boolean RButton2 = false;


signed int dx = -127;
signed int dy = 40;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);

  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    while (1);
  }
  
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].attach( BUTTON_PINS[i] , INPUT_PULLUP  );       //setup the bounce instance for the current button
    buttons[i].interval(30);              // interval in ms
  }


}

void loop() {

  for (int i = 0; i < NUM_BUTTONS; i++)  {
    // Update the Bounce instance :
    buttons[i].update();
  }

  //Computer one computer two or phone
  //long press button 4 to switch between devices
  if ( buttons[2].read() == HIGH && buttons[3].read() == LOW &&
       buttons[0].read() == HIGH && buttons[1].read() == HIGH ) {

    if (phoneActive == false) {

      phoneActive = true;
      phoneTimer = millis();

    }

    if ((millis() - phoneTimer > phonePressTime) ) {
      phoneActiveLong = true;

    }
  }

  if ( buttons[2].read() == HIGH && buttons[3].read() == HIGH &&
       buttons[0].read() == HIGH && buttons[1].read() == HIGH &&  phoneActiveLong == true) {
        
    phoneActive = false;
    phoneActiveLong = false;
    device ++;
    if (device > 3) device = 1;
    
  }

  if ( buttons[3].read() == HIGH ) {
    if (device == 1) comp1();
    if (device == 2) phone();
    if (device == 3) comp2();
  }

}

//using two buttons (0,1,2)
//0 is use to jump the pointer horzontally with a short press (alternating direction)
//0 is use to jump the pointer vertically with a long press (alternating direction)
//It is used to limit the amount of head movement required

//1 is the left mouse button

//0 and 1 pressed together is the right mouse button

//2 is scroll. short press down. long press up.

void comp1() {
 
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  vx = -((gx - averageX) / 200);//change value as needed for mouse sensitivity
  vy = ((gz - averageZ) / 200);//change value as needed for mouse sensitivity


 mouseMove1(vx, vy, buttonState,0);

  if ( buttons[1].read() == LOW && lastButton1 == false) {

    lastButton1 = true;
    buttonState = 1;//left mouse down click
  }

  if ( buttons[1].read() == HIGH && lastButton1 == true) {

    lastButton1 = false;
    buttonState = 0;//buttons released
  }


  if ( buttons[0].read() == LOW &&  buttons[1].read() == LOW &&  RButton2 == false) {
    RButton2 = true;
    buttonState = 2;//right mouse down click
    button0Active = false;
  }


  if ( buttons[0].read() == HIGH &&  buttons[1].read() == HIGH && RButton2 == true) {

    RButton2 = false;
    buttonState = 0;
  }
  
  if ( buttons[0].read() == LOW &&  buttons[1].read() == HIGH && RButton2 == false) {


    if (button0Active == false) {

      button0Active = true;
      buttonTimer = millis();

    }

    if ((millis() - buttonTimer > longPressTime)) {


      mouseMove1(0, dy, 0, 0);
      longPressActive = true;
    }
  }
  else  if (buttons[0].read() == HIGH ) {

    if (button0Active == true) {

      if (longPressActive == true) {

        longPressActive = false;
        dy = dy * -1;

      } else {
        for (int i = 0; i < 5; i++)  {
          mouseMove1(dx, 0, 0, 0);
        }

      }

      dx = dx * -1;

      button0Active = false;
    }
  }


  if ( buttons[2].read() == LOW) {


    if (button2Active == false) {

      button2Active = true;
      buttonTimer = millis();

    }

    if ((millis() - buttonTimer > longPressTime) ) {
      mouseMove1(0, 0, buttonState, 1);

      delay(85);
      longPress2Active = true;
    }

  }
  else  if (buttons[2].read() == HIGH ) {

    if (button2Active == true) {

      if (longPress2Active == true) {

        longPress2Active = false;

      } else {

        mouseMove1(0, 0, buttonState, -5);
        delay(85);

      }

      button2Active = false;

    }

  }

  

}

//using three buttons (0,1,2)
//0 is use to jump the pointer horzontally with a short press (alternating direction)
//0 is use to jump the pointer vertically with a long press (alternating direction)
//It is used to limit the amount of head movement required

//1 is the left mouse button (similar to a tap or swipe)

//2 is to scroll. short press down. long press up. Certain apps do not respond to the left click swipe (e.g. google chrome)
void phone() {


  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  vx = -((gx - averageX) / 200);//change value as needed for mouse sensitivity
  vy = ((gz - averageZ) / 200);//change value as needed for mouse sensitivity


  mouseMove2(vx, vy, buttonState, 0);

  if ( buttons[1].read() == LOW && lastButton1 == false) {
  
    lastButton1 = true;
    buttonState = 1;
  }

  if (  buttons[1].read() == HIGH && lastButton1 == true) {
   
    lastButton1 = false;
    buttonState = 0;
  }


  if ( buttons[0].read() == LOW ) {


    if (button0Active == false) {

      button0Active = true;
      buttonTimer = millis();

    }
    if ((millis() - buttonTimer > longPressTime)) {

      mouseMove2(0, dy, buttonState, 0);

      longPressActive = true;
    }
  }
  else  if (buttons[0].read() == HIGH ) {

    if (button0Active == true) {

      if (longPressActive == true) {

        longPressActive = false;
        dy = dy * -1;

      } else {


        for (int i = 0; i < 5; i++)  {
          mouseMove2(dx, 0, buttonState, 0);
        }

      }

      dx = dx * -1;

      button0Active = false;
    }


  }

  if ( buttons[2].read() == LOW) {


    if (button2Active == false) {

      button2Active = true;
      buttonTimer = millis();

    }

    if ((millis() - buttonTimer > longPressTime) ) {
      mouseMove2(0, 0, buttonState, 1);

      delay(85);
      longPress2Active = true;
    }

  }
  else  if (buttons[2].read() == HIGH ) {

    if (button2Active == true) {

      if (longPress2Active == true) {

        longPress2Active = false;

      } else {

        mouseMove2(0, 0, buttonState, -5);
        delay(85);

      }

      button2Active = false;

    }

  }

}



//using two buttons (0,1,2)
//0 is use to jump the pointer horzontally with a short press (alternating direction)
//0 is use to jump the pointer vertically with a long press (alternating direction)
//It is used to limit the amount of head movement required

//1 is the left mouse button

//0 and 1 pressed together is the right mouse button

//2 is scroll. short press down. long press up.

void comp2() {
 
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  vx = -((gx - averageX) / 125);//change value as needed for mouse sensitivity
  vy = ((gz - averageZ) / 125);//change value as needed for mouse sensitivity


 mouseMove3(vx, vy, buttonState,0);

  if ( buttons[1].read() == LOW && lastButton1 == false) {

    lastButton1 = true;
    buttonState = 1;//left mouse down click
  }

  if ( buttons[1].read() == HIGH && lastButton1 == true) {
    //if (  digitalRead(BUTTON_PINS[1]) == HIGH && lastButton1 == true) {

    lastButton1 = false;
    buttonState = 0;//buttons released
  }


  if ( buttons[0].read() == LOW &&  buttons[1].read() == LOW &&  RButton2 == false) {
    RButton2 = true;
    buttonState = 2;//right mouse down click
    button0Active = false;
  }


  if ( buttons[0].read() == HIGH &&  buttons[1].read() == HIGH && RButton2 == true) {

    RButton2 = false;
    buttonState = 0;
  }
  
  if ( buttons[0].read() == LOW &&  buttons[1].read() == HIGH && RButton2 == false) {


    if (button0Active == false) {

      button0Active = true;
      buttonTimer = millis();

    }

    if ((millis() - buttonTimer > longPressTime)) {


      mouseMove3(0, dy, 0, 0);
      longPressActive = true;
    }
  }
  else  if (buttons[0].read() == HIGH ) {

    if (button0Active == true) {

      if (longPressActive == true) {

        longPressActive = false;
        dy = dy * -1;

      } else {
        for (int i = 0; i < 5; i++)  {
          mouseMove3(dx, 0, 0, 0);
        }

      }

      dx = dx * -1;

      button0Active = false;
    }
  }


  if ( buttons[2].read() == LOW) {


    if (button2Active == false) {

      button2Active = true;
      buttonTimer = millis();

    }

    if ((millis() - buttonTimer > longPressTime) ) {
      mouseMove3(0, 0, buttonState, 1);

      delay(85);
      longPress2Active = true;
    }

  }
  else  if (buttons[2].read() == HIGH ) {

    if (button2Active == true) {

      if (longPress2Active == true) {

        longPress2Active = false;

      } else {

        mouseMove3(0, 0, buttonState, -5);
        delay(85);

      }

      button2Active = false;

    }

  }

  

}




void mouseMove3(int dx, int dy, int bttn, int scroll) {
  Serial3.write((byte)0xFD); //Start HID Report
  Serial3.write((byte)0x5); //Length byte
  Serial3.write((byte)0x2); //Descriptor byte
  Serial3.write(bttn);
  Serial3.write(dx);
  Serial3.write(dy);
  Serial3.write(scroll);

  delay(15);
}

void mouseMove1(int dx, int dy, int bttn, int scroll) {
  Serial1.write((byte)0xFD); //Start HID Report
  Serial1.write((byte)0x5); //Length byte
  Serial1.write((byte)0x2); //Descriptor byte
  Serial1.write(bttn);
  Serial1.write(dx);
  Serial1.write(dy);
  Serial1.write(scroll);

  delay(15);
}

void mouseMove2(int dx, int dy, int bttn, int scroll) {
  Serial2.write((byte)0xFD); //Start HID Report
  Serial2.write((byte)0x5); //Length byte
  Serial2.write((byte)0x2); //Descriptor byte
  Serial2.write(bttn);
  Serial2.write(dx);
  Serial2.write(dy);
  Serial2.write(scroll);

  delay(15);
}
