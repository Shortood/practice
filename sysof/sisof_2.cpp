#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    string line, temp, file1, file2;
    ofstream writeFile;
    string result[3];

    // cin >> file1 >> file2;
    ifstream file(argv[1]);   // srcfile
    writeFile.open(argv[2]);  // Intfile

    if (file.is_open() && writeFile.is_open()) {  //파일을 성공적으로 불러왔다면
        while (getline(file, line)) {             //한줄을 받아온다
            int cnt = 0;                          //단어 갯수 확인
            stringstream ss(line);                //다시 한번 공백 단위로 자르기
            writeFile.width(9);
            writeFile << std::left << "Label";
            writeFile.width(8);
            writeFile << std::left << "Opcode";
            writeFile << std::left << "Operand" << endl;
            while (ss >> temp) {
                result[cnt++] = temp;  //단어를 저장한다
            }
            if (cnt == 2) {  //라벨 없음
                writeFile.width(8);
                writeFile << std::left << result[0];
                writeFile << std::left << result[1] << endl;
            } else {  //라벨 있음
                writeFile.width(9);
                writeFile << std::left << result[0];
                writeFile.width(8);
                writeFile << std::left << result[1];
                writeFile << std::left << result[2] << endl;
            }
        }
    } else
        cout << "Unable to open file";  //파일이 없을때
    file.close();                       //파일을 닫는다.
}