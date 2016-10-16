
/* ******************* */
/* motor control state */
/* ******************* */

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

void MotorControl_loop() {
   if (mc_stopped) {
     analogWrite(MOTORCONTROL_PWMAPIN, 0);
     analogWrite(MOTORCONTROL_PWMBPIN, 0);
   }
   else
   {
     analogWrite(MOTORCONTROL_PWMAPIN, mc_leftPower);
     digitalWrite(MOTORCONTROL_DIRAPIN, mc_leftDir);
     analogWrite(MOTORCONTROL_PWMBPIN, mc_rightPower);
     digitalWrite(MOTORCONTROL_DIRBPIN, mc_rightDir);
   }  
}

inline void MotorControl_start () {
  mc_stopped = false;
}

inline void MotorControl_stop () {
  mc_stopped = true;
}

inline void MotorControl_setLeft (byte n, bool dir) {
  mc_leftPower = n;
  mc_leftDir = dir;
}

inline void MotorControl_setRight (byte n, bool dir) {
  mc_rightPower = n;
  mc_rightDir = dir;
}

