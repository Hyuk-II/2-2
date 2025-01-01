// 2021111971 이재혁 문제 3
#include <iostream>
#include <string>
using namespace std;

class RBNode {
  private:
    string color;   // Node의 색
    int value;      // Node의 값
    RBNode *parent; // 부모노드
    RBNode *left;   // 왼쪽 자식노드
    RBNode *right;  // 오른쪽 자식노드

  public:
    RBNode(int value = 0, int isRoot = 0) {
        // 매개변수가 2개라면 root 노드
        if (isRoot) { // root 노드라면 흑색으로 설정
            color = "BLACK";
        } else {
            color = "RED";
        }

        this->value = value; // 값 설정
        RBNode *left = NULL;
        RBNode *right = NULL;
        RBNode *parent = NULL;
        // 아직 연결 X
    }

    void toggleColor() { // 현재 설정된 색상 반전
        if (this->color == "RED") {
            this->color = "BLACK";
        } else {
            this->color = "RED";
        }
    }

    void print(int n = 0) { // 트리 출력 n은 현재 출력할 노드의 깊이
                            // 같은 부모를 가지는 형제를 같은 들여쓰기로 표현
                            //   자식2(오른쪽) -> 같은 들여쓰기 형제관계
                            // 부모
                            //   자식1(왼쪽)
                            // 트리가 왼쪽으로 누운 상태

        if (this->right) { // 오른쪽 자식이 존재하면
            // 깊이를 1추가해 노드 출력
            this->right->print(n + 1);
        } else { // 오른쪽 자식이 없다면
                 // 깊이를 1추가해 Nil임을 표시
            for (int i = 0; i < n + 1; i++) {
                cout << "       ";
            }
            cout << "Nil" << endl;
        }

        for (int i = 0; i < n; i++) { // 현재 깊이 만큼 들여쓰기
            cout << "       ";
        }

        // 현재 노드의 값, 색 출력
        cout << this->value << "(" << this->color << ")" << endl;

        // 자식 노드 출력
        if (this->left) { // 왼쪽 자식이 존재하면
            // 깊이를 1 추가해 노드 출력
            this->left->print(n + 1);
        } else { // 왼쪽 자식이 없다면
                 // 깊이를 1추가해 Nil임을 표시
            for (int i = 0; i < n + 1; i++) {
                cout << "       ";
            }
            cout << "Nil" << endl;
        }
    }

    void insert(int v) { // 노드 삽입
        if (this->value < v) {
            // 삽입할 노드의 값이 현재 값보다 클 때
            if (this->right) {
                // 오른쪽 자식이 있다면, 왼쪽 자식에서 삽입
                this->right->insert(v);
            } else {
                // 오른쪽 자식이 없다면, 새로운 노드를 생성해 연결
                RBNode *node = new RBNode(v);
                this->right = node;
                node->parent = this;
                // 삽입노드 기준으로 트리조정
                fixTree(node);
            }
        } else {
            // 삽입할 노드의 값이 현재 노드의 값보다 작을 때
            if (this->left) {
                // 왼쪽 자식이 있다면, 왼쪽 자식에서 삽입
                this->left->insert(v);
            } else {
                // 왼쪽 자식이 없다면, 새로운 노드를 생성해 연결
                RBNode *node = new RBNode(v);
                this->left = node;
                node->parent = this;
                // 삽입노드 기준으로 트리조정
                fixTree(node);
            }
        }
    }

    void turnLeft() {
        RBNode *p = this->parent;          // 현재 노드의 부모노드
        RBNode *gp = this->parent->parent; // 현재 노드의 조부모노드

        if (gp == NULL) { // 부모 노드가 루트면 -> 현재 노드가 루트가 됨
            // 부모 노드의 오른쪽 자식을 현재 노드의 왼쪽 자식으로 변경
            p->right = this->left;
            if (this->left) {
                // 왼쪽 자식이 존재하면 부모노드 변경
                this->left->parent = p;
            }

            // 현재 노드의 왼쪽 자식을 부모노드로 설정
            this->left = p;
            p->parent = this;

            // 현재 노드의 부모 노드 Nil로 설정됨 -> root 노드가 됨
            this->parent = gp;
        } else {
            if (p == gp->left) {
                // 부모가 조부모의 왼쪽 자식일 경우
                // 부모 노드의 오른쪽 자식을 현재 노드의 왼쪽 자식으로 변경
                p->right = this->left;
                if (this->left) {
                    // 왼쪽 자식이 존재하면 부모노드 변경
                    this->left->parent = p;
                }

                // 현재 노드의 왼쪽 자식을 부모노드로 설정
                this->left = p;
                p->parent = this;

                // 부모 노드가 조부모 노드의 왼쪽 자식이었기 때문에
                // 조부모 노드의 왼쪽 자식으로 변경
                gp->left = this;
                this->parent = gp;
            } else {
                // 부모가 조부모의 오른쪽 자식일 경우, 회전 후
                // 조부모 노드의 연결부분만 오른쪽 자식으로 변경
                p->right = this->left;
                if (this->left) {
                    this->left->parent = p;
                }

                this->left = p;
                p->parent = this;

                gp->right = this;
                this->parent = gp;
            }
        }
    }

