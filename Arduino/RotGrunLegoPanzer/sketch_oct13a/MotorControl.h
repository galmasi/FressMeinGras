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

void MotorControlInit() {
  pinMode(MC_PWMAPIN, OUTPUT);
  pinMode(MC_PWMBPIN, OUTPUT);
  pinMode(MC_DIRAPIN, OUTPUT);
  pinMode(MC_DIRBPIN, OUTPUT);
  mc_stopped = 1;
}

void MotorControlLoop() {
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

void MotorControlStart () {
  mc_stopped = 0;
}

void MotorControlStop () {
  mc_stopped = 1;
}

void MotorSetLeft (int x) {
  mc_leftPower = 
}

