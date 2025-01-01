#include <stdio.h>
// NASM에서 구현된 함수 선언
extern void simd_vector_mul_sum(float *a, float *b, float *result, float *sum);

int main() {
    // 데이터 초기화
    float a[4] = {1.0, 2.0, 3.0, 4.0}; // 첫 번째 벡터
    float b[4] = {5.0, 6.0, 7.0, 8.0}; // 두 번째 벡터
    float result[4];                   // 원소별 곱셈 결과 저장 배열
    float sum = 0.0;                   // 합계를 저장할 변수

    // NASM에서 작성된 SIMD 함수 호출
    simd_vector_mul_sum(a, b, result, &sum);
    // 결과 출력
    printf("Result vector: [%f, %f, %f, %f]\n", result[0], result[1], result[2],
           result[3]);
    printf("Sum: %f\n", sum);
    return 0;
}