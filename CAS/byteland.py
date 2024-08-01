MOD = 10**9 + 7

def solve_instance(n, m, d, cities, towers):
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    dp[0][0] = 1  # Base case: 1 way to cover 0 cities with 0 towers
    
    for j in range(1, m + 1):
        for i in range(n - 1, -1, -1):
            pos = next((idx for idx, city in enumerate(cities) if city > towers[j - 1] + d), n)
            for k in range(i + 1, pos + 1):
                dp[j][k] = (dp[j][k] + dp[j - 1][i]) % MOD

    return [dp[i][n] for i in range(1, m + 1)]

def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    index = 0
    C = int(data[index])
    index += 1
    
    results = []
    
    for _ in range(C):
        n = int(data[index])
        m = int(data[index + 1])
        d = int(data[index + 2])
        index += 3
        
        cities = list(map(int, data[index:index + n]))
        index += n
        
        towers = list(map(int, data[index:index + m]))
        index += m
        
        result = solve_instance(n, m, d, cities, towers)
        results.append(result)
    
    for result in results:
        print(" ".join(map(str, result)))

if __name__ == "__main__":
    main()
