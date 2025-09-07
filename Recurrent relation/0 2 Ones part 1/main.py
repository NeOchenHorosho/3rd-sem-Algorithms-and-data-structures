import math
inp = list(map(int, input().split()))
print(math.comb(inp[0], inp[1])%1000000007)