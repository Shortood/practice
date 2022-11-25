import java.util.*;

public class TypeTransformer {

    public static Program T(Program p, TypeMap tm) { // 프로그램 변환
        Block body = (Block) T(p.body, tm); // body 부분 변환
        return new Program(p.decpart, body); // 바뀐 body를 넣어 새 객체 생성
    }

    public static Expression T(Expression e, TypeMap tm) {// expression 변환
        if (e instanceof Value) // value 라면
            return e; // 바로 리턴
        if (e instanceof Variable) // variavle 이라면
            return e; // 바로 리턴
        if (e instanceof Binary) { // 이항 연산자라면
            Binary b = (Binary) e; // binary 형태로 저장
            Type typ1 = StaticTypeCheck.typeOf(b.term1, tm);// term1 타입 저장
            Type typ2 = StaticTypeCheck.typeOf(b.term2, tm);// term2 타입 저장
            Expression t1 = T(b.term1, tm); // term1 변환
            Expression t2 = T(b.term2, tm); // term2 변환
            if (typ1 == Type.INT)// term의 타입이 int 라면
                return new Binary(b.op.intMap(b.op.val), t1, t2); // int형으로 연산자 변환
            else if (typ1 == Type.FLOAT) // term의 타입이 float 라면
                return new Binary(b.op.floatMap(b.op.val), t1, t2); // float형으로 연산자 변환
            else if (typ1 == Type.CHAR) // term의 타입이 char 라면
                return new Binary(b.op.charMap(b.op.val), t1, t2);// char형으로 연산자 변환
            else if (typ1 == Type.BOOL) // term의 타입이 bool 라면
                return new Binary(b.op.boolMap(b.op.val), t1, t2);// bool형으로 연산자 변환
            throw new IllegalArgumentException("should never reach here");
        }
        // student exercise
        if (e instanceof Unary) { // 단항연산자 라면
            Unary u = (Unary) e; // unary 형태로 저장
            Type typ = StaticTypeCheck.typeOf(u.term, tm); // term의 타입 저장
            Expression t = T(u.term, tm);// term 변환
            if (typ == Type.INT) // term의 타입이 int 라면
                return new Unary(u.op.intMap(u.op.val), t); // int형으로 연산자 변환
            else if (typ == Type.FLOAT)// term의 타입이 float 라면
                return new Unary(u.op.floatMap(u.op.val), t); // float형으로 연산자 변환
            else if (typ == Type.CHAR)// term의 타입이 char 라면
                return new Unary(u.op.charMap(u.op.val), t); // char형으로 연산자 변환
            else if (typ == Type.BOOL)// term의 타입이 bool 라면
                return new Unary(u.op.boolMap(u.op.val), t);// bool형으로 연산자 변환
            throw new IllegalArgumentException("should never reach here");
        }
        throw new IllegalArgumentException("should never reach here");
    }

    public static Statement T(Statement s, TypeMap tm) { // statement 변환
        if (s instanceof Skip) // skip이라면
            return s;// 바로 리턴
        if (s instanceof Assignment) { // assignment 라면
            Assignment a = (Assignment) s; // assignment 형태로 저장
            Variable target = a.target; // 변수를 가져와 저장
            Expression src = T(a.source, tm); // source를 변환해 저장
            Type ttype = (Type) tm.get(a.target); // 변수의 타입 저장
            Type srctype = StaticTypeCheck.typeOf(a.source, tm); // source의 타입 저장
            if (ttype == Type.FLOAT) {// 변수의 타입이 float 라면
                if (srctype == Type.INT) { // source의 타입이 int라면
                    src = new Unary(new Operator(Operator.I2F), src); // float로 변환
                    srctype = Type.FLOAT; // float로 변환
                }
            } else if (ttype == Type.INT) { // 변수의 타입이 int 라면
                if (srctype == Type.CHAR) { // source의 타입이 char라면
                    src = new Unary(new Operator(Operator.C2I), src); // int로 변환
                    srctype = Type.INT;
                }
            }
            StaticTypeCheck.check(ttype == srctype,
                    "bug in assignment to " + target);
            return new Assignment(target, src);
        }
        if (s instanceof Conditional) { // conditional 이라면
            Conditional c = (Conditional) s;// conditional 형태로 변환
            Expression test = T(c.test, tm);// test 부분 변환
            Statement tbr = T(c.thenbranch, tm);// then 부분 변환
            Statement ebr = T(c.elsebranch, tm); // else 부분 변환
            return new Conditional(test, tbr, ebr); // 변환한 부분들을 이용해 새 객체 생성
        }
        if (s instanceof Loop) { // loop라면
            Loop l = (Loop) s; // loop 형태로 저장
            Expression test = T(l.test, tm); // test부분 변환
            Statement body = T(l.body, tm); // body부분 변환
            return new Loop(test, body); // 변환한 부분들을 넣어 새 객체 생성
        }
        if (s instanceof Block) { // block 이라면
            Block b = (Block) s; // block 형태로 저장
            Block newb = new Block(); // 새 block 객체 생성
            for (Statement stmt : b.members) // b의 멤버들을
                newb.members.add(T(stmt, tm)); // 하나씩 변환해 저장
            return newb;
        }
        throw new IllegalArgumentException("should never reach here");
    }

    public static void main(String args[]) {
        Parser parser = new Parser(new Lexer(args[0]));
        Program prog = parser.program();
        System.out.println("Begin parsing... " + args[0]);
        prog.display(); // student exercise
        System.out.println("\nBegin type checking..." + args[0]);
        System.out.println("Type map:");
        TypeMap map = StaticTypeCheck.typing(prog.decpart); // 타입 맵 생성
        map.display(); // student exercise //타입 맵 생성
        if (StaticTypeCheck.V(prog)) // 타입 에러 확인
            System.out.println("Fine type error");
        else {
            Program out = T(prog, map); // 변환한 ast 트리 만들기
            System.out.println("Transformed Abstract Syntax Tree");
            out.display(); // 출력
        }
        // student exercise
    } // main

} // class TypeTransformer
