/*
 *  File:       func.c
 *  Author:     Carl B. Smiley
 *  Date:       Nov 11 2020
 *  Course:     Fundamentals of Embedded and Real Time Systems
 *
 * Description: Implementation for Question2 of Assignment04
 */
int func1(int a1, int a2, int a3, int a4, int a5) {
  return a5;
}

void func2() {
    func1(1,2,3,4,5);
}

int main() {
    func2();
}