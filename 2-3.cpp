#include <iostream>
#include <ctime>
#define max(a, b) ( ((a) > (b)) ? (a) : (b) )
using namespace std;

struct avl {
    int data, height;
    avl *left, *right; 
    avl(int const& data) : data(data), height(1), left(NULL), right(NULL){}
    ~avl() {
        delete left;
        delete right;
    }
};

template <typename T>
class Stack {
private:
    struct node {
        T key;
        node *next;
        node(T const& key, node* next) : key(key), next(next) {}
    };
    struct node *head, *z;

public:
    Stack() {
        head = NULL;
    };
    
    ~Stack() {
        node* tmp;
        for(z = head; z != nullptr; z = tmp) {
            tmp = z->next;
            delete z;
        }
    };

    void push(T const& v) {
        head = new node(v, head);
    };
    
    T pop() {
        if (empty()) return 0;
        z = head;
        T v = z->key;
        head = head->next;
        delete z;
        return v;
    };

    T top() const {
        if (head == NULL) return 0;
        return head->key;
    }
    
    int empty() {
        return head == NULL;
    };
};

class Set {
private:
	struct avl *root, *tmp;

    avl* insertAvl(avl* node, int data) {
		if (empty(node)) return new avl(data);

		if (data < node->data) 
            node->left = insertAvl(node->left, data);

		else if (data > node->data) 
            node->right = insertAvl(node->right, data);
		
        node = balance(node);
        return node;
	}

    avl* rotateLL(avl* node) {
        avl* left = node->left;
        node->left = left->right;
        left->right = node;

        setHeight(left); 
        return left;
    }

    avl* rotateRR(avl* node) {
        avl* right = node->right;
        node->right = right->left;
        right->left = node;

        setHeight(right); 
        return right;
    }

    avl* rotateLR(avl* node) {
        node->left = rotateRR(node->left);
        return rotateLL(node);
    }

    avl* rotateRL(avl* node) {
        node->right = rotateLL(node->right);
        return rotateRR(node);
    }

    avl* balance(avl* node) {
        int difference = getDifference(node);
        if (difference >= 2) {
            if (getDifference(node->left) >= 1) node = rotateLL(node);
            else  node = rotateLR(node);
        }

        else if (difference <= -2) {
            if (getDifference(node->right) <= -1) node = rotateRR(node);
            else node = rotateRL(node);
        }

        setHeight(node); 
        return node;
    }

    int getDifference(avl* node) {
        if (node == NULL) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }   

    int getHeight(avl* node) {
        if (node == NULL) return 0;
        return node->height;    
    }

    void setHeight(avl* node) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    void inorder(avl* node) {
		if (empty(node)) return;
		inorder(node->left);
		cout << node->data << " ";
		inorder(node->right);
	}

    bool containsAvl(avl* node, int data) {
		if (empty(node))  return false;
		return node->data == data || containsAvl(node->left, data) || containsAvl(node->right, data);
	}

    bool empty(avl* node) { return !node; }

public:
	Set() { root = NULL; }
    ~Set() {delete root;}

	void insert(int data) {
		if (!containsAvl(root, data)) 
            root = insertAvl(root, data);
	}

	Set unionSet(Set& s) {
		Set u;

		if (root == NULL) return s;
		if (s.root == NULL) return *this;

		Stack<avl*> stack;
		stack.push(root);
		while (!stack.empty()) {
			tmp = stack.pop();

			u.insert(tmp->data);
			if (tmp->right) stack.push(tmp->right);
			if (tmp->left) stack.push(tmp->left);
		}

		stack.push(s.root);
		while (!stack.empty()) {
			tmp = stack.pop();

			u.insert(tmp->data);
			if (tmp->right) stack.push(tmp->right);
			if (tmp->left) stack.push(tmp->left);
		}

		return u;
	}

    Set intersectionSet(Set& s) {
		Set x;
		Stack<avl*> stack;
		stack.push(root); 

		while (!stack.empty()) {
            tmp = stack.pop();

			if (s.contains(tmp->data)) x.insert(tmp->data);
			if (tmp->right) stack.push(tmp->right);
			if (tmp->left) stack.push(tmp->left);
		}
		return x;
	}

	void printSet() {
		inorder(root);
        cout << "\n";
	}

    bool contains(int data) { return containsAvl(root, data); }

    bool empty() { return !root; }
};

int main() {
    srand(time(NULL));
    Set a, b;

    int n, m;
    cin >> n >> m;
    while (n--) a.insert(rand() % 30 + 1);
    while (m--) b.insert(rand() % 30 + 1);

    cout << "a : ";
    a.printSet();
    
    cout << "b : ";
    b.printSet();

    cout << "u : ";
    a.unionSet(b).printSet();

    cout << "x : ";
    a.intersectionSet(b).printSet();
}