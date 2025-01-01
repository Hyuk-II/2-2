#include <stdint.h> // 어셈블리 함수 선언
#include <stdio.h>
// extern int32_t SumValsI32_b(int32_t a, int32_t b, int32_t c, int32_t d,
//                             int32_t e, int32_t f, int32_t g, int32_t h);
int main() {
    // int32_t a = 1, b = 2, c = 3, d = 4;
    // int32_t e = 5, f = 6, g = 7, h = 8;
    // int32_t result = SumValsI32_b(a, b, c, d, e, f, g, h);
    // printf("Sum of values: %d\n", result);
    int ar2[6] = {1, 2, 3, 4, 5, 6};
    ar2[1] = ar2[0] + ar2[1];
    ar2[2] = ar2[4] - ar2[ar2[ar2[1]]];
    ar2[3] = ar2[4] / (ar2[4] - ar2[1]);
    ar2[4] = ar2[1] * ar2[3] - (ar2[0] * 2);
    for (int i = 0; i < 6; i++) {
        printf("%d ", ar2[i]);
    }
    return 0;
}