import java.util.*;

public class Parser { // 실제 분석
    // Recursive descent parser that inputs a C++Lite program and
    // generates its abstract syntax. Each method corresponds to
    // a concrete syntax grammar rule, which appears as a comment
    // at the beginning of the method.

    Token token; // 토큰 객체 생성/current token from the input stream
    Lexer lexer; // lexer 객체 생성

    public Parser(Lexer ts) { // Open the C++Lite source program
        lexer = ts; // 받아온 lexer객체를 lexer에 넣는다/ as a token stream, and
        token = lexer.next(); // 첫 토큰을 받아온다/retrieve its first Token
    }

    private String match(TokenType t) {
        String value = token.value(); // 토큰의 값을 저장
        if (token.type().equals(t)) // t와 토큰의 타입이 같다면
            token = lexer.next(); // 다음 토큰을 받아온다
        else // 아니면 에러 처리
            error(t);
        return value; // 이전 토큰의 값을 리턴한다
    }

    private void error(TokenType tok) { // 토큰 타입에 대한 에러처리
        System.err.println("Syntax error: expecting: " + tok
                + "; saw: " + token);
        System.exit(1);
    }

    private void error(String tok) { // 문자열 타입에 대한 토큰 에러처리
        System.err.println("Syntax error: expecting: " + tok
                + "; saw: " + token);
        System.exit(1);
    }

    public Program program() { // 프로그램 분석
        // Program --> void main ( ) '{' Declarations Statements '}'
        TokenType[] header = { TokenType.Int, TokenType.Main,
                TokenType.LeftParen, TokenType.RightParen };
        for (int i = 0; i < header.length; i++) // bypass "int main ( )"
            match(header[i]); // 메인의 헤드부분이 맞게 나왔는지 확인
        match(TokenType.LeftBrace); // 왼쪽 중괄호 확인
        // student exercise /Declarations Statements를 call
        Declarations declarations = declarations(); // declarations 생성
        Block block = new Block(); // block 생성
        // 블럭에는 ;, {, idenifier, if문, while문이 올 수 있다
        while (token.type().equals(TokenType.Semicolon) ||
                token.type().equals(TokenType.LeftBrace) ||
                token.type().equals(TokenType.Identifier) ||
                token.type().equals(TokenType.If) ||
                token.type().equals(TokenType.While)) {
            block.members.add(statement()); // 위에 해당하는 statement를 추가한다
        }
        match(TokenType.RightBrace); // 오른쪽 중괄호 확인 -> block이 끝남
        return new Program(declarations, block); // student exercise /프로그램 객체 리턴
    }

    private Declarations declarations() { // 선언
        // Declarations --> { Declaration }
        Declarations declar = new Declarations(); // 새로운 객체 생성
        while (isType()) { // 타입이 유효하다면
            declaration(declar); // declaration을 추가해준다
        }
        return declar;// 객체 리턴
        // student exercise
    }

    private void declaration(Declarations ds) { // 선언
        // Declaration --> Type Identifier { , Identifier } ;
        // student exercise
        Type type = type(); // 토큰에 해당하는 타입 생성
        Variable variable; // 변수 생성
        Declaration declar; // 변수 생성

        while (true) {
            variable = new Variable(match(TokenType.Identifier)); // 변수가 identifier가 맞다면 객체 생성
            declar = new Declaration(variable, type); // indentifier 와 type을 넣어 객체 생성
            ds.add(declar); // declarations 객체에 declaration 객체를 추가해준다
            if (token.type().equals(TokenType.Comma) == false) // 만약 ,가 없다면 끝낸다
                break;
            token = lexer.next(); // 아니라면 다음 토큰도 계속해서 확인한다
        }
        match(TokenType.Semicolon); // ;와 문장이 제대로 끝났는지 확인한다
    }

