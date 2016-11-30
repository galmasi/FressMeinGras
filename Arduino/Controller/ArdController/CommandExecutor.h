unsigned long lastHeartBeat;

void CommandExecutor_init()
{
  lastHeartBeat = millis();
}

void CheckHeartBeat()
{
  // we expect a heartbeat to be send every 750msec
  // the 1000msec check provides some slack
  if (millis() > (lastHeartBeat + 1000)) {
    // we lost communication with RC
    MotorControl_stop();
    CommandInterpreter_log("STOP",0);
  }
}

inline void CommandExecutor_exec ()
{
  char c = CommandInterpreter_command();
  int n;

  //  Serial.print("execute command: ");
  //  Serial.write(c);
  //  Serial.print(" ");
  //  Serial.print(CommandInterpreter_param());
  //  Serial.println("");
  switch (c) {
  case 'G':   // GO
    {
      MotorControl_start();
      CommandInterpreter_log("GO", 0);
      break;
    }
  case 'S':   // STOP
    {
      MotorControl_stop();
      CommandInterpreter_log("STOP",0);
      break;
    }
  case 'L':   // TANK LEFT  TRACK -127 .. +127   
    {
      n = CommandInterpreter_param();
      //gCommandInterpreter_log("LEFT ", n);
      MotorControl_left (n);
      break;
    }
  case 'R': // TANK RIGHT TRACK -127 .. +127   
    {
      n = CommandInterpreter_param();
      //CommandInterpreter_log("RIGHT ", n);
      MotorControl_right (n);
      break;
    }
  case 'V': // VELOCITY -127..+127
    {
      n = CommandInterpreter_param();
      //gCommandInterpreter_log("VEL ", n);
      MotorControl_velocity(n);
      break;
    }
  case 'T':  // TURN -127..+127
    {
      n = CommandInterpreter_param();
      //gCommandInterpreter_log("TURN", n);
      MotorControl_turn(n);
      break;
    }
  case 'P':  // PING RADAR  
    {
      long distance = Radar_ping();
      Serial.print("PING ");
      Serial.println(distance);
      break;
    }
  case 'H':  // HEARTBEAT 
    {
      // we send the heartbeat every 750msec in case no commands are coming
      // from the controller.
      // Any command should be taken as a heartbeat, so move the hearbeat
      // outside this case statement
      break;
    }
  }
  lastHeartBeat = millis();
}



