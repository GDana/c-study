#include <stdio.h>

int main5(void)
{
	//int subway_1 = 30;	//����ö 1ȣ���� 30���� Ÿ�� �ִ�
	//int subway_2 = 40;
	//int subway_3 = 50;

	//printf("����ö 1ȣ���� %d ���� Ÿ�� �ֽ��ϴ�\n", subway_1);
	//printf("����ö 2ȣ���� %d ���� Ÿ�� �ֽ��ϴ�\n", subway_2);
	//printf("����ö 3ȣ���� %d ���� Ÿ�� �ֽ��ϴ�\n", subway_3);

	/*int subway_array[3];
	subway_array[0] = 30;
	subway_array[1] = 40;
	subway_array[2] = 50;

	for (int i = 0; i < 3; i++) {
		printf("����ö %d ȣ���� %d ���� Ÿ�� �ֽ��ϴ�\n", i + 1, subway_array[i]);
	}*/

	/*int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int i = 0; i < 10; i++) {
		printf("%d\n", arr[i]);
	}*/

	// ����, ���ڿ�
	//char c = 'A';
	//printf("%c\n", c);

	// ���ڿ� ������ '��'�� �ǹ��ϴ� Null ���� '\0'�� ���ԵǾ�� ��
	/*char str[6] = "coding";	*/
	//char str[7] = "coding";	//str[6]�� 0�� ���ԵǸ鼭 �������
	//printf("%s\n", str);
	//printf("%d\n", sizeof(str));

	//for (int i = 0; i < sizeof(str); i++) {
	//	printf("%c\n", str[i]);
	//}

	//char kor[] = "�����ڵ�";	// ->9byte, �ѱ� 8byte + ���ڿ� �� 1byte
	//printf("%s\n", kor);
	//printf("%d\n", sizeof(kor));
	//���� 1���� : 1byte
	//�ѱ� 1���� : 2byte

	//char c_array[10] = { 'c', 'o', 'd', 'i', 'n', 'g' };	
	//for (int i = 0; i < sizeof(c_array); i++) {
	//	printf("%c\n", c_array[i]);	//�ʱ�ȭ ���� ���� ���Ҵ� ����
	//}
	//for (int i = 0; i < sizeof(c_array); i++) {
	//	printf("%d\n", c_array[i]);	//�ƽ�Ű�ڵ�, �ʱ�ȭ ���� ���� ���Ҵ� 0
	//}

	printf("%c\n", 'a');
	printf("%d\n", 'a');

	printf("%c\n", 'b');
	printf("%d\n", 'b');

	printf("%c\n", 'A');
	printf("%d\n", 'A');

	printf("%c\n", '0');
	printf("%d\n", '0');

	printf("%c\n", '1');
	printf("%d\n", '1');

	return 0;
}