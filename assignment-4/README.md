# Sonar Image Processing Analyzer

This C program processes sonar images represented as **N × N matrices of intensity values (0–255)** to analyze whale movements. The program performs **matrix generation, in-place rotation, and in-place 3×3 smoothing filtering** using **pointer arithmetic**. It demonstrates programming concepts like **pointers, functions, loops, control flow, and memory-efficient computation**.

---

## Features

- **Generate Random Sonar Matrix**: Creates an N × N matrix with random intensity values between 0 and 255.
- **Rotate Matrix 90° Clockwise**: In-place rotation using pointer arithmetic and layer-wise swapping of values.
- **Apply 3×3 Smoothing Filter**: Replaces each element with the average of itself and its valid neighbors using O(N) extra space (no additional N × N array).
- **Pointer-Based Access**: All operations are performed using pointers only — no array indexing (`matrix[i][j]`) is used.
- **Memory Efficient**: Extra space limited to O(N), suitable for memory-constrained environments like onboard marine research systems.
- **Proper Input Validation**: Ensures matrix size is between 2 and 10.

---

## Input Format

- Enter matrix size (2–10): 3

---

## Output Format

- **Original Randomly Generated Matrix**  
- **Matrix after 90° Clockwise Rotation**  
- **Matrix after Applying 3×3 Smoothing Filter**

Example:

The Original matrix:
12 60 90
200 150 30
10 220 180

The Rotated matrix:
10 200 12
220 150 60
180 30 90

The Smoothed matrix:
145 115 80
125 105 78
145 90 67

---

## Usage

### Compile
```bash
gcc sonar_matrix.c -o sonar
