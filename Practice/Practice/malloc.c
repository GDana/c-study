#define _CRT_SECURE_NO_WARNINGS   
#include <stdio.h>
#include <string.h>    
#include <stdlib.h>    

struct Person {    
    char name[20];        
    float age;
    char address[100];    
    float* career;          // ����ü�� ������ ��� 
};

int main()
{
    struct Person* p1 = malloc(sizeof(struct Person));    
    float num = 0.2;

    strcpy(p1->name, "������");
    p1->age = 29.9;
    strcpy(p1->address, "��õ�� ��� ���");
    p1->career = &num;

    printf("�̸�: %s\n", p1->name);       // ȫ�浿
    printf("����: %f\n", p1->age);        // 30
    printf("�ּ�: %s\n", p1->address);    // ����� ��걸 �ѳ���
    printf("���� ���: %f\n", *p1->career);
    printf("���� ���: %f\n", *(*p1).career);
 
    free(p1);    // ���� �޸� ����

    return 0;
}