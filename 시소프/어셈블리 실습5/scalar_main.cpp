#include <stdio.h>
// NASM에서 구현된 함수 선언
extern void scalar_vector_mul_sum(float *a, float *b, float *result,
                                  float *sum);
int main() {
    float a[4] = {1.0, 2.0, 3.0, 4.0};
    float b[4] = {5.0, 6.0, 7.0, 8.0};
    float result[4];
    float sum = 0.0;
    // NASM 함수 호출
    scalar_vector_mul_sum(a, b, result, &sum);
    // 결과 출력
    printf("Result vector: [%f, %f, %f, %f]\n", result[0], result[1], result[2],
           result[3]);
    printf("Sum: %f\n", sum);
    return 0;
}