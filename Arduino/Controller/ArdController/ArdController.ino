

/* this prevents compile errors - an arduino bug */
char foo;

#include <SoftwareSerial.h>

/* *********************************************** */
/*      GLOBAL PIN ASSIGNMENTS                     */
/* *********************************************** */

#define BTSERIAL_TX 12  
#define BTSERIAL_RX 13  
#define RADAR_PINGPIN 10
#define RADAR_PONGPIN 11


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

#include "CommandInterpreter.h"

//#include "MotorControl_L298N.h"
#include <Sabertooth.h>
#include "MotorControl_Sabertooth.h"
//#include "MotorControl_Lego.h"

//#include "Radar.h"
#include "CommandExecutor.h"

void setup()
{
  Serial.begin(9600);    
//  Serial.println("FressMeinGrass starting");
  MotorControl_init();
//  Radar_init();
  CommandInterpreter_init();
//  Serial.println("FressMeinGrass Ready");
  CommandExecutor_init();
}

void loop()
{
//  Radar_loop();

  
  if (CommandInterpreter_loop())
    CommandExecutor_exec();
//  else 
//    CheckHeartBeat();
}




