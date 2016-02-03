from math import exp, floor
e = exp(1)
for n in range(1, 14):
    threshold = int(n/e)
    print(' '.join(map(str, [0 if i < threshold else n if i == n-1 else (n-1) // (n-i) for i in range(n)])))
