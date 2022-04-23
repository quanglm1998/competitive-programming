n = int(input())
a = list(map(int,input().split(' ')))
res = 0
MOD = 1000000007

for i in range(n):
  cur = 1
  for j in range(i, -1, -1):
    # print(i, j, cur)
    cur = pow(a[j], cur)
    res += cur % MOD

print(res)
