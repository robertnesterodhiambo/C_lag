#include <iostream>
using namespace std;

// A1: Print numbers from A to B
void printNumbers(int A, int B) {
    if (A > B) return;
    cout << A << " ";
    printNumbers(A + 1, B);
}

// A2: Print numbers from A to B in steps of 5
void printNumbersInSteps(int A, int B) {
    if (A > B) return;
    cout << A << " ";
    printNumbersInSteps(A + 5, B);
}

// A2: Kilometers to Miles conversion
void printKphToMph(int A, int B) {
    if (A > B) return;
    int mph = (int)(A / 1.609344 + 0.5); // Convert and round
    cout << A << " kph is " << mph << " mph" << endl;
    printKphToMph(A + 5, B);
}

int main() {
    // A1 example
    printNumbers(10, 20);

    // A2 step example
    printNumbersInSteps(10, 90);

    // A2 Kph to Mph conversion example
    printKphToMph(10, 90);

    return 0;
}
