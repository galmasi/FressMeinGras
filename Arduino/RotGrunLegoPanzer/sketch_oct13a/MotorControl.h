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

int mc_leftPower  = 0;
int mc_leftDir    = 1;
int mc_rightPower = 0;
int mc_rightDir   = 1;
int mc_stopped    = 1;

/* *********************************************** */
/* set pin modes, and make sure motor will be stopped */
/* *********************************************** */

void MotorControl_init() {
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

void MotorControl_start () {
  mc_stopped = 0;
}

void MotorControl_stop () {
  mc_stopped = 1;
}

void MotorControl_setLeft (int n, int dir) {
  mc_leftPower = n;
  mc_leftDir = dir;
}

void MotorControl_setRight (int n, int dir) {
  mc_rightPower = n;
  mc_rightDir = dir;
}

