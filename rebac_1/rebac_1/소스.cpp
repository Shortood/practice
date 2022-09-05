#include <iostream>

using namespace std;

int fac(int n) {
	if (n >= 2) return n*fac(n - 1);
	else return 1;
}

int main() {
	int n;
	cin >> n;
	cout << fac(n);
}