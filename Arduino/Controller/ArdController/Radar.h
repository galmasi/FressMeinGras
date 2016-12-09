void Radar_init(void)
{
  pinMode(RADAR_PINGPIN, OUTPUT);
  pinMode(RADAR_PONGPIN, INPUT);
}

void Radar_loop(void)
{
}

#if 0

// every 15000 counts, run a radar loop

long _rdrctr = 0;
void Radar_loop() {
  if ((_rdrctr%15000)==0) {
    long r = Radar_ping();
    CommandInterpreter_log ("Radar", (int)r);
  }
  _rdrctr++;
}

long Radar_ping(void)
{
  // send pulse
  digitalWrite(RADAR_PINGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(RADAR_PINGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(RADAR_PINGPIN, LOW);
  // wait for pulse
  long duration = pulseIn(RADAR_PONGPIN, HIGH, 2000000/340);
  long distance = (duration/2) / 29.1;
  return distance;
}

#endif
