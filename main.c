#include <Arduino.h>
#define MS_INTERVAL 200
#define relay LED_BUILTIN
#define clap A0

bool relay_value = LOW;

void setup() {

  pinMode(clap, INPUT);
  pinMode(relay, OUTPUT);
}

void loop() {

  digitalWrite( relay, relay_value);

  if( !digitalRead( clap ) )   // clap
    return;

  delay( MS_INTERVAL );
  if( digitalRead( clap ) ) // silence
    return;

  delay( MS_INTERVAL );      
  if( digitalRead( clap ) )   // second clap
    relay_value=!relay_value;
}
