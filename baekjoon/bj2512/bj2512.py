from sys import stdin, stdout

N = int(stdin.readline())
B = [int(b) for b in stdin.readline().rstrip().split()]
M = int(stdin.readline())

if (sum(B) <= M):
    result = max(B)
else:
    left = 1
    right = max(B)

    while (left != right):
        mid = (left + right) // 2
        s = sum(min(b, mid) for b in B)

        if (s <= M): # true decision
            left = mid + 1
        else: # false decision
            right = mid
    
    result = left - 1

stdout.write(str(result))