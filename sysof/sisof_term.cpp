#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
using namespace std;

void error(string x) {  //에러출럭
    cout << x << endl;
}

int locctr, startaddress, programlength;

bool opfind(string op) {  // opcode 찾기
    ifstream optab("OPTAB");
    string templine;
    if (optab.is_open()) {
        while (getline(optab, templine)) {
            stringstream ss(templine);
            ss >> templine;
            // cout << templine << endl;
            if (templine == op) {
                ss >> templine;
                optab.close();
                return true;
            }
        }
    }
    optab.close();
    return false;
}
string getop(string op) {  // op코드의 값 리턴
    ifstream optab("OPTAB");
    string templine;
    if (optab.is_open()) {
        while (getline(optab, templine)) {
            stringstream ss(templine);
            ss >> templine;
            if (templine == op) {
                ss >> templine;
                break;
            }
        }
    }
    optab.close();
    return templine;
}

bool symbol_find(string op) {  //심볼 찾기
    ifstream symfile("SYMTAB");
    string templine;
    if (symfile.is_open()) {
        while (getline(symfile, templine)) {
            stringstream ss(templine);
            ss >> templine;
            // cout << templine << endl;
            if (templine == op) {
                ss >> templine;
                symfile.close();
                return true;
            }
        }
    }
    symfile.close();
    return false;
}

int oxtoten(string ox) {  // 16진수를 10진수로 변환
    int t[5] = {4096, 256, 16, 1}, h = 0;
    // cout << "ox " << ox << endl;
    for (int i = 0; i < 4; i++) {
        if (ox[i] >= '0' && ox[i] <= '9')
            h += t[i] * (ox[i] - '0');
        else {
            h += t[i] * (ox[i] - 'a' + 10);
        }
    }
    return h;
}
int getsymboladd(string op) {  //심볼의 주소 찾기
    ifstream symfile("SYMTAB");
    string templine;
    if (symfile.is_open()) {
        while (getline(symfile, templine)) {
            stringstream ss(templine);
            ss >> templine;
            if (templine == op) {
                ss >> templine;
                break;
            }
        }
    }
    symfile.close();
    return oxtoten(templine);
}

string oxstring(int s) {  // 4비트 10진수 수를 받아 16진수로 바꾸어 리턴
    string result = "";
    int t[5] = {4096, 256, 16, 1}, h;
    for (int i = 0; i < 4; i++) {
        h = s / t[i];
        s = s % t[i];
        if (h >= 10 && h <= 16) {
            result += h + 87;
        } else if (h < 10)
            result += to_string(h);
        else
            cout << "oxerror" << endl;
    }
    // cout << "re " << result << endl;
    return result;
}

string oxstringbyte(int s) {  // 2비트 10진수 수를 받아 16진수로 바꾸어 리턴
    string result = "";
    int t[3] = {16, 1}, h;
    for (int i = 0; i < 2; i++) {
        h = s / t[i];
        s = s % t[i];
        if (h >= 10 && h <= 16) {
            result += h + 87;
        } else if (h < 10)
            result += to_string(h);
        else
            cout << "oxerror" << endl;
    }
    return result;
}

string oxstringword(int s) {  // 6비트 10진수 수를 받아 16진수로 바꾸어 리턴
    string result = "";
    int t[7] = {16777216, 1048576, 65536, 4096, 16, 1}, h;
    for (int i = 0; i < 6; i++) {
        h = s / t[i];
        s = s % t[i];
        if (h >= 10 && h <= 16) {
            result += h + 87;
        } else if (h < 10)
            result += to_string(h);
        else
            cout << "oxerror" << endl;
    }
    // cout << result << endl;
    return result;
}

