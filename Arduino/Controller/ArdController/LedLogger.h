void LedLogger_init() {
    pinMode(LEDRED_PIN, OUTPUT);
    pinMode(LEDGRN_PIN, OUTPUT);
    pinMode(LEDBLU_PIN, OUTPUT);
    digitalWrite(LEDRED_PIN, 1);   
    digitalWrite(LEDGRN_PIN, 1);   
    digitalWrite(LEDBLU_PIN, 1);   
}
    
void LedLogger_set(int red, int green, int blue) {
  if (red == 1) digitalWrite(LEDRED_PIN, 0); else digitalWrite(LEDRED_PIN, 1); 
  if (green == 1) digitalWrite(LEDGRN_PIN, 0); else digitalWrite(LEDGRN_PIN, 1);
  if (blue == 1) digitalWrite(LEDBLU_PIN, 0); else digitalWrite(LEDBLU_PIN, 1);
}
