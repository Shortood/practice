// Abstract syntax for the language C++Lite,
// exactly as it appears in Appendix B.

import java.util.*;

class Program {
    // Program = Declarations decpart ; Block body
    Declarations decpart;
    Block body;

    Program(Declarations d, Block b) {
        decpart = d;
        body = b;
    }

    void display() { // 화면에 결과 출력
        // student exercise
        System.out.println();

        System.out.println("Program (abstract syntax) : ");

        decpart.display(1); // height를 1증가시키고 declaration을 출력
        body.display(1);// height를 1증가시키고 body를 출력
    }

}

class Declarations extends ArrayList<Declaration> { //
    // Declarations = Declaration*
    // (a list of declarations d1, d2, ..., dn)
    public void display(int height) {// declarations 출력
        System.out.print("  ");
        System.out.println("Declaractions: ");
        for (int i = 0; i <= height; i++)
            System.out.print("  ");
        System.out.print("Declaractions = {");
        for (int i = 0; i < size(); i++) {
            get(i).display(); // 배열의 i번째를 출력
            if (i < size() - 1)// 다음 배열이 있다면 ,출력
                System.out.print(", ");
        }
        System.out.println("}");
    }
}

class Declaration { // 선언
    // Declaration = Variable v; Type t
    Variable v;
    Type t;

    Declaration(Variable var, Type type) { // 입력받은 값과 타입을 넣는다
        v = var;
        t = type;
    } // declaration */

    public void display() { // declaration 출력
        System.out.print("<" + v + ", " + t + ">");
    }
}

class Type {
    // Type = int | bool | char | float
    final static Type INT = new Type("int"); // 각 타입 동적할당
    final static Type BOOL = new Type("bool");
    final static Type CHAR = new Type("char");
    final static Type FLOAT = new Type("float");
    // final static Type UNDEFINED = new Type("undef");

    private String id;

    private Type(String t) { // 입력받은 id를 저장한다
        id = t;
    }

    public String toString() { // id값 리턴
        return id;
    }
}

abstract class Statement { // 상속을 위한 추상 클래스
    // Statement = Skip | Block | Assignment | Conditional | Loop
    public void display(int height) { // 추상 클래스 상속을 위한 선언
    }
}

class Skip extends Statement { // 생략
}

class Block extends Statement {
    // Block = Statement*
    // (a Vector of members)
    public ArrayList<Statement> members = new ArrayList<Statement>();

    public void display(int height) { // block 출력
        for (int i = 0; i < height; i++)
            System.out.print("  ");

        System.out.println("Blocks: ");

        for (Statement st : members) // 배열에 저장된 block의 멤버들을 출력
            st.display(height + 1);
    }
}

class Assignment extends Statement {
    // Assignment = Variable target; Expression source
    Variable target;
    Expression source;

    Assignment(Variable t, Expression e) {
        target = t;
        source = e;
    }

    public void display(int height) {// Assignment 출력
        for (int i = 0; i < height; i++)
            System.out.print("  ");

        System.out.println("Assignment: ");

        target.display(height + 1); // height를 1증가시키고 variable 출력
        source.display(height + 1);// height를 1증가시키고 expression 출력
    }

}

class Conditional extends Statement {
    // Conditional = Expression test; Statement thenbranch, elsebranch
    Expression test;
    Statement thenbranch, elsebranch;
    // elsebranch == null means "if... then"

    Conditional(Expression t, Statement tp) { // else가 없는 경우
        test = t;
        thenbranch = tp;
        elsebranch = new Skip();
    }

    Conditional(Expression t, Statement tp, Statement ep) {// else가 있는 경우
        test = t;
        thenbranch = tp;
        elsebranch = ep;
    }

    public void display(int height) {// conditional 출력
        for (int i = 0; i < height; i++)
            System.out.print("  ");

        System.out.println("IfStatement:");

        test.display(height + 1); // express 출력
        thenbranch.display(height + 1); // thenbranch 출력
        elsebranch.display(height + 1); // elsebranch 출력
    }
}

class Loop extends Statement {
    // Loop = Expression test; Statement body
    Expression test;
    Statement body;

