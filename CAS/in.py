MOD = 10**9 + 7

class ModInt:
    def __init__(self, x=0):
        x %= MOD
        if x < 0:
            x += MOD
        self.val = x

    def __iadd__(self, other):
        self.val += other.val
        if self.val >= MOD:
            self.val -= MOD
        return self

    def __isub__(self, other):
        self.val -= other.val
        if self.val < 0:
            self.val += MOD
        return self

    def __add__(self, other):
        result = ModInt(self.val)
        result += other
        return result

    def __sub__(self, other):
        result = ModInt(self.val)
        result -= other
        return result

    def __mul__(self, other):
        return ModInt(self.val * other.val)

    def __imul__(self, other):
        self.val = (self.val * other.val) % MOD
        return self

    def __repr__(self):
        return str(self.val)

def compute_ways(a, b, d):
    n = len(a)
    m = len(b)
    add = max(a[-1], b[-1]) + d + 1
    a.append(add)
    b.append(add)
    n += 1
    m += 1

    dp = [[ModInt(0) for _ in range(m+1)] for _ in range(m)]
    sdp = [[ModInt(0) for _ in range(m+1)] for _ in range(m)]

    for i in range(m):
        dp[i][1] = ModInt(int(a[0] >= b[i] - d))
        sdp[i][1] = dp[i][1] + (sdp[i-1][1] if i > 0 else ModInt(0))

    for j in range(2, m+1):
        for i in range(m):
            last_uncovered = lower_bound(a, b[i] - d) - 1
            istar = 0
            if last_uncovered >= 0:
                istar = lower_bound(b, a[last_uncovered] - d)
            if istar < i:
                dp[i][j] = sdp[i-1][j-1] - (sdp[istar-1][j-1] if istar > 0 else ModInt(0))
            else:
                dp[i][j] = ModInt(0)
            sdp[i][j] = sdp[i-1][j] + dp[i][j]

    return [dp[m-1][j] for j in range(2, m+1)]

def lower_bound(arr, x):
    low, high = 0, len(arr)
    while low < high:
        mid = (low + high) // 2
        if arr[mid] < x:
            low = mid + 1
        else:
            high = mid
    return low

def main():
    input_file_path = r'/home/dragon/Git/C_lag/CAS/test_data/01/input'  # Replace with the actual path to your input file
    output_file_path = r'/home/dragon/Git/C_lag/CAS/test_data/01/output'  # Replace with the actual path to your output file

    with open(input_file_path, 'r') as infile:
        lines = infile.readlines()

    tc = int(lines[0].strip())
    index = 1

    results = []
    for _ in range(tc):
        n, m, k = map(int, lines[index].strip().split())
        index += 1

        a = list(map(int, lines[index].strip().split()))
        index += 1

        b = list(map(int, lines[index].strip().split()))
        index += 1

        result = compute_ways(a, b, k)
        results.append(result)

    with open(output_file_path, 'w') as outfile:
        for result in results:
            outfile.write(" ".join(map(str, result)) + "\n")


if __name__ == "__main__":
    main()
