/* this prevents compile errors - an arduino bug */
char foo;

#include <SoftwareSerial.h>

/* *********************************************** */
/*      GLOBAL PIN ASSIGNMENTS                     */
/* *********************************************** */

#define BTSERIAL_TX 10   //12
#define BTSERIAL_RX 11   //13

#if 0
#define RADAR_PINGPIN 10
#define RADAR_PONGPIN 11
#endif

/* other PINS used, please keep consistent 
 * Lego:  2,3,8,9
 * L298N: 2,3,4,5,6,7
 */

/* *********************************************** */
/*     subsystem definitions                       */
/* *********************************************** */

/* all motorvalues are byte and in the range of -127 .. +127 
 * for indicating backward to forward or left to right (turn)
 */
 
typedef signed char motorval_t;  

#include "MotorControl_L298N.h"
//#include "MotorControl_Lego.h"

#include "CommandInterpreter.h"
//#include "Radar.h"
long Radar_ping() { return 0; }

#include "CommandExecutor.h"

void setup() {
    Serial.begin(9600);    
    Serial.println("FressMeinGrass starting");
    MotorControl_init();
//    Radar_init();
    CommandInterpreter_init();
    CommandExecutor_init();
}

void loop() {
//  Radar_loop();
  if (CommandInterpreter_loop())
      CommandExecutor_exec();
}



