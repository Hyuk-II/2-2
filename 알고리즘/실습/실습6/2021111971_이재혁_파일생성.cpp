#include <fstream>
#include <iostream>
#include <random> // OS의 균일한 난수 생성보장
using namespace std;

int main() {
    random_device rd;  // 시드값을 얻기 위한 random_device
    mt19937 gen(rd()); // random_device 를 통해 난수 생성 엔진을 초기화
    uniform_int_distribution<int> dis(0, 3); // 0 부터 3의 균열한 난수 생성

    ofstream fwriter;          // 텍스트 파일에 입력할 객체
    fwriter.open("input.txt"); // input.txt

    for (int i = 0; i < 100000; i++) {
        switch (dis(gen)) {
        case 0:
            fwriter.write("A", 1);
            break;
        case 1:
            fwriter.write("C", 1);
            break;
        case 2:
            fwriter.write("G", 1);
            break;
        case 3:
            fwriter.write("T", 1);
            break;
        }
    }
    fwriter.close();
}