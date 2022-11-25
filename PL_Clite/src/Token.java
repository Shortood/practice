public class Token { // tokentype을 기반으로 각각의 토큰들을 정의

    private static final int KEYWORDS = TokenType.Eof.ordinal();

    private static final String[] reserved = new String[KEYWORDS];
    private static Token[] token = new Token[KEYWORDS];
    // 키워드에 해당하는 토큰들을 final 객체를 이용해 중복되지 않도록 생성
    public static final Token eofTok = new Token(TokenType.Eof, "<<EOF>>");
    public static final Token boolTok = new Token(TokenType.Bool, "bool");
    public static final Token charTok = new Token(TokenType.Char, "char");
    public static final Token elseTok = new Token(TokenType.Else, "else");
    public static final Token falseTok = new Token(TokenType.False, "false");
    public static final Token floatTok = new Token(TokenType.Float, "float");
    public static final Token ifTok = new Token(TokenType.If, "if");
    public static final Token intTok = new Token(TokenType.Int, "int");
    public static final Token mainTok = new Token(TokenType.Main, "main");
    public static final Token trueTok = new Token(TokenType.True, "true");
    public static final Token whileTok = new Token(TokenType.While, "while");
    public static final Token leftBraceTok = new Token(TokenType.LeftBrace, "{");
    public static final Token rightBraceTok = new Token(TokenType.RightBrace, "}");
    public static final Token leftBracketTok = new Token(TokenType.LeftBracket, "[");
    public static final Token rightBracketTok = new Token(TokenType.RightBracket, "]");
    public static final Token leftParenTok = new Token(TokenType.LeftParen, "(");
    public static final Token rightParenTok = new Token(TokenType.RightParen, ")");
    public static final Token semicolonTok = new Token(TokenType.Semicolon, ";");
    public static final Token commaTok = new Token(TokenType.Comma, ",");
    public static final Token assignTok = new Token(TokenType.Assign, "=");
    public static final Token eqeqTok = new Token(TokenType.Equals, "==");
    public static final Token ltTok = new Token(TokenType.Less, "<");
    public static final Token lteqTok = new Token(TokenType.LessEqual, "<=");
    public static final Token gtTok = new Token(TokenType.Greater, ">");
    public static final Token gteqTok = new Token(TokenType.GreaterEqual, ">=");
    public static final Token notTok = new Token(TokenType.Not, "!");
    public static final Token noteqTok = new Token(TokenType.NotEqual, "!=");
    public static final Token plusTok = new Token(TokenType.Plus, "+");
    public static final Token minusTok = new Token(TokenType.Minus, "-");
    public static final Token multiplyTok = new Token(TokenType.Multiply, "*");
    public static final Token divideTok = new Token(TokenType.Divide, "/");
    public static final Token andTok = new Token(TokenType.And, "&&");
    public static final Token orTok = new Token(TokenType.Or, "||");

    private TokenType type;
    private String value = "";

    private Token(TokenType t, String v) { // identifier를 처리하기 위해 string을 입력받아
        type = t; // 토큰의 타입 지정
        value = v;// 토큰의 id값 지정
        if (t.compareTo(TokenType.Eof) < 0) {
            int ti = t.ordinal();
            reserved[ti] = v; // id값을 저장
            token[ti] = this; // 생성된 토큰을 저장
        }
    }

    public TokenType type() { // 토큰의 타입 리턴
        return type;
    }

    public String value() { // 토큰의 값 리턴
        return value;
    }

    public static Token keyword(String name) {
        char ch = name.charAt(0); // 첫번째 글자를 저장
        if (ch >= 'A' && ch <= 'Z') // 키워드는 첫글자가 대문자일 수 없으므로 첫번째 글자가 A와 Z사이이면
            return mkIdentTok(name);// identifier로 구분해 리턴
        for (int i = 0; i < KEYWORDS; i++)
            if (name.equals(reserved[i])) // 입력받은 이름과 같은 id를 가진 토큰을 찾는다
                return token[i]; // 찾았다면 토큰 리턴
        return mkIdentTok(name);// 아니라면 identifier로 구분해 리턴
    } // keyword
      // 리터럴을 생성

    public static Token mkIdentTok(String name) { // identifier형태의 토큰을 만들어 리턴
        return new Token(TokenType.Identifier, name);
    }

    public static Token mkIntLiteral(String name) {// int 형태의 토큰을 만들어 리턴
        return new Token(TokenType.IntLiteral, name);
    }

    public static Token mkFloatLiteral(String name) {// float 형태의 토큰을 만들어 리턴
        return new Token(TokenType.FloatLiteral, name);
    }

    public static Token mkCharLiteral(String name) {// char 형태의 토큰을 만들어 리턴
        return new Token(TokenType.CharLiteral, name);
    }

    public String toString() { // 각각의 토큰들을 출력
        if (type.compareTo(TokenType.Identifier) < 0) // 만약 현재의 토큰 타입이 int, float, char가 아니라면
            return value; // 값을 리턴
        return type + "\t" + value; // int, float, char 중 하나라면 타입과 값 함께 리턴
    } // toString

    public static void main(String[] args) { // 테스트를 위한 메인 메소드
        System.out.println(eofTok); // eof토큰을 넣어 실행
        System.out.println(whileTok); // while토큰을 넣어 실행
    }
} // Token
  // main 이 여러개 -> 진입점 여러개