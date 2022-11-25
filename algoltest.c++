#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

template <typename itemType>
class Stack {
   public:
    Stack() {  // ?ㅻ뱶? z?ъ씤??珥덇린??
        head = NULL;
        z = NULL;
    }
    ~Stack() {  //?ㅻ뱶? z?ъ씤??珥덇린??
        if (head != NULL) {
            while (head != NULL) {
                z = head;
                head = head->next;
                delete z;
            }
        }
        z = NULL;
    }                 //?대? ?꾨? ???섏뿀?쇰?濡?delete X
    void push(int v)  //?몄떆
    {
        if (empty())  //留뚯빟 鍮꾩뼱?덈떎硫?
        {             //?ㅻ뱶 異붽?
            head = new node;
            head->key = v;
            head->next = NULL;
        } else  //?꾨땲?쇰㈃ ???몃뱶 異붽??????몃뱶瑜??ㅻ뱶濡??댁???
        {
            z = new node;
            z->key = v;
            z->next = head;
            head = z;
        }
    }
    int gettop() {
        return head->key;
    }
    int pop()  //??
    {
        z = head;           // z???ㅻ뱶
        int tmp = z->key;   // z???ㅺ컪??蹂닿?
        head = head->next;  //?ㅻ뱶瑜??ㅼ쓬 ?몃뱶濡???꺼以??
        delete z;           //?몃뱶 ??젣
        return tmp;         //??젣???몃뱶 媛?由ы꽩
    }
    int empty()  // head媛 ?녿떎硫?鍮꾩뼱?덈떎
    {
        return (head == NULL);
    }

   private:
    struct node {
        itemType key;       //?ㅺ컪
        struct node* next;  //?ㅼ쓬 ?몃뱶瑜?媛由ы궡
    };
    struct node *head, *z;  //?ㅻ뱶 ?ъ씤?곗? ?꾩떆 ?ъ씤??
};

class Node {
   public:
    int num;
    Node* left;
    Node* right;
    Node(int& num);
    ~Node();
};

Node::Node(int& num) {
    this->num = num;
    this->left = NULL;
    this->right = NULL;
}

Node::~Node() {
    if (this->left != NULL)
        delete this->left;
    if (this->right != NULL)
        delete this->right;
}

class BinarySearchTree {
   private:
    Node* root;
    void insert(Node*& tree, int num);
    void getStack(Node* tree, Stack<int>& stk);

   public:
    BinarySearchTree();
    ~BinarySearchTree();
    void insert(int num);
    void getStack(Stack<int>& stk);
};

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
        this->insert(this->root, num);
    }
}

void BinarySearchTree::insert(Node*& tree, int num) {
    if (tree == NULL) {
        tree = new Node(num);
    }

    if (tree->num == num) {
    } else if (tree->num > num) {
        this->insert(tree->right, num);
    } else {
        this->insert(tree->left, num);
    }
}

void BinarySearchTree::getStack(Stack<int>& stk) {
    if (this->root != NULL) {
        this->getStack(this->root, stk);
    }
}

void BinarySearchTree::getStack(Node* tree, Stack<int>& stk) {
    if (tree != NULL) {
        getStack(tree->left, stk);
        stk.push(tree->num);
        getStack(tree->right, stk);
    }
}

void clearStk(Stack<int>& stk) {
    while (!stk.empty())
        stk.pop();
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

    Stack<int> stkA;
    Stack<int> stkB;

    setA.getStack(stkA);
    setB.getStack(stkB);

    // cout << "UNION : ";
    while (!stkA.empty() || !stkB.empty()) {
        if (stkA.gettop() == stkB.gettop()) {
            // cout << stkA.top() << " ";
            stkA.pop();
            stkB.pop();
        } else if (stkA.gettop() < stkB.gettop()) {
            // cout << stkA.top() << " ";
            stkA.pop();
        } else {
            // cout << stkB.top() << " ";
            stkB.pop();
        }

        if (stkA.empty()) {
            while (!stkB.empty()) {
                // cout << stkB.top() << " ";
                stkB.pop();
            }
        } else if (stkB.empty()) {
            while (!stkA.empty()) {
                // cout << stkA.top() << " ";
                stkA.pop();
            }
        }
    }
    // cout << endl;

    setA.getStack(stkA);
    setB.getStack(stkB);

    // cout << "INTERSECTION : ";
    while (!stkA.empty() && !stkB.empty()) {
        if (stkA.gettop() == stkB.gettop()) {
            // cout << stkA.top() << " ";
            stkA.pop();
            stkB.pop();
        } else if (stkA.gettop() < stkB.gettop()) {
            stkA.pop();
        } else {
            stkB.pop();
        }
    }
    // cout << endl;

    finish = clock();

    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << duration << "second" << endl;
    return 0;
}
