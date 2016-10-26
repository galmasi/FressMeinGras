
void CommandExecutor_init() {
}


inline void CommandExecutor_exec () {
  char c = CommandInterpreter_command();
  int n;
  switch (c) {
      case 'G': {
        MotorControl_start();
        CommandInterpreter_log("GO", 0);
        break;
      }
      case 'S': {
        MotorControl_stop();
        CommandInterpreter_log("STOP",0);
        break;
      }
      case 'L': {
        n = CommandInterpreter_param();
        //gCommandInterpreter_log("LEFT ", n);
        MotorControl_left (n);
        break;
      }
      case 'R': {
        n = CommandInterpreter_param();
        //CommandInterpreter_log("RIGHT ", n);
        MotorControl_right (n);
        break;
      }
      case 'V': {
        n = CommandInterpreter_param();
        //gCommandInterpreter_log("VEL ", n);
        MotorControl_velocity(n);
        break;
      }
      case 'T': {
        n = CommandInterpreter_param();
        //gCommandInterpreter_log("TURN", n);
        MotorControl_turn(n);
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