int pass1(string ar) {
    string line;
    ofstream writeFile, writesymtable;
    string label, op, operand, label2, op2;
    ifstream file(ar);  // srcfile

    writeFile.open("INTFILE");  // Intfile
    map<string, int> symtab;
    writesymtable.open("SYMTAB");
    if (file.is_open() && writeFile.is_open() && writesymtable.is_open()) {  //파일을 성공적으로 불러왔다면
        getline(file, line);
        label = line.substr(0, 9);
        op = line.substr(9, 8);
        operand = line.substr(17);
        if (op == "start   ") {                   // if OPCODE = ‘START’ then
            locctr = stoi(operand, nullptr, 16);  // initialize LOCCTR to starting address
            startaddress = locctr;                // save #[OPERAND] as starting address
        } else                                    // else { Initialize LOCCTR to 0 }
            locctr = 0;

        // write line to intermediate file
        writeFile.width(5);
        writeFile << std::left << std::hex << locctr;
        writeFile << label << op << operand << endl;
        // read next input line
        // while OPCODE != ‘END’ do {
        while (getline(file, line) && op2 != "end") {  // read next input line
            writeFile.width(5);
            label = line.substr(0, 9);
            op = line.substr(9, 8);
            operand = line.substr(17);
            if (label[0] != '.') {  // if this is not a comment line then
                writeFile << std::left << std::hex << locctr;
                if (label[0] != ' ') {  // if there is a symbol in the LABEL field then
                    stringstream ss(label);
                    ss >> label2;
                    if (symtab.find(label2) == symtab.end())  // search SYMTAB for LABEL
                        symtab.insert({label2, locctr});      // else insert (LABEL, LOCCTR) into SYMTAB
                    else                                      // if found then set error flag (duplicate symbol)
                        error("Error at Symtab(duplicate)");
                }

                writeFile << label << op << operand << endl;  // write line to intermediate file
                // write last line to intermediate file
                stringstream ss(op);
                ss >> op2;
                if (opfind(op2)) {           // search OPTAB for OPCODE
                    locctr += 3;             // if found then
                } else if (op2 == "resw") {  // else if OPCODE = ‘RESW’ then
                    locctr += stoi(operand) * 3;
                } else if (op2 == "resb") {  // else if OPCODE = ‘RESB’ then
                    locctr += stoi(operand);
                } else if (op2 == "word") {  // else if OPCODE = ‘WORD’ then
                    locctr += 3;
                } else if (op2 == "byte") {  // else if OPCODE = ‘BYTE’ then
                    stringstream ss(operand);
                    ss >> operand;
                    locctr += operand.length() - 3;  // c, ", "빼기
                } else if (op2 == "end") {
                    programlength = locctr - startaddress;                            // save (LOCCTR – starting address) as program length
                    for (auto iter = symtab.begin(); iter != symtab.end(); iter++) {  //심볼테이믈 파일에 저장
                        writesymtable << iter->first << " ";
                        writesymtable.width(4);
                        writesymtable.fill('0');
                        writesymtable << std::hex << iter->second;
                        writesymtable << " 0" << endl;
                    }
                } else {  // else set error flag (invalid operation code)
                    error("Error at Optable(invalid operation code)");
                    break;
                }
            } else
                writeFile << "     " << line << endl;
        }
    } else
        cout << "Unable to open file";  //파일이 없을때
    file.close();                       //파일을 닫는다.
    return programlength;
}

