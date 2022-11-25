import java.io.*;

public class Lexer {

    private boolean isEof = false;
    private char ch = ' ';
    private BufferedReader input;
    private String line = "";
    private int lineno = 0;
    private int col = 1;
    private final String letters = "abcdefghijklmnopqrstuvwxyz"
            + "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    private final String digits = "0123456789";
    private final char eolnCh = '\n';
    private final char eofCh = '\004';

    // cpp파일들을 받아서 토큰들로 분해
    public Lexer(String fileName) { // source filename
        try { // 파일이름을 받아 해당파일 오픈
            input = new BufferedReader(new FileReader(fileName));
        } catch (FileNotFoundException e) {// 파일을 못 찾았다면
            System.out.println("File not found: " + fileName);
            System.exit(1);
        }
    }

    private char nextChar() { // 다음 문자 리턴
        if (ch == eofCh)
            error("Attempt to read past end of file");
        col++; // 다음 문자를 확인하기 위해 1을 더함
        if (col >= line.length()) {// 현재 라인의 길이를 넘겼다면
            try { // 새 라인을 받아온다
                line = input.readLine();
            } catch (IOException e) { // 예외 처리
                System.err.println(e);
                System.exit(1);
            } // try
            if (line == null) // 만약 파일을 모두 받아왔다면
                line = "" + eofCh; // 파일의 마지막을 뜻하는 문자를 넣는다
            else { // 받아왔다면
                   // System.out.println(lineno + ":\t" + line);
                lineno++; // 몇 행인지 저장
                line += eolnCh; // 일어온 줄의 마지막을 뜻하는 문자를 넣는다
            } // if line
            col = 0;// 다시 첫 문자를 받아오기 위해 초기화
        } // if col

        return line.charAt(col); // 다음 문자 리턴
    }

    public Token next() { // Return next token
        do { // character를 하나씩 받아오고 해당 캐릭터가 무엇인지 mapping
            if (isLetter(ch)) { // 받아온 문자가 알파벳인지 확인 // ident or keyword
                String spelling = concat(letters + digits);
                return Token.keyword(spelling); // 키워드인지 indentifier인지 구분해 리턴
            } else if (isDigit(ch)) { // 숫자인지 확인 // int or float literal
                String number = concat(digits); // 숫자부분을 받아온다
                if (ch != '.') // .이 없다면 int형태이므로// int Literal
                    return Token.mkIntLiteral(number); // int형태로 토큰을 리턴
                number += concat(digits); // .뒷부분도 받아온다
                return Token.mkFloatLiteral(number); // float 형태로 토큰 리턴
            } else
                switch (ch) { // ch의 값에 따라
                    case ' ':
                    case '\t':
                    case '\r':
                    case eolnCh: // 줄의 마지막이라면
                        ch = nextChar(); // 바로 다음 문자를 받아옴
                        break;
                    // 특수문자이면 operator로 처리
                    case '/': // '/'라면 //divide or comment
                        ch = nextChar(); // 다음 문자를 받아오고
                        if (ch != '/') // 또 '/'가 아니라면
                            return Token.divideTok; // 나누기로 처리한다
                        // 만약 '//'라면 주석으로 처리
                        do { // 줄의 끝까지 받아온다
                            ch = nextChar();
                        } while (ch != eolnCh);
                        ch = nextChar(); // 다음 문자를 받는다
                        break;

                    case '\'': // 문자형태의 '라면 //char literal
                        char ch1 = nextChar(); // 다음 문자를 ch1변수에 저장
                        nextChar(); // 다음 '를 가져온다 // get '
                        ch = nextChar(); // 다음 문자를 받는다
                        return Token.mkCharLiteral("" + ch1); // 작은 따옴표 속 문자를 문자형으로 처리해 토큰에 저장

                    case eofCh: // 파일의 끝이라면
                        return Token.eofTok; // eof토큰으로 처리

                    case '+': // +라면
                        ch = nextChar(); // 다음 문자를 받고
                        return Token.plusTok;// +토큰으로 처리한다

                    // - * ( ) { } ; , student exercise
                    case '-': // -라면
                        ch = nextChar(); // 다음 문자를 받고
                        return Token.minusTok;// -토큰으로 처리한다

                    case '*': // *라면
                        ch = nextChar(); // 다음 문자를 받고
                        return Token.multiplyTok;// *토큰으로 처리한다

                    case '(': // (라면
                        ch = nextChar(); // 다음 문자를 받고
                        return Token.leftParenTok;// (토큰으로 처리한다

                    case ')': // (라면
                        ch = nextChar(); // 다음 문자를 받고
                        return Token.rightParenTok;// )토큰으로 처리한다

                    case '{': // {라면
                        ch = nextChar(); // 다음 문자를 받고
                        return Token.leftBraceTok;// {토큰으로 처리한다

                    case '}': // (라면
                        ch = nextChar(); // 다음 문자를 받고
                        return Token.rightBraceTok;// }토큰으로 처리한다

                    case ';': // ;라면
                        ch = nextChar(); // 다음 문자를 받고
                        return Token.semicolonTok;// 세미콜론 토큰으로 처리한다

                    case ',': // ,라면
                        ch = nextChar(); // 다음 문자를 받고
                        return Token.commaTok;// 콤마 토큰으로 처리한다

                    case '&': // &라면
                        check('&'); // 다음문자도 &인지 확인
                        return Token.andTok; // 맞다면 and토큰으로 처리

                    case '|':
                        check('|'); // 다음문자도 |인지 확인
                        return Token.orTok; // 맞다면 or 토큰으로 처리

                    case '=': // 다음문자도 =인지 확인
                        return chkOpt('=', Token.assignTok,
                                Token.eqeqTok); // =이 총 1개인지 2개인지에 따라 처리
                    // < > ! student exercise
                    case '<': // &라면
                        return chkOpt('=', Token.ltTok,
                                Token.lteqTok); // 다음에 =이 오는지 안오는지에 따라 처리
                    case '>': // &라면
                        return chkOpt('=', Token.gtTok,
                                Token.gteqTok); // 다음에 =이 오는지 안오는지에 따라 처리
                    case '!': // &라면
                        return chkOpt('=', Token.notTok,
                                Token.noteqTok); // 다음에 =이 오는지 안오는지에 따라 처리
                    default:
                        error("Illegal character " + ch);
                } // switch
        } while (true);
    } // next

