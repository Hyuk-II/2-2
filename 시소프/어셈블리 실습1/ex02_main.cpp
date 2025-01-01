#include <iostream>
using namespace std;

// 어셈블리 함수 선언
extern "C" int BitwiseAnd(int a, int b);
extern "C" int BitwiseOr(int a, int b);
extern "C" int BitwiseXor(int a, int b);
extern "C" int BitwiseNot(int a);

int main() {
    int a = 0x55; // 01010101
    int b = 0xAA; // 10101010
    // 비트 연산 결과 출력
    cout << "a AND b = " << hex << BitwiseAnd(a, b) << endl;
    cout << "a OR b = " << hex << BitwiseOr(a, b) << endl;
    cout << "a XOR b = " << hex << BitwiseXor(a, b) << endl;
    cout << "NOT a = " << hex << BitwiseNot(a) << endl;
    return 0;
}