#include <stdio.h>

// 어셈블리로 구현된 dot_product 함수 선언
extern int dot_product(int* vec1, int* vec2, int n);

int main() {
    // 테스트할 두 벡터 정의
    int vec1[] = {1, 2, 3, 4, 5};
    int vec2[] = {6, 7, 8, 9, 10};
    // 6 14 24 36 50 
    int n = sizeof(vec1) / sizeof(vec1[0]);  // 벡터 길이

    // dot_product 함수 호출
    int result = dot_product(vec1, vec2, n);

    // 결과 출력
    printf("Dot product of vec1 and vec2: %d\n", result);

    return 0;
}
