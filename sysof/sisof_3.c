#include <stdio.h>
#include <string.h>

int main() {
    char indev[25] = "0010030C1006000005FFFFFF?";  //문자열
    char temp;                                     //문자 임시저장
    int hex[25] = {
        //수 저장
        0,
    };
    for (int i = 0; i < 25; i++) {
        if (indev[i] >= 'A' && indev[i] <= 'F') {        //만약 A와 F사이의 수라면
            temp = indev[i] - 'A' + 10;                  // A의 아스키코드값 만큼 뺴준다
        } else if (indev[i] >= '0' && indev[i] < '9') {  // 0부터 9사이의 수라면
            temp = indev[i] - '0';                       // 0의 아스키 코드만큼 빼준다
        }
        hex[i] = temp;  //수로 바뀐 값을 저장
    }

    for (int i = 0; i < 25; i++) {  // 16진수로 출력
        printf("%x", hex[i]);
    }
    printf("\n");
}