    Loop(Expression t, Statement b) {
        test = t;
        body = b;
    }

    public void display(int height) { // loop 출력
        for (int i = 0; i < height; i++)
            System.out.print("  ");

        System.out.println("Loop:");

        test.display(height + 1); // expression 출력
        body.display(height + 1); // body 부분 출력
    }
}

abstract class Expression { // 추상클래스
    // Expression = Variable | Value | Binary | Unary
    public void display(int height) {
    }
}

class Variable extends Expression { // 변수
    // Variable = String id
    private String id;

    Variable(String s) { // 입력받은 값을 id에 저장
        id = s;
    }

    public String toString() { // id 값 리턴
        return id;
    }

    public boolean equals(Object obj) { // id값 비교
        String s = ((Variable) obj).id;
        return id.equals(s); // case-sensitive identifiers
    }

    public int hashCode() {// 해쉬코드 리턴
        return id.hashCode();
    }

    public void display(int height) { // 변수 출력
        for (int i = 0; i < height; i++)
            System.out.print("  ");

        System.out.println("Variable: " + id);
    }
}

abstract class Value extends Expression {
    // Value = IntValue | BoolValue |
    // CharValue | FloatValue
    protected Type type;
    protected boolean undef = true;

    int intValue() {
        assert false : "should never reach here";
        return 0;
    }

    boolean boolValue() {
        assert false : "should never reach here";
        return false;
    }

    char charValue() {
        assert false : "should never reach here";
        return ' ';
    }

    float floatValue() {
        assert false : "should never reach here";
        return 0.0f;
    }

    boolean isUndef() {
        return undef;
    }

    Type type() { // 타입 리턴
        return type;
    }

    static Value mkValue(Type type) {// 타입에 따라 새 객체 동적할당
        if (type == Type.INT)
            return new IntValue();
        if (type == Type.BOOL)
            return new BoolValue();
        if (type == Type.CHAR)
            return new CharValue();
        if (type == Type.FLOAT)
            return new FloatValue();
        throw new IllegalArgumentException("Illegal type in mkValue");
    }
}

class IntValue extends Value { // int 형태
    private int value = 0;

    IntValue() { // 타입 설정
        type = Type.INT;
    }

    IntValue(int v) {
        this();
        value = v; // 값 넣기
        undef = false;
    }

    int intValue() { // 값 리턴
        assert !undef : "reference to undefined int value";
        return value;
    }

    public String toString() {// 값 리턴
        if (undef)
            return "undef";
        return "" + value;
    }

    public void display(int height) { // intvalue 출력
        for (int i = 0; i < height; i++)
            System.out.print("  ");
        System.out.println("IntValue: " + value);
    }
}

class BoolValue extends Value { // bool 형태
    private boolean value = false;

    BoolValue() { // 타입 설정
        type = Type.BOOL;
    }

    BoolValue(boolean v) { // 값 넣기
        this();
        value = v;
        undef = false;
    }

    boolean boolValue() { // 값 리턴
        assert !undef : "reference to undefined bool value";
        return value;
    }

    int intValue() { // 값을 int형태로 리턴
        assert !undef : "reference to undefined bool value";
        return value ? 1 : 0;
    }

    public String toString() { // 값을 string형태로 리턴
        if (undef)
            return "undef";
        return "" + value;
    }

    public void display(int height) {// boolvalue 출력
        for (int i = 0; i < height; i++)
            System.out.print("  ");
        System.out.println("BoolValue: " + value);
    }
}

class CharValue extends Value { // char 형태
    private char value = ' ';

    CharValue() { // 타입 설정
        type = Type.CHAR;
    }

    CharValue(char v) { // 값넣기
        this();
        value = v;
        undef = false;
    }

    char charValue() { // 값 리턴
        assert !undef : "reference to undefined char value";
        return value;
    }

    public String toString() { // string형태로 값 리턴
        if (undef)
            return "undef";
        return "" + value;
    }

    public void display(int height) {// charvalue 출력
        for (int i = 0; i < height; i++)
            System.out.print("  ");
        System.out.println("CharValue: " + value);
    }
}

class FloatValue extends Value { // float 형태
    private float value = 0;