void pass2(int programlength) {
    ifstream intfile("INTFILE");
    ofstream objFile;
    string line, label, op, operand, loc, tempstring, startaddress;
    string x;
    string textrecord = "";
    int opaddress, position, cur;
    objFile.open("OBJFILE");

    if (intfile.is_open()) {
        // read first input line {from intermediate file}
        getline(intfile, line);
        loc = line.substr(0, 5);
        stringstream s1(loc);
        s1 >> loc;
        startaddress = loc;
        label = line.substr(5, 9);
        stringstream s2(label);
        s2 >> label;
        op = line.substr(14, 8);
        stringstream s3(op);
        s3 >> op;
        operand = line.substr(22);
        stringstream s4(operand);
        s4 >> operand;
        // if OPCODE = ‘START’ then {write listing line; read next input line }
        if (op == "start") {  // write Header record to object program
            objFile << 'H';
            objFile << label << " ";
            objFile.width(6);
            objFile.fill('0');
            objFile << loc;
            cur = oxtoten(loc);
            string strlength = to_string(programlength);
            objFile.width(6);
            objFile.fill('0');
            objFile << std::hex << programlength << endl;
        }
        // initialize first Text record
        getline(intfile, line);
        loc = line.substr(0, 5);
        stringstream a1(loc);
        a1 >> loc;
        label = line.substr(5, 9);
        stringstream a2(label);
        a2 >> label;
        op = line.substr(14, 8);
        stringstream a3(op);
        a3 >> op;
        operand = line.substr(22);
        stringstream a4(operand);
        a4 >> operand;
        if ((position = operand.find(",")) != std::string::npos) {  // exaddr,x indev,x
            x = operand.substr(position + 1, std::string::npos);
            operand = operand.substr(0, position);
        } else
            x = "";
        while (op != "end") {                 // while OPCODE != ‘END’ do {
            if (label != ".") {               // if this is not a comment line then {
                if (opfind(op)) {             // search OPTAB for OPCODE
                    if (operand[0] != ' ') {  // if there is a symbol in the OPERAND field then{
                        // search SYMTAB for OPERAND
                        if (symbol_find(operand)) {  // if found then store symbol value as operand address
                            opaddress = getsymboladd(operand);
                            if (x != "") {  // index mode
                                opaddress += 8 * pow(16, 3);
                            }
                            // cout << operand << " " << opaddress << endl;
                        } else {  // else { store 0 as operand address set error flag (undefined symbol)}
                            opaddress = 0;
                            // cout << operand << " ";
                            error("error(undefined symbol)");
                        }
                    } else {  // else { store 0 as operand address
                        opaddress = 0;
                    }
                    tempstring = getop(op);
                    tempstring += oxstring(opaddress);
                    // if object code will not fit into the current text record then
                    if (textrecord.length() + tempstring.length() <= 60) {
                        textrecord += tempstring;  // add object code to Text record
                    } else {                       // write Text record to object program
                        objFile << "T";
                        objFile.width(6);
                        objFile.fill('0');
                        objFile << std::hex << cur;
                        objFile.width(2);
                        objFile.fill('0');
                        objFile << oxstringbyte(textrecord.length() / 2);
                        objFile << textrecord << endl;
                        cur += (textrecord.length() / 2);
                        textrecord = tempstring;  // initialize new Text record
                    }
                } else if (op == "word") {      // else if OPCODE = ‘BYTE’ or ‘WORD’ then
                    opaddress = stoi(operand);  // convert constant to object code
                    tempstring = oxstringword(opaddress);
                    // if object code will not fit into the current text record then
                    if (textrecord.length() + tempstring.length() <= 60)
                        textrecord += tempstring;  // add object code to Text record
                    else {                         // write Text record to object program
                        objFile << "T";
                        objFile.width(6);
                        objFile.fill('0');
                        objFile << std::hex << cur;
                        objFile.width(2);
                        objFile.fill('0');
                        objFile << oxstringbyte(textrecord.length() / 2);
                        objFile << textrecord << endl;
                        cur += textrecord.length() / 2;
                        textrecord = tempstring;  // initialize new Text record
                    }
                } else if (op == "byte") {
                    operand = operand.substr(2, operand.length() - 2);
                    // if object code will not fit into the current text record then
                    if (textrecord.length() + operand.length() <= 60) {
                        // add object code to Text record
                        for (int i = 0; i < operand.length() - 1; i++) {
                            textrecord += oxstringbyte((int)(operand[i]));
                        }
                    } else {  // write Text record to object program
                        objFile << "T";
                        objFile.width(6);
                        objFile.fill('0');
                        objFile << std::hex << cur;
                        objFile.width(2);
                        objFile.fill('0');
                        objFile << oxstringbyte(textrecord.length() / 2);
                        objFile << textrecord << endl;
                        cur += textrecord.length() / 2;
                        textrecord = "";  ////initialize new Text record
                        for (int i = 0; i < operand.length() - 1; i++) {
                            textrecord += oxstringbyte(operand[i]);
                        }
                    }
                } else if (op == "resb" && textrecord.length() != 0) {  // resb나 resw가 나오면 줄바꿈
                    if (textrecord.length() != 0) {
                        objFile << "T";
                        objFile.width(6);
                        objFile.fill('0');
                        objFile << std::hex << cur;
                        objFile.width(2);
                        objFile.fill('0');
                        objFile << oxstringbyte(textrecord.length() / 2);
                        objFile << textrecord << endl;
                    }
                    cur += textrecord.length() / 2 + stoi(operand);
                    textrecord = "";
                } else if (op == "resw") {
                    if (textrecord.length() != 0) {
                        objFile << "T";
                        objFile.width(6);
                        objFile.fill('0');
                        objFile << std::hex << cur;
                        objFile.width(2);
                        objFile.fill('0');
                        objFile << oxstringbyte(textrecord.length() / 2);
                        objFile << textrecord << endl;
                    }
                    cur += textrecord.length() / 2 + 3 * stoi(operand);
                    textrecord = "";
                }
            }
            //다음줄 받아오기
            getline(intfile, line);
            loc = line.substr(0, 5);
            stringstream a1(loc);
            a1 >> loc;
            label = line.substr(5, 9);
            stringstream a2(label);
            a2 >> label;
            op = line.substr(14, 8);
            stringstream a3(op);
            a3 >> op;
            operand = line.substr(22);
            stringstream a4(operand);
            a4 >> operand;
            if ((position = operand.find(",")) != std::string::npos) {  // table,x
                x = operand.substr(position + 1, std::string::npos);
                operand = operand.substr(0, position);
            } else
                x = "";
        }  // write last Text record to object program
        if (textrecord.length() != 0) {
            objFile << "T";
            objFile.width(6);
            objFile.fill('0');
            objFile << std::hex << cur;
            objFile.width(2);
            objFile.fill('0');
            objFile << oxstringbyte(textrecord.length() / 2);
            objFile << textrecord << endl;
        }
        // write End record to object program
        objFile << "E";
        objFile.width(6);
        objFile.fill('0');
        objFile << startaddress;
    }

    intfile.close();
}
int main() {
    pass2(pass1("SRCFILE"));
}