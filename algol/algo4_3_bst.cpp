#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class Node {
   public:
    string str;
    int dupli;
    Node* left;
    Node* right;
    Node(string str) {
        this->str = str;
        this->dupli = 1;
        this->left = NULL;
        this->right = NULL;
    };
    ~Node() {
        if (this->left != NULL)
            delete this->left;
        if (this->right != NULL)
            delete this->right;
    };
};

class BinarySearchTree {
   private:
    Node* root;

    void insert(Node*& tree, string str) {
        if (tree == NULL) {  //현재 보는 위치가 비었다면
            tree = new Node(str);
        } else {
            if (tree->str == str) {              //현재 보는 위치와 단어가 같다면
                (tree->dupli)++;                 //갯수 증가
            } else if (tree->str < str) {        //넣은 단어가 더 크다면
                this->insert(tree->right, str);  //오른쪽으로 간다
            } else {                             //작다면
                this->insert(tree->left, str);   //왼쪽으로 간다
            }
        }
    };

    void print(Node* tree, int& cnt) {  // cnt는 30개까지만 출력하기 위한 변수
        if (tree != NULL) {
            print(tree->left, cnt);  //왼쪽부터 출력
            if (cnt < 30) {          // 30개 까지만 출력
                cout << tree->str << " - " << tree->dupli << "\n";
                cnt++;
            } else {
                return;
            }
            print(tree->right, cnt);  //오른쪽 출력
        }
    };

   public:
    BinarySearchTree() {
        this->root = NULL;
    };

    ~BinarySearchTree() {
        if (this->root != NULL)
            delete this->root;
    };

    void insert(string str) {
        if (this->root == NULL) {  //트리가 비었다면
            this->root = new Node(str);
        } else {
            if (root->str == str)
                (root->dupli)++;  // 만약 root왜 단어가 같다면 갯수 증가
            else                  //아니면 넣을 위치 찾기
                this->insert(this->root, str);
        }
    };

    void print() {
        if (root != NULL) {
            int cnt = 0;
            print(root->left, cnt);                                 //왼쪽부터 출력
            if (cnt < 30) {                                         //왼쪽을 모두 출력하고 아직 30개가 되지 않았다면
                cout << root->str << " - " << root->dupli << "\n";  // root 출력
            } else {
                return;
            }
            print(root->right, cnt);  //오른쪽 출력
        }
    };
};

int main() {
    string line, temp;
    ifstream file("datafile.txt");  //파일 읽기

    BinarySearchTree bst;
    if (file.is_open()) {
        while (getline(file, line, '\0')) {  //한 줄씩 공백 단위로 받아오기
            stringstream ss(line);           //다시 한번 공백 단위로 자르기
            while (ss >> temp) {
                // cout << temp << endl;
                bst.insert(temp);  //트리에 삽입
            }
        }
    } else
        cout << "Unable to open file";  //파일이 없을때
    file.close();                       //파일을 닫는다.
    bst.print();                        //출력
}