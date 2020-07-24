# Binary Search Algorithm을 사용할 때 주의할 점
1. 탐색 범위 설정
    * 주어진 문제에 한해 탐색 범위를 적절하게 정한다. 그렇지 않을 경우에는 시간 초과 등의 문제가 생길 수 있다. 꼭 수학적으로 범위를 생각해보자.
1. 어떤 것이 정답이 될 것인지 미리 정해놓는다.
    * `left`와 `right` 중 어떤 것이 `mid`를 넘어가는지 명확하게 정한다.
    * `left`와 `right`의 움직임을 명확하게 정하지 않으면 일반화 되지 않은 채로 이진 탐색이 진행되므로 어떤 예외 상황이 발생할 지 모른다.
    * 백준 2805 문제를 해결하는 중
        ``` python
        left = 0
        right = S
        while (left != right):
            mid = (left + right) // 2
            cutted_tree_length = sum([max(0, v - mid) for v in T])

            if (cutted_tree_length < M):
                right = mid - 1
            elif (cutted_tree_length >= M):
                left = mid + 1

        stdout.write(str(left - 1))
        ```
        에서 `right = mid - 1` 부분을 보자. `right = right - 1` statement가 수행되고 나서 `left`와 `right`가 같아졌을 때 정답이 `left - 1`이 될 수 있을까? 질문을 해보자. 즉, `left - 1`이 답이라는 것을 전제한 후에 `left`와 `right`를 조절해야 한다. 당연한 이야기지만 처음에 이진 탐색을 이용해서 문제를 해결할 때 이 부분을 간과해서 많이 틀렸다.
3. 이것 저것 다 고치고 최적화를 할 만큼 했는데도 시간 초과가 발생한다면 `pypy3`를 사용해보자.
    * 시간 초과가 계속 일어나서 끙끙거리다 정현이가 `pypy3`을 사용하면 해결될 수도 있다 해서 `pypy3`을 이용해서 돌렸더니 허무하게 정답에 이르렀다.