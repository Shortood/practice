#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    string tag, progname, addr, size;
    string length, codes;
    string others;
    string line, temp;
    int conver[62];
    ifstream file("DEVF2");
    if (file.is_open()) {              //파일을 성공적으로 불러왔다면
        while (getline(file, line)) {  //한줄을 받아온다
            // stringstream ss(line);
            // ss >> line;

            tag = line.substr(0, 1);
            if (tag == "H") {
                progname = line.substr(1, 6);
                addr = line.substr(7, 6);
                size = line.substr(13, 6);
                cout << tag << " " << progname << " " << addr << " " << size << endl;
            } else if (tag == "T") {
                addr = line.substr(1, 6);
                length = line.substr(7, 2);
                codes = line.substr(9, 51);
                for (int i = 0; i < codes.length(); i++) {
                    if (codes[i] >= '0' && codes[i] <= '9') {
                        conver[i] = (int)(codes[i]) - 48;
                    } else if (codes[i] >= 'A' && codes[i] <= 'F') {
                        conver[i] = (int)(codes[i]) - 55;
                    }
                }
                cout << tag << " " << addr << " " << length << " " << codes << "/" << endl;
                cout << codes.length() << " ";
                for (int i = 0; i < codes.length(); i++) {
                    cout << conver[i] << " ";
                }
                cout << endl;
            } else if (tag == "M") {
                addr = line.substr(1, 6);
                length = line.substr(7, 2);
                others = line.substr(9, 51);
                cout << tag << " " << addr << " " << length << " " << others << endl;
            } else if (tag == "E") {
                others = line.substr(1, 6);
                cout << tag << " " << others << endl;
            } else
                cout << "tag error" << endl;
        }
    } else
        cout << "Unable to open file";  //파일이 없을때
    file.close();
}