    private boolean isLetter(char c) { // 스펠링인지 확인
        return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
    }

    private boolean isDigit(char c) { // 숫자인지 확인
        return (c >= '0' && c <= '9'); // student exercise
    }

    private void check(char c) { // c와 같은 문자인지 확인
        ch = nextChar(); // 다음 문자를 받는다
        if (ch != c) // 받아온 문자가 c와 같지 않다면
            error("Illegal character, expecting " + c); // 에러 출력
        ch = nextChar(); // 다음 문자를 받는다
    }

    private Token chkOpt(char c, Token one, Token two) {
        ch = nextChar(); // 다음 문자를 받는다
        if (ch != c) {// 받아온 문자가 c와 같지 않다면
            ch = nextChar(); // 다음 문자를 받는다
            return one;
        } else {
            ch = nextChar(); // 다음 문자를 받는다
            return two;
        }
        // student exercise
    }

    private String concat(String set) { // set문자열에 포함하는 문자들 찾아 합치기
        String r = ""; // r 초기화
        do {
            r += ch; // r에 ch문자를 넣는다
            ch = nextChar(); // 다음 문자를 넣는다
        } while (set.indexOf(ch) >= 0); // ch가 set에 있는 동안 반복
        return r; // 문자열 리턴
    }

    public void error(String msg) { // 에러 처리
        System.err.print(line); // 에러가 난 라인 출력
        System.err.println("Error: column " + col + " " + msg); // 에러가 난 행과 메시지 출력
        System.exit(1); // 시스템 종료
    }

    static public void main(String[] argv) {
        Lexer lexer = new Lexer(argv[0]); // lexer 객체 생성
        Token tok = lexer.next(); // lexer를 통해 토큰을 받는다
        while (tok != Token.eofTok) {// 모든 파일을 읽을 동안
            System.out.println(tok.toString()); // 토큰들을 string형태로 출력
            tok = lexer.next(); // 토큰들을 계속 받는다
        }
    } // main

}
