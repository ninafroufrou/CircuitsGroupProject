#include <ShiftRegister74HC595.h>

// Two chained 74HC595s: 16 outputs total
// dataPin = 2, clockPin = 3, latchPin = A1
ShiftRegister74HC595<2> sr(2, 3, A1);

// Example: use row pin 4 (ROW_0)
#define ROW_0 4

void setup() {
  pinMode(ROW_0, OUTPUT);

  // Clear all outputs on the shift register
  sr.setAllLow();

  // Start serial for debugging
  Serial.begin(9600);
}

void loop() {
  // Prepare outputs array for the shift register
  uint8_t outputs[16];
  for (int i = 0; i < 16; i++) outputs[i] = LOW;

  // Turn ON column 0 (Q0 of the first 74HC595)
  outputs[4] = HIGH;

  // Push to shift register
  sr.setAll(outputs);

  // Activate row 0
  digitalWrite(ROW_0, HIGH);

  // LED at row 0, column 0 should light
  delay(1000);

  // Turn it off again
  sr.setAllLow();
  digitalWrite(ROW_0, LOW);
  delay(1000);
}