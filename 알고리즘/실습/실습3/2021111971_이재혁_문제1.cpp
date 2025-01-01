// 2021111971 이재혁 문제 1
#include <fstream>
#include <iostream>
using namespace std;

class Palindrome {
  public:
    Palindrome() { // 파일로 부터 문자열을 불러와 배열에 저장한다.
        ifstream fin;
        fin.open("실습3.txt");

        int i = 0;
        char c;
        while ((c = fin.get()) != EOF) {
            content[i] = c;
            i++;
        }
        // 파일의 내용을 전부 읽은 후 줄바꿈을 기준으로 문자열을 나눠
        // 회문을 판별
    }

    void it_check() { // 비 순환적 확인 (반복문)
        // 회문 : 문자열을 뒤집어 "읽어도" 같은 문자열
        // -> 반대로 읽어도 같은 알파벳 순서인지 확인 (대소문자 구분 X, 공백
        // 무시)

        int start = 0; // 문자열의 시작 index
        while (1) {
            char str[100]; // 파일에 있는 문자열
            int i;
            for (i = 0; this->isSentence(start + i); i++) {
                str[i] = content[start + i];
            } // 문자열의 시작 index부터 줄바꿈까지 하나의 문자열로 저장

            for (int j = 0; j < i; j++) {
                if ((int)str[j] > 64 && (int)str[j] < 91) {
                    str[j] = (char)((int)str[j] + 32);
                }
            } // 복사한 문자열을 모두 소문자로 통일

            int isPalindrome = 1; // 회문인지 판별할 변수
            // 문자열을 절반으로 나눴을 때
            int left = 0;      // 왼쪽을 확인할 index
            int right = i - 1; // 오른쪽을 확인할 index
            while (1) {
                if (str[left] != str[right]) {
                    isPalindrome = 0;
                    break;
                } // 문자열의 가장 왼쪽과 가장 오른쪽이 다르다면 회문 X
                while (str[++left] == ' ') {
                }
                while (str[--right] == ' ') {
                }
                // 다음 문자를 확인할 때, 다음번 문자만 비교 -> 공백 무시
                if (left >= right) {
                    break;
                }
                // 왼쪽 오른쪽 index가 교차되었다면 확인 완료
                // left == right -> 문자열의 길이 홀수
                // left > right  -> 문자열의 길이 짝수
            }
            if (isPalindrome) { // 변수의 값이 여전히 1 이면 회문
                // 저장한 문자열을 전부 소문자로 통일했기 때문에 원본의 문자열
                // 출력
                for (int j = start; j < start + i; j++) {
                    cout << content[j];
                }
                cout << " is Palindrome" << endl;
            } else {
                for (int j = start; j < start + i; j++) {
                    cout << content[j];
                }
                cout << " is not Palindrome" << endl;
            }

            start = start + i + 1;
            // i가 잘라낸 문자열의 끝
            // 끝 다음문자는 다음 문자열의 시작,
            // 다음 반복을 위해 시작점 수정
            if (!(this->isSentence(start))) {
                // 시작점이 알파벳이나, 공백문자가 아니라면, 파일의 끝
                // 회문 판별 종료
                break;
            }
        }
    }

    void re_check(int n) { // 순환적 확인 (재귀호출)
        // n번째 index의 값부터 문자열 판별 시작
        // n번째 index 부터 '\n'까지가 하나의 문자열
        if (!(this->isSentence(n))) {
            // n번째 index의 값이 알파벳 또는 공백이 아니라면, 파일의 끝
            // 회문 판별 종료
            return;
        }

        // 비 순환적 확인과 같은 방식, n = start
        while (1) {
            char str[100];
            int i;
            for (i = 0; this->isSentence(n + i); i++) {
                str[i] = content[n + i];
            }

            int isPalindrome = 1;
            int left = 0;
            int right = i - 1;
            while (1) {
                if (str[left] != str[right]) {
                    isPalindrome = 0;
                    break;
                }
                while (str[++left] == ' ') {
                }
                while (str[--right] == ' ') {
                }
                if (left >= right) {
                    break;
                }
            }
            if (isPalindrome) {
                for (int j = n; j < n + i; j++) {
                    cout << content[j];
                }
                cout << " is Palindrome" << endl;
            } else {
                for (int j = n; j < n + i; j++) {
                    cout << content[j];
                }
                cout << " is not Palindrome" << endl;
            }
            n = n + i + 1; // 지금 확인한 다음 index로 시작점 조정
            if (!(this->isSentence(n))) {
                break;
            }
        }
        re_check(n); // 다음 index를 시작으로 재귀호출
    }

    void print() {
        // 문자열이 비어있지 않은 동안 값을 출력
        for (int i = 0; content[i]; i++) {
            cout << content[i];
        }
        cout << endl;
    }

    int isSentence(int n) {
        if ((content[n] > 64 && content[n] < 91) ||
            (content[n] > 96 && content[n] < 123) || content[n] == ' ') {
            return 1;
        } else
            return 0;
    }

  private:
    // 파일로 부터 최대 100개의 글자를 읽어 회문 판별
    // 문장은 줄바꿈으로 구분
    char content[100];
};

int main() {
    Palindrome p;
    cout << "------- 읽어들인 문자열 -------" << endl;
    p.print();
    cout << "-------- 비 순환적 확인 --------" << endl;
    p.it_check();
    cout << "-------- 순환적 확인 ---------" << endl;
    p.re_check(0);
}