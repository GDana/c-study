#define _CRT_SECURE_NO_WARNINGS   
#include <stdio.h>
#include <string.h>    
#include <stdlib.h>    

struct Person {    
    char name[20];        
    float age;
    char address[100];    
    float* career;          // 구조체의 포인터 멤버 
};

int main()
{
    struct Person* p1 = malloc(sizeof(struct Person));    
    float num = 0.2;

    strcpy(p1->name, "김현선");
    p1->age = 29.9;
    strcpy(p1->address, "부천시 어딘구 어디동");
    p1->career = &num;

    printf("이름: %s\n", p1->name);       // 홍길동
    printf("나이: %f\n", p1->age);        // 30
    printf("주소: %s\n", p1->address);    // 서울시 용산구 한남동
    printf("개발 경력: %f\n", *p1->career);
    printf("개발 경력: %f\n", *(*p1).career);
 
    free(p1);    // 동적 메모리 해제

    return 0;
}