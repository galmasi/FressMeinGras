/************************************************************
 * This modules controls the Sabertooth 2x32 controller
 ************************************************************/

#include <Sabertooth.h>

Sabertooth ST(128);

/* ******************* */
/* motor control state */
/* ******************* */

bool mc_stopped = true;
motorval_t mc_left    = 0;
motorval_t mc_right   = 0;
motorval_t mc_turn    = 0;

//char mc_gear   = 10;

#define ST_MOTOR_LEFT  1
#define ST_MOTOR_RIGHT 2

/* *********************************************** */
/* set pin modes, and make sure motor will be stopped */
/* *********************************************** */

static inline void Sabertooth_stop(void)
{
}


inline void MotorControl_init(void) 
{
  mc_stopped = false;

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

  ST.setRamping(14);
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

inline void MotorControl_start(void)
{
  mc_stopped = false;
  // since it was stopped all values should be
  // still set to idle
}

inline void MotorControl_stop(void)
{
  mc_stopped = true;
  mc_left = mc_right = 0;
  Sabertooth_stop();
}

inline void MotorControl_left(motorval_t speed) 
{
  if (mc_stopped) return; 

  ST.motor(ST_MOTOR_LEFT, scaleM(speed));
}

inline void MotorControl_right(motorval_t speed) 
{
  motorval_t mc_right_new, setval;

  if (mc_stopped) return; 

  ST.motor(ST_MOTOR_RIGHT, scaleM(speed));

}

inline void MotorControl_turn(motorval_t turn)
{
  mc_turn = turn;  
}

#define turnscaleL(s) ((char) ((int)(s)*(128+(mc_turn))/(int)128))
#define turnscaleR(s) ((char) ((int)(s)*(128-(mc_turn))/(int)128))

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

