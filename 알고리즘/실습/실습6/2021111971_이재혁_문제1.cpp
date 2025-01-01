// 2021111971 이재혁 문제1
#include <chrono> // 함수 시간측정을 위한 라이브러리
#include <cmath>  // 해시 연산을 위한 (제곱) 라이브러리
#include <iostream>
#include <string>
using namespace std;
using namespace chrono;

class Matching {
  private:
    char *text;
    char *pattern;
    int tlen;
    int plen;

  public:
    Matching() {
        string input;
        cout << "TextString 입력" << endl;
        getline(cin, input);

        tlen = input.length();
        text = new char[tlen];

        for (int i = 0; i < tlen; i++) {
            text[i] = input[i];
        }

        cout << "PatternString 입력" << endl;
        getline(cin, input);

        plen = input.length();
        pattern = new char[plen];

        for (int i = 0; i < plen; i++) {
            pattern[i] = input[i];
        }
    }

    ~Matching() {
        delete[] text;
        delete[] pattern;
    }

    void BruteForce() {
        cout << "----------- BruteForce -----------" << endl;
        system_clock::time_point start_time = system_clock::now();
        for (int i = 0; i < tlen; i++) {
            if (text[i] == pattern[0]) {
                // text의 문자가 pattern의 첫글자와 같다면
                // pattern 길이 만큼 문자비교
                int isMatching = 1; // 매칭여부를 저장하는 변수
                for (int j = 1; j < plen; j++) {
                    if (text[i + j] != pattern[j]) {
                        // 만약 중간에 다른 값이 들어있다면
                        isMatching = 0; // 매칭 X
                        break;
                    }
                }
                if (isMatching) {
                    // 문자열이 매칭되었다면 범위 출력
                    cout << "Matching" << endl;
                    cout << "TextString[" << i << "] ~ TextString["
                         << i - 1 + plen << "]" << endl;
                }
            }
        }
        system_clock::time_point end_time = system_clock::now();

        nanoseconds nano = end_time - start_time;
        cout << "걸린시간(nano sec) : " << nano.count() << endl;
    }

    void KMP() {
        cout << "-------------- KMP --------------" << endl;
        system_clock::time_point start_time = system_clock::now();
        int *table; // Pattern의 최대 접두부를 저장하는 배열
        table = new int[plen];

        int preIndex = 0; // 접두사 시작 인덱스
        table[0] = 0;     // 첫 글자의 최대 접두부는 0
        for (int sufIndex = 1; sufIndex < plen; sufIndex++) {
            // pattern의 1번 index부터 접미사 시작인덱스
            while (preIndex > 0 && pattern[preIndex] != pattern[sufIndex]) {
                // 접두사와 접미사의 시작을 비교해 겹치는 부분이 있거나
                // 맨 처음 접두사 까지 시작인덱스 변경
                preIndex = table[preIndex - 1];
            }
            if (pattern[preIndex] == pattern[sufIndex]) {
                // 접두사의 시작과 접미사의 시작이 같다면
                table[sufIndex] = ++preIndex;
                // 이전까지 접두부 길이 + 1
            } else {
                // 그렇지 않았다면 preIndex가 pattern의 맨 앞 -> 0
                // 겹치는 부분이 없고, 현재 비교하는 자리도 다름
                table[sufIndex] = preIndex;
            }
        }

        // 접두부 테이블을 활용해 문자열 비교
        int pindex = 0; // pattern 자리를 확인할 index
        // text를 모두 확인하면서 pattern이 존재하는지 확인
        for (int i = 0; i < tlen; i++) {
            while (pindex > 0 && text[i] != pattern[pindex]) {
                // pattern 시작 위치 조정
                pindex = table[pindex - 1];
                // pindex가 현재 위치에서 접두부와 겹치는 부분이 있다면
                // 그 접두부 다음 값 부터 다시 비교
            }
            if (text[i] == pattern[pindex]) {
                pindex++; // 매칭된 index + 1 = 매칭되는 길이
                if (pindex == plen) {
                    // pattern의 길이동안 문자열이 일치했다면
                    // pattern이 포함되어있음

                    cout << "Matching" << endl;
                    // 현재 위치에서 pattern 문자열의 길이 만큼 앞쪽에서
                    // 부터 pattern 존재
                    cout << "TextString[" << (i + 1 - pindex)
                         << "] ~ TextString[" << i << "]" << endl;
                    pindex = table[pindex - 1];
                }
            }
        }
        system_clock::time_point end_time = system_clock::now();

        nanoseconds nano = end_time - start_time;
        cout << "걸린시간(nano sec) : " << nano.count() << endl;
        delete[] table;
    }