    private Type type() { // 타입
        // Type --> int | bool | float | char
        Type t = null;
        // student exercise
        if (token.type().equals(TokenType.Int)) // 토큰의 타입에 맞게 t변수의 타입을 설정한다
            t = Type.INT;
        else if (token.type().equals(TokenType.Bool))
            t = Type.BOOL;
        else if (token.type().equals(TokenType.Float))
            t = Type.FLOAT;
        else if (token.type().equals(TokenType.Char))
            t = Type.CHAR;
        else // 해당하는 타입이 없다면 오류 출력
            error("Error in Type");
        token = lexer.next(); // 다음 토큰을 받는다
        return t; // 타입 리턴
    }

    private Statement statement() {
        // Statement --> ; | Block | Assignment | IfStatement | WhileStatement
        Statement s = new Skip(); // skip 객체를 미리 넣어준다
        // student exercise
        if (token.type().equals(TokenType.Semicolon)) { // ;이라면 skip
        } else if (token.type().equals(TokenType.LeftBrace)) // {이라면 block이므로 statements를 생성
            s = statements();
        else if (token.type().equals(TokenType.Identifier)) // identifier라면 assignment를 생성
            s = assignment();
        else if (token.type().equals(TokenType.If)) // if라면 ifstatement 생성
            s = ifStatement();
        else if (token.type().equals(TokenType.While))// while라면 whilestatement 생성
            s = whileStatement();
        else // 아니라면 에러 처리
            error("Error in Statement");
        return s;
    }

    private Block statements() {
        // Block --> '{' Statements '}'
        Block b = new Block(); // block 객체 생성
        // student exercise
        match(TokenType.LeftBrace); // { 가 정상적으로 왔는지 확인
        // statements 확인
        while (token.type().equals(TokenType.Semicolon) // block에 올수 있는 statement들이 왔는지 확인
                || token.type().equals(TokenType.LeftBrace)
                || token.type().equals(TokenType.Identifier)
                || token.type().equals(TokenType.If)
                || token.type().equals(TokenType.While)) {
            b.members.add(statement()); // 해당하는 statement들을 저장
        }
        match(TokenType.RightBrace);// } 확인
        return b;
    }

    private Assignment assignment() { // 할당
        // Assignment --> Identifier = Expression ;
        Variable target = new Variable(match(TokenType.Identifier)); // 타입이 indentifier에 맞는 변수가 왔는지 확인
        match(TokenType.Assign); // =을 뜻하는 토큰이 있는지 확인
        Expression source = expression(); // expression 생성
        match(TokenType.Semicolon); // ;을 통해 문장이 정상적으로 끝났는지 확인
        Assignment assign = new Assignment(target, source); // 변수와 expression을 넣어 assignment객체 생성
        return assign; // student exercise
    }

    private Conditional ifStatement() { // 조건문
        // IfStatement --> if ( Expression ) Statement [ else Statement ]
        Conditional state;
        match(TokenType.If); // if가 왔는지 확인
        match(TokenType.LeftParen); // (가 왔는지 확인
        Expression express = expression(); // expression 객체 생성
        match(TokenType.RightParen); // ) 가 왔는지 확인
        Statement thenbranch = statement(); // then 문 생성
        if (token.type().equals(TokenType.Else)) { // 다음 토큰이 else 토큰이라면
            match(TokenType.Else); // else 토큰인지 확인하고
            Statement elsebranch = statement(); // else 문 생성
            state = new Conditional(express, thenbranch, elsebranch); // else가 포함된 조건문 객체 생성
        } else// else가 포함되지 않은 조건문 객체 생성
            state = new Conditional(express, thenbranch);
        return state; // student exercise
    }

    private Loop whileStatement() {// 반복문
        // WhileStatement --> while ( Expression ) Statement
        Loop loop;// loop 선언
        match(TokenType.While); // while토큰이 왔는지 확인
        match(TokenType.LeftParen); // (가 왔는지 확인
        Expression express = expression(); // expression 선언
        match(TokenType.RightParen); // )가 왔는지 확인
        Statement state = statement(); // statement 생성
        loop = new Loop(express, state); // expression과 statement를 넣고 loop객체 생성
        return loop; // student exercise
    }

