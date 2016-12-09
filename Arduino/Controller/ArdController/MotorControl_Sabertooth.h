#include <Sabertooth.h>

/************************************************************
 * This modules controls the Sabertooth 2x32 controller
 * The Sabertooth is to be setup in Serial Mode:
 * DIPs:  1=off, 2=off, 3..6=on (assume power supply)
 *
 * ST (Sabertooth 2x32) can be controlled in serial mode
 * in two different ways. 
 * (a) provide to the power to the individual motors directly
 * (b) control the velocity and turn
 *
 * To select (a) #define SABERTOOTH_CTRL_DUAL_MODE
 * 
 * at this point (b) is not yet working !!!!!!!!!!!!!!
 * ************************************************************/

#define SABERTOOTH_CTRL_MODE_DUAL   /* turns on dual mode (a)  */

Sabertooth ST(128);    // connect the S1 line to the TX of UNO

/* ******************* */
/* motor control state */
/* ******************* */

bool mc_stopped = true;
motorval_t mc_turn    = 0;

/* *********************************************** */
/* set pin modes, and make sure motor will be stopped */
/* *********************************************** */


inline void MotorControl_init(void) 
{
  mc_stopped = true;

  SabertoothTXPinSerial.begin(9600);

  ST.autobaud();

  // See the Sabertooth 2x60 documentation for information on ramping values.
  // There are three ranges: 1-10 (Fast), 11-20 (Slow), and 21-80 (Intermediate).
  // The ramping value 14 used here sets a ramp time of 4 seconds for full
  // forward-to-full reverse.
  //
  // 0 turns off ramping. Turning off ramping requires a power cycle.
  //
  // WARNING: The Sabertooth remembers this command between restarts AND in all modes.
  // To change your Sabertooth back to its default, call ST.setRamping(0)

  ST.setRamping(30);  // used to be 14
}

/* *********************************************** */
/* Like every motor this has a non-linear behavior */
/* with respect to voltage supplied.               */
/* We provide a curve here to get smoother scale   */
/* *********************************************** */

#define scaleM(v) (v)  // later with gear

/* *********************************************** */
/* if motor is stopped, write zeroes.              */
/* else write state values.                        */
/* *********************************************** */

//char mc_gear   = 10;

#define ST_MOTOR_LEFT  1
#define ST_MOTOR_RIGHT 2

inline void MotorControl_start(void)
{
  mc_stopped = false;
  mc_turn = 0;

  // since it was stopped all values should be
  // still set to idle
}

inline void MotorControl_stop(void)
{
  mc_stopped = true;
  mc_turn = 0;
  ST.stop();
}

inline void MotorControl_left(motorval_t speed) 
{
  if (mc_stopped) return; 
  CommandInterpreter_log("Sabertoothleft", speed);
  ST.motor(ST_MOTOR_LEFT, scaleM(speed));
}

inline void MotorControl_right(motorval_t speed) 
{
  if (mc_stopped) return; 

  CommandInterpreter_log("Sabertoothright", speed);
  ST.motor(ST_MOTOR_RIGHT, scaleM(speed));
}

#ifdef SABERTOOTH_CTRL_MODE_DUAL  

/*********************************************************************
 * 
 * DUAL MOTOR CONTROL MODE
 *
 *********************************************************************/

#define turnscaleL(s) ((char) ((int)(s)*(128+(mc_turn))/(int)128))
#define turnscaleR(s) ((char) ((int)(s)*(128-(mc_turn))/(int)128))

inline void MotorControl_turn(motorval_t turn)
{
  mc_turn = turn;  
}

void MotorControl_velocity(motorval_t speed)
{
  motorval_t lspeed, rspeed;
  lspeed = rspeed = speed;
  if (speed) {
    if (mc_turn < 0)
      lspeed = turnscaleL(speed);
    else {
      rspeed = turnscaleR(speed);
    }
  }
  MotorControl_left(lspeed);
  MotorControl_right(rspeed);
}

#else

/*********************************************************************
 * 
 * TURN_VELOCITY_MODE 
 *
 *********************************************************************/

inline void MotorControl_turn(motorval_t turn)
{
   if (mc_stopped) 
     turn = 0;
   ST.drive(turn);
}

void MotorControl_velocity(motorval_t speed)
{
   if (mc_stopped) 
     speed = 0;
   ST.drive(speed);
}

#endif

