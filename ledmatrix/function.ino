void resetMatrix() {
  for (int r = 0; r < 10; r++) {
    for (int c = 0; c < 10; c++) {
      c = constrain(c, 0, 9);   // clamp to valid column range
      matrix[r][c] = 0;
    }
  }
}

// Example: sine wave across 10×10 grid
// Each frame shifts the wave horizontally

void sin1() {
  for (int r = 0; r < 10; r++) {
    int c = (int)(5 + 4 * sin(r * 0.6)); // sine formula
    c = constrain(c, 0, 9);   // clamp to valid column range
    matrix[r][c] = 1;
  }
}

void sin2() {
  for (int r = 0; r < 10; r++) {
    int c = (int)(5 + 4 * sin(r * 0.6 + 0.5));
    c = constrain(c, 0, 9);   // clamp to valid column range
    matrix[r][c] = 1;
  }
}

void sin3() {
  for (int r = 0; r < 10; r++) {
    int c = (int)(5 + 4 * sin(r * 0.6 + 1.0));
    c = constrain(c, 0, 9);   // clamp to valid column range
    matrix[r][c] = 1;
  }
}

void sin4() {
  for (int r = 0; r < 10; r++) {
    int c = (int)(5 + 4 * sin(r * 0.6 + 1.5));
    c = constrain(c, 0, 9);   // clamp to valid column range
    matrix[r][c] = 1;
  }
}

void sin5() {
  for (int r = 0; r < 10; r++) {
    int c = (int)(5 + 4 * sin(r * 0.6 + 2.0));
    c = constrain(c, 0, 9);   // clamp to valid column range
    matrix[r][c] = 1;
  }
}

void sin6() {
  for (int r = 0; r < 10; r++) {
    int c = (int)(5 + 4 * sin(r * 0.6 + 2.5));
    c = constrain(c, 0, 9);   // clamp to valid column range
    matrix[r][c] = 1;
  }
}

void sin7() {
  for (int r = 0; r < 10; r++) {
    int c = (int)(5 + 4 * sin(r * 0.6 + 3.0));
    c = constrain(c, 0, 9);   // clamp to valid column range
    matrix[r][c] = 1;
  }
}

void sin8() {
  for (int r = 0; r < 10; r++) {
    int c = (int)(5 + 4 * sin(r * 0.6 + 3.5));
    c = constrain(c, 0, 9);   // clamp to valid column range
    matrix[r][c] = 1;
  }
}