    private Expression expression() {
        // Expression --> Conjunction { || Conjunction }
        Expression e = conjunction(); // conjunction 선언

        while (token.type().equals(TokenType.Or)) { // or을 뜻하는 토큰인 ||가 있을 동안
            Operator op = new Operator(match(token.type())); // operator 객체를 생성하고
            Expression term2 = conjunction(); // 새 conjunction 생성
            e = new Binary(op, e, term2); // 이항연산자에 넣어 두개를 합친다
        }
        return e; // student exercise
    }

    private Expression conjunction() {
        // Conjunction --> Equality { && Equality }
        Expression e = equality(); // equality 선언
        while (token.type().equals(TokenType.And)) { // and를 뜻하는 &&토큰이 있을 경우
            Operator op = new Operator(match(token.type())); // operator 객체를 생성하고
            Expression term2 = equality(); // 새 equality 생성
            e = new Binary(op, e, term2); // 이항연산자를 통해 두 개를 합친다
        }
        return e; // student exercise
    }

    private Expression equality() {
        // Equality --> Relation [ EquOp Relation ]
        Expression e = relation(); // relation 선언
        while (isEqualityOp()) { // == 이나 !=가 왔는지 확인
            Operator op = new Operator(match(token.type())); // operator 객체를 생성하고
            Expression term2 = relation(); // 새 relation 생성
            e = new Binary(op, e, term2);// 이항연산자를 통해 두 개를 합친다
        }
        return e; // student exercise
    }

    private Expression relation() {
        // Relation --> Addition [RelOp Addition]
        Expression e = addition(); // addition 선언
        while (isRelationalOp()) { // <, >, <=, >=가 왔는지 확인
            Operator op = new Operator(match(token.type())); // operator 객체를 생성하고
            Expression term2 = addition(); // 새 addition 생성
            e = new Binary(op, e, term2);// 이항연산자를 통해 두 개를 합친다
        }
        return e; // student exercise
    }

    private Expression addition() {
        // Addition --> Term { AddOp Term }
        Expression e = term(); // term 선언
        while (isAddOp()) { // +, - 왔는지 확인
            Operator op = new Operator(match(token.type()));// operator 객체를 생성하고
            Expression term2 = term(); // 새 term 생성
            e = new Binary(op, e, term2);// 이항연산자를 통해 두 개를 합친다
        }
        return e;
    }

    private Expression term() {
        // Term --> Factor { MultiplyOp Factor }
        Expression e = factor(); // factor 선언
        while (isMultiplyOp()) { // *, / 왔는지 확인
            Operator op = new Operator(match(token.type())); // operator 객체를 생성하고
            Expression term2 = factor(); // 새 factor 생성
            e = new Binary(op, e, term2); // 이항연산자를 통해 두 개를 합친다
        }
        return e;
    }

    private Expression factor() {
        // Factor --> [ UnaryOp ] Primary
        if (isUnaryOp()) { // !, - 왔는지 확인
            Operator op = new Operator(match(token.type())); // operator 객체를 생성하고
            Expression term = primary(); // 새 primary 생성
            return new Unary(op, term); // 단항 연상자 리턴
        } else // 없다면
            return primary(); // primary 리턴
    }

