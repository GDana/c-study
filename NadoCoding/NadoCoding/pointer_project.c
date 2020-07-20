#include <stdio.h>
#include <time.h>

// ����Ⱑ 6������ �־��
// �̵��� ���׿� ��� �ִµ�, �縷�̿���
// �縷�� �ʹ� ������.. �ʹ� �����ؼ� ���� ���� ���� ���� �ؿ�.
// ���� �� �����ϱ� ���� �������� ���׿� ���� �༭ ����⸦ ����ּ���
// ������ �ð��� �������� ���� Ŀ����.. ���߿��� �ȳ�

int level;
int arrayFish[6];
int* cursor;
void initData();
void printFishes();

int main(void) {
	long startTime = 0;	//���� ���� �ð�
	long totalElapsedTime = 0;	//�� ��� �ð�
	long prevElapesdTime = 0;	//���� ��� �ð�(�ֱٿ� ���� �� �ð� ����)

	int num;	//�� �� ���׿� ���� �� ������ ����� �Է�
	initData();

	cursor = arrayFish;	//cursor[0].. cursour[1]..
	startTime = clock();	//���� �ð��� millisecond(1000���� 1��) ������ ��ȯ

	while (1) {
		printFishes();
		//getchar();	//�ӽ÷� ����� �Է� ���
		printf("�� �� ���׿� ���� �ֽðھ��?");
		scanf_s("%d", &num);

		//�Է°� üũ
		if (num < 1 || num > 6) {
			printf("\n�Է°��� �߸� �Ǿ����ϴ�\n");
			continue;
		}

		// �� ��� �ð�
		totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC;
		printf("�� ��� �ð� : %ld ��\n", totalElapsedTime);

		// ���� �� �� �ð�(���������� �� �� �ð�) ���ķ� �帥 �ð�
		prevElapesdTime = totalElapsedTime - prevElapesdTime;
		printf("�ֱ� ��� �ð� : %ld ��\n", prevElapesdTime);
	}
	return 0;
}

void initData() {
	level = 1;	//���� ����(1~5)
	for (int i = 0; i < 6; i++) {
		arrayFish[i] = 100;	//������ �� ����(0 ~ 100)
	}
}

void printFishes() {
	printf("%3d�� %3d�� %3d�� %3d�� %3d�� %3d��\n", 1, 2, 3, 4, 5, 6);
	for (int i = 0; i < 6; i++) {
		printf(" %4d ", arrayFish[i]);
	}
	printf("\n\n");
}