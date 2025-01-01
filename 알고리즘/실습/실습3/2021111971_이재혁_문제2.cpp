// 2021111971 이재혁 문제 2
#include <iostream>
using namespace std;

class Heap {
  public:
    // 배열의 값 10개를 입력받아 arr 배열에 저장
    Heap() {
        cout << "배열의 값 10개 입력" << endl;
        for (int i = 0; i < 10; i++) {
            cin >> arr[i];
        }
    }

    // 배열의 현재 상태를 출력
    void print() {
        for (int i = 0; i < 10; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // 주어진 배열을 힙 구조로 만드는 메소드
    void buildHeap() {
        // 0부터 n-1까지의 배열을 힙 구조로 변환
        // 앞에서 부터 노드를 삽입하며 현재 삽입한 노드가 부모 노드보다 크다면
        // 원소교환
        for (int insert = 0; insert < 10; insert++) {
            int child = insert;
            while (child > 0) {
                switch (child % 2) // 현재 삽입할 노드의 위치 확인
                {
                case 1: // 현재 삽입할 노드가 왼쪽 : parent_index = child/2
                    if (arr[child / 2] < arr[child]) {
                        int tmp = arr[child / 2];
                        arr[child / 2] = arr[child];
                        arr[child] = tmp;
                    }
                    child /= 2;
                    break;

                case 0:
                    // 현재 삽입할 노드가 오른쪽 : parent_index = child/2 - 1
                    if (arr[child / 2 - 1] < arr[child]) {
                        int tmp = arr[child / 2 - 1];
                        arr[child / 2 - 1] = arr[child];
                        arr[child] = tmp;
                    }
                    child = child / 2 - 1;
                    break;
                }
            }
            this->print();
        }
    }

    void adjustHeap(int n) {
        // 최대 값을 제거한 후 Heap을 조절하는 메소드
        // 자식 노드의 값 중 큰 값과 비교해 원소를 조정
        int root = 0;
        while (root * 2 + 1 < n) {
            int child = root * 2 + 1;
            if (arr[child] < arr[child + 1])
                child++;

            if (arr[root] < arr[child]) {
                int tmp = arr[root];
                arr[root] = arr[child];
                arr[child] = tmp;
            }
            root = child;
        }
    }

    void HeapSort() {
        // 힙에서 최대값을 계속해서 꺼내 배열의 맨 마지막으로 이동
        // 배열의 크기를 하나씩 줄여가며 그 다음 큰 값은
        // 이전 정렬 때 뽑은 가장 큰 값 앞에 위치
        for (int i = 9; i > 0; i--) {
            // 현재 배열의 최댓값인 처음 원소를 마지막으로 이동
            int tmp = arr[0];
            arr[0] = arr[i];
            arr[i] = tmp;

            // 배열의 마지막 원소를 제외한 부분을 다시 힙 재구성
            this->adjustHeap(i - 1);
            this->print(); // 힙을 다시 재구성 후 배열 확인
        }
        // 원소 2개가 남았을 때 0번 index의 값이 더 크므로 (MAX HEAP)
        // 자식 원소와 교환 후 정렬 종료
        int tmp = arr[0];
        arr[0] = arr[1];
        arr[1] = tmp;

        cout << "------- 정렬완료 --------" << endl;
        this->print(); // 정렬이 완료된 배열 확인
    }

  private:
    int arr[10]; // 배열을 저장하는 멤버 변수
};

int main() {
    Heap h; // Heap 객체 생성 및 배열 입력
    cout << "------- 힙 구조 생성 -------" << endl;
    h.buildHeap(); // 입력된 배열을 힙 구조로 변환

    cout << "---------- 힙 정렬 --------" << endl;
    h.HeapSort(); // 힙 정렬 수행
}
// 4 1 3 2 16 9 10 14 8 7