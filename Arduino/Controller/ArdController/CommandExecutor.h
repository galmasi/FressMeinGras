/* ******************************************************** */
/* *    command executor state                            * */
/* ******************************************************** */

unsigned long _ce_lastHeartBeat;  /* timing of last heartbeat heard from BlueTooth */
motorval_t          _ce_fwLimit;        /* forward speed limit */
motorval_t          _ce_bwLimit;        /* backward speed limit */
motorval_t          _ce_turn;           /* last turn value */
motorval_t          _ce_speed;          /* last speed value */

motorval_t state; /* !!!!! */


/* ******************************************************** */
/*           initialize state                               */
/* ******************************************************** */

inline void CommandExecutor_init()
{
  _ce_lastHeartBeat = millis();
  _ce_fwLimit = 0;
  _ce_bwLimit = 0;
  _ce_turn = 0;
  _ce_speed = 0;
}

/* ******************************************************** */
/*          update LEDs, check heartbeat etc.               */
/* ******************************************************** */
inline void CommandExecutor_loop()
{
  #if 0
  // we expect a heartbeat to be send every 750msec
  // the 1000msec check provides some slack
  if (millis() > (_ce_lastHeartBeat + 1000)) {
    // we lost communication with RC
    MotorControl_stop();
    _ce_fwLimit = 0;
    _ce_bwLimit = 0;
    Logger_log("Heartbeat lost", 0);
  }
  #endif
}

inline motorval_t CommandExecutor_limit (motorval_t n)
{
  if (n>_ce_fwLimit) return _ce_fwLimit;
  else if (n<-_ce_bwLimit) return -_ce_bwLimit;
  else return n;
}

inline motorval_t CommandExecutor_p2r (motorval_t turn, motorval_t speed)
{
  if (turn>=0) return speed;
  else return (int)speed*((int)turn+64)/64;
}

/* ******************************************************** */
/*          enable running - remove limits.                 */
/* ******************************************************** */

inline void CommandExecutor_Go ()
{
  MotorControl_start();
  _ce_fwLimit = 127;
  _ce_bwLimit = 127;
  _ce_speed = 0;
  Logger_log ("GO", 0);
}

inline void CommandExecutor_Stop ()
{
  MotorControl_stop();
  _ce_fwLimit = 0;
  _ce_bwLimit = 0;
  _ce_speed = 0;
  Logger_log("STOP",0);
}

// direction: 
// 1 = STOP fwd, SLOW bwd
// -1 = STOP bwd, SLOW fwd
// 0 = SLOW in both directions

void CommandExecutor_Slow(signed char dir)
{
  MotorControl_stop();
  _ce_fwLimit = 15;
  _ce_bwLimit = 15;
  if (dir > 0) _ce_fwLimit = 0;
  if (dir < 0) _ce_bwLimit = 0;
  _ce_speed = 0;
  Logger_log("SLOW",dir);
}

inline void CommandExecutor_Left(motorval_t n)
{
  MotorControl_left (CommandExecutor_limit(n));
  Logger_log("LEFT", n);
}

inline void CommandExecutor_Right(motorval_t n)
{
  MotorControl_right (CommandExecutor_limit(n));
  Logger_log("RIGHT", n);
}

inline void CommandExecutor_Turn(motorval_t n)
{
  _ce_turn = n;
  motorval_t l = CommandExecutor_limit(CommandExecutor_p2r(-_ce_turn, _ce_speed));
  motorval_t r = CommandExecutor_limit(CommandExecutor_p2r(_ce_turn, _ce_speed));
  MotorControl_left (l);
  MotorControl_right(r);
  Logger_log("Turn", _ce_turn);
  Logger_log("Vel", _ce_speed);
  Logger_log("LEFT", l);
  Logger_log("RIGHT", r);  
}

inline void CommandExecutor_Velocity(motorval_t n)
{
  _ce_speed = n;
  motorval_t l = CommandExecutor_limit(CommandExecutor_p2r(-_ce_turn, _ce_speed));
  motorval_t r = CommandExecutor_limit(CommandExecutor_p2r(_ce_turn, _ce_speed));
  MotorControl_left (l);
  MotorControl_right(r);
  Logger_log("Turn", _ce_turn);
  Logger_log("Vel", _ce_speed);
  Logger_log("LEFT", l);
  Logger_log("RIGHT", r);  
}

inline void CommandExecutor_Ping ()
{
}

inline void CommandExecutor_HeartBeat()
{
  // we send the heartbeat every 750msec in case no commands are coming
  // from the controller.
  // Any command should be taken as a heartbeat, so move the hearbeat
  // outside this case statement
  _ce_lastHeartBeat = millis();
}

