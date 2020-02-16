//configure rn42
//run this program before pairing with computer or phone

void setup() {

  Serial1.begin(115200);
  //Serial2.begin(115200); //use Serial2 and 3 for additional bluetooth modules(e.g. phone and 2 computers)
  //Serial3.begin(115200);

  delay(1000);
  Serial1.print("$$$");delay(1000);//enter command mode
  Serial1.print("SM,6\r\n");delay(500);//set auto-connect to last paired host
  Serial1.print("S~,6\r\n");delay(500);//set HID profile
  Serial1.print("SH,0230\r\n");delay(500);//set as combomouse
  Serial1.print("R,1\r\n");delay(500);//set as combomouse
  
}

void loop() {}
