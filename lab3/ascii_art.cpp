#include <iostream>
using namespace std;

// B1: Print N stars
void stars(int N) {
    for (int i = 0; i < N; i++) cout << "*";
    cout << endl;
}

// B2: Print N spaces
void spaces(int N) {
    for (int i = 0; i < N; i++) cout << " ";
}

// B3: Print A dots and B stars followed by A dots
void dotsstars(int A, int B) {
    for (int i = 0; i < A; i++) cout << ".";
    for (int i = 0; i < B; i++) cout << "*";
    for (int i = 0; i < A; i++) cout << ".";
    cout << endl;
}

// B4: Print sequence (count down and up simultaneously)
void sequence(int A, int B) {
    while (A > 0 && B <= A) {
        cout << A << " " << B << endl;
        A -= 2;
        B++;
    }
}

// B5: Draw right-angled triangle using dotsstars
void triangle(int A, int B) {
    for (int i = 0; i < A; i++) {
        dotsstars(i, (2 * (A - i)) - 1);
    }
}

// B6: Draw a triangle pointing up
void uptriangle(int A, int B) {
    for (int i = A; i > 0; i--) {
        dotsstars(i - 1, (2 * (A - i)) + 1);
    }
}

// B7: Draw a diamond
void diamond(int A) {
    uptriangle(A, 1);
    triangle(A, 1);
}

int main() {
    // Test functions
    stars(5);          // B1
    dotsstars(3, 4);   // B3
    sequence(9, 1);    // B4
    triangle(5, 1);    // B5
    uptriangle(5, 1);  // B6
    diamond(5);        // B7

    return 0;
}
