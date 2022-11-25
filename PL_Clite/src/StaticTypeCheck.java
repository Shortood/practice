// StaticTypeCheck.java

import java.util.*;

// Static type checking for Clite is defined by the functions 
// V and the auxiliary functions typing and typeOf.  These
// functions use the classes in the Abstract Syntax of Clite.

public class StaticTypeCheck {
    private static boolean errorcheck; // 에러가 났는지 체크하는 bool타입 변수

    public static TypeMap typing(Declarations d) {
        TypeMap map = new TypeMap(); // 새 TypeMap 객체 생성
        for (Declaration di : d) // 선언부를 입력받고 map에 추가
            map.put(di.v, di.t);
        return map;
    }

    public static void check(boolean test, String msg) {
        if (test) // 에러가 없다면 리턴
            return;
        errorcheck = true; // 에라가 있다고 체크
        System.err.println(msg); // 메시지 출력
        // System.exit(1); //프로그램 종료
    }

    public static void V(Declarations d) {// Declarations 검사
        for (int i = 0; i < d.size() - 1; i++)// 모든 Declaration 검사
            for (int j = i + 1; j < d.size(); j++) {
                Declaration di = d.get(i);
                Declaration dj = d.get(j);
                check(!(di.v.equals(dj.v)), // 같은 변수를 찾으면 에러처리
                        "duplicate declaration: " + dj.v);
            }
    }

    public static boolean V(Program p) { // Program 검사
        V(p.decpart); // declarations 파트 검사
        V(p.body, typing(p.decpart)); // body와 declarations의 type map 검사
        return errorcheck; // 프로그램에 에러가 있는지 리턴
    }

    public static Type typeOf(Expression e, TypeMap tm) {
        if (e instanceof Value) // expression이 Value 라면
            return ((Value) e).type; // 값의 타입 리턴
        if (e instanceof Variable) { // expression이 Variable 라면
            Variable v = (Variable) e; // e를 variable형태로 저장
            check(tm.containsKey(v), "undefined variable: " + v); // 맵에 키값이 있는지 확인
            return (Type) tm.get(v); // 변수의 타입 리턴
        }
        if (e instanceof Binary) { // 이항 연산자 라면
            Binary b = (Binary) e;// e를 Binary 형태로 저장
            if (b.op.ArithmeticOp()) // 산술 연산이라면
                if (typeOf(b.term1, tm) == Type.FLOAT) // float 형태라면
                    return (Type.FLOAT); // float 타입 리턴
                else
                    return (Type.INT); // int 타입 리턴
            if (b.op.RelationalOp() || b.op.BooleanOp()) // 관계연산자나 논리연산자라면
                return (Type.BOOL); // bool 타입 리턴
        }
        if (e instanceof Unary) { // 단항 연산자라면
            Unary u = (Unary) e; // e를 Unary 형태로 저장
            if (u.op.NotOp()) // not 연산자라면
                return (Type.BOOL); // bool 타입 리턴
            else if (u.op.NegateOp()) // negate 연산자라면
                return typeOf(u.term, tm); // 같은 타입 리턴
            else if (u.op.intOp()) // int 연산자라면
                return (Type.INT); // int 타입 리턴
            else if (u.op.floatOp())// float 연산자라면
                return (Type.FLOAT);// float 타입 리턴
            else if (u.op.charOp())// char 연산자라면
                return (Type.CHAR);// char 타입 리턴
        }
        throw new IllegalArgumentException("should never reach here");
    }

