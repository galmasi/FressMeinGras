#include <SoftwareSerial.h>
#include "MotorControl.h"

SoftwareSerial btSerial(13,12);


void setup() {
    
    Serial.begin(9600);
    
    btSerial.begin(9600);
    Serial.println("Hello1");
    MotorControl_Init();
}



void loop() {
  CommandInterpreter_loop();
  
   if (btSerial.available()) {
       char c = btSerial.read();
       if (actionChar (c)) {
          if (_cmd == 'G') {
            Serial.println("GO");
            _stopped = 0;
          }
          else if (_cmd == 'S') {
            Serial.println("STOP");
            _stopped = 1;
          }
          else if (_cmd == 'L') {
            Serial.print ("LEFT ");
            Serial.println(_n);
            MotorControl_SetLeft (abs(_n-256), (_n > 256));
          }
          else if (_cmd == 'R') {
            Serial.print ("RIGHT ");
            Serial.println(_n);
            MotorControl_SetRight (abs(_n-256), (_n > 256));
          }
       }
   }
   if (Serial.available()) {
       char c = Serial.read();
       btSerial.write(c);
       Serial.write(c);
   }
   
   MotorControl_loop();
}



