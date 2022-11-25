#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

map<string, string> optab;

void opinsert() {
    optab.insert({"add", "18"});
    optab.insert({"and", "40"});
    optab.insert({"comp", "28"});
    optab.insert({"div", "24"});
    optab.insert({"j", "3c"});
    optab.insert({"jeq", "30"});
    optab.insert({"jgt", "34"});
    optab.insert({"jlt", "38"});
    optab.insert({"jsub", "48"});
    optab.insert({"lda", "00"});
    optab.insert({"ldch", "50"});
    optab.insert({"ldl", "08"});
    optab.insert({"ldx", "04"});
    optab.insert({"mul", "20"});
    optab.insert({"or", "44"});
    optab.insert({"rd", "d8"});
    optab.insert({"rsub", "4c"});
    optab.insert({"sta", "0c"});
    optab.insert({"stch", "54"});
    optab.insert({"stl", "14"});
    optab.insert({"stsw", "e8"});
    optab.insert({"stx", "10"});
    optab.insert({"sub", "1c"});
    optab.insert({"td", "e0"});
    optab.insert({"tix", "2c"});
    optab.insert({"wd", "dc"});
}
void error(string x) {
    cout << x << endl;
}

int main(int argc, char* argv[]) {
    string line;
    ofstream writeFile;
    string result[3];
    string label, op, operand, label2, op2;
    int locctr, startaddress, programlength;
    ifstream file(argv[1]);   // srcfile
    writeFile.open(argv[2]);  // Intfile
    map<string, int> symtab;

    if (file.is_open() && writeFile.is_open()) {  //파일을 성공적으로 불러왔다면
        opinsert();                               // op table 만들기
        getline(file, line);
        label = line.substr(0, 9);
        op = line.substr(9, 8);
        operand = line.substr(17);
        if (op == "start   ") {
            locctr = stoi(operand, nullptr, 16);
            startaddress = locctr;
        } else {
            locctr = 0;
        }
        writeFile.width(5);
        writeFile << std::left << std::hex << " ";
        writeFile.width(9);
        writeFile << std::left << "Label";
        writeFile.width(8);
        writeFile << std::left << "Opcode";
        writeFile << "Operand" << endl;

        writeFile.width(5);
        writeFile << std::left << std::hex << locctr;
        writeFile << label << op << operand << endl;

        while (getline(file, line)) {  //한줄을 받아온다
            writeFile.width(5);
            writeFile << std::left << std::hex << locctr;
            label = line.substr(0, 9);
            op = line.substr(9, 8);
            operand = line.substr(17);
            if (label[0] != ' ') {
                stringstream ss(label);
                ss >> label2;
                if (symtab.find(label2) == symtab.end())
                    symtab.insert({label2, locctr});
                else
                    error("Error at Symtab");
            }

            writeFile << label << op << operand << endl;
            stringstream ss(op);
            ss >> op2;
            if (optab.find(op2) != optab.end()) {
                locctr += 3;
            } else if (op2 == "resw") {
                locctr += stoi(operand) * 3;
            } else if (op2 == "resb") {
                locctr += stoi(operand);
            } else if (op2 == "word") {
                locctr += 3;
            } else if (op2 == "byte") {
                locctr += operand.length() - 3;  // c, ", "빼기
            } else if (op2 == "end") {
                programlength = locctr - startaddress;
                /*
                for (auto iter = optab.begin(); iter != optab.end(); iter++) {
                    writeFile << iter->first << " " << iter->second << endl;
                }
                */
                writeFile << endl;
                writeFile << "Symtab" << endl;
                for (auto iter = symtab.begin(); iter != symtab.end(); iter++) {
                    writeFile << iter->first << " " << iter->second << " 0" << endl;
                }

                return 0;
            } else {
                error("Error at Optable");
                return 0;
            }
        }
    } else
        cout << "Unable to open file";  //파일이 없을때
    file.close();                       //파일을 닫는다.
}