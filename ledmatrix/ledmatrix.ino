#include <ShiftRegister74HC595.h>

// Two chained 74HC595s: 16 outputs total
// dataPin = 2, clockPin = 3, latchPin = 4
ShiftRegister74HC595<2> sr(2, 3, 4);

// Direct Arduino pins for 10 rows
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

// Timing and animation control
int RowDuration = 500;
int row = 0;
unsigned long oldMicros = 0;
int count = 0;
int stretch = 20;

// Matrix state: 10 rows × 10 columns
int matrix[10][10] = {{0}};

void setup() {
  Serial.begin(9600);

  // Rows as outputs
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

  // Clear everything
  sr.setAllLow();

  /*          ARDUINO NANO                                74HC595 (two chained)               
              D2 |-> DS (SER, dataPin)        Q0–Q9  -> Column select lines (Columns 0–9)
              D3 |-> SHCP (SRCLK, clockPin)   Q10–Q15 -> (unused or spare)
              D4–D13 -> Row select lines (Rows 0–9)

              VCC (+5V)  -> 74HC595 VCC
              GND        -> 74HC595 GND
              OE (pin 13)-> GND   (always enabled)
              MR (pin 10)-> VCC   (no reset)

   Notes:
   - Rows are driven directly by Arduino pins.
   - Columns are driven by the shift registers.
   - Only one row is active at a time, columns define which LEDs in that row light.
  */
}

void loop() {
  if (micros() >= oldMicros) {
    oldMicros = micros() + RowDuration;

    if (count == 0)        { resetMatrix(); sin1(); }
    if (count == stretch)  { resetMatrix(); sin2(); }
    if (count == 2*stretch){ resetMatrix(); sin3(); }
    if (count == 3*stretch){ resetMatrix(); sin4(); }
    if (count == 4*stretch){ resetMatrix(); sin5(); }
    if (count == 5*stretch){ resetMatrix(); sin6(); }
    if (count == 6*stretch){ resetMatrix(); sin7(); }
    if (count == 7*stretch){ resetMatrix(); sin8(); }

    updateMatrix(row);

    row++;
    count++;
    if (row == 10) row = 0;                       // wrap back to first row (0–9)
    if (count == 8*stretch) count = 0;            // wrap animation frame counter
  }
}

void resetMatrix() {
  for (int r = 0; r < 10; r++)
    for (int c = 0; c < 10; c++)
      matrix[r][c] = 0;
}

// Example animation frames
void sin1() { for (int c = 0; c < 10; c++) matrix[0][c] = 1; }
void sin2() { for (int c = 0; c < 10; c++) matrix[1][c] = 1; }
void sin3() { for (int c = 0; c < 10; c++) matrix[2][c] = 1; }
void sin4() { for (int c = 0; c < 10; c++) matrix[3][c] = 1; }
void sin5() { for (int c = 0; c < 10; c++) matrix[4][c] = 1; }
void sin6() { for (int i = 0; i < 10; i++) matrix[i][i] = 1; }
void sin7() { for (int i = 0; i < 10; i++) matrix[i][9 - i] = 1; }
void sin8() { for (int r = 0; r < 10; r++) for (int c = 0; c < 10; c++) if ((r+c)%2==0) matrix[r][c]=1; }

void updateMatrix(int activeRow) {
  // Turn off all rows first
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

  // Prepare outputs for columns
  uint8_t outputs[16];
  for (int i = 0; i < 16; i++) outputs[i] = LOW;

  // Set columns 0–9 via shift register
  for (int c = 0; c < 10; c++) {
    if (matrix[activeRow][c] == 1) outputs[c] = HIGH;
  }

  // Push to shift registers
  sr.setAll(outputs);

  // Activate the current row (LOW = active if using N‑MOSFETs)
  switch (activeRow) {
    case 0: digitalWrite(ROW_0, LOW); break;
    case 1: digitalWrite(ROW_1, LOW); break;
    case 2: digitalWrite(ROW_2, LOW); break;
    case 3: digitalWrite(ROW_3, LOW); break;
    case 4: digitalWrite(ROW_4, LOW); break;
    case 5: digitalWrite(ROW_5, LOW); break;
    case 6: digitalWrite(ROW_6, LOW); break;
    case 7: digitalWrite(ROW_7, LOW); break;
    case 8: digitalWrite(ROW_8, LOW); break;
    case 9: digitalWrite(ROW_9, LOW); break;
  }
}