    FloatValue() { // 타입 설정
        type = Type.FLOAT;
    }

    FloatValue(float v) { // 값 설정
        this();
        value = v;
        undef = false;
    }

    float floatValue() { // 값 리턴
        assert !undef : "reference to undefined float value";
        return value;
    }

    public String toString() { // string형태로 값 리턴
        if (undef)
            return "undef";
        return "" + value;
    }

    public void display(int height) {// floatvalue 출력
        for (int i = 0; i < height; i++)
            System.out.print("  ");
        System.out.println("FloatValue: " + value);
    }

}

class Binary extends Expression { // 2항 연산
    // Binary = Operator op; Expression term1, term2
    Operator op;
    Expression term1, term2;

    Binary(Operator o, Expression l, Expression r) {
        op = o;
        term1 = l;
        term2 = r;
    } // binary

    public void display(int height) { // 이항연산자 출력
        for (int i = 0; i < height; i++)
            System.out.print("  ");
        System.out.println("Binary:");
        op.display(height + 1); // operator 출력
        term1.display(height + 1);// term1 출력
        term2.display(height + 1); // term2 출력
    }
}

class Unary extends Expression { // 1항 연산
    // Unary = Operator op; Expression term
    Operator op;
    Expression term;

    Unary(Operator o, Expression e) {
        op = o;
        term = e;
    } // unary

    public void display(int height) { // 단항 연산자 출력
        for (int i = 0; i < height; i++)
            System.out.print("  ");

        System.out.println("Unary: ");
        op.display(height + 1); // operator 출력
        term.display(height + 1); // term 출력
    }
}

class Operator { // 타입에 받는 operator 선언
    // Operator = BooleanOp | RelationalOp | ArithmeticOp | UnaryOp
    // BooleanOp = && | ||
    final static String AND = "&&";
    final static String OR = "||";
    // RelationalOp = < | <= | == | != | >= | >
    final static String LT = "<";
    final static String LE = "<=";
    final static String EQ = "==";
    final static String NE = "!=";
    final static String GT = ">";
    final static String GE = ">=";
    // ArithmeticOp = + | - | * | /
    final static String PLUS = "+";
    final static String MINUS = "-";
    final static String TIMES = "*";
    final static String DIV = "/";
    // UnaryOp = !
    final static String NOT = "!";
    final static String NEG = "-";
    // CastOp = int | float | char
    final static String INT = "int";
    final static String FLOAT = "float";
    final static String CHAR = "char";
    // Typed Operators
    // RelationalOp = < | <= | == | != | >= | >
    final static String INT_LT = "INT<";
    final static String INT_LE = "INT<=";
    final static String INT_EQ = "INT==";
    final static String INT_NE = "INT!=";
    final static String INT_GT = "INT>";
    final static String INT_GE = "INT>=";
    // ArithmeticOp = + | - | * | /
    final static String INT_PLUS = "INT+";
    final static String INT_MINUS = "INT-";
    final static String INT_TIMES = "INT*";
    final static String INT_DIV = "INT/";
    // UnaryOp = !
    final static String INT_NEG = "-";
    // RelationalOp = < | <= | == | != | >= | >
    final static String FLOAT_LT = "FLOAT<";
    final static String FLOAT_LE = "FLOAT<=";
    final static String FLOAT_EQ = "FLOAT==";
    final static String FLOAT_NE = "FLOAT!=";
    final static String FLOAT_GT = "FLOAT>";
    final static String FLOAT_GE = "FLOAT>=";
    // ArithmeticOp = + | - | * | /
    final static String FLOAT_PLUS = "FLOAT+";
    final static String FLOAT_MINUS = "FLOAT-";
    final static String FLOAT_TIMES = "FLOAT*";
    final static String FLOAT_DIV = "FLOAT/";
    // UnaryOp = !
    final static String FLOAT_NEG = "-";
    // RelationalOp = < | <= | == | != | >= | >
    final static String CHAR_LT = "CHAR<";
    final static String CHAR_LE = "CHAR<=";
    final static String CHAR_EQ = "CHAR==";
    final static String CHAR_NE = "CHAR!=";
    final static String CHAR_GT = "CHAR>";
    final static String CHAR_GE = "CHAR>=";
    // RelationalOp = < | <= | == | != | >= | >
    final static String BOOL_LT = "BOOL<";
    final static String BOOL_LE = "BOOL<=";
    final static String BOOL_EQ = "BOOL==";
    final static String BOOL_NE = "BOOL!=";
    final static String BOOL_GT = "BOOL>";
    final static String BOOL_GE = "BOOL>=";
    // Type specific cast
    final static String I2F = "I2F";
    final static String F2I = "F2I";
    final static String C2I = "C2I";
    final static String I2C = "I2C";

