#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
using namespace std;

class Node {
   public:
    int num;
    int dupli;
    Node* left;
    Node* right;
    Node(int& num);
    ~Node();
};

class BinarySearchTree {
   private:
    Node* root;
    void insert(Node*& tree, int num);
    void getStack(Node* tree, stack<int>& stk);

   public:
    BinarySearchTree();
    ~BinarySearchTree();
    void insert(int num);
    void getStack(stack<int>& stk);

    // 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
    // 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
    // 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
    // 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
    // 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
    // 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
    // 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
    void getShow();
    void getShow(Node* tree);
};

Node::Node(int& num) {
    this->num = num;
    this->dupli = 1;
    this->left = NULL;
    this->right = NULL;
}

Node::~Node() {
    if (this->left != NULL)
        delete this->left;
    if (this->right != NULL)
        delete this->right;
}

BinarySearchTree::BinarySearchTree() {
    this->root = NULL;
}

BinarySearchTree::~BinarySearchTree() {
    if (this->root != NULL)
        delete this->root;
}

void BinarySearchTree::insert(int num) {
    if (this->root == NULL) {
        this->root = new Node(num);
    } else {
        if (root->num == num)
            (root->dupli)++;  // NULL이 아니고 같은 숫자면 중첩값 증가
        else
            this->insert(this->root, num);
    }
}

void BinarySearchTree::insert(Node*& tree, int num) {
    if (tree == NULL) {
        tree = new Node(num);
    } else {
        if (tree->num == num) {
            (tree->dupli)++;  // NULL이 아니고 같은 숫자면 중첩값 증가
        } else if (tree->num > num) {
            this->insert(tree->right, num);
        } else {
            this->insert(tree->left, num);
        }
    }
}

void BinarySearchTree::getStack(stack<int>& stk) {
    if (this->root != NULL) {
        this->getStack(this->root, stk);
    }
}

void BinarySearchTree::getStack(Node* tree, stack<int>& stk) {
    if (tree != NULL) {
        getStack(tree->left, stk);
        for (int i = 0; i < tree->dupli; i++) {
            stk.push(tree->num);  // 중첩값만큼 스택에 넣어줌
        }
        getStack(tree->right, stk);
    }
}

void showUnion(stack<int> stkOne, stack<int> stkTwo) {
    cout << "UNION : ";
    while (!stkOne.empty() || !stkTwo.empty()) {
        if (stkOne.top() == stkTwo.top()) {
            cout << stkOne.top() << " ";
            stkOne.pop();
            stkTwo.pop();
        } else if (stkOne.top() < stkTwo.top()) {
            cout << stkOne.top() << " ";
            stkOne.pop();
        } else {
            cout << stkTwo.top() << " ";
            stkTwo.pop();
        }

        if (stkOne.empty()) {
            while (!stkTwo.empty()) {
                cout << stkTwo.top() << " ";
                stkTwo.pop();
            }
        } else if (stkTwo.empty()) {
            while (!stkOne.empty()) {
                cout << stkOne.top() << " ";
                stkOne.pop();
            }
        }
    }
    cout << endl;
    return;
}

void showIntersection(stack<int> stkOne, stack<int> stkTwo) {
    cout << "INTERSECTION : ";
    while (!stkOne.empty() && !stkTwo.empty()) {
        if (stkOne.top() == stkTwo.top()) {
            cout << stkOne.top() << " ";
            stkOne.pop();
            stkTwo.pop();
        } else if (stkOne.top() < stkTwo.top()) {
            stkOne.pop();
        } else {
            stkTwo.pop();
        }
    }
    cout << endl;
    return;
}

int main(int argc, char const* argv[]) {
    clock_t start, finish;
    double duration;
    start = clock();
    int n, m;
    cin >> n >> m;

    BinarySearchTree setA;
    BinarySearchTree setB;

    for (int i = 0; i < n; i++)
        setA.insert(rand() % n);

    for (int i = 0; i < m; i++)
        setB.insert(rand() % m);

    // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ 지워야함 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//
    // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ 지워야함 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//
    // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ 지워야함 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//
    // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ 지워야함 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//
    // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ 지워야함 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//
    cout << "A: ";
    setA.getShow();
    cout << endl;

    cout << "B: ";
    setB.getShow();
    cout << endl;
    // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ 지워야함 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//
    // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ 지워야함 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//
    // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ 지워야함 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//
    // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ 지워야함 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//
    // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ 지워야함 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//

    stack<int> stkA;
    stack<int> stkB;

    setA.getStack(stkA);
    setB.getStack(stkB);

    showUnion(stkA, stkB);

    showIntersection(stkA, stkB);

    finish = clock();

    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << duration << "초" << endl;
    return 0;
}

// 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
// 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
// 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
// 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
// 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
// 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
// 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임
// 지워야하는 함수 : 두개의 트리 상태를 보기위한 함수임

void BinarySearchTree::getShow() {
    if (root != NULL) {
        getShow(root->left);
        for (int i = 0; i < root->dupli; i++) {
            printf("%d ", root->num);
        }
        getShow(root->right);
    }
}

void BinarySearchTree::getShow(Node* tree) {
    if (tree != NULL) {
        getShow(tree->left);
        for (int i = 0; i < tree->dupli; i++) {
            printf("%d ", tree->num);
        }
        getShow(tree->right);
    }
}