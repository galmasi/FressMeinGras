#include <SoftwareSerial.h>
#include "MotorControl.h"

SoftwareSerial btSerial(13,12);


void setup() {
    Serial.begin(9600);    
    Serial.println("FressMeinGrass starting");
    MotorControl_init();
    CommandInterpreter_init();
}



void loop() {
  MotorControl_loop();
  if (CommandInterpreter_loop()) {
    char c = CommandInterpreter_command();
    switch (c) {
      case 'G': {
        Serial.println("GO");
        MotorControl_start();
        break;
      }
      case 'S': {
        Serial.println("STOP");
        MotorControl_stop();
        break;
      }
      case 'L': {
        int n = CommandInterpreter_argument();
        int p = abs(_n-256);
        int d = (n>256);
        Serial.print ("LEFT ");
        Serial.print(p);
        Serial.println (d?" FWD":"BACK");
        MotorControl_setLeft (p, d);
        break;
      case 'R': {
        int n = CommandInterpreter_argument();
        int p = abs(_n-256);
        int d = (n>256);
        Serial.print ("RIGHT ");
        Serial.print(p);
        Serial.println (d?" FWD":"BACK");
        MotorControl_setRight (p, d);
        break;
     }
   }   
}



