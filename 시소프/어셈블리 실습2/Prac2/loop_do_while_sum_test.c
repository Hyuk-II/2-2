#include <stdio.h>

extern int do_while_loop_sum(int* arr, int n);  // 외부 어셈블리 함수 선언

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    // do-while 루프를 사용하여 배열 요소의 합 계산
    int sum_do_while = do_while_loop_sum(arr, n);

    // 결과 출력 및 검증
    printf("Sum using do-while loop: %d\n", sum_do_while);

    return 0;
}

