/* logging */


void Logger_init() {
  Serial.begin(9600);
}

void Logger_loop() {
}

void Logger_log(char * text, motorval_t param) {
  Serial.print(text);
  Serial.print(" ");
  Serial.println(param);
}

