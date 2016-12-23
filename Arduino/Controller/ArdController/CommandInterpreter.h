
#define COMMAND_MODE 0
#define PARAM_MODE 1

/** 

  Generic interpeter class to handle commands from bluetooth or from
  a raspberry pi.
  
  Note that the interpreter has a "privileged" bit - without that
  it is unable to issue GO or STOP commands to the executor, and any
  heartbeats it sends are ignored.
  
  */


class CommandInterpreter
{
 private:
  byte       _mode      ;   /* set to 1 when waiting for digits */
  char       _command   ;   /* the last command we received */
  motorval_t _param     ;   /* parameter received with command */
  motorval_t _param_mult;   /* either 1 or -1 dependent whether a negative number was specified */
  bool       _privileged;   /* true if this interpreter is allowed to issue START, STOP, HEARTBEAT commands */
  Stream   * _serial    ;

 public:
  inline CommandInterpreter(bool privileged=false)
    {
      _mode       = 0;
      _command    = ' ';
      _param      = 0;
      _param_mult = 1;
      _serial     = NULL;
      _privileged = privileged;
    }

  inline void setSerial(Stream *s) { _serial = s; }

  inline void loop() {
    if (!_serial) return;
    if (_serial->available()<=0) return;
    char c = _serial->read();
    if (_mode == COMMAND_MODE)
      switch (c) {
      case 'S': {
	  _mode = COMMAND_MODE;
	  if (_privileged) CommandExecutor_Stop();
	  return;
	}
      case 'G':	{
	_mode = COMMAND_MODE;
	if (_privileged) CommandExecutor_Go();
	return;
      }
      case 'H':	{
	_mode = COMMAND_MODE;
	if (_privileged) CommandExecutor_HeartBeat();
	return;
      }
      case 'P': {
	_mode = COMMAND_MODE;
	CommandExecutor_Ping();
	return;
      }
      case 'L':  // left track    when track control is selected
      case 'R':  // right track   when track control is selected
      case 'T':  // turn degree   when steering is selected
      case 'V':  // velocity      when steering is selected 
	{
	  _mode          = PARAM_MODE;
	  _param         = 0;
	  _param_mult    = 1;
	  _command       = c;
	  return;
	}
      default: {
	// unknown codes are ignored.
	return;
      }}
    
    else if (_mode == PARAM_MODE) {
      if ((c == '-') && (_mode == 1)) {
	_param_mult = -1;
	_mode = PARAM_MODE;
	return;
      }
      else if ('0' <= c && c <= '9') {
	_param = _param * 10 + ((int)c-(int)'0');
	_mode = PARAM_MODE;
	return;
      }
      else if (c == '\n') {
	_mode = COMMAND_MODE;
	_param = _param * _param_mult;
	switch (_command) {
        case 'L': {
          CommandExecutor_Left (_param);
          return;
        }
        case 'R': {
          CommandExecutor_Right (_param);
          return;
        }
        case 'T': {
          CommandExecutor_Turn (_param);
          return;
        }
        case 'V': {
          CommandExecutor_Velocity (_param);
          return;
        }}
      }
    }
  }
};



#include <SoftwareSerial.h>

SoftwareSerial btSerial(BTSERIAL_RX,BTSERIAL_TX);
CommandInterpreter btinterp(true); // privileged

#ifdef HAVE_COMPUTER
  SoftwareSerial ctSerial(CSERIAL_RX, CSERIAL_TX);
  CommandInterpreter cinterp;
#endif

inline void CommandInterpreter_init()
{
  btSerial.begin(9600);
  btinterp.setSerial(&btSerial);
#ifdef HAVE_COMPUTER
  ctSerial.begin(9600);
  cinterp.setSerial(&ctSerial);
#endif
}

inline void CommandInterpreter_loop()
{
  btSerial.listen();
  btinterp.loop();
#ifdef HAVE_COMPUTER
  ctSerial.listen();
  cinterp.loop();
#endif
}