    String val;

    Operator(String s) { // 값 설정
        val = s;
    }

    public String toString() { // 값 리턴
        return val;
    }

    public boolean equals(Object obj) {// 값 비교
        return val.equals(obj);
    }

    boolean BooleanOp() { // and 나 or 인지 확인
        return val.equals(AND) || val.equals(OR);
    }

    boolean RelationalOp() { // 크기 비교 연산 인지 확인
        return val.equals(LT) || val.equals(LE) || val.equals(EQ)
                || val.equals(NE) || val.equals(GT) || val.equals(GE);
    }

    boolean ArithmeticOp() {// 사칙 연산 인지 확인
        return val.equals(PLUS) || val.equals(MINUS)
                || val.equals(TIMES) || val.equals(DIV);
    }

    boolean NotOp() {// not 인지 확인
        return val.equals(NOT);
    }

    boolean NegateOp() {
        return val.equals(NEG);
    }

    boolean intOp() { // int 인지 확인
        return val.equals(INT);
    }

    boolean floatOp() {// float 인지 확인
        return val.equals(FLOAT);
    }

    boolean charOp() {// char 인지 확인
        return val.equals(CHAR);
    }

    final static String intMap[][] = {
            { PLUS, INT_PLUS }, { MINUS, INT_MINUS },
            { TIMES, INT_TIMES }, { DIV, INT_DIV },
            { EQ, INT_EQ }, { NE, INT_NE }, { LT, INT_LT },
            { LE, INT_LE }, { GT, INT_GT }, { GE, INT_GE },
            { NEG, INT_NEG }, { FLOAT, I2F }, { CHAR, I2C }
    };

    final static String floatMap[][] = {
            { PLUS, FLOAT_PLUS }, { MINUS, FLOAT_MINUS },
            { TIMES, FLOAT_TIMES }, { DIV, FLOAT_DIV },
            { EQ, FLOAT_EQ }, { NE, FLOAT_NE }, { LT, FLOAT_LT },
            { LE, FLOAT_LE }, { GT, FLOAT_GT }, { GE, FLOAT_GE },
            { NEG, FLOAT_NEG }, { INT, F2I }
    };

    final static String charMap[][] = {
            { EQ, CHAR_EQ }, { NE, CHAR_NE }, { LT, CHAR_LT },
            { LE, CHAR_LE }, { GT, CHAR_GT }, { GE, CHAR_GE },
            { INT, C2I }
    };

    final static String boolMap[][] = {
            { EQ, BOOL_EQ }, { NE, BOOL_NE }, { LT, BOOL_LT },
            { LE, BOOL_LE }, { GT, BOOL_GT }, { GE, BOOL_GE },
    };

    final static private Operator map(String[][] tmap, String op) {
        for (int i = 0; i < tmap.length; i++) // 입력받은 형태에 맞춰
            if (tmap[i][0].equals(op)) // operator 형 동적할당
                return new Operator(tmap[i][1]);
        assert false : "should never reach here";
        return null;
    }

    final static public Operator intMap(String op) {// int형으로 op변환
        return map(intMap, op);
    }

    final static public Operator floatMap(String op) {// float형으로 op변환
        return map(floatMap, op);
    }

    final static public Operator charMap(String op) {// char형으로 op변환
        return map(charMap, op);
    }

    final static public Operator boolMap(String op) {// bool으로 op변환
        return map(boolMap, op);
    }

    public void display(int height) { // operator 출력
        for (int i = 0; i < height; i++)
            System.out.print("  ");
        System.out.println("Operator: " + val);
    }
}
