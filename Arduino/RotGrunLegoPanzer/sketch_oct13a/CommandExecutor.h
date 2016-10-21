
void CommandExecutor_init() {
}


inline void CommandExecutor_loop () {
  char c = CommandInterpreter_command();
  switch (c) {
      case 'G': {
        CommandInterpreter_log("GO", 0);
        MotorControl_start();
        break;
      }
      case 'S': {
        MotorControl_stop();
        CommandInterpreter_log("STOP",0);
        break;
      }
      case 'L': {
        int n = CommandInterpreter_param();
        int p = abs(n-256);
        bool d = (n>256);
        //gCommandInterpreter_log("LEFT ", p*(d?1:-1));
        MotorControl_setLeft (p, d);
        break;
      }
      case 'R': {
        int n = CommandInterpreter_param();
        int p = abs(n-256);
        bool d = (n>256);
        //CommandInterpreter_log("RIGHT ", p*(d?1:-1));
        MotorControl_setRight (p, d);
        break;
     }
     case 'P': {
        long distance = Radar_ping();
        Serial.print("PING ");
        Serial.println(distance);
        break;
     }
  }
}