    private Expression primary() {
        // Primary --> Identifier | Literal | ( Expression )
        // | Type ( Expression )
        Expression e = null;
        if (token.type().equals(TokenType.Identifier)) { // identifier가 왔는지 확인
            e = new Variable(match(TokenType.Identifier)); // 왔다면 객체 생성
        } else if (isLiteral()) {// literal이 왔다면
            e = literal(); // literal 생성
        } else if (token.type().equals(TokenType.LeftParen)) {// (가 왔다면
            token = lexer.next(); // 다음 토큰 가져옴
            e = expression(); // expression 생성
            match(TokenType.RightParen); // )가 왔는지 확인
        } else if (isType()) { // type이 왔다면
            Operator op = new Operator(match(token.type())); // operator 객체를 생성
            match(TokenType.LeftParen); // ( 가 왔는지 확인
            Expression term = expression(); // expression 확인
            match(TokenType.RightParen); // )가 왔는지 확인
            e = new Unary(op, term); // 단항 연산자 생성
        } else
            error("Identifier | Literal | ( | Type");
        return e;
    }

    private Value literal() {
        Value value = null;
        String tokval = token.value(); // 토큰의 값 저장

        if (token.type().equals(TokenType.IntLiteral)) {// int리터럴인지 확인
            value = new IntValue(Integer.parseInt(tokval)); // int 값으로 설정
            token = lexer.next();
        } else if (token.type().equals(TokenType.True)) {// bool리터럴 중 true인지 확인
            value = new BoolValue(true);// bool: true 값으로 설정
            token = lexer.next();
        } else if (token.type().equals(TokenType.False)) {// bool리터럴 중 false인지 확인
            value = new BoolValue(false);// bool: false 값으로 설정
            token = lexer.next();
        } else if (token.type().equals(TokenType.FloatLiteral)) {// float리터럴인지 확인
            value = new FloatValue(Float.parseFloat(tokval)); // float 값으로 설정
            token = lexer.next();
        } else if (token.type().equals(TokenType.CharLiteral)) {// char 리터럴인지 확인
            value = new CharValue(tokval.charAt(0));// char 값으로 설정
            token = lexer.next();
        } else
            error("Error in literal");
        return value; // student exercise
    }

    private boolean isAddOp() { // 토큰이 +,- 인지 확인
        return token.type().equals(TokenType.Plus) ||
                token.type().equals(TokenType.Minus);
    }

    private boolean isMultiplyOp() { // 토큰이 *,/ 인지 확인
        return token.type().equals(TokenType.Multiply) ||
                token.type().equals(TokenType.Divide);
    }

    private boolean isUnaryOp() {// 토큰이 !, - 인지 확인
        return token.type().equals(TokenType.Not) ||
                token.type().equals(TokenType.Minus);
    }

    private boolean isEqualityOp() {// 토큰이 ==,!= 인지 확인
        return token.type().equals(TokenType.Equals) ||
                token.type().equals(TokenType.NotEqual);
    }

    private boolean isRelationalOp() {// 토큰이 <,>,<=,>= 인지 확인
        return token.type().equals(TokenType.Less) ||
                token.type().equals(TokenType.LessEqual) ||
                token.type().equals(TokenType.Greater) ||
                token.type().equals(TokenType.GreaterEqual);
    }

    private boolean isType() {// 토큰이 유요한 타입인지 확인
        return token.type().equals(TokenType.Int)
                || token.type().equals(TokenType.Bool)
                || token.type().equals(TokenType.Float)
                || token.type().equals(TokenType.Char);
    }

    private boolean isLiteral() {// 토큰이 유요한 리터럴인지 확인
        return token.type().equals(TokenType.IntLiteral) ||
                isBooleanLiteral() ||
                token.type().equals(TokenType.FloatLiteral) ||
                token.type().equals(TokenType.CharLiteral);
    }

    private boolean isBooleanLiteral() {// 토큰이 boolean 타입인지 확인
        return token.type().equals(TokenType.True) ||
                token.type().equals(TokenType.False);
    }

    public static void main(String args[]) { // 매개변수로 파일 이름
        Parser parser = new Parser(new Lexer(args[0])); // lexer을 통해 토큰을 만들고 parser 실행
        Program prog = parser.program(); // 테스트 실행
        prog.display(); // display abstract syntax tree
    } // main

} // Parser
