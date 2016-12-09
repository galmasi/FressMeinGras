/************************************************************
 * This modules controls the L298N dual channel controller
 ************************************************************/

/* ******************* */
/* motor control state */
/* ******************* */


int  mc_leftPower  = 0;
bool mc_leftDir    = true;
int  mc_rightPower = 0;
bool mc_rightDir   = true;
bool mc_stopped    = true;

/* *********************************************** */
/* set pin modes, and make sure motor will be stopped */
/* *********************************************** */

inline void MotorControl_init() {
  pinMode(LEGOMOTOR_PWMAPIN, OUTPUT);
  pinMode(LEGOMOTOR_PWMBPIN, OUTPUT);
  pinMode(LEGOMOTOR_DIRAPIN, OUTPUT);
  pinMode(LEGOMOTOR_DIRBPIN, OUTPUT);
  mc_stopped = 1;
}

/* *********************************************** */
/* if motor is stopped, write zeroes.              */
/* else write state values.                        */
/* *********************************************** */


inline void MotorControl_left (motorval_t speed)
{
  mc_leftPower = 2*abs(speed);
  mc_leftDir = (speed>0);
  analogWrite(LEGOMOTOR_PWMAPIN, mc_leftPower);
  digitalWrite(LEGOMOTOR_DIRAPIN, mc_leftDir);
}

inline void MotorControl_right (motorval_t speed)
{
  mc_rightPower = 2*abs(speed);
  mc_rightDir = (speed>0);
  analogWrite(LEGOMOTOR_PWMBPIN, mc_rightPower);
  digitalWrite(LEGOMOTOR_DIRBPIN, mc_rightDir);
}

inline void MotorControl_start (void) 
{
  mc_stopped = false;
  analogWrite(LEGOMOTOR_PWMAPIN, 0);
  analogWrite(LEGOMOTOR_PWMBPIN, 0);
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

