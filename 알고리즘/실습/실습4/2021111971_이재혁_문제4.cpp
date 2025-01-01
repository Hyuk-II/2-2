// 2021111971 이재혁 문제 4
#include <iostream> // 표준 입출력을 위한 헤더 파일
using namespace std;

class TreeNode {
  public:
    TreeNode(int v) { // 노드의 값, 자식 노드를 NULL로 설정
        value = v;
        left = NULL;
        right = NULL;
    }

    // 새로운 노드를 트리에 삽입하는 함수
    void insertNode(TreeNode *node) {
        // 삽입할 노드의 값이 현재 노드의 값보다 작은 경우
        // 현재 노드의 왼쪽에 삽입
        if (this->value > node->value) {
            if (this->left) { // 왼쪽 자식이 있으면 왼쪽에서 다시 확인
                this->left->insertNode(node);
            } else { // 왼쪽 자식이 없으면 새로운 노드를 왼쪽에 삽입
                this->left = node;
            }
        } else { // 삽입할 노드의 값이 현재 노드의 값보다 큰 경우
            if (this->right) { // 오른쪽 자식이 있으면 오른쪽에서 다시 확인
                this->right->insertNode(node);
            } else { // 오른쪽 자식이 없으면 새로운 노드를 오른쪽에 삽입
                this->right = node;
            }
        }
    }

    // 특정 값을 가지는 노드를 삭제하는 함수
    TreeNode *deleteNode(TreeNode *node, int value) {
        if (node == NULL) // 삭제할 노드를 찾지 못한 경우
            return node;

        // 삭제할 값이 현재 노드의 값보다 작은 경우, 왼쪽 서브트리에서 탐색
        if (value < node->value)
            node->left = deleteNode(node->left, value);
        // 삭제할 값이 현재 노드의 값보다 큰 경우, 오른쪽 서브트리에서 탐색
        else if (value > node->value)
            node->right = deleteNode(node->right, value);
        else { // 삭제할 값을 찾은 경우
            // 자식이 없거나 한쪽만 있는 경우
            if (node->left == NULL) {
                TreeNode *tmp = node->right; // 오른쪽 자식을 임시로 저장
                free(node);                  // 현재 노드 메모리 해제
                return tmp; // 오른쪽 자식 반환 (왼쪽이 없을 경우)
            }
            if (node->right == NULL) {
                TreeNode *tmp = node->left; // 왼쪽 자식을 임시로 저장
                free(node);                 // 현재 노드 메모리 해제
                return tmp; // 왼쪽 자식 반환 (오른쪽이 없을 경우)
            }

            // 양쪽 자식이 모두 있는 경우, 오른쪽 서브트리에서 가장 작은 값을
            // 찾음
            TreeNode *tmp = minNode(node->right);
            node->value = tmp->value; // 해당 값을 현재 노드로 이동
            node->right =
                deleteNode(node->right, tmp->value); // 해당 노드를 삭제
        }
        return node; // 삭제 후의 노드를 반환
    }

    // 주어진 트리에서 가장 작은 값을 가지는 노드를 찾는 함수
    TreeNode *minNode(TreeNode *root) {
        TreeNode *tmp = root;
        while (tmp->left != NULL) // 왼쪽 자식이 없을 때까지 탐색
            tmp = tmp->left;
        return tmp; // 가장 작은 값을 가지는 노드 반환
    }

    // 트리출력 : 중위순회
    void printTree() {
        cout << this->value << " ";
        if (this->left) { // 왼쪽 자식이 있으면 왼쪽 서브트리 출력
            this->left->printTree();
        }
        if (this->right) { // 오른쪽 자식이 있으면 오른쪽 서브트리 출력
            this->right->printTree();
        }
    }

    // 소멸자: 트리의 모든 노드를 재귀적으로 삭제
    ~TreeNode() {
        if (left) // 왼쪽 자식이 있으면 삭제
            delete left;
        if (right) // 오른쪽 자식이 있으면 삭제
            delete right;
    }

  private:
    int value;       // 현재 노드의 값
    TreeNode *left;  // 왼쪽 자식 노드
    TreeNode *right; // 오른쪽 자식 노드
};

int main() {
    TreeNode *root; // 트리의 루트 노드를 가리킬 포인터
    cout << "10 개의 노드 값 입력 >> ";
    int input;
    cin >> input;
    root = new TreeNode(input); // 첫 번째 입력 값으로 루트 노드 생성
    for (int i = 0; i < 9; i++) { // 9개의 추가 노드를 입력받아 트리에 삽입
        cin >> input;
        root->insertNode(new TreeNode(input)); // 입력받은 값을 삽입
    }

    root->printTree(); // 현재 트리의 노드 값 출력
    cout << endl;

    cout << "------- 6 삭제 ---------" << endl;
    root = root->deleteNode(root, 6); // 값이 6인 노드를 삭제
    root->printTree();                // 노드 삭제 후 트리 출력
    cout << endl;

    cout << "------- 20 삭제 ---------" << endl;
    root = root->deleteNode(root, 20); // 값이 20인 노드를 삭제
    root->printTree();                 // 노드 삭제 후 트리 출력
    cout << endl;

    delete root; // 트리 메모리 해제
}
// 20 6 2 4 16 10 8 12 14 9
