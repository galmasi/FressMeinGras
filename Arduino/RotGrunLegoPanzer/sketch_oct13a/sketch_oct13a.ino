#include <SoftwareSerial.h>
#include "MotorControl.h"

SoftwareSerial btSerial(13,12);


void setup() {
    
    Serial.begin(9600);
    
    btSerial.begin(9600);
    Serial.println("Hello1");
    MotorControl_Init();
}

int _mode=0;
char _cmd;
int _n;

int actionChar (char c) {
  //Serial.print("Got char: ");
  //Serial.write(c);
  //Serial.println("");
  if (_mode == 0) {
    // waiting for a command
    if (c == 'L' || c == 'R' ) {
      _mode = 1;
      _n = 0;
      _cmd = c;
      return 0;
    }
    else if (c == 'S' || c == 'G') {
      _mode = 0;
      _n = 0;
      _cmd = c;
      return 1;
    }
    else
      return 0;
  }
  else if (_mode == 1) {
    // waiting for a number or return
    if (c == '\n') {
       _mode = 0;
       return 1;
    }
    else if ('0' <= c && c <= '9') {
       _n = _n * 10 + ((int)c-(int)'0');
       _mode = 1;
       return 0;
    }
    else {
      return 0;
    }
  }
}



void loop() {
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
}



