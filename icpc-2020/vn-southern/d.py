a = int(input())
b = int(input())

f = 0
cur = 1
for i in range(a, b + 1):
    cur = cur * (i % 9) % 9
    if cur == 0:
        f = 1
        break

if cur == 0:
    cur = 9

print(cur)