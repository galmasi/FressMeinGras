/* *********************************************** */
/*  the pins below are defined in the Velleman kit */
/* *********************************************** */

#define MC_PWMAPIN 3
#define MC_DIRAPIN 2
#define MC_PWMBPIN 9
#define MC_DIRBPIN 8

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
  pinMode(MC_PWMAPIN, OUTPUT);
  pinMode(MC_PWMBPIN, OUTPUT);
  pinMode(MC_DIRAPIN, OUTPUT);
  pinMode(MC_DIRBPIN, OUTPUT);
  mc_stopped = 1;
}

/* *********************************************** */
/* if motor is stopped, write zeroes.              */
/* else write state values.                        */
/* *********************************************** */

void MotorControl_loop() {
   if (mc_stopped) {
     analogWrite(MC_PWMAPIN, 0);
     analogWrite(MC_PWMBPIN, 0);
   }
   else
   {
     analogWrite(MC_PWMAPIN, mc_leftPower);
     digitalWrite(MC_DIRAPIN, mc_leftDir);
     analogWrite(MC_PWMBPIN, mc_rightPower);
     digitalWrite(MC_DIRBPIN, mc_rightDir);
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

