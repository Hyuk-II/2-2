#include <stdio.h>
#include <string.h>
/* 공격자
가 호출하려는 타겟 함수 */
void target_function() { printf("Exploit 성공! target_function 호출 완료.\n"); }
/* 취약한 함수 */
void echo() {
    char buf[8]; /* 너무 작은 버퍼 */
    gets(buf);   /* 입력 크기를 확인하지 않음 */
    puts(buf);
}
/* 메인 함수 */
int main() {
    echo(); // 취약한 함수 호출
    return 0;
}