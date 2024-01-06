#include <Arduino.h>

#define MS_INTERVAL 800
#define MS_DEBOUNCE_INTERVAL 250

#define SENSOR_PIN PB2
#define RELAY_PIN PB1

bool relay_value = HIGH;

/*******************/

bool checkForAClap( int timeLimit_ms ){

  int waiting_start = millis();
  while ( timeLimit_ms > (int)(millis()-waiting_start) ) {
    if ( digitalRead( SENSOR_PIN )) {      
      return true;    
    }
  }
  return false;
}

/*******************/

void setup(){
  
  //pinMode(SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite( RELAY_PIN, relay_value);
}

void loop(){

  while( ! digitalRead( SENSOR_PIN ) ){}                            // Awaits for a start clap

  delay( MS_DEBOUNCE_INTERVAL );                                    // Check for silence between claps
  if( checkForAClap( MS_INTERVAL - MS_DEBOUNCE_INTERVAL ) ){        
    return;
  }

  if( ! checkForAClap( MS_INTERVAL ) ){                             // Check for a second clap
    return;
  }

  digitalWrite( RELAY_PIN, relay_value^=1 );                        // Toggle the relay state
  delay(MS_INTERVAL*2);
}
