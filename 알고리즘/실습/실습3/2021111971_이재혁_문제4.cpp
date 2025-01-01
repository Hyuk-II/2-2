// 2021111971 이재혁 문제 4

#include <iostream>
using namespace std;

class Merge {
  public:
    // 10개의 값을 가지는 배열 생성
    Merge() {
        cout << "배열원소 10개 입력 >> ";
        for (int i = 0; i < 10; i++) {
            cin >> arr[i];
        }
    }

    void merge(int left, int mid, int right) {
        // index: left ~ mid와 mid+1 ~ right의 병합
        int *list;
        list = new int[right - left + 1];

        int start1 = left;    // 왼쪽 부분배열의 시작 index
        int start2 = mid + 1; // 오른쪽 부분배열의 시작 index
        int index = 0;        // 정렬된 원소가 들어갈 배열의 index

        while (start1 <= mid && start2 <= right) {
            if (arr[start1] < arr[start2]) {
                list[index++] = arr[start1++];
            } else {
                list[index++] = arr[start2++];
            }
        } // 두개의 부분배열들을 비교하면서 작은 것들을 먼저 임시 배열에 저장

        if (start1 > mid) { // 왼쪽 부분배열의 값들이 먼저 다 들어갔다면
            // 오른쪽 부분배열의 값들을 그대로 이어 붙이기
            for (int i = start2; i <= right; i++) {
                list[index++] = arr[i];
            }
        } else { // 오른쪽 부분배열의 값들이 먼저 다 들어갔다면
            // 왼쪽 부분배열의 값들을 그대로 이어 붙이기
            for (int i = start1; i <= mid; i++) {
                list[index++] = arr[i];
            }
        }

        for (int i = 0; i < index; i++) {
            arr[left + i] = list[i];
        } // 임시로 저장한 배열의 순서를 원래 배열에 저장

        this->print(); // 병합 후 현재 배열상태 출력
        delete[] list;
    }

    void re_MergeSort(int left, int right) {
        // 순환적 병합정렬
        // 정렬할 배열의 시작과 끝 index를 매개변수로 전달받는다.
        if (left < right) { // 배열의 범위가 1이상 일때 정렬한다.
            int mid = (left + right) / 2; // 배열을 2부분으로 나눌 중간 index
            this->re_MergeSort(left, mid); // 왼쪽 부분배열을 다시 병합정렬
            this->re_MergeSort(mid + 1, right); // 오른쪽 부분배열 다시 병합정렬
            this->merge(left, mid, right); // 나누었던 부분배열을 병합
        }
    }

    void it_MergeSort() {
        // 비순환적 병합 정렬
        // 병합할 부분배열의 크기를 1부터 2배씩 늘려가며 (분할을 n/2로 하기때문)
        // 병합시행
        for (int size = 1; size <= 9; size += size) {
            // 부분배열의 크기를 1부터 전체배열의 크기까지 2배씩 늘려간다
            for (int start = 0; start <= 9 - size; start += 2 * size) {
                // start : 2개의 부분배열 중 가장 왼쪽에 있는 index
                // 인접한 부분배열이기 때문에 시작과 끝 index를 알면 병합가능
                int mid = start + size - 1;
                // start 부터 시작해 2*size 만큼 이동하면
                // 다음 정렬해야 하는 부분배열들의 시작
                // 따라서 -1을 하면 부분배열들의 마지막 index
                int end = start + 2 * size - 1 < 9 ? start + 2 * size - 1 : 9;

                this->merge(start, mid, end); // 나눈 배열 병합
            }
        }
    }

    void print() {
        for (int i = 0; i < 10; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void setArr() {
        cout << "배열원소 10개 입력 >> ";
        for (int i = 0; i < 10; i++) {
            cin >> arr[i];
        }
    }

  private:
    int arr[10];
};

int main() {
    Merge m;
    cout << "정렬 이전 원소" << endl;
    m.print();
    cout << "-------- 순환적 병합 정렬 --------" << endl;
    m.re_MergeSort(0, 9);
    cout << "----------- 정렬 완료 -----------" << endl;
    m.print();

    m.setArr();
    cout << "------ 비 순환적 병합 정렬 -------" << endl;
    m.it_MergeSort();
    cout << "----------- 정렬 완료 -----------" << endl;
    m.print();
}

// 30 20 40 35 5 50 45 10 25 15