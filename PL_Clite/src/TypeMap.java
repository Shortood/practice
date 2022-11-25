import java.util.*;

public class TypeMap extends HashMap<Variable, Type> {

    // TypeMap is implemented as a Java HashMap.
    // Plus a 'display' method to facilitate experimentation.
    public void display() { // 해쉬 형태로 만들어져 있는 타입맵을 출력
        String temp = ""; // 문자열 초기화
        for (Map.Entry<Variable, Type> e : this.entrySet()) { // 해쉬에 저장되어 있는 값들을 모두 본다
            if (e != null) { // 키와 값을 합쳐 문자열에 추가
                temp += "<" + e.getKey() + ", " + e.getValue() + ">, ";
            }
        } // 출력
        System.out.println("{ " + temp.substring(0, Math.max(temp.length() - 2, 1)) + " }\n");
    }

}
