# Student Performance Analyzer

This C program analyzes the academic performance of multiple students based on marks obtained in three subjects. It calculates total marks, average marks, assigns a grade, and displays a performance pattern using stars (`*`) based on the grade. The program demonstrates key programming concepts like **structures, functions, recursion, loops, control flow, and variable scope**.  

---

## Features

- **Input Student Details**: Roll Number, Name, and marks for three subjects.  
- **Calculate Total and Average**: Using arithmetic operators.  
- **Assign Grades**:
  
  | Average | Grade |
  |---------|-------|
  | ≥ 85    | A     |
  | ≥ 70    | B     |
  | ≥ 50    | C     |
  | ≥ 35    | D     |
  | < 35    | F     |
  
- **Display Performance Pattern**: Prints a number of stars based on grade (A: 5, B: 4, C: 3, D: 2).  
- **Skip Performance Stars**: Students with average < 35 will not display stars.  
- **Recursion**: Roll numbers of students are printed using a recursive function.  
- **Proper Input Validation**: Ensures marks are within 0–100.  

---

## Usage

### Compile
```bash
gcc assignment-3/solution3.c -o performance
```
### Run
```bash
./performance
```