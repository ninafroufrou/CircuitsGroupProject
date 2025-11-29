// -------------------- Row Pin Assignments (Arduino Nano) --------------------
#define ROW_0 4   // Row 0
#define ROW_1 5   // Row 1
#define ROW_2 6   // Row 2
#define ROW_3 7   // Row 3
#define ROW_4 8   // Row 4
#define ROW_5 9   // Row 5
#define ROW_6 10  // Row 6
#define ROW_7 11  // Row 7
#define ROW_8 12  // Row 8
#define ROW_9 13  // Row 9

// -------------------- Column Assignments (Shift Register outputs) --------------------
// Q0–Q9 from the chained 74HC595s
#define COL_0 0   // Column 0
#define COL_1 1   // Column 1
#define COL_2 2   // Column 2
#define COL_3 3   // Column 3
#define COL_4 4   // Column 4
#define COL_5 5   // Column 5
#define COL_6 6   // Column 6
#define COL_7 7   // Column 7
#define COL_8 8   // Column 8
#define COL_9 9   // Column 9

// -------------------- Matrix State --------------------
// 10 rows × 10 columns
// 0 = off, 1 = on
int matrix[10][10] = {0};