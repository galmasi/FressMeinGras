

/* this prevents compile errors - an arduino bug */
char foo;

#include <SoftwareSerial.h>
#include <Sabertooth.h>

/* *************************************************************** */
/* These defines determine what features we use                    */
/* *************************************************************** */
/* HAVE_BUMPERS - define it if you have bumper hardware.           */
/* MOTOR_LEGO, MOTOR_SABERTOOTH, MOTOR_L298 - define one of these! */
/* HAVE_SERIALPORT - the serial port is free for logging purposes. */
/* HAVE_HEARTBEAT - set it if your bluetooth commander is sending it. */

#define HAVE_BUMPERS 1

// #define MOTOR_LEGO 1
#define MOTOR_SABERTOOTH 1
// #define MOTOR_L298 1

//#define HAVE_SERIALPORT 1

#define HAVE_HEARTBEAT 1

/* *************************************************************** */
/* GLOBAL PIN ASSIGNMENTS for all functional units                 */
/* This ensures consistency - overlaps will be immediately visible */
/* *************************************************************** */

#define BTSERIAL_TX 12  
#define BTSERIAL_RX 13

#define RADAR_PINGPIN 10
#define RADAR_PONGPIN 11

#define BUMPER_PIN_0 A0
#define BUMPER_PIN_1 A1

// these overlap with the L298
#define LEDRED_PIN 6
#define LEDGRN_PIN 5
#define LEDBLU_PIN 4

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
/* 1B) Led status announcer                        */
/* *********************************************** */

#ifdef HAVE_SERIALPORT
#include "SerialLogger.h"
#else
#include "NoopLogger.h"
#endif

#include "LedLogger.h"

/* *********************************************** */
/*  2)  drivers for motors and sensors             */
/* ----------------------------------------------- */
/* 2A) physical motor control (lego, L298N or ST)  */
/* 2B) radar                                       */ 
/* *********************************************** */

#ifdef MOTOR_L298
  #include "MotorControl_L298N.h"
#else
  #ifdef MOTOR_SABERTOOTH
    #include "MotorControl_Sabertooth.h"
  #else
    #ifdef MOTOR_LEGO
       #include "MotorControl_Lego.h"
    #endif
  #endif
#endif

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

#ifdef HAVE_BUMPERS
  #include "Bumper.h"
#endif

void setup()
{
  Logger_init();
  LedLogger_init();

#ifdef HAVE_BUMPERS
  Bumper_init();
#endif

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
#ifdef HAVE_BUMPERS
  Bumper_loop();
#endif
  CommandExecutor_loop();
}




