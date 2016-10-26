/*********************************************************
 * Legacy controller from Hubertus .. now depricated
 * functionality merged with Gheorghe's
 ********************************************************/

#include <SoftwareSerial.h>
SoftwareSerial BT(7, 8);

// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND

#define st_enabled (0)
#define MOTOR_DRIVER_L298N

#ifdef MOTOR_DRIVER_L298N
//--------------------- L298N_related_code
//
#define L298N_AF (2)   // forward
#define L298N_AB (3)   // backward
#define L298N_AE (5)   // PWM
#define L298N_BF (9)   // forward
#define L298N_BB (10)  // backward
#define L298N_BE (6)   // PWM

void setup_L298N()
{
  // enable the modes of the L298N
  pinMode(L298N_AF, OUTPUT);
  pinMode(L298N_AB, OUTPUT);
  pinMode(L298N_AE, OUTPUT);
  pinMode(L298N_BF, OUTPUT);
  pinMode(L298N_BB, OUTPUT);
  pinMode(L298N_BE, OUTPUT);

  // set everything off
  analogWrite(L298N_AE, 0);
  analogWrite(L298N_BE, 0);

  digitalWrite(L298N_AF, LOW);
  digitalWrite(L298N_AB, LOW);
  digitalWrite(L298N_BF, LOW);
  digitalWrite(L298N_BB, LOW);
}

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
static char leftM  = 0;
static char rightM = 0;
static char gear   = 10;

#define scaleM(v) (v)  // later with gear

void setLeftSpeed(char speed)
{
  static char newleftM;
  char setval;
  
  newleftM = scaleM(speed);
  if (st_enabled) Serial.print("set left: "); Serial.print(newleftM, DEC); Serial.print("\n");
  if ((newleftM == 0) && (leftM == 0)) {
    digitalWrite(L298N_BB, LOW);
    digitalWrite(L298N_BF, LOW);
  }
  if ((newleftM >= 0) && (leftM <= 0)) {
    digitalWrite(L298N_BB, LOW);
    digitalWrite(L298N_BF, HIGH);
    Serial.print("MOVE L POS\n");
  }
  if ((newleftM <= 0) && (leftM >= 0)) {
    digitalWrite(L298N_BF, LOW);
    digitalWrite(L298N_BB, HIGH);
    Serial.print("MOVE L NEG\n");
  }
  setval = abs(newleftM);
  analogWrite(L298N_BE, speed_to_pwm[setval]);
  leftM = newleftM;
}

void setRightSpeed(char speed)
{
  static char newrightM;
  char setval;
  
  newrightM = scaleM(speed);
  if (st_enabled) { Serial.print("set right: "); Serial.print(newrightM, DEC); Serial.print("\n"); }
  if ((newrightM==0) || (rightM == 0)) {
    digitalWrite(L298N_AB, LOW);
    digitalWrite(L298N_AF, LOW); 
  }
  if ((newrightM >= 0) && (rightM <= 0)) {
    digitalWrite(L298N_AB, LOW);
    digitalWrite(L298N_AF, HIGH);
    if (st_enabled) Serial.print("MOVE R POS\n");
  }
  if ((newrightM <= 0) && (rightM >= 0)) {
    digitalWrite(L298N_AF, LOW);
    digitalWrite(L298N_AB, HIGH);
    if (st_enabled) Serial.print("MOVE R NEG\n");
  }
  setval = abs(newrightM);
  analogWrite(L298N_AE, speed_to_pwm[setval]);
  rightM = newrightM;
}

static char globalTurn = 0;

void setTurn(char turn)
{
  globalTurn = turn;  
}

#define turnscaleL(s) ((char) ((int)(s)*(128+(globalTurn))/(int)128))
#define turnscaleR(s) ((char) ((int)(s)*(128-(globalTurn))/(int)128))

void setSpeed(char speed)
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

void stopImmediately()
{
  setLeftSpeed(0);
  setRightSpeed(0);
}
#endif

///////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  // set digital pin to control as an output
  pinMode(13, OUTPUT);

  setup_L298N();

  // set the data rate for the SoftwareSerial port
  BT.begin(9600);
  //BT.begin(38400);
  Serial.begin(9600);
  // Send test message to other device
  Serial.println("Hello from Arduino");
}

struct cmd {
  char cmd;
  char value;  // [ -127 .. 127 ]
};

char a; // stores incoming character from other device
char validcmd[] = "LRSTCG";

int cmdparser(char a, struct cmd * cmd)
{
  static int state = 0; // nothing received yet
  static int value = 0;
  static char cmdtok = 0;
  static int multiplier = -1;
  char *cptr;
  int rc = 0;

  switch (state) {

    case 0: // waiting for a command token
      for (cptr = validcmd; *cptr && (*cptr != a) ; cptr++);
      if (*cptr) {
        cmdtok = *cptr;
        state = 1; // we got command, waiting for number
        value = 0;
        multiplier = 1; // assume positive
      }
      break;
    case 1: // waiting for a number or a negative sign
      if (a == ' ')
        break; // stay in state
      state = 2;
      if (a == '-') {
        multiplier = -1;
        break;
      }
    case 2: // parsing a number
      if ((a >= '0') && (a <= '9')) {
        value = 10 * value + (a - '0');
        break;
      }
      if (a == '\n') {
        // command end is reached
        cmd->value = (char) (value * multiplier);
        cmd->cmd   = cmdtok;
        rc = 1;
      }
      state = 0;
      break;
  }
  return rc;
}



//#define scaleM(v) (((v)/10)*gear)
#define scaleM(v) (v)

void execute_cmd(struct cmd * cmd)
{

  if (st_enabled) { Serial.print("cmd: "); Serial.print(cmd->cmd); Serial.print(" , "); Serial.print(cmd->value, DEC);  Serial.println(""); }
  switch (cmd->cmd) {
    case 'L':
      setLeftSpeed(cmd->value);
      break;
    case 'R':
      setRightSpeed(cmd->value);
      break;
    case 'S':
      setSpeed(cmd->value);
      break;
    case 'T':
      setTurn(cmd->value);
      break;
    case 'G':
      break;
    case 'C':
      break; // not handled yet
    case 'X':
      stopImmediately();
      break;
  }
}

void loop()
{
  struct cmd cmd;
  if (BT.available())
    // if text arrived in from BT serial...
  {
    a = (BT.read());
    //Serial.print(a); // Serial.println("");
    if (cmdparser(a, &cmd)) {
      execute_cmd(&cmd);
      //Serial.println("new command");
    }
  }
}


