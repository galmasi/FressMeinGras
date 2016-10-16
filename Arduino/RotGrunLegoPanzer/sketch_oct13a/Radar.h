void Radar_init() {
  pinMode(RADAR_PINGPIN, OUTPUT);
  pinMode(RADAR_PONGPIN, INPUT);
}

void Radar_loop() {
}

long Radar_ping() {
  // send pulse
  digitalWrite(RADAR_PINGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(RADAR_PINGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(RADAR_PINGPIN, LOW);
  // wait for pulse
  long duration = pulseIn(RADAR_PONGPIN, HIGH);
  long distance = (duration/2) / 29.1;
  return distance;
}

