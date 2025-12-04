// Pins (change only if your wiring is different)
const int DATA_PIN  = 2;  // SER
const int CLOCK_PIN = 3;  // SRCLK
const int LATCH_PIN = A1;   // RCLK
const int ROW_PIN = 4;

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("Shift register test starting");
}

void loop() {
    // Example: turn Arduino pin 4 ON
  digitalWrite(ROW_PIN, HIGH);
  // 1. All outputs OFF (0x00)
  Serial.println("ALL OFF");
  sendByte(0x00);
  delay(1000);

  // 2. All outputs ON (0xFF)
  Serial.println("ALL ON");
  sendByte(0xFF);
  delay(1000);

  // 3. Walk a single '1' across all 8 outputs
  Serial.println("Walking bit");
  for (int i = 0; i < 8; i++) {
    byte pattern = (1 << i);
    Serial.print("Bit: ");
    Serial.println(pattern, BIN);

    sendByte(pattern);
    delay(300);
  }

  // 4. Walk a single '0' across all 8 outputs (inverse)
  Serial.println("Walking inverse bit");
  for (int i = 0; i < 8; i++) {
    byte pattern = ~(1 << i);
    Serial.print("Inv: ");
    Serial.println(pattern, BIN);

    sendByte(pattern);
    delay(300);
  }

    // Example: turn Arduino pin 4 OFF again
  digitalWrite(ROW_PIN, LOW);


  delay(1000);
}

// ---- Helper ----
void sendByte(byte b) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, b);
  digitalWrite(LATCH_PIN, HIGH);
}
