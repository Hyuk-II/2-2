// 2021111971 이재혁

#include "ex01.h"
#include <iostream>
using namespace std;

void DisplayResults(int a, int b, int c, int d, int r1, int r2) {
    cout << "----- Results for ex01 -----\n";
    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';
    cout << "c = " << c << '\n';
    cout << "d = " << d << '\n';
    cout << "r1 = " << r1 << '\n';
    cout << "r2 = " << r2 << '\n';
    cout << '\n';
}

extern "C" int AddSubI32_a(int a, int b, int c, int d);
// (a + b) - (c + d) + 7
// asm과 link할 함수

int main() {
    int a = 10;
    int b = 40;
    int c = 9;
    int d = 6;
    int r1 = (a + b) - (c + d) + 7;
    int r2 = AddSubI32_a(a, b, c, d);
    DisplayResults(a, b, c, d, r1, r2);
    return 0;
}