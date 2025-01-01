#include <stdio.h> 
typedef unsigned char *pointer;
// 데이터의 주소를 가리키는 데이터 타입

void show_bytes(pointer start, size_t len) {
    size_t i;
    for(i = 0; i < len; i++) {
        printf("%p\t0x%.2x\n",start+i,start[i]);
        printf("\n");
    }
    // 데이터 타입의 길이 만큼 낮은 주소부터 바이트에 저장된 값 출력
}

int main() {
    int a = 15213;
    printf("a = %x;\n", a);
    show_bytes((pointer)&a, sizeof(int));
}