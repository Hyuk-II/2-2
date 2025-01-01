// 202111971 이재혁

#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int minus(int a, int b) {
    return a - b;
}

int main() {
    int sum = add(3, 5);
    int diff = minus(3, 5);
    printf("Sum : %d\n", sum);
    printf("Minus : %d\n", sum);
    return 0;
}