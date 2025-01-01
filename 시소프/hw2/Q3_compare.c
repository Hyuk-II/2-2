#include <stdio.h>
#include <limits.h> // INT_MAX 사용

int main() {
    int x = INT_MAX; // 가장 큰 int (양수)
    int y = 1;       // 1 양수

    // 변수가 양수인지 확인
    printf("x : %d\n", x);
    printf("y : %d\n", y);

    if(x + y > 0) {
        printf("x + y > 0 입니다.\n%d\n", x+y);
    }
    else {
        printf("x + y < 0 입니다.\n%d\n", x+y);
    }

    printf("%d", 8 & 7);
}