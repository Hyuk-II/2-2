#include <stdio.h>

// for 루프: 배열의 모든 요소를 더하기
int for_loop_sum(int* arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    // for 루프에서 계산된 합을 저장
    int sum_for = for_loop_sum(arr, n);
    
    // 결과 출력 및 검증
    printf("Sum using for loop: %d\n", sum_for);

    return 0;
}
