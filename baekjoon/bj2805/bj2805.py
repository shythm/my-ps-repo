from sys import stdin, stdout

N, M = (int(p) for p in stdin.readline().rstrip().split())
T = [int(p) for p in stdin.readline().rstrip().split()]

# left, right, mid are associate with a tree cutter height.
left = 0
right = max(T)
while (left != right):
    mid = (left + right) // 2
    cutted_tree_length = sum([max(0, v - mid) for v in T]) # LeLU = max(0, x)
    # print(left, mid, right, '-', cutted_tree_length)
    if (cutted_tree_length < M): # false decision
        # it means that the tree cutter height should be smaller.
        right = mid
    elif (cutted_tree_length >= M): # true decision
        # it means that the tree cutter height should be higher.
        left = mid + 1

stdout.write(str(left - 1))