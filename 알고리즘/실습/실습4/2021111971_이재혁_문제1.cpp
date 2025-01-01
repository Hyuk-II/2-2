// 2021111971 이재혁 문제1

#include <cstdlib> // 난수 생성을 위한 라이브러리
#include <ctime>   // 난수 생성을 위한 라이브러리
#include <iostream>
using namespace std;

int num[100001] = {0};
// 난수의 발생여부를 저장할 배열
// index에 해당하는 난수가 발생했다면 1, 발생하지 않았다면 0의 값 저장

class Find {
  public:
    Find() { // 1000개의 고유한 난수를 생성하여 배열에 저장
        int i = 0;
        while (i < 1000) {
            int n = rand() % 100000 + 1;
            // 1 ~ 100000 사이의 난수 생성
            if (num[n] == 0) { // 처음 발생한 난수라면
                arr[i] = n;    // 배열에 추가
                num[n] = 1;    // 난수가 생성됐음을 표시
                i++;           // 다음에 추가할 위치로 이동
            }
        }
    }

    void Minimum() { // 배열에서 최솟값을 찾아 출력하는 메소드
        cout << "----- Minimum() -----" << endl;
        int min = arr[0]; // 최솟값을 첫 번째 배열 값으로 초기화
        for (int i = 1; i < 1000; i++) {
            if (arr[i] < min) { // 더 작은 값이 발견되면 최솟값 갱신
                min = arr[i];
            }
        }
        cout << "배열의 최솟값 : " << min << endl;
    }

    void Maximun() { // 배열에서 최댓값을 찾아 출력하는 메소드
        cout << "----- Maximum() -----" << endl;
        int max = arr[0]; // 최댓값을 첫 번째 배열 값으로 초기화
        for (int i = 1; i < 1000; i++) {
            if (arr[i] > max) { // 더 큰 값이 발견되면 최댓값 갱신
                max = arr[i];
            }
        }
        cout << "배열의 최댓값 : " << max << endl;
    }

    void FindMinMax() { // 배열에서 최솟값과 최댓값을 모두 찾아 출력하는 메소드
        cout << "----- FindMinMax() -----" << endl;
        int max = arr[0]; // 최댓값을 첫 번째 배열 값으로 초기화
        int min = arr[0]; // 최솟값을 첫 번째 배열 값으로 초기화
        for (int i = 1; i < 1000; i++) {
            if (arr[i] > max) { // 더 큰 값이 발견되면 최댓값 갱신
                max = arr[i];
            } else if (arr[i] < min) { // 더 작은 값이 발견되면 최솟값 갱신
                min = arr[i];
            }
            // 최댓값을 찾았다면 그 값은 최솟값이 될 수 없으므로
            // else if문을 사용해 실행시간 최적화
        }
        cout << "배열의 최솟값 : " << min << endl;
        cout << "배열의 최댓값 : " << max << endl;
    }

    void print() {
        cout << "index 0 : " << arr[0] << endl;
        cout << "index 999 : " << arr[999] << endl;
    }

    void merge(int left, int mid, int right) {
        int *list;
        list = new int[right - left + 1];

        int start1 = left;
        int start2 = mid + 1;
        int index = 0;

        while (start1 <= mid && start2 <= right) {
            if (arr[start1] < arr[start2]) {
                list[index++] = arr[start1++];
            } else {
                list[index++] = arr[start2++];
            }
        }

        if (start1 > mid) {
            for (int i = start2; i <= right; i++) {
                list[index++] = arr[i];
            }
        } else {
            for (int i = start1; i <= mid; i++) {
                list[index++] = arr[i];
            }
        }

        for (int i = 0; i < index; i++) {
            arr[left + i] = list[i];
        }
        delete[] list;
    }

    void re_MergeSort(int left, int right) {
        if (left < right) {
            int mid = (left + right) / 2;
            this->re_MergeSort(left, mid);
            this->re_MergeSort(mid + 1, right);
            this->merge(left, mid, right);
        }
    }

  private:
    int arr[1000];
};

int main() {
    srand((unsigned int)time(NULL));
    Find f;
    f.Minimum();
    f.Maximun();
    f.FindMinMax();

    cout << "정렬 후 0, 999 번 index 확인" << endl;
    f.re_MergeSort(0, 999);
    f.print();
}