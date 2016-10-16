int radar_timer = 0;
int radar_lastreturn=-1;

void Radar_init() {
  pinMode(RADAR_PINGPIN, OUTPUT);
  pinMode(RADAR_PONGPIN, INPUT);
}

void Radar_ping() {
  radar_timer = millis();
}


void Radar_loop() {
}

