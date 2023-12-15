#include <Arduino.h>
// #define MS_INTERVAL 255
// #define relay LED_BUILTIN
// #define clap A0

int MS_INTERVAL = 800;
int MS_DEBOUNCE_INTERVAL = 250;
int relay = LED_BUILTIN;
int clap = A0;

bool relay_value = LOW;

/*******************/

int checkForAClap( int timeLimit_ms ){

  int waiting_start = millis();
  while ( timeLimit_ms > (int)(millis()-waiting_start) ) {
    if ( digitalRead( clap )) {      
      return true;    
    }
  }
  return false;
}

/*******************/

void setup() {

  pinMode(clap, INPUT);
  pinMode(relay, OUTPUT);

  Serial.begin(9600);
}

void loop() {  

  delay(1000);

  while( ! digitalRead( clap ) ){}                            // Awaits for a start clap
  delay( MS_DEBOUNCE_INTERVAL );

  Serial.println(1);
  if( checkForAClap( MS_INTERVAL - MS_DEBOUNCE_INTERVAL ) ){  // Checks for silence between claps
    return;
  } 

  Serial.println(2);
  if( ! checkForAClap( MS_INTERVAL ) ){                       // Cheks for a second clap
    return;
  }

  relay_value=!relay_value;
  digitalWrite( relay, relay_value );
  Serial.println(3);
  return;
}
