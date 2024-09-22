#include <iostream>
using namespace std;

// C1: Recursive function to print a sequence like 1 2 3 ... N ... 3 2 1
void printSequence(int N) {
    if (N < 1) return;
    cout << N << " ";
    printSequence(N - 1);
}

// C2: Print the pattern from 1 up to N and back down
void printPattern(int N) {
    if (N == 0) return;
    for (int i = 1; i <= N; i++) cout << i << " ";
    for (int i = N - 1; i > 0; i--) cout << i << " ";
    cout << endl;
}

// C3: Print pattern and sum of integers in each row
void printPatternWithSum(int N) {
    for (int i = 1; i <= N; i++) {
        int sum = 0;
        for (int j = 1; j <= i; j++) {
            cout << j << " ";
            sum += j;
        }
        for (int j = i - 1; j > 0; j--) {
            cout << j << " ";
            sum += j;
        }
        cout << "sum=" << sum << endl;
    }
}

int main() {
    // C1 example: print 1 2 3 4 3 2 1 (for N=4)
    printSequence(4);
    cout << endl;

    // C2 example: print the pattern for N=3
    printPattern(3);

    // C3 example: print pattern with sum
    printPatternWithSum(3);

    return 0;
}
