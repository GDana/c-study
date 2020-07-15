#include <stdio.h>

int main5(void)
{
	//int subway_1 = 30;	//지하철 1호차에 30명이 타고 있다
	//int subway_2 = 40;
	//int subway_3 = 50;

	//printf("지하철 1호차에 %d 명이 타고 있습니다\n", subway_1);
	//printf("지하철 2호차에 %d 명이 타고 있습니다\n", subway_2);
	//printf("지하철 3호차에 %d 명이 타고 있습니다\n", subway_3);

	/*int subway_array[3];
	subway_array[0] = 30;
	subway_array[1] = 40;
	subway_array[2] = 50;

	for (int i = 0; i < 3; i++) {
		printf("지하철 %d 호차에 %d 명이 타고 있습니다\n", i + 1, subway_array[i]);
	}*/

	/*int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int i = 0; i < 10; i++) {
		printf("%d\n", arr[i]);
	}*/

	// 문자, 문자열
	//char c = 'A';
	//printf("%c\n", c);

	// 문자열 끝에는 '끝'을 의미하는 Null 문자 '\0'이 포함되어야 함
	/*char str[6] = "coding";	*/
	//char str[7] = "coding";	//str[6]에 0이 삽입되면서 정상출력
	//printf("%s\n", str);
	//printf("%d\n", sizeof(str));

	//for (int i = 0; i < sizeof(str); i++) {
	//	printf("%c\n", str[i]);
	//}

	//char kor[] = "나도코딩";	// ->9byte, 한글 8byte + 문자열 끝 1byte
	//printf("%s\n", kor);
	//printf("%d\n", sizeof(kor));
	//영어 1글자 : 1byte
	//한글 1글자 : 2byte

	//char c_array[10] = { 'c', 'o', 'd', 'i', 'n', 'g' };	
	//for (int i = 0; i < sizeof(c_array); i++) {
	//	printf("%c\n", c_array[i]);	//초기화 되지 않은 원소는 공백
	//}
	//for (int i = 0; i < sizeof(c_array); i++) {
	//	printf("%d\n", c_array[i]);	//아스키코드, 초기화 되지 않은 원소는 0
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