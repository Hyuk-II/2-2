// 2021111971 이재혁 문제2
#include <chrono> // 함수 시간측정을 위한 라이브러리
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;
using namespace chrono;

class PatternWriter {
  private:
    int n, m;
    string text;
    char *pattern;

  public:
    PatternWriter(int textLen, int patternLen) {
        random_device rd;  // 시드값을 얻기 위한 random_device
        mt19937 gen(rd()); // random_device 를 통해 난수 생성 엔진을 초기화

        uniform_int_distribution<int> dis(0, 3); // 0 부터 3의 균열한 난수 생성
        n = textLen, m = patternLen;
        // input으로 부터 n개의 문자를 읽어와 text로 사용
        ifstream r("input.txt");
        getline(r, text);
        text = text.substr(0, n);

        pattern = new char[m];
        for (int i = 0; i < m; i++) {
            switch (dis(gen)) { // 생성한 난수에 따라 4개의 문자 중 하나로 설정
            case 0:
                pattern[i] = 'A';
                break;
            case 1:
                pattern[i] = 'C';
                break;
            case 2:
                pattern[i] = 'G';
                break;
            case 3:
                pattern[i] = 'T';
                break;
            }
        }
        // 길이가 m인 랜덤 패턴

        cout << "Find " << pattern << endl;
        // 현재 어떤 패턴이 설정되어 있는지 확인
    }

    void BruteForce(int file = 0) {
        cout << "BruteForce" << endl;
        system_clock::time_point start_time = system_clock::now();
        ofstream writer;
        if (file) {                       // 매개변수가 있다면
            writer.open("output_b2.txt"); // output_b2에 작성
        } else {                          // 없다면
            writer.open("output_b1.txt"); // output_b2에 작성
        }
        writer << pattern << " : "; // 현재 패턴 기록

        for (int i = 0; i < n; i++) {
            if (text[i] == pattern[0]) {
                // text의 문자가 pattern의 첫글자와 같다면
                // pattern 길이 만큼 문자비교
                int isMatching = 1; // 매칭여부를 저장하는 변수
                for (int j = 1; j < m; j++) {
                    if (text[i + j] != pattern[j]) {
                        // 만약 중간에 다른 값이 들어있다면
                        isMatching = 0; // 매칭 X
                        break;
                    }
                }
                if (isMatching) {
                    // 문자열이 매칭되었다면 파일에 시작 인덱스 작성
                    writer << i << " ";
                }
            }
        }

        writer << endl;

        system_clock::time_point end_time = system_clock::now();
        nanoseconds nano = end_time - start_time;
        cout << "걸린시간(nano sec) : " << nano.count() << endl;
    }

    void KMP(int file = 0) {
        cout << "KMP" << endl;
        system_clock::time_point start_time = system_clock::now();

        ofstream writer;
        if (file) {                       // 매개변수가 있다면
            writer.open("output_k2.txt"); // output_k2에 작성
        } else {                          // 없다면
            writer.open("output_k1.txt"); // output_k1에 작성
        }
        writer << pattern << " : "; // 현재 패턴 기록

        int *table; // Pattern의 최대 접두부를 저장하는 배열
        table = new int[m];

        int preIndex = 0; // 접두사 시작 인덱스
        table[0] = 0;     // 첫 글자의 최대 접두부는 0
        for (int sufIndex = 1; sufIndex < m; sufIndex++) {
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
        for (int i = 0; i < n; i++) {
            while (pindex > 0 && text[i] != pattern[pindex]) {
                // pattern 시작 위치 조정
                pindex = table[pindex - 1];
                // pindex가 현재 위치에서 접두부와 겹치는 부분이 있다면
                // 그 접두부 다음 값 부터 다시 비교
            }
            if (text[i] == pattern[pindex]) {
                pindex++; // 매칭된 index + 1 = 매칭되는 길이
                if (pindex == m) {
                    // 문자열이 매칭되었다면 파일에 시작 인덱스 작성
                    writer << i << " ";
                }
            }
        }

        system_clock::time_point end_time = system_clock::now();
        nanoseconds nano = end_time - start_time;
        cout << "걸린시간(nano sec) : " << nano.count() << endl;
        delete[] table;
    }

    void setPattern(string p) {
        // 새로운 문자열로 패턴 세팅
        delete[] pattern;
        m = p.length();
        pattern = new char[m];
        for (int i = 0; i < m; i++) {
            pattern[i] = p[i];
        }
    }
};

int main() {
    int n, m;
    cout << "n : text 길이, m : pattern 길이, 입력 (n >= m) >> ";
    cin >> n >> m;

    PatternWriter p(n, m);
    // text길이가 n, pattern 길이가 m인 무작위 염기서열 탐색
    p.BruteForce();
    p.KMP();

    cout << "======== Find ACCGTAT ========" << endl;
    p.setPattern("ACCGTAT");
    p.BruteForce();
    p.KMP();

    // text길이가 1000~100000, pattern 길이가 5~40인 무작위 염기서열 탐색
    for (int i = 1000; i <= 100000; i *= 10) {
        for (int j = 5; j <= 40; j += 5) {
            cout << "=== text length : " << i << " pattern length : " << j
                 << " ===" << endl;
            PatternWriter p2(i, j);
            // ouput_b2, k2 에 기록
            p2.BruteForce(2);
            p2.KMP(2);
        }
    }
}