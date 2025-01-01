// 2021111971 이재혁
// 문제 1번
#include <iostream>
using namespace std;

class BubbleSort {
  public:
    ~BubbleSort() {
        delete[] arr;
    } // 객체가 소멸할 때 동적할당 했던 배열 메모리 반환

    void setArr() { // 정렬 할 배열을 입력받을 메소드
        cout << "배열의 길이 입력 : ";
        cin >> len; // 길이를 입력받아 멤버 변수에 저장

        arr = new int[len]; // 길이 만큼 멤버 포인터 변수에 배열할당

        cout << "배열 입력 : ";
        for (int i = 0; i < len; i++) {
            cin >> arr[i];
        } // 길이개수 만큼 배열 입력
    }

    void printArr() { // 배열을 출력하는 메소드
        for (int i = 0; i < len; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void it_BubbleSort() { // 비순환적 버블정렬
        cout << "-------- 비순환적 버블정렬 --------\n원래 배열" << endl;
        this->printArr();
        // 0번째 index부터 마지막 1개전 index까지
        for (int i = 0; i < len - 1; i++) { // 모든 원소에 대해서 정렬
            int isSorted = 1;               // 정렬여부를 확인할 변수
            for (int j = 0; j < len - i - 1; j++) {
                // 현재 원소부터 정렬횟수 -1 까지 비교
                if (arr[j] >
                    arr[j + 1]) { // 현재원소가 다음원소보다 크다면 위치변경
                    int tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                    isSorted =
                        0; // 원소의 교환이 발생했으면 정렬이 되지 않았던 배열
                }
            }
            if (isSorted) { // 원소의 교환이 없었다면 이미 정렬된 배열
                cout << "정렬 완료" << endl;
                this->printArr();
                break;
            }
            // 정렬상황출력
            cout << i + 1 << "번째 정렬" << endl;
            this->printArr();
        }
    }

    void re_BubbleSort(int n) {
        // 정렬횟수를 매개변수로 전달받아 (길이 - 정렬횟수 - 1) index까지
        // 버블정렬 시행 가장 큰 원소를 오른쪽으로 이동시키기 때문에
        // 정렬횟수만큼 뺀 길이를 다시 정렬
        if (n == 0) { // 처음 정렬을 시작하면 원래 배열 출력
            cout << "--------- 순환적 버블정렬 --------\n원래 배열" << endl;
            this->printArr();
        } else if (n == len) { // n-1번의 비교로 모든 원소를 비교하기 때문에
                               // n번째엔 종료
            return;
        }
        int isSorted = 1; // 정렬여부 확인할 변수
        for (int i = 0; i < len - n - 1; i++) {
            if (arr[i] >
                arr[i + 1]) { // 현재원소가 다음원소보다 크다면 원소교환
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                isSorted = 0; // 원소 교환이 일어났다면 정렬되지 않았던 배열
            }
        }
        if (isSorted) { // 원소교환이 없어다면 정렬되었던 변수
            cout << "정렬 완료" << endl;
            this->printArr();
            return;
        } else {
            // 정렬상황출력
            cout << n + 1 << "번째 정렬" << endl;
            this->printArr();
            // 재귀적으로 다음 정렬 호출
            re_BubbleSort(n + 1);
        }
    }

  private:
    int *arr; // 정렬할 배열의 위치를 알고있는 포인터
    int len;  // 정렬할 배열의 길이정보를 알고있는 포인터
};

int main() {
    BubbleSort b;

    b.setArr();
    b.it_BubbleSort();

    b.setArr();
    b.re_BubbleSort(0);
}

// 배열의 길이 8
// 입력의 원소 30 20 40 10 5 10 30 15
// 입력의 원소 10 9 8 7 6 5 4 3