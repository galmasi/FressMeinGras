void LedLogger_init() {
    pinMode(LEDRED_PIN, OUTPUT);
    pinMode(LEDGRN_PIN, OUTPUT);
    pinMode(LEDBLU_PIN, OUTPUT);
    digitalWrite(LEDRED_PIN, 1);   
    digitalWrite(LEDGRN_PIN, 1);   
    digitalWrite(LEDBLU_PIN, 1);   
}
    
void LedLogger_set(int red, int green, int blue) {
   digitalWrite(LEDRED_PIN, red==0);  
   digitalWrite(LEDGRN_PIN, green=0);  
   digitalWrite(LEDBLU_PIN, blue==0);  
}
