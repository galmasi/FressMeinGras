#include <SoftwareSerial.h>

SoftwareSerial mySerial(13,12);

int _pwmAPin = 3;
int _dirAPin = 2;
int _pwmBPin = 9;
int _dirBPin = 8;

int _leftPower = 0;
int _leftDir = 1;
int _rightPower = 0;
int _rightDir = 1;

int _stopped = 1;

void setup() {
    pinMode(_pwmAPin, OUTPUT);
    pinMode(_dirAPin, OUTPUT);
    pinMode(_pwmBPin, OUTPUT);
    pinMode(_dirBPin, OUTPUT);
    
    Serial.begin(9600);
    
    mySerial.begin(9600);
    Serial.println("Hello1");
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
   if (mySerial.available()) {
       char c = mySerial.read();
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
            _leftPower = abs(_n-256);
            _leftDir = (_n > 256);
          }
          else if (_cmd == 'R') {
            Serial.print ("RIGHT ");
            Serial.println(_n);
            _rightPower = abs(_n-256);
            _rightDir = (_n > 256);
          }
       }
   }
   if (Serial.available()) {
       char c = Serial.read();
       mySerial.write(c);
       Serial.write(c);
   }
   if (_stopped) {
     analogWrite(_pwmAPin, 0);
     analogWrite(_pwmBPin, 0);
   }
   else
   {
     analogWrite(_pwmAPin, _leftPower);
     digitalWrite(_dirAPin, _leftDir);

     analogWrite(_pwmBPin, _rightPower);
     digitalWrite(_dirBPin, _rightDir);
   }
}
