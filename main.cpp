#include "Kill.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
	printf("**************QQ��������ɱ���****************\n");
	printf("*************�����������ʼ��ɱ***************\n");
	printf("******************����n����*******************\n");
	char n;
	CKill kill;
	int os = 0;
	printf("******�������������ϵͳ******\n\n0.Windows XP\n1.Windows 7\n");
	
	scanf("%d",&os);
	printf("*************�����������ʼ��ɱ***************\n");
	if(0 == os)
		kill.baseaddress = 0x00129F78;
	else
		kill.baseaddress = 0x00129F78;
	
	while(scanf("%c",&n))
	{
		getchar();
		if('n' == n)
		{
			printf("ллʹ�ã�\n");
			system("pause");
			break;
		}
		else
		{
			kill.OnKill();
		}
	}
	return 0;
}