// signal level that means "bumper is triggered"
// for PNP sensors that is usually "1"
// for NPN sensors it is "0"

#if defined(BUMPER_NPN)
  #define BUMPER_TRIGGERED 0
#elif defined(BUMPER_PNP)
  #define BUMPER_TRIGGERED 1
#else
  #error "Have to define one of BUMPER_NPN or BUMPER_PNP if you define HAVE_BUMPERS"
#endif


byte _bumper_state = 0;

void Bumper_init() {
    pinMode(BUMPER_PIN_0, INPUT);
    pinMode(BUMPER_PIN_1, INPUT);
}


// bumper loop has debounce logic

void Bumper_loop() {
  int v1 = digitalRead(BUMPER_PIN_0);
  int v2 = digitalRead(BUMPER_PIN_1);
  
  if (v1 != BUMPER_TRIGGERED && v2 != BUMPER_TRIGGERED) {
    // bumper is not triggered.
    if (_bumper_state==1) Logger_log ("UNBUMP", 0);
    _bumper_state = 0;
    return;
  }
  else
  {
    if (_bumper_state==0) {
        Logger_log ("BUMP", 0);
        CommandExecutor_Stop(); // we just hit something. Stop right away.
    }
    CommandExecutor_Slow(0); // keep it slow until vehicle is unstuck.
    _bumper_state = 1;
    return;
  }
}

