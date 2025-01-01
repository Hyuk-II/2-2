// loop_sum_conversion_test.c 
#include <stdio.h>

// NASM으로 구현된 jump-to-middle 방식의 while 루프
extern int jump_to_middle_loop_sum(int* arr, int n); 

// NASM으로 구현된 guarded-do 방식의 for 루프
extern int guarded_do_loop_sum(int* arr, int n);

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    // NASM에서 구현된 각 루프 방식으로 계산된 합을 저장
    int sum_jump_to_middle = jump_to_middle_loop_sum(arr, n);
    int sum_guarded_do = guarded_do_loop_sum(arr, n);

    // 결과 출력 및 검증
    printf("Sum using jump-to-middle loop: %d\n", sum_jump_to_middle);
    printf("Sum using guarded-do loop: %d\n", sum_guarded_do);

    return 0;
}
