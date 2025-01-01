#include <stdio.h>
// NASM에서 구현된 함수 선언
extern int compare_floats(float a, float b);
extern int compare_doubles(double a, double b);
int main() {
    float f1 = 5.5, f2 = 3.3;
    double d1 = 4.4, d2 = 4.4;
    // float 비교
    int float_result = compare_floats(f1, f2);
    // -2, 1,0, 1 중 하나 출력
    printf("Float comparison result: %d\n", float_result);

    // double 비교
    int double_result = compare_doubles(d1, d2);
    // -2, -1, 0, 1 중 하나 출력
    printf("Double comparison result: %d\n", double_result);
    return 0;
}