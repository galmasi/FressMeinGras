/* *********************************************** */
/*      GLOBAL PIN ASSIGNMENTS                     */
/* *********************************************** */

#define MOTORCONTROL_PWMAPIN 3
#define MOTORCONTROL_DIRAPIN 2
#define MOTORCONTROL_PWMBPIN 9
#define MOTORCONTROL_DIRBPIN 8

#define BTSERIAL_TX 12
#define BTSERIAL_RX 13

#define RADAR_PING 10
#define RADAR_PONG 11

/* *********************************************** */
/*     subsystem definitions                       */
/* *********************************************** */

#include "MotorControl.h"
#include "Radar.h"
#include "CommandInterpreter.h"
#include "CommandExecutor.h"

void setup() {
    Serial.begin(9600);    
    Serial.println("FressMeinGrass starting");
    MotorControl_init();
    Radar_init();
    CommandInterpreter_init();
    CommandExecutor_init();
}

void loop() {
  Radar_loop();
  MotorControl_loop();
  if (CommandInterpreter_loop()) CommandExecutor();
}



