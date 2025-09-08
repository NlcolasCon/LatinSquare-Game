# Latin Square Game (C)

A terminal-based implementation of the **Latin Square puzzle**, written in C.  
The program loads a partially completed Latin square from a text file, displays it, and allows the user to interactively solve it by entering moves.

---

## Project Explanation
A **Latin square of order n** is an `n x n` grid filled with integers from `1` to `n`, where each number appears exactly once per row and once per column.  

This project demonstrates structured programming in C, including:
- 2D arrays
- File input/output
- User interaction with formatted input
- Validation and error handling
- Modular design with functions

---

### Core Functions
- **readLatinSquare()** → loads puzzle from file  
- **displayLatinSquare()** → prints the square in formatted style (with parentheses for fixed cells)  
- **play()** → interactive gameplay loop  
- **writeLatinSquare()** → saves the current/solved puzzle to output file  

---

## Repository Structure
LatinSquare-Game/
┣ src/
┃ ┗ latinsquare.c
┣ LICENSE
┣ README.md

---

## Features
- Load Latin square puzzles from `.txt` files
- Display board with fixed/user-filled cells
- Interactive solving:
  - `i,j=val` → insert value  
  - `i,j=0` → clear cell  
  - `0,0=0` → save and exit  
- Error handling for invalid moves/inputs
- Save progress or final solution to output file

---

## Technologies
- Language: C (ISO C standard)
- Paradigm: Structured Programming
- Tools: GCC / Clang / Any C IDE

---

## Author
- Developed by Nicolas Constantinou
- 2024

---

## Usage

### Compile
```bash
gcc src/latinsquare.c -o latinsquare

