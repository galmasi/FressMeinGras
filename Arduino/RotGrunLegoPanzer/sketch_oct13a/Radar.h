int radar_timer = 0;
bool radar_running = false;

void Radar_init() {
  pinMode(RADAR_PINGPIN, OUTPUT);
  pinMode(RADAR_PONGPIN, INPUT);
}

void Radar_ping() {
  if (radar_running) return;
  radar_running = true;
  radar_timer = millis();
  digitalWrite(RADAR_PINGPIN, 1);
  digitalWrite(RADAR_PINGPIN, 0);
}

void Radar_loop() {
  if (!radar_running) return;
  bool z = digitalRead(RADAR_PONGPIN);
  if (z) {
    radar_running = false;
    radar_timer = millis() - radar_timer();
    Serial.print("Radar return ms = ");
    Serial.writeln(radar_timer);
  }
}

