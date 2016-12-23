/* *************************************************************** */
/* pre-selected configurations. pick one!                          */
/* *************************************************************** */

#define LEGOPANZER 1
// #define TOYROBOT 1
// #define MODEL_T 1
//#define KUBELWAGEN 1


/* *************************************************************** */
/* These defines determine what features each configuration uses.  */
/* *************************************************************** */
/* HAVE_BUMPERS - define it if you have bumper hardware.           */
/* MOTOR_LEGO, MOTOR_SABERTOOTH, MOTOR_L298 - define one of these! */
/* HAVE_SERIALPORT - the serial port is free for logging purposes. */
/* HAVE_HEARTBEAT - set it if your bluetooth commander is sending it. */
/* *************************************************************** */

#if defined(LEGOPANZER)
  // #define HAVE_BUMPERS -- no bumpers
  #define HAVE_HEARTBEAT 1
  #define HAVE_SERIALPORT 1
  #define MOTOR_LEGO 1
  //#define HAVE_COMPUTER 1

#elif defined(TOYROBOT)
  // #define HAVE_BUMPERS  -- no bumpers
  #define HAVE_HEARTBEAT 1
  #define HAVE_SERIALPORT 1
  #define MOTOR_L298 1

#elif defined(MODEL_T)
  #define HAVE_BUMPERS 1
  #define BUMPER_NPN 1
  #define HAVE_HEARTBEAT 1
  // #define HAVE_SERIALPORT -- no serial port, since using sabertooth
  #define MOTOR_SABERTOOTH 1

#elif defined(KUBELWAGEN)
  #define HAVE_BUMPERS 1
  #define BUMPER_NPN 1
  #define HAVE_HEARTBEAT 1
  // #define HAVE_SERIALPORT -- no serial port, since using sabertooth
  #define MOTOR_SABERTOOTH 1
  #define HAVE_COMPUTER 1

#else
  #error "You have to choose one of (lego,toy,model_t,jeep). See top of Configuration.h"
#endif

/* *************************************************************** */
/*        conistency checks                                        */
/* *************************************************************** */

#if (defined(HAVE_SERIALPORT) && defined(MOTOR_SABERTOOTH))
  #error "Cannot have Sabertooth and serial logging operate over the same line"
#endif


/* *************************************************************** */
/* GLOBAL PIN ASSIGNMENTS for all functional units                 */
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
