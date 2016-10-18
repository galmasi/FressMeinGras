
byte cmd_mode    = 0;      /* set to 1 when waiting for digits */
char cmd_command = ' ';    /* the last command we received */
int  cmd_param   = 0;      /* parameter received with command */

SoftwareSerial btSerial(BTSERIAL_RX,BTSERIAL_TX);

void CommandInterpreter_init() {
  btSerial.begin(9600);
  cmd_command = ' '; 
}

/* ************************************************** */
/*  is a complete command ready for interpretation?   */
/* ************************************************** */

char CommandInterpreter_command() {
  return cmd_command;
}

int CommandInterpreter_param() {
  return cmd_param;
}

void CommandInterpreter_log(String text, int num) {
  btSerial.print("T ");
  btSerial.print(text);
  btSerial.print (" ");
  btSerial.println(num);
  Serial.print(text);
  Serial.print(" ");
  Serial.println(num);
}

/* ************************************************** */
/*    check and consume incoming command from BT      */
/* ************************************************** */

bool CommandInterpreter_loop() {
  if (!btSerial.available()) return false;

  char c = btSerial.read();
  //Serial.print("Got char: ");
  //Serial.write(c);
  //Serial.println("");
  if (cmd_mode == 0) {
    switch (c) {
      // these commands have parameters, we have to wait for the param
      case 'L':
      case 'R': {
        cmd_mode          = 1;
        cmd_param         = 0;
        cmd_command       = c;
        return false;
      }
      // these commands are singletons, return them immediately
      case 'S':
      case 'G':
      case 'P': {
        cmd_mode         = 0;
        cmd_param        = 0;
        cmd_command      = c;
        return true;
      }
      default: {
        return false;
      }
    }
  } else if (cmd_mode > 0) {
    // newline finalizes the command
    if (c == '\n') {
       cmd_mode = 0;
       return true;
    }

    // accumulating digits for the command parameter
    else if ('0' <= c && c <= '9') {
       cmd_param = cmd_param * 10 + ((int)c-(int)'0');
       cmd_mode = 1;
       return false;
    }
    else {
      return true;
    }
  }
}

