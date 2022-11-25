#include <cstring>
#include <iostream>

using namespace std;

int brutesearch(string p, string a) {
    int i, j, M = p.length(), N = a.length();
    int index[1000];
    int cnt = 0;
    for (i = 0, j = 0; i < N; i++, j++) {
        if (a[i] != p[j]) {
            i -= j - 1;
            j = -1;
        }
        cout << j << " " << M << endl;
        if (j == M) {
            cout << "find" << endl;
            index[cnt++] = j;
            i -= j - 1;
            j = -1;
        }
    }
    return cnt;
}

int main() {
    string text = "A STRING SEARCHING EXAMPLE CONSISTING OF A GIVEN STING";
    string pattern = "STING";

    cout << brutesearch(pattern, text) << endl;
}