'''
    The following lines implement arithmetic modulo 10 ** 9 + 7 
    In your solution, please use the functions addMod, subMod, mulMod to do addition, subtraction and multiplication on the answer
    For this question, the model solutions needs only addition and subtraction. 
    Multiplication is also implemented for you -- in case you need it.
'''
MOD = 10 ** 9 + 7
# To make sure your result is correct, use the addMod, subMod and mulMod functions to add, subtract and multiply numbers to compute your answer
def addMod(a, b):
    c = (a + b) % MOD 
    if c < 0:
        c += MOD 
    return c
def subMod(a, b):
    c = (a - b) % MOD 
    if c < 0:
        c += MOD 
    return c
def mulMod(a, b):
    c = (a * b) % MOD 
    if c < 0:
        c += MOD 
    return c
''' 
Complete the following function that takes as input: 
 (i) a 0-indexed array of size n -- representing the city locations
 (ii) a 0-indexed array of size m -- representing potential tower locations
 (iii) an integer d -- the coverage radius of a tower
 and returns as output:
 (i) an array of m integers, where the i^{th} integer denotes the number of ways to place towers at exactly (i+1) out of m locations
     satisfying the constraints in the question
'''
def computeWays(cities, towers, d):
    n, m = len(cities), len(towers)
    # Example that computes (3 ** 20) modulo 10 ** 9 + 7
    ans = 1
    for _ in range(20):
        ans = mulMod(ans, 3) # Observe that ans never exceeds 10 ** 9 + 7 throughout the computation
    print("{0} = 3 ** 20 modulo (10 ** 9 + 7)".format(ans))
    return [0 for _ in range(m)]
# The following lines take care of input and output for you. You may ignore this section.

T = int(input())
for _ in range(T):
    n, m, d = map(int, input().split())
    cities = list(map(int, input().split()))
    towers = list(map(int, input().split()))
    print(*computeWays(cities, towers, d))
