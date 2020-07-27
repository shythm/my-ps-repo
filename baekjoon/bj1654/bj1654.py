from sys import stdin, stdout

(K, N) = (int(p) for p in stdin.readline().rstrip().split())
L = []
for i in range(K):
    L.append(int(stdin.readline()))

left = 1
right = max(L)

if (sum([l // right for l in L]) >= N):
    stdout.write(str(right))
else:
    while (left != right):
        mid = (left + right) // 2
        count = sum([l // mid for l in L])
        # print(left, mid, right, ':', count)
        if (count >= N):
            left = mid + 1
        else:
            right = mid

    stdout.write(str(left - 1))