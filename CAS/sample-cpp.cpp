#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <assert.h>
using namespace std;

/* The following lines implement arithmetic modulo 10^9 + 7 
    In your solution, you can pretend modInt is a normal integer and use normal arithmetic : addition, subtraction and multiplication
    For this question, the model solutions needs only addition and subtraction. 
    Multiplication is also implemented for you -- in case you need it.
*/
const int MOD = (int)1e9 + 7;
struct modInt {
    int val;
    modInt(long long x = 0) {
        x %= MOD;
        if (x < 0) x += MOD;
        val = x;
    }
};
void operator+=(modInt &a, modInt b) {
    a.val += b.val;
    if (a.val >= MOD) a.val -= MOD;
}
void operator-=(modInt &a, modInt b) {
    a.val -= b.val;
    if (a.val < 0) a.val += MOD;
}
modInt operator+(modInt a, modInt b) {a += b; return a;}
modInt operator-(modInt a, modInt b) {a -= b; return a;}
modInt operator*(modInt a, modInt b) {return modInt(a.val * 1LL * b.val);}
void operator*=(modInt &a, modInt b) {a = (a * b);}
ostream& operator<<(ostream &out, modInt a) {out << a.val; return out;}
/* End of modulo operations */

// You may change this to vector<int> also and the pseudo-code printing the output still works (because of auto)!
// If you do so, make sure you return the answer modulo 10^9 + 7 and be careful of overflows, underflows, negative numbers etc.
vector<modInt> computeWays(vector<int> &a, vector<int> &b, int d) {
    int n = a.size(), m = b.size();
    // Here is an example using modInt class to compute 3^{20} modulo 10^9 + 7
    modInt ans = 1;
    for (int i=1;i<=20;++i) {
        ans *= 3; // Because of the way modInt class is implemented, ans never exceeds 10^9 + 6
    }
    cout << ans << " = 3 ** 20 modulo 10 ** 9 + 7\n";
    // A good rule of thumb : whatever variable represents the answer in your program, declare it to be `modInt` instead of `int`
    // You should only use the operators : +, -, +=, -=, *, *= on variables of type modInt (you should not need anything else, in fact model solution does not need multiplication)
    return vector<modInt>(m, modInt(0));
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int t = 0; t < tc; t++) {
        int n, m, d;
        cin >> n >> m >> d;
        vector<int> a(n), b(m);
        for (auto &x : a) cin >> x;
        for (auto &x : b) cin >> x;
        auto vec = computeWays(a, b, d);
        int sz = vec.size();
        for (int i=0;i<sz;++i) {
            cout << vec[i] << " \n"[i==sz-1];
        }
    }
}
