
/* ******************* */
/* motor control state */
/* ******************* */

bool mc_stopped  = true;
char mc_leftM    = 0;
char mc_rightM   = 0;
char globalTurn  = 0;

//char mc_gear   = 10;

// L298N has Motor A and Motor B
// each motor requires 3 pins
// forward,backward and pwm supplied voltage
#define L298N_AF (2)   // forward
#define L298N_AB (3)   // backward
#define L298N_AE (5)   // PWM
#define L298N_BF (9)   // forward
#define L298N_BB (10)  // backward
#define L298N_BE (6)   // PWM

/* *********************************************** */
/* set pin modes, and make sure motor will be stopped */
/* *********************************************** */

inline void L298N_stop()
{
  // set everything off
  digitalWrite(L298N_AF, LOW);
  digitalWrite(L298N_AB, LOW);
  digitalWrite(L298N_BF, LOW);
  digitalWrite(L298N_BB, LOW); 

  analogWrite(L298N_AE, 0);
  analogWrite(L298N_BE, 0);
}


inline void MotorControl_init() {
  // enable the modes of the L298N
  pinMode(L298N_AF, OUTPUT);
  pinMode(L298N_AB, OUTPUT);
  pinMode(L298N_AE, OUTPUT);
  pinMode(L298N_BF, OUTPUT);
  pinMode(L298N_BB, OUTPUT);
  pinMode(L298N_BE, OUTPUT);

  L298N_stop();
  mc_stopped = 1;
}

/* *********************************************** */
/* Like every motor this has a non-linear behavior */
/* with respect to voltage supplied.               */
/* We provide a curve here to get smoother scale   */
/* *********************************************** */

char speed_to_pwm[128] = {
  // we need to get more juice to the 
  // motors to start in early 
    0, 11, 16, 20, 23, 25, 28, 30, 32, 34,
   36, 38, 39, 41, 42, 44, 45, 47, 48, 49,
   51, 52, 53, 54, 55, 57, 58, 59, 60, 61,
   62, 63, 64, 65, 66, 67, 68, 69, 70, 71,
   72, 72, 73, 74, 75, 76, 77, 78, 78, 79,
   80, 81, 82, 82, 83, 84, 85, 85, 86, 87,
   88, 88, 89, 90, 91, 91, 92, 93, 93, 94,
   95, 95, 96, 97, 97, 98, 99, 99, 100, 101,
  101, 102, 102, 103, 104, 104, 105, 106, 106, 107,
  107, 108, 109, 109, 110, 110, 111, 111, 112, 113,
  113, 114, 114, 115, 115, 116, 116, 117, 118, 118,
  119, 119, 120, 120, 121, 121, 122, 122, 123, 123,
  124, 124, 125, 125, 126, 126, 127, 127
};

#define scaleM(v) (v)  // later with gear

/* *********************************************** */
/* if motor is stopped, write zeroes.              */
/* else write state values.                        */
/* *********************************************** */

void MotorControl_loop() {
   if (mc_stopped) {
	L298N_stop();
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
  static char newleftM;
  char setval;
  
  newleftM = scaleM(speed);
  if ((newleftM == 0) && (leftM == 0)) {
    digitalWrite(L298N_BB, LOW);
    digitalWrite(L298N_BF, LOW);
  }
  if ((newleftM >= 0) && (leftM <= 0)) {
    digitalWrite(L298N_BB, LOW);
    digitalWrite(L298N_BF, HIGH);
  }
  if ((newleftM <= 0) && (leftM >= 0)) {
    digitalWrite(L298N_BF, LOW);
    digitalWrite(L298N_BB, HIGH);
  }
  setval = abs(newleftM);
  analogWrite(L298N_BE, speed_to_pwm[setval]);
  leftM = newleftM;
}

inline void MotorControl_setRight (byte n, bool dir) {
  static char newrightM;
  char setval;
  
  newrightM = scaleM(speed);
  if ((newrightM==0) || (rightM == 0)) {
    digitalWrite(L298N_AB, LOW);
    digitalWrite(L298N_AF, LOW); 
  }
  if ((newrightM >= 0) && (rightM <= 0)) {
    digitalWrite(L298N_AB, LOW);
    digitalWrite(L298N_AF, HIGH);
  }
  if ((newrightM <= 0) && (rightM >= 0)) {
    digitalWrite(L298N_AF, LOW);
    digitalWrite(L298N_AB, HIGH);
  }
  setval = abs(newrightM);
  analogWrite(L298N_AE, speed_to_pwm[setval]);
  rightM = newrightM;
}

void MotorControl_setTurn(char turn)
{
  globalTurn = turn;  
}

#define turnscaleL(s) ((char) ((int)(s)*(128+(globalTurn))/(int)128))
#define turnscaleR(s) ((char) ((int)(s)*(128-(globalTurn))/(int)128))

void MotorControl_setVelocity(char speed)
{
  char lspeed, rspeed;
  lspeed = rspeed = speed;
  if (speed) {
      if (globalTurn < 0)
         lspeed = turnscaleL(speed);
      else {
         rspeed = turnscaleR(speed);
      }
  }
  setLeftSpeed(lspeed);
  setRightSpeed(rspeed);
}