    void turnRight() {
        RBNode *p = this->parent;          // 현재 노드의 부모노드
        RBNode *gp = this->parent->parent; // 현재 노드의 조부모노드

        if (gp == NULL) { // 부모 노드가 루트면 -> 현재 노드가 루트가 됨
            // 부모 노드의 왼쪽 자식을 현재 노드의 오른쪽 자식으로 변경
            p->left = this->right;
            if (this->right) {
                // 오른쪽 자식이 존재하면 부모노드 변경
                this->right->parent = p;
            }

            // 현재 노드의 오른쪽 자식을 부모 노드로 연결
            this->right = p;
            p->parent = this;

            // 현재 노드의 부모 노드 Nil로 설정됨 -> root 노드가 됨
            this->parent = gp;
        } else {
            if (p == gp->left) { // 부모가 조부모의 왼쪽 자식일 경우

                // 부모 노드의 왼쪽 자식을 현재 노드의 오른쪽 자식으로 변경
                p->left = this->right;
                if (this->right) {
                    // 오른쪽 자식이 존재하면 부모노드 변경
                    this->right->parent = p;
                }

                // 현재 노드의 오른쪽 자식을 부모 노드로 연결
                this->right = p;
                p->parent = this;

                // 부모 노드가 조부모 노드의 왼쪽 자식이었기 때문에
                // 조부모 노드의 왼쪽 자식으로 변경
                gp->left = this;
                this->parent = gp;

            } else {
                // 부모가 조부모의 오른쪽 자식일 경우, 회전 후
                // 조부모 노드의 연결부분만 오른쪽 자식으로 변경
                p->left = this->right;
                if (this->right) {
                    this->right->parent = p;
                }

                this->right = p;
                p->parent = this;

                gp->right = this;
                this->parent = gp;
            }
        }
    }

    void fixTree(RBNode *z) { // 삽입한 노드 기준으로 트리 조정
        if (z->parent) {
            // 조정하고자 하는 노드가 루트 노드가 아닐경우 조정
            // 루트 노드의 조정은 색만 확인

            RBNode *p = z->parent;   // 기준 노드의 부모노드
            RBNode *gp = p->parent;  // 기준 노드의 조부모노드
            if (p->color == "RED") { // 부모노드가 RED -> 조정필요
                if (p == gp->left) { // 부모가 왼쪽 자식일 경우
                    if (gp->right && gp->right->color == "RED") {
                        // 삼촌노드가 적색 노드일 경우
                        p->toggleColor();
                        if (gp->right) {
                            gp->right->toggleColor();
                            // 삼촌노드 흑색으로 설정
                        }
                        gp->toggleColor(); // 조부모 노드 적색으로 설정
                        this->fixTree(gp); // 조부모 노드 기준으로 트리 수정
                    } else {               // 삼촌이 Nil이거나, 흑색노드인 경우
                        if (z == p->right) { // Case 2인 경우
                            z->turnLeft();   // Case 3가 됨
                            z->turnRight();
                            z->toggleColor(); // 조부모가 된 z 흑색으로 설정
                            z->right
                                ->toggleColor(); // 자식이된 노드 적색으로 설정
                        } else { // Case 3의 경우 부모를 기준으로 우회전
                            p->turnRight();
                            p->toggleColor(); // 조부모가 된 p 흑색으로 설정
                            p->right
                                ->toggleColor(); // 자식이된 노드 적색으로 설정
                        }
                    }
                } else { // 부모가 오른쪽 자식일 경우
                    if (gp->left && gp->left->color == "RED") {
                        // 삼촌노드가 적색 노드일 경우
                        p->toggleColor(); // 부모노드 흑색으로 설정
                        if (gp->left) {
                            gp->left->toggleColor();
                            // 삼촌노드 흑색으로 설정
                        }
                        gp->toggleColor();  // 조부모 노드 적색으로 설정
                        this->fixTree(gp);  // 조부모 노드 기준으로 트리 수정
                    } else {                // 삼촌이 Nil이거나, 흑색노드인 경우
                        if (z == p->left) { // Case 2인 경우
                            z->turnRight(); // Case 3가 됨
                            z->turnLeft();
                            z->toggleColor(); // 조부모가 된 z 흑색으로 설정
                            z->right
                                ->toggleColor(); // 자식이된 노드 적색으로 설정
                        } else { // Case 3의 경우 부모를 기준으로 좌회전
                            p->turnLeft();
                            p->toggleColor(); // 조부모가 된 p 흑색으로 설정
                            p->left
                                ->toggleColor(); // 자식이된 노드 적색으로 설정
                        }
                    }
                }
            }
        }

        // 루트 노드 흑색으로 설정
        RBNode *tmp = this;
        while (tmp->parent) {
            tmp = tmp->parent;
        }
        tmp->color = "BLACK";
    }

    // 트리가 조정되면 root노드가 가리키는 값이 최상위 노드가 아닐 수 있음
    RBNode *getRoot() {
        RBNode *tmp = this;   // 현재 노드부터
        while (tmp->parent) { // 부모가 Nil일 때 까지, 즉 루트노드까지 이동
            tmp = tmp->parent;
        }
        return tmp; // 루트 노드 반환
    }

    RBNode *buildTree(int n) { // 트리 생성
        RBNode *root;
        int input;
        cout << "노드 입력 >> ";
        cin >> input;
        cout << "-----Root 생성-----" << endl;
        root = new RBNode(input, 1); // 루트 생성
        root->print();

        for (int i = 0; i < n - 1; i++) {
            cout << "노드 입력 >> ";
            cin >> input;
            cout << "-----" << input << " 삽입-----" << endl;
            root->insert(input);    // 입력받은 값으로 노드 삽입
            root = root->getRoot(); // 루트 노드 최신화
            root->print();          // 트리 확인
        }

        return root; // 루트 노드 반환
    }
};

int main() {
    RBNode *root;
    int input;

    cout << "노드 개수 입력 >> ";
    cin >> input;
    root = root->buildTree(input);
}
// 20 15 14 12 13 1