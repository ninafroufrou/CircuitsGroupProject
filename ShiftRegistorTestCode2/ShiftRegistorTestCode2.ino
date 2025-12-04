// Pins for shift register
const int DATA_PIN  = 2;   // SER
const int CLOCK_PIN = 3;   // SRCLK
const int LATCH_PIN = A1;  // RCLK

// Row pins (Arduino 4–13)
const int ROW_PINS[10] = {4,5,6,7,8,9,10,11,12,13};

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  for (int i = 0; i < 10; i++)
    pinMode(ROW_PINS[i], OUTPUT);

  Serial.begin(115200);
  Serial.println("Two-chip test starting");
}

void loop() {
  // Enable all rows
  for (int i = 0; i < 10; i++)
    digitalWrite(ROW_PINS[i], HIGH);

  // Turn on all 16 outputs (both shift registers)
  sendTwoBytes(0xFF, 0xFF);  // chip2 = 0xFF, chip1 = 0xFF
  delay(2000);

  // Turn everything off
  for (int i = 0; i < 10; i++)
    digitalWrite(ROW_PINS[i], LOW);

  sendTwoBytes(0x00, 0x00);  // chip2 = 0x00, chip1 = 0x00
  delay(2000);
}

// ---- Helper ----
// First byte shifted goes to chip2 (far), second goes to chip1 (near)
void sendTwoBytes(byte chip2, byte chip1) {
  digitalWrite(LATCH_PIN, LOW);

  // Shift to chip2 first, then chip1
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, chip2);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, chip1);

  digitalWrite(LATCH_PIN, HIGH);
}
