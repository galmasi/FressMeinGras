#define BUMPER_TRIGGERED 1

byte _bumper_state = 0;

void Bumper_init() {
    pinMode(BUMPER_PIN, INPUT);

}


// bumper loop has debounce logic

void Bumper_loop() {
  int v = digitalRead(BUMPER_PIN);
  
  if (v != BUMPER_TRIGGERED) {
    // bumper is not triggered.
    if (_bumper_state==1) Logger_log ("UNBUMP", 0);
    _bumper_state = 0;
    return;
  }
  else 
  {
    if (_bumper_state==0) Logger_log ("BUMP", 0);
    CommandExecutor_Slow(0); // being triggered right now
    _bumper_state = 1;
    return;
  }
}

