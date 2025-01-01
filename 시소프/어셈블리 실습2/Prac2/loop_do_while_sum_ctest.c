// loop_do_while_sum_ctest.c
#include <stdio.h>

// do-while 루프: 배열의 모든 요소를 더하기
int do_while_loop_sum(int* arr, int n) {
    int i = 0;
    int sum = 0;
    do {
        sum += arr[i];
        i++;
    } while (i < n);
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 각 루프에서 계산된 합을 저장
    int sum_do_while = do_while_loop_sum(arr, n);
     // 결과 출력 및 검증
    printf("Sum using do-while loop: %d\n", sum_do_while);

    return 0;
}
