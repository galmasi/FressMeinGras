/************************************************************
 * This modules controls the L298N dual channel controller
 ************************************************************/

/* ******************* */
/* motor control state */
/* ******************* */

#define MOTORCONTROL_PWMAPIN 3
#define MOTORCONTROL_DIRAPIN 2
#define MOTORCONTROL_PWMBPIN 9
#define MOTORCONTROL_DIRBPIN 8

byte mc_leftPower  = 0;
bool mc_leftDir    = true;
byte mc_rightPower = 0;
bool mc_rightDir   = true;
bool mc_stopped    = true;

/* *********************************************** */
/* set pin modes, and make sure motor will be stopped */
/* *********************************************** */

inline void MotorControl_init() {
  pinMode(MOTORCONTROL_PWMAPIN, OUTPUT);
  pinMode(MOTORCONTROL_PWMBPIN, OUTPUT);
  pinMode(MOTORCONTROL_DIRAPIN, OUTPUT);
  pinMode(MOTORCONTROL_DIRBPIN, OUTPUT);
  mc_stopped = 1;
}

/* *********************************************** */
/* if motor is stopped, write zeroes.              */
/* else write state values.                        */
/* *********************************************** */


inline void MotorControl_left (motorval_t speed)
{
  mc_leftPower = abs(speed-256);
  mc_leftDir = (speed>256);
  analogWrite(MOTORCONTROL_PWMAPIN, mc_leftPower);
  digitalWrite(MOTORCONTROL_DIRAPIN, mc_leftDir);
}

inline void MotorControl_right (motorval_t speed)
{
  mc_rightPower = abs(speed-256);
  mc_rightDir = (speed>256);
  analogWrite(MOTORCONTROL_PWMBPIN, mc_rightPower);
  digitalWrite(MOTORCONTROL_DIRBPIN, mc_rightDir);
}

inline void MotorControl_start (void) 
{
  mc_stopped = false;
  analogWrite(MOTORCONTROL_PWMAPIN, 0);
  analogWrite(MOTORCONTROL_PWMBPIN, 0);
}

inline void MotorControl_stop (void) 
{
  mc_stopped = true;
  MotorControl_left(0);
  MotorControl_right(0);
}

inline void MotorControl_velocity(motorval_t speed)
{
  // please complete see L298N
}

inline void MotorControl_turn(motorval_t speed)
{
  // please complete see L298N
}

