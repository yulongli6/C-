#define _CRT_SECURE_NO_DEPRECATE 1
#include<stdio.h>
#if 0
void checkCPUendian()
{
	union {
		unsigned int a;
		unsigned char c;
	}endian;
	endian.a = 0x12345678;
	printf("%s\n", (0x12 == endian.c) ? "���ģʽ" : "С��ģʽ");
}

int main()
{
	checkCPUendian();
	return 0;
}
#endif

int checkCPUendian()
{
	int num = 1;
	if (*(char *)&num == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	if (checkCPUendian() == 1)
	{
		printf("���Ļ�����С���ֽ���\n");
	}
	else
	{
		printf("���Ļ����Ǵ���ֽ���\n");
	}
	return 0;
}
