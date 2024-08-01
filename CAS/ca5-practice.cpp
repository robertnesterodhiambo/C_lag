#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <assert.h>
using namespace std;

/* The following lines implement arithmetic modulo 10 ** 9 + 7 
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
vector<modInt> computeWays(vector<int> &a, vector<int> &b, int d) {
    int n = a.size(), m = b.size(), add = max(a.back(), b.back()) + d + 1;
    a.push_back(add);
    b.push_back(add);
    n += 1; m += 1;
    // dp[i][j] = # of ways to cover all cities to the left tower i with exactly j towers to the left of i (including i)
    vector<vector<modInt> > dp(m, vector<modInt>(m+1, 0));
    // sdp[i][j] = SUM dp[ii][j] over all 0 <= ii <= i (needed only for optimized m^2 \log n, m^2 solutions)
    vector<vector<modInt> > sdp(m, vector<modInt>(m+1, 0));

    // The following lines set up the base cases 
    for (int i=0;i<m;++i) {
        dp[i][1] = a[0] >= b[i] - d;
        sdp[i][1] = (i > 0 ? sdp[i-1][1] : 0) + dp[i][1];
    }
    /*
        The following lines implement three versions of the solution with different time complexities.
        Comment out two of them and keep only one.
        Lines 58-68 implement O(m^3 \log n) solution
    */
    for (int j=2;j<=m;++j) {
        for (int i=0;i<m;++i) {
            // Calculate dp[i][j] using the recurrence
            for (int ii=0;ii<i;++ii) {
                // Check that no city exists between b[ii] + d + 1 and b[i] - d - 1
                int st = lower_bound(a.begin(), a.end(), b[ii] + d + 1) - a.begin();
                int en = upper_bound(a.begin(), a.end(), b[i] - d - 1) - a.begin();
                if (en - st <= 0) dp[i][j] += dp[ii][j-1]; // update dp[i][j]
            }
        }
    }

    /*
        Lines 73-90 implement optimized O(m^2 \log n)
    */
    for (int j=2;j<=m;++j) {
        for (int i=0;i<m;++i) {
            // Calculate dp[i][j] using the recurrence : Find sub-array [istar, i-1] that matters
            // last_uncovered is the index of the first uncovered city to left of b[i]
            int last_uncovered = (int)(lower_bound(a.begin(), a.end(), b[i] - d) - a.begin()) - 1;
            // the desired sub-array is [istar, i-1]
            int istar = 0;
            if (last_uncovered >= 0) {
                istar = lower_bound(b.begin(), b.end(), a[last_uncovered] - d) - b.begin();
            }
            if (istar < i) {
                // Calculate sum in O(1) time using prefix sums
                dp[i][j] = sdp[i-1][j-1] - (istar > 0 ? sdp[istar-1][j-1] : 0);
            } else dp[i][j] = 0;
            // Calculate prefix sums
            sdp[i][j] = (i > 0 ? sdp[i-1][j] : 0) + dp[i][j];
        }
    }

    /*
        Lines 96-109 implement optimized O(m^2) solution (two-pointer style)
    */

    for (int j=2;j<=m;++j) {
        int last_uncovered = -1, istar = 0;
        for (int i=0;i<m;++i) {
            // Calculate dp[i][j] using the recurrence : Find sub-array [istar, i-1] that matters
            // last_uncovered is the index of the first uncovered city to left of b[i]
            while (last_uncovered + 1 < n && a[last_uncovered + 1] < b[i] - d) ++last_uncovered; // update last_uncovered from previous value
            // min_next is the minimum position of the next tower to the left of b[i] (-1, if all towers are ok)
            int min_next = last_uncovered >= 0 ? a[last_uncovered] - d : -1;
            // the desired sub-array is [istar, i-1]
            while (istar < i && b[istar] < min_next) ++istar; // update istar from previous value
            if (istar < i) dp[i][j] = sdp[i-1][j-1] - (istar > 0 ? sdp[istar-1][j-1] : 0); 
            else dp[i][j] = 0;
            sdp[i][j] = (i > 0 ? sdp[i-1][j] : 0) + dp[i][j];
        }
    }

    return vector<modInt>(dp[m-1].begin() + 2, dp[m-1].end());
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    int sn = 0;
    for (int t = 0; t < tc; t++) {
        int n, m, k;
        cin >> n >> m >> k;
        assert(1 <= n && n <= (int)1e5);
        assert(1 <= m && m <= 1200);
        assert(1 <= k && k <= (int)1e9);
        sn += m;
        vector<int> a(n), b(m);
        int pre = 0;
        for (auto &x : a) {
            cin >> x;
            assert(1 <= x && x <= (int)1e9);
            assert(x > pre);
            pre = x;
        }
        pre = 0;
        for (auto &x : b) {
            cin >> x;
            assert(1 <= x && x <= (int)1e9);
            assert(x > pre);
            pre = x;
        }
        auto vec = computeWays(a, b, k);
        int sz = vec.size();
        for (int i=0;i<sz;++i) {
            cout << vec[i] << " \n"[i==sz-1];
        }
    }
    assert(sn <= (int)2400);
    // cerr << sn << " total size\n";
}
