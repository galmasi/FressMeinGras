
inline void CommandExecutor() {
  char c = CommandInterpreter_command();
  switch (c) {
      case 'G': {
        Serial.println("GO");
        MotorControl_start();
        break;
      }
      case 'S': {
        Serial.println("STOP");
        MotorControl_stop();
        break;
      }
      case 'L': {
        int n = CommandInterpreter_param();
        int p = abs(n-256);
        bool d = (n>256);
        Serial.print ("LEFT ");
        Serial.print(p);
        Serial.println (d?" FWD":"BACK");
        MotorControl_setLeft (p, d);
        break;
      }
      case 'R': {
        int n = CommandInterpreter_param();
        int p = abs(n-256);
        bool d = (n>256);
        Serial.print ("RIGHT ");
        Serial.print(p);
        Serial.println (d?" FWD":"BACK");
        MotorControl_setRight (p, d);
        break;
     }
  }
}

