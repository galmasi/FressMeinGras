#include <SoftwareSerial.h>
#include "MotorControl.h"
#include "CommandInterpreter.h"
#include "CommandExecutor.h"



void setup() {
    Serial.begin(9600);    
    Serial.println("FressMeinGrass starting");
    MotorControl_init();
    CommandInterpreter_init();
}

void loop() {
  MotorControl_loop();
  if (CommandInterpreter_loop()) CommandExecutor();
}