    void RabinKarp() {
        cout << "----------- RabinKarp ----------" << endl;
        system_clock::time_point start_time = system_clock::now();
        int *hash; // text 문자의 부분 문자열을 해싱해 배열에 저장
        hash = new int[tlen - plen + 1]; // pattern의 길이 만큼 총 길이가 압축

        hash[0] = 0;         // text의 초기 해싱값 저장
        int q = 1000003;     // 해싱한 값이 1000003(소수)이 넘지 않도록 mod연산
        int patternHash = 0; // pattern의 해싱값 저장

        for (int i = 0; i < plen; i++) {
            // 해싱 방법
            // 현재 문자에 'A'를 빼 적당히 작은 수로 맞춘뒤 (알파벳은 0~25로
            // 설정) 앞자리를 가장 높은 자리로 설정 해 10의 plen-1 제곱부터
            // 한차수씩 내려옴
            hash[0] += (text[i] - 'A' + 1) * (int)pow(10, plen - i - 1) % q;
            hash[0] = hash[0] % q;

            patternHash +=
                (pattern[i] - 'A' + 1) * (int)pow(10, plen - i - 1) % q;
            patternHash = patternHash % q;
        }

        for (int i = 1; i < tlen - plen + 1; i++) {
            // 현재 해싱값은, 이전 해싱값에서 가장 앞자리를 계산해 뺀뒤,
            // 10을 곱해 (이전 해싱값의 두번째 값부터 모두 한자리씩 올라감)
            // 새로운 값(마지막값)을 더한다
            hash[i] =
                (hash[i - 1] -
                 (text[i - 1] - 'A' + 1) * (int)pow(10, plen - 1) % q + q) %
                q;
            // + q 를 하는 이유는 최상위 값을 뺐을 때 음수가 되면
            // 해싱값이 달라질 수 있음
            hash[i] = (hash[i] * 10 + (text[i + plen - 1] - 'A' + 1)) % q;
        }

        for (int i = 0; i < tlen - plen + 1; i++) {
            // hash배열의 값과, pattern의 값과 비교
            if (hash[i] == patternHash) {
                cout << "hashMatcing" << endl;
                // 해시 매칭 발생 (text에서 pattern의 개수와 유사해야 좋은
                // 해싱)
                int isMatching =
                    1; // 해시 매칭된 값이 실제 pattern값인지 확인필요
                for (int j = 0; j < plen; j++) {
                    // 매칭된 위치 부터 text와 pattern을 비교
                    if (text[i + j] != pattern[j]) {
                        isMatching = 0;
                        // 해시매칭된 값의 실제값과, pattern값이 다르면
                        // 해싱한 값이 같은 다른 문자열
                        break;
                    }
                }
                if (isMatching) { // 해시매칭 값이 실제 pattern값 인지 확인
                    cout << "Matching" << endl;
                    cout << "TextString[" << (i) << "] ~ TextString["
                         << i + plen - 1 << "]" << endl;
                }
            }
        }

        system_clock::time_point end_time = system_clock::now();

        nanoseconds nano = end_time - start_time;
        cout << "걸린시간(nano sec) : " << nano.count() << endl;
        delete[] hash;
    }
};

int main() {
    Matching m;
    m.BruteForce();
    m.KMP();
    m.RabinKarp();
}

// A STRING SEARCHING EXAMPLE CONSISTING OF A GIVEN PATTERN STRING
// STRING

// 접두부 테이블 test case
// acbdacba
// acacabacacabacacac
// ababd
// adcbadeadcbadcbadcf
// adcbadcf

// ababacabacaabacaaba
// abacaaba