    public static void V(Expression e, TypeMap tm) {// expression 검사
        if (e instanceof Value) // expression이 value 형태라면
            return; // 바로 메소드 종료
        if (e instanceof Variable) {// expression이 variable 형태라면
            Variable v = (Variable) e; // expression을 Variable 형태로 저장
            check(tm.containsKey(v), "undeclared variable: " + v);// 이미 변수가 있는지 확인
            return;
        }
        if (e instanceof Binary) { // expression이 binary 형태라면
            Binary b = (Binary) e;// expression을 binary 형태로 저장
            Type typ1 = typeOf(b.term1, tm); // term 1의 타입 저장
            Type typ2 = typeOf(b.term2, tm); // term 2의 타입 저장
            V(b.term1, tm); // term1 검사
            V(b.term2, tm); // term2 검사
            if (b.op.ArithmeticOp()) // 산술 연산자라면
                check(typ1 == typ2 && // 두 term의 타입이 같고 int 나 float인지 확인
                        (typ1 == Type.INT || typ1 == Type.FLOAT), "type error for " + b.op);
            else if (b.op.RelationalOp()) // 관계연산자라면
                check(typ1 == typ2, "type error for " + b.op); // 두 term의 타입이 같은지 확인
            else if (b.op.BooleanOp()) // 논리연산자 라면
                check(typ1 == Type.BOOL && typ2 == Type.BOOL, // 두 term bool 타입인지 확인
                        b.op + ": non-bool operand");
            else
                throw new IllegalArgumentException("should never reach here");
            return;
        }
        // student exercise
        if (e instanceof Unary) { // 단항 연산자라면
            Unary u = (Unary) e; // expression을 unary형태로 저장
            Type typ = typeOf(u.term, tm); // term의 타입 저장
            V(u.term, tm); // term 검사

            if (u.op.NotOp()) // not 연산자라면
                check(typ == Type.BOOL, u.op + ": non-bool operand"); // term의 타입이 bool인지 확인
            else if (u.op.intOp()) // int 연산자라면 term의 타입이 float나 char인지 확인
                check(typ == Type.FLOAT || typ == Type.CHAR, u.op + ": non-float or non-char operand");
            else if (u.op.floatOp())// float 연산자라면 term의 타입이 int 인지 확인
                check(typ == Type.INT, u.op + ": non-int operand"); //
            else if (u.op.charOp())// char 연산자라면 term의 타입이 char 인지 확인
                check(typ == Type.INT, u.op + ": non-int operand");
            else if (u.op.NegateOp())// negate 연산자라면 term의 타입이 int나 float인지 확인
                check(typ == Type.INT || typ == Type.FLOAT, u.op + ": non-int or non-float operand");
            else
                throw new IllegalArgumentException("should never reach here");
            return;
        }
        throw new IllegalArgumentException("should never reach here");
    }

    public static void V(Statement s, TypeMap tm) { // Statement 검사
        if (s == null) // statement가 비어있다면 error 처리
            throw new IllegalArgumentException("AST error: null statement");
        if (s instanceof Skip) // skip 이라면
            return; // 아무 처리도 하지 않고 메소드 종료
        if (s instanceof Assignment) { // assignment 라면
            Assignment a = (Assignment) s; // Assignment 형태로 저장
            // 변수가 typemap에 있는지 확인
            check(tm.containsKey(a.target), " undefined target in assignment: " + a.target);
            V(a.source, tm); // a의 source 검사
            Type ttype = (Type) tm.get(a.target); // 변수의 타입
            Type srctype = typeOf(a.source, tm); // source의 타입
            if (ttype != srctype) { // 타입이 다르다면
                if (ttype == Type.FLOAT) // 변수의 타입이 float라면 source의 타입이 int인지 검사
                    check(srctype == Type.INT, "mixed mode assignment to " + a.target);
                else if (ttype == Type.INT) // 변수의 타입이 int라면 source의 타입이 char인지 검사
                    check(srctype == Type.CHAR, "mixed mode assignment to " + a.target);
                else // 오류 처리
                    check(false, "mixed mode assignment to " + a.target);
            }
            return;
        }
        // student exercise
        if (s instanceof Conditional) { // conditional 이라면
            Conditional c = (Conditional) s; // conditional 형태로 저장
            V(c.test, tm); // test 부분 검사

            Type ctype = typeOf(c.test, tm); // test 부분 타입 저장
            if (ctype == Type.BOOL) { // test 부분의 타입이 bool이라면
                V(c.thenbranch, tm); // then 부분 검사
                V(c.elsebranch, tm); // else 부분 검사
            } else// 아니라면 오류 처리
                check(false, "type error in Conditional" + c.test);
            return;
        }

        if (s instanceof Loop) { // loop 라면
            Loop l = (Loop) s; // loop 형태로 저장
            V(l.test, tm); // test 부분 검사
            Type ltype = typeOf(l.test, tm); // test 부분의 타입 저장
            if (ltype == Type.BOOL) { // test 부분의 타입이 bool이라면
                V(l.body, tm); // body 부분 검사
                return;
            } else // 아니라면 오류처리
                check(false, "type error in LOOP" + l.test);
        }

        if (s instanceof Block) { // block 이라면
            Block b = (Block) s; // block 형태로 저장
            for (Statement st : b.members)// block 속 statement 들을
                V(st, tm); // 검사
            return;
        }
        throw new IllegalArgumentException("should never reach here");
    }

    public static void main(String args[]) {
        Parser parser = new Parser(new Lexer(args[0])); // lexer와 parser 실행
        Program prog = parser.program();
        prog.display(); // student exercise
        System.out.println("\nBegin type checking...");
        System.out.println("Type map:");
        TypeMap map = typing(prog.decpart); // type map 생성
        map.display(); // student exercise
        V(prog);
    } // main

} // class StaticTypeCheck
