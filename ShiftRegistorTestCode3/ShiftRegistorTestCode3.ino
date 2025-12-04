const int DATA_PIN  = 2;   // SER
const int CLOCK_PIN = 3;   // SRCLK
const int LATCH_PIN = A1;  // RCLK

const int ROW_PINS[10] = {4,5,6,7,8,9,10,11,12,13};

void sendTwoBytes(byte chip2, byte chip1) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, chip2); // far chip
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, chip1); // near chip
  digitalWrite(LATCH_PIN, HIGH);
}

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  // Turn ON all rows
  for (int i = 0; i < 10; i++) {
    pinMode(ROW_PINS[i], OUTPUT);
    digitalWrite(ROW_PINS[i], HIGH);
  }

  // Turn ON all 16 outputs (both shift registers)
  sendTwoBytes(0xFF, 0xFF);
}

void loop() {
}
