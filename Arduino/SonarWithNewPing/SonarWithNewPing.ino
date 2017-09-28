#include <NewPing.h>

#define SONAR_NUM 5      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(13, 12, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(11, 10, MAX_DISTANCE),
  NewPing(9, 8, MAX_DISTANCE),
  NewPing(7, 6, MAX_DISTANCE),
  NewPing(5, 4, MAX_DISTANCE),
};

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

int pingvalues[5];

void loop() { 
    // Loop through each sensor
    // Wait 50ms between pings (about 20 pings/sec).
    // 29ms should be the shortest delay between pings.
  delay(50); 
  pingvalues[0] = sonar[0].ping_cm();
  delay(50); 
  pingvalues[2] = sonar[2].ping_cm();
  delay(50); 
  pingvalues[4] = sonar[4].ping_cm();
  delay(50); 
  pingvalues[1] = sonar[1].ping_cm();
  delay(50); 
  pingvalues[3] = sonar[3].ping_cm();

  for (uint8_t j=0; j<SONAR_NUM; j++) {
    Serial.print (pingvalues[j]);
    Serial.print (" ");
  }
  Serial.println();
}

