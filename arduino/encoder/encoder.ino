/*
    Rotary Encoder - Polling Example
    
    The circuit:
    * encoder pin A to Arduino pin encA
    * encoder pin B to Arduino pin encB
    * encoder ground pin to ground (GND)
    * encoder button pin to encBtn
    * encoder button ground pin to ground (GND)
*/

// rotary encoder pins
#define encBtn  D5
#define encA    D6
#define encB    D7


#include <Rotary.h>

Rotary r = Rotary(D6, D7);

/*
// ISR for encoder management
void encoderprocess (){
  encoder.process();
}
*/


void setup() {
  Serial.begin(115200);
  Serial.println("Started");
  r.begin();

  /*
  // encoder with interrupt on the A & B pins
  attachInterrupt(digitalPinToInterrupt(encA), encoderprocess, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encB), encoderprocess, CHANGE);  
  */
}

void loop() {

  unsigned char result = r.process();
  if (result) {
    Serial.println(result == DIR_CW ? "Right" : "Left");
  }

  /*
    Serial.println(r.pos);
  */
  
}
