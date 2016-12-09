/* ***************************************************************** */
/*            Bluetooth command reader.                              */
/* ***************************************************************** */


/* ************************************************** */
/*         Bluetooth reader state                     */
/* ************************************************** */

byte       _bt_mode       = 0;   /* set to 1 when waiting for digits */
char       _bt_command    = ' '; /* the last command we received */
motorval_t _bt_param      = 0;   /* parameter received with command */
motorval_t _bt_param_mult = 1;   /* either 1 or -1 dependent whether a negative number was specified */

#include <SoftwareSerial.h>

SoftwareSerial btSerial(BTSERIAL_RX,BTSERIAL_TX);

/* ************************************************** */
/* initialize bluetooth serial                        */
/* ************************************************** */

void BluetoothInterpreter_init()
{
  btSerial.begin(9600);
  _bt_command = ' '; 
}

/* ************************************************** */
/*    check and consume incoming command from BT      */
/* ************************************************** */

void BluetoothInterpreter_loop()
{
  if (!btSerial.available()) return;
  char c = btSerial.read();

  /* ****************** */
  /* command mode       */
  /* ****************** */

  if (_bt_mode == 0) {
    switch (c) {
      // STOP
      case 'S':
      {
        _bt_mode         = 0;
        CommandExecutor_Stop();
        return;
      }
      // GO
      case 'G':
      {
        _bt_mode         = 0;
        CommandExecutor_Go();
        return;
      }
      // PING  
      case 'P': 
      {
        _bt_mode         = 0;
        CommandExecutor_Ping();
        return;
      }
      // these commands have parameters, we have to wait for the param
      case 'L':  // left track    when track control is selected
      case 'R':  // right track   when track control is selected
      case 'T':  // turn degree   when steering is selected
      case 'V':  // velocity      when steering is selected 
      {
        _bt_mode          = 1;
        _bt_param         = 0;
        _bt_param_mult    = 1;
        _bt_command       = c;
        return;
      }
      default: 
      {
        // unknown codes are ignored.
        return;
      }
    }
  } 

  /* ****************** */
  /*  parameter mode    */
  /* ****************** */

  else if (_bt_mode > 0) {
    // check for negative sign
    if ((c == '-') && (_bt_mode == 1)) {
      _bt_param_mult = -1;
      _bt_mode = 2;
      return;
    }
    // accumulating digits for the command parameter
    else if ('0' <= c && c <= '9') {
      _bt_param = _bt_param * 10 + ((int)c-(int)'0');
      _bt_mode = 1;
      return;
    }

    // newline finalizes the command
    else if (c == '\n') {
      _bt_mode = 0;
      _bt_param = _bt_param * _bt_param_mult;
      switch (_bt_command) {
        case 'L': {
          CommandExecutor_Left (_bt_param);
          return;
        }
        case 'R': {
          CommandExecutor_Right (_bt_param);
          return;
        }
        case 'T': {
          CommandExecutor_Turn (_bt_param);
          return;
        }
        case 'V': {
          CommandExecutor_Velocity (_bt_param);
          return;
        }
      }
    }
   // garbage characters are ignored   
  }
}

