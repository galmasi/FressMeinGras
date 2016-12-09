

/* this prevents compile errors - an arduino bug */
char foo;

#include <SoftwareSerial.h>
#include <Sabertooth.h>


/* *************************************************************** */
/* GLOBAL PIN ASSIGNMENTS for all functional units                 */
/* This ensures consistency - overlaps will be immediately visible */
/* *************************************************************** */

#define BTSERIAL_TX 12  
#define BTSERIAL_RX 13

#define RADAR_PINGPIN 10
#define RADAR_PONGPIN 11

// we are overloading the radar pins. NEEDS FIXED
#define BUMPER_PIN 10

// these overlap with the L298
#define LEDRED_PIN 4
#define LEDGRN_PIN 5
#define LEDBLU_PIN 6

#define LEGOMOTOR_PWMAPIN 3
#define LEGOMOTOR_DIRAPIN 2
#define LEGOMOTOR_PWMBPIN 9
#define LEGOMOTOR_DIRBPIN 8

#define L298N_AF (4)   // forward
#define L298N_AB (7)   // backward
#define L298N_AE (6)   // PWM
#define L298N_BF (2)   // forward
#define L298N_BB (3)   // backward
#define L298N_BE (5)   // PWM

/* other PINS used, please keep consistent 
 * L298N: 2,3,4,5,6,7
 */

/* ************************************************************ */
/* all motorvalues are byte and in the range of -127 .. +127    */
/* for indicating backward to forward or left to right (turn)   */
/* ************************************************************ */

typedef signed char motorval_t;  

/* *********************************************** */
/* 1A) Logging  (one of noop or serial)            */
/* 1B) LED TBD                                     */
/* *********************************************** */

//#include "NoopLogger.h"
#include "SerialLogger.h"
#include "LedLogger.h"

/* *********************************************** */
/*  2)  drivers for motors and sensors             */
/* ----------------------------------------------- */
/* 2A) physical motor control (lego, L298N or ST)  */
/* 2B) radar                                       */ 
/* *********************************************** */

//#include "MotorControl_L298N.h"
//#include "MotorControl_Sabertooth.h"
#include "MotorControl_Lego.h"
#include "Radar.h"

/* *********************************************** */
/* 3) Command Executor                             */
/* Mediates all interaction with physical devices, */
/* keeps relevant state and logs actions.          */
/* *********************************************** */

#include "CommandExecutor.h"

/* *********************************************** */
/* 4) Interpreters only talk to the executor.      */
/* Please never reach directly to the device.      */
/* ----------------------------------------------- */
/* 4A) Bluetooth Interpreter                       */
/* 4B) Raspi interpreter TBD                       */
/* 4C) bumper pin driver                           */ 
/* *********************************************** */

#include "BluetoothInterpreter.h"
//
#include "Bumper.h"

void setup()
{
  Logger_init();
  LedLogger_init();
  MotorControl_init();
  Radar_init();
  CommandExecutor_init();
  BluetoothInterpreter_init();
  Logger_log("FMG ready", 0);
}

void loop()
{
  BluetoothInterpreter_loop();
  Radar_loop();
  Bumper_loop();
  CommandExecutor_loop();
}




