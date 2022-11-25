#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string line;
    string line2;
    ifstream file("Optab.txt");
    string key;

    cin >> key;
    if (file.is_open()) {
        while (getline(file, line, ',')) {
            getline(file, line2);
            if (key == line) {
                cout << line2 << endl;
                return 0;
            }
        }
        cout << "Can't Found" << endl; //값을 못 찾았을때
    } else
        cout << "Unable to open file"; //파일이 없을때
    file.close();  //파일을 닫는다.
}