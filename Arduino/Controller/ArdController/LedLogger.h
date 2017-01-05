#define LEDLOGGER_STOP        0
#define LEDLOGGER_GO          1
#define LEDLOGGER_SLOW        2
#define LEDLOGGER_NOHEARTBEAT 3


byte _led_state = LEDLOGGER_STOP;

void LedLogger_init() {
    pinMode(LEDRED_PIN, OUTPUT);
    pinMode(LEDGRN_PIN, OUTPUT);
    pinMode(LEDBLU_PIN, OUTPUT);
    digitalWrite(LEDRED_PIN, 1);   
    digitalWrite(LEDGRN_PIN, 1);   
    digitalWrite(LEDBLU_PIN, 1);   
}
    
void LedLogger_set(byte newstate) {
  _led_state = newstate;
  if (_led_state == LEDLOGGER_GO) {
      digitalWrite(LEDRED_PIN, 1);
      digitalWrite(LEDGRN_PIN, 0);
      digitalWrite(LEDBLU_PIN, 1);
    }
  else if (_led_state == LEDLOGGER_STOP) {
    digitalWrite(LEDRED_PIN, 0);
    digitalWrite(LEDGRN_PIN, 1);
    digitalWrite(LEDBLU_PIN, 1);
  }  
}

void LedLogger_loop ()
{
  if (_led_state == LEDLOGGER_SLOW) {
    // fast pink blink
    int x = (millis()/500)&1;
    digitalWrite(LEDRED_PIN, x);
    digitalWrite(LEDGRN_PIN, 1);
    digitalWrite(LEDBLU_PIN, x);
  }
  else if (_led_state == LEDLOGGER_NOHEARTBEAT) {
    // fast red blink
    int x = (millis()/100)&1;
    digitalWrite(LEDRED_PIN, x);
    digitalWrite(LEDGRN_PIN, 1);
    digitalWrite(LEDBLU_PIN, 1);
  }
  else if (_led_state == LEDLOGGER_STOP) {
    // very slow blink red and nothing
    int x = (millis()/1000)&1;
    digitalWrite(LEDRED_PIN, x);
    digitalWrite(LEDGRN_PIN, 1);
    digitalWrite(LEDBLU_PIN, 1);
  }  
  else if (_led_state == LEDLOGGER_GO) {
    // very slow blink blue and green
    int x = (millis()/1000)&1;
    digitalWrite(LEDRED_PIN, 1);
    digitalWrite(LEDGRN_PIN, x);
    digitalWrite(LEDBLU_PIN, 1-x);
  }  
}

