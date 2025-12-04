#include <ShiftRegister74HC595.h>

// Two chained 74HC595s: 16 outputs total
ShiftRegister74HC595<2> sr(2, 3, A1);

// Row pins
#define ROW_0 4
#define ROW_1 5
#define ROW_2 6
#define ROW_3 7
#define ROW_4 8
#define ROW_5 9
#define ROW_6 10
#define ROW_7 11
#define ROW_8 12
#define ROW_9 13

void setup() {
  pinMode(ROW_0, OUTPUT);
  pinMode(ROW_1, OUTPUT);
  pinMode(ROW_2, OUTPUT);
  pinMode(ROW_3, OUTPUT);
  pinMode(ROW_4, OUTPUT);
  pinMode(ROW_5, OUTPUT);
  pinMode(ROW_6, OUTPUT);
  pinMode(ROW_7, OUTPUT);
  pinMode(ROW_8, OUTPUT);
  pinMode(ROW_9, OUTPUT);

  sr.setAllLow();
}

void loop() {
  // Prepare outputs array
  uint8_t outputs[16];
  for (int i = 0; i < 16; i++) outputs[i] = HIGH;   // use LOW if active‑low

  // Push to shift register
  sr.setAll(outputs);

  // Turn on all rows
  digitalWrite(ROW_0, HIGH);
  digitalWrite(ROW_1, HIGH);
  digitalWrite(ROW_2, HIGH);
  digitalWrite(ROW_3, HIGH);
  digitalWrite(ROW_4, HIGH);
  digitalWrite(ROW_5, HIGH);
  digitalWrite(ROW_6, HIGH);
  digitalWrite(ROW_7, HIGH);
  digitalWrite(ROW_8, HIGH);
  digitalWrite(ROW_9, HIGH);

  // All LEDs should be lit
  delay(2000);

  // Turn everything off again
  sr.setAllLow();
  digitalWrite(ROW_0, LOW);
  digitalWrite(ROW_1, LOW);
  digitalWrite(ROW_2, LOW);
  digitalWrite(ROW_3, LOW);
  digitalWrite(ROW_4, LOW);
  digitalWrite(ROW_5, LOW);
  digitalWrite(ROW_6, LOW);
  digitalWrite(ROW_7, LOW);
  digitalWrite(ROW_8, LOW);
  digitalWrite(ROW_9, LOW);

  delay(2000);
}