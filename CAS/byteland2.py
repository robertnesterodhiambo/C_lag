MOD = 10**9 + 7

def solve_instance(n, m, d, cities, towers):
    dp = [[0] * (m + 1) for _ in range(m + 1)]
    result = [0] * m
    
    for i in range(1, m + 1):
        if towers[i-1] + d < cities[0] or towers[i-1] - d > cities[-1]:
            continue
        dp[i][1] = 1

    for i in range(2, m + 1):
        for j in range(1, i + 1):
            covered = True
            for k in range(n):
                if abs(cities[k] - towers[i-1]) > d:
                    covered = False
                    break
            if not covered:
                continue
            for l in range(1, j + 1):
                dp[i][j] += dp[i-1][l]
                dp[i][j] %= MOD

    for i in range(1, m + 1):
        result[i-1] = dp[m][i]

    return result

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
        print(' '.join(map(str, result)))

if __name__ == "__main__":
    main()
