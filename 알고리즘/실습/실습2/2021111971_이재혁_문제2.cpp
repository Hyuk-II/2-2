// 2021111971 이재혁
// 문제 2번

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int num[100001] = {0};
// 난수의 발생여부를 저장할 배열
// index에 해당하는 난수가 발생했다면 1, 발생하지 않았다면 0의 값 저장

class QuickSort {
  public:
    QuickSort() { // 객체가 생성될 때, 난수배열을 생성하고, 스택의 마지막
                  // index를 -1로 설정한다
        int i = 0;
        while (i < 10) {
            int n = rand() % 100000 + 1;
            // 1 ~ 100000 사이의 난수 생성
            if (num[n] == 0) { // 처음 발생한 난수라면
                arr[i] = n;    // 배열에 추가
                num[n] = 1;    // 생성된 난수로 표시
                i++;           // 다음에 추가할 위치로 이동
            }
        }
        top = -1; // 스택의 최고 index를 -1로 설정 -> 스택이 비어있음
    }

    void setArr() { // 새로운 난수 배열을 생성하는 메소드
        for (int i = 0; i < 10; i++) {
            num[arr[i]] = 0;
        }
        // 기존 배열에 존재하는 값을 다시 생성되지 않은 값으로 설정
        // arr[i]는 객체가 생성될 때 한번 생성되기 때문에,
        // setArr() 메소드에서 다시 초기화 후 생성해야한다.
        int i = 0;
        while (i < 10) {
            int n = rand() % 100000 + 1;
            if (num[n] == 0) {
                arr[i] = n;
                num[n] = 1;
                i++;
            }
        } // 난수 배열 다시 생성
    }

    void printArr() {
        for (int i = 0; i < 10; i++) {
            cout << arr[i] << "\t";
        }
        cout << endl;
    } // 난수 배열 값 출력

    // 순환적 퀵 정렬 : 정렬한 시작, 끝 index를 매개변수로 받아
    // 정렬 후 새로운 범위로 재귀호출
    void re_QuickSort(int first, int last) {
        // 전달받은 index들이 같거나 이미 교차된 상태라면
        // 더 이상 분할 할 수 없는 상태
        if (first >= last) {
            return;
        }

        // 정렬 전 배열 출력
        cout << "index : " << first << " ~ " << last << " 정렬전" << endl;
        this->printArr();

        // first를 index로 갖는 값을 기준으로 퀵정렬 시행
        int left = first + 1; // 기준 값 보다 작은 값을 확인할 변수
        int right = last;     // 기준 값 보다 큰 값을 확인할 변수

        while (left <= right) {
            // left right가 만났다면 왼쪽에는 기준보다 큰 값
            // 오른쪽에는 기준보다 작은 값이 위치해야함 -> 내림차순 정렬
            // 등호를 포함하는 이유
            // 2개의 값을 정렬할 때 left right가 같아짐
            // left, right 값을 조정하지 않으면 수를 비교하지 않고
            // 값을 교환하기 때문에 기준 값이 더 작아도 오른쪽에 위치할 수 있음
            // 따라서 등호를 추가해 같은 값에서도 left, right값을 조절
            while (left <= last && arr[left] > arr[first]) {
                left++;
            } // 주어진 범위를 넘어가지 않는 선에서 기준값 보다 작은 값을 찾는다
            while (first < right && arr[right] < arr[first]) {
                right--;
            } // 주어진 범위를 넘어가지 않는 선에서 기준값 보다 큰 값을 찾는다

            if (left < right) {
                // left right가 만나지 않았다면 기준보다
                // 작은 값이 교차점의 왼쪽, 큰 값은 교차점의 오른쪽에 위치한다
                // 따라서 두 값을 교환한다 -> 내림차순 정렬
                int tmp = arr[left];
                arr[left] = arr[right];
                arr[right] = tmp;
            }
        }
        // left와 right가 교차되었으면 기준 값을 교차점의 값과 교환한다
        int tmp = arr[first];
        arr[first] = arr[right];
        arr[right] = tmp;
        // right 왼쪽에는 arr[right] 보다 큰 값
        // 오른쪽에는 arr[right] 보다 작은 값이 위치하게 된다

        cout << "정렬 후" << endl;
        this->printArr();

        re_QuickSort(first, right - 1); // 기준 값 왼쪽 배열을 다시 퀵 정렬
        re_QuickSort(left, last); // 기준 값 오른쪽 배열을 다시 퀵 정렬
    }

    // 비순환적 퀵 정렬
    // 정렬해야하는 범위의 index를 stack에 push하고
    // stack에 index가 존재하면 값을 꺼내와 해당하는 범위 만큼 퀵 정렬 시행
    void it_QuickSort() {
        this->s_push(0);
        this->s_push(9);
        // 0~9범위의 퀵정렬 부터 시행

        while (!this->s_empty()) {
            // stack에 정렬해야하는 index범위가 존재하면 퀵 정렬 시행

            int last = this->s_pop();
            int first = this->s_pop();
            // stack은 LIFO 형식이기 때문에 끝 index 먼저 저장

            // 퀵 정렬 시행
            if (first >= last) {
                continue;
            }

            cout << "index : " << first << " ~ " << last << " 정렬전" << endl;
            this->printArr();

            int left = first + 1;
            int right = last;
            while (left <= right) {
                while (left <= last && arr[left] > arr[first]) {
                    left++;
                }
                while (first < right && arr[right] < arr[first]) {
                    right--;
                }
                if (left < right) {
                    int tmp = arr[left];
                    arr[left] = arr[right];
                    arr[right] = tmp;
                }
            }
            int tmp = arr[first];
            arr[first] = arr[right];
            arr[right] = tmp;

            cout << "정렬 후" << endl;
            this->printArr();

            // 1개의 원소로 분할되지 않았으면 stack에 index 범위를 추가해 다음
            // 정렬 시행
            if (first < right - 1) {
                this->s_push(first);
                this->s_push(right - 1);
            }
            if (left < last) {
                this->s_push(left);
                this->s_push(last);
            }
        }
    }

    // 기본적인 stack 연산들
    // stack의 가장 마지막 값을 저장하는 index인 top을 활영해 연산 수행
    // stack 배열 내부에 값은 존재하지만, top index로 값을 덮어쓰고, 반환
    // 값을 논리적으로 관리
    void s_push(int n) { stack[++top] = n; }
    int s_pop() { return stack[top--]; }
    int s_empty() {
        if (top == -1) {
            return 1;
        } else {
            return 0;
        }
    }

  private:
    int arr[10];
    int stack[4];
    // it_QucikSort시 사용할 스택 가능한 좌표의 개수는 10개를 넘을 수 없다
    int top;
    // stack의 마지막 값이 저장된 index -1의 값을 가지면 stack에 값이 없고
    // 0이면 가장 마지막 값이 0번 index에 존재한다는 의미
};

int main() {
    srand((unsigned int)time(NULL));
    QuickSort q;
    cout << "---------- 순환적 퀵 정렬 ----------\n원래배열" << endl;
    q.printArr();
    q.re_QuickSort(0, 9);

    q.setArr();
    cout << "---------- 비순환적 퀵 정렬 ----------\n원래배열" << endl;
    q.printArr();
    q.it_QuickSort();
}