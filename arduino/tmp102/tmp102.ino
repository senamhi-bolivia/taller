/*
Read the temperature from an LM75-derived temperature sensor, and display it
in Celcius every 250ms. Any LM75-derived temperature should work.
*/

#include <Temperature_LM75_Derived.h>

// The Generic_LM75 class will provide 9-bit (±0.5°C) temperature for any
// LM75-derived sensor. More specific classes may provide better resolution.

TI_TMP102  temperature;

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  Serial.print("Temperature C = ");
  Serial.println(temperature.readTemperatureC());

  delay(250);
}
