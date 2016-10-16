#include <SoftwareSerial.h>

int  cmd_mode    = 0;      /* set to 1 when waiting for digits */
char cmd_command = ' ';    /* the last command we received */
int  cmd_param   = 0;      /* parameter received with command */
int  cmd_ready   = 0;      /* is command ready for executor */

void CommandInterpreter_init() {
  btSerial.begin(9600);
  cmd_ready = 0;
  cmd_command = ' ';    
}

/* ************************************************** */
/*  is a complete command ready for interpretation?   */
/* ************************************************** */
int CommandInterpreter_ready() {
  return cmd_ready;
}

char CommandInterpreter_lastCommand() {
  return cmd_command;
}

int CommandInterpreter_param() {
  return cmd_param;
}

/* ************************************************** */
/*    check and consume incoming command from BT      */
/* ************************************************** */

void CommandInterpreter_loop() {
  cmd_ready = 0;
  if (!btSerial.available()) return;

  char c = btSerial.read();
  //Serial.print("Got char: ");
  //Serial.write(c);
  //Serial.println("");
  if (cmd_mode == 0) {
    // waiting for a command
    switch (c) {
      case 'L':
      case 'R': {
        cmd_mode          = 1;
        cmd_param         = 0;
        cmd_lastcommand   = c;
        cmd_ready         = 0;
        break;
      }
      case 'S':
      case 'G' {
        cmd_mode         = 0;
        cmd_param        = 0;
        cmd_lastcommand  = c;
        cmd_ready        = 1;
        break;
      }
      default: {
        cmd_ready        = 0;
        break;
      }
  } else if (cmd_mode == 1) {
    if (c == '\n') {
       cmd_mode = 0;
       cmd_ready = 1;
    }
    else if ('0' <= c && c <= '9') {
       cmd_param = cmd_param * 10 + ((int)c-(int)'0');
       cmd_mode = 1;
       cmd_ready = 1;
    }
    else {
      cmd_ready = 0;
    }
  }
}

