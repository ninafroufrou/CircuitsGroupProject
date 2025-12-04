// ==========================================================
// ==================== PIN DEFINITIONS =====================
// ==========================================================

const int DATA_PIN  = 2;      // SER
const int CLOCK_PIN = 3;      // SRCLK
const int LATCH_PIN = A1;     // RCLK
const int BUTTON_PIN = A0;

const int ROW_PINS[10] = {4,5,6,7,8,9,10,11,12,13};

// ==========================================================
// ==================== FRAMEBUFFER ==========================
// ==========================================================

uint8_t frame[10][2];

// ==========================================================
// ==================== SHIFT REGISTER =======================
// ==========================================================

void sendTwoBytes(byte chip2, byte chip1) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, chip2);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, chip1);
  digitalWrite(LATCH_PIN, HIGH);
}

// ==========================================================
// ==================== PIXEL + FRAME ========================
// ==========================================================

void setPixel(int x, int y, bool state) {
  if (x < 0 || x > 9 || y < 0 || y > 9) return;

  if (x < 8) {
    if (state) frame[y][0] |=  (1 << x);
    else       frame[y][0] &= ~(1 << x);
  } else {
    int bit = x - 8;
    if (state) frame[y][1] |=  (1 << bit);
    else       frame[y][1] &= ~(1 << bit);
  }
}

void clearFrame() {
  for (int r = 0; r < 10; r++) {
    frame[r][0] = 0;
    frame[r][1] = 0;
  }
}

// ==========================================================
// =================== DISPLAY REFRESH =======================
// ==========================================================

void refreshDisplay() {
  for (int r = 0; r < 10; r++) {

    for (int i = 0; i < 10; i++)
      digitalWrite(ROW_PINS[i], LOW);

    sendTwoBytes(frame[r][1], frame[r][0]);

    digitalWrite(ROW_PINS[r], HIGH);

    delayMicroseconds(800);
  }
}

// ==========================================================
// =================== BUTTON & MODES ========================
// ==========================================================

int mode = 0;

// robust debounce:
static bool buttonState = HIGH;
static bool lastStableState = HIGH;
static unsigned long lastChangeTime = 0;

// ==========================================================
// ======================== SETUP ============================
// ==========================================================

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  for (int i = 0; i < 10; i++) {
    pinMode(ROW_PINS[i], OUTPUT);
    digitalWrite(ROW_PINS[i], LOW);
  }
}

// ==========================================================
// ===================== ANIMATION 0 =========================
// ✨ Random Smooth Twinkle Field
// ==========================================================

float sparkle[10][10];

void animationSparkle() {
  clearFrame();

  for (int y = 0; y < 10; y++) {
    for (int x = 0; x < 10; x++) {

      float target = random(0, 100);
      sparkle[x][y] = sparkle[x][y] * 0.85 + target * 0.15;

      if (sparkle[x][y] > 60) {
        setPixel(x, y, 1);
      }
    }
  }
}

// ==========================================================
// ===================== ANIMATION 1 =========================
// 🌊 Smooth horizontal wave
// ==========================================================

int waveT = 0;

void animationWave() {
  clearFrame();

  for (int y = 0; y < 10; y++) {
    for (int x = 0; x < 10; x++) {

      float v = sin((x + waveT) * 0.6 + y * 0.15);

      if (v > 0.2)
        setPixel(x, y, 1);
    }
  }

  waveT++;
  if (waveT > 2000) waveT = 0;
}

// ==========================================================
// ===================== ANIMATION 2 =========================
// 🐍 Snake-Style Spiral Sweep
// ==========================================================

// Spiral position list (precomputed)
int spiralX[100];
int spiralY[100];
bool spiralBuilt = false;

void buildSpiral() {
  if (spiralBuilt) return;

  int left = 0, right = 9, top = 0, bottom = 9;
  int index = 0;

  while (left <= right && top <= bottom) {
    // top row
    for (int x = left; x <= right; x++) {
      spiralX[index] = x;
      spiralY[index] = top;
      index++;
    }
    top++;

    // right column
    for (int y = top; y <= bottom; y++) {
      spiralX[index] = right;
      spiralY[index] = y;
      index++;
    }
    right--;

    if (top <= bottom) {
      // bottom row
      for (int x = right; x >= left; x--) {
        spiralX[index] = x;
        spiralY[index] = bottom;
        index++;
      }
      bottom--;
    }

    if (left <= right) {
      // left column
      for (int y = bottom; y >= top; y--) {
        spiralX[index] = left;
        spiralY[index] = y;
        index++;
      }
      left++;
    }
  }

  spiralBuilt = true;
}

int spiralHead = 0;

void animationSpiral() {
  clearFrame();

  buildSpiral();

  // draw a growing snake of length L
  const int L = 25; // length of visible segment

  for (int i = 0; i < L; i++) {
    int idx = (spiralHead - i + 100) % 100;
    setPixel(spiralX[idx], spiralY[idx], 1);
  }

  spiralHead++;
  if (spiralHead >= 100) spiralHead = 0;
}

// ==========================================================
// ========================== LOOP ===========================
// ==========================================================

void loop() {

  // ----------- Button debounce -----------
  int raw = digitalRead(BUTTON_PIN);

  if (raw != buttonState) {
    buttonState = raw;
    lastChangeTime = millis();
  }

  if ((millis() - lastChangeTime) > 40) {
    if (buttonState != lastStableState) {
      lastStableState = buttonState;

      if (buttonState == LOW) {  // press event
        mode++;
        if (mode > 2) mode = 0;
      }
    }
  }

  // ----------- Run animations -----------
  if (mode == 0) animationSparkle();
  else if (mode == 1) animationWave();
  else animationSpiral();

  refreshDisplay();
}
