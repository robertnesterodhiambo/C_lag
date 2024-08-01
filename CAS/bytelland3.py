import os

MOD = 10**9 + 7

def count_ways_to_place_towers(n, m, d, cities, towers, coverage_file):
    # Initialize the DP table with zeroes
    dp = [[0] * (m + 1) for _ in range(m + 1)]
    dp[0][0] = 1  # Base case: 1 way to place 0 towers with 0 cities covered
    
    # Array to store the result for each number of towers
    result = [0] * m

    # Open the coverage file for writing coverage details
    with open(coverage_file, 'w') as f_coverage:
        for i in range(1, m + 1):
            # Compute coverage range for the current tower
            coverage_start = towers[i - 1] - d
            coverage_end = towers[i - 1] + d
            
            # Find the range of cities covered by the current tower
            start_city_idx = 0
            while start_city_idx < n and cities[start_city_idx] < coverage_start:
                start_city_idx += 1
            
            end_city_idx = start_city_idx
            while end_city_idx < n and cities[end_city_idx] <= coverage_end:
                end_city_idx += 1
            
            covered_cities = end_city_idx - start_city_idx

            # Write the coverage details to the file
            f_coverage.write(f"Tower {i}: Coverage range [{coverage_start}, {coverage_end}], Covered cities: {covered_cities}\n")
            
            # Update DP table based on the number of towers and covered cities
            for k in range(1, i + 1):
                dp[i][k] = dp[i - 1][k] % MOD
                if covered_cities >= k:
                    dp[i][k] = (dp[i][k] + dp[i - 1][k - 1]) % MOD

            # Store the result for the current number of towers
            result[i - 1] = dp[i][i]

    return result

def process_input(input_file, coverage_file):
    with open(input_file, 'r') as f:
        lines = f.read().strip().split('\n')
    
    C = int(lines[0])
    index = 1
    results = []
    
    for _ in range(C):
        n, m, d = map(int, lines[index].split())
        cities = list(map(int, lines[index + 1].split()))
        towers = list(map(int, lines[index + 2].split()))
        index += 3
        results.append(count_ways_to_place_towers(n, m, d, cities, towers, coverage_file))
    
    return results

def main():
    base_dir = '/home/dragon/Git/C_lag/CAS/test_data'
    folders = ['01', '02', '03', '04', '05']
    
    for folder in folders:
        input_file = os.path.join(base_dir, folder, 'input')
        output_file = os.path.join(base_dir, folder, 'output')
        coverage_file = os.path.join(base_dir, folder, 'coverage.txt')
        
        print(f"Processing {input_file}...")
        results = process_input(input_file, coverage_file)
        
        with open(output_file, 'w') as f:
            for result in results:
                f.write(' '.join(map(str, result)) + '\n')

if __name__ == '__main__':
    main()
