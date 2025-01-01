#include <stdio.h>

int main() {
    int a = -9;
    // 1을 4byte의 최상위 위치인 32번째 칸으로 이동
    // & 연산시 a의 최상위 비트의 결과가 출력된다.
    if (a & (1 << 31)) {
        // MSB == 1 : 음수
        printf("MSB : 1 (음수)\n");
    } else {
        // MSB == 0 : 양수
        printf("MSB : 0 (양수)\n");  
    }

    printf("a / 8: %d\n", a / 8);
    printf("a >> 3: %d\n", a >> 3);
    // division과 shift의 연산결과를 출력

    if (a / 8 == a >> 3) { // 두 연산을 비교
        printf("a / 8 and a >> 3 are the same.\n");
    } else {
        printf("a / 8 and a >> 3 are different.\n");
    }
}