#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "conio.h"

char dirFormat(char dir[]); 
void dirTrim(char dir[]);
void dirPreProcess(char dir[]);

#define True (1);
#define False (0)



int main() 
{
	
	while (1)
	{
	
		char dir[1000];
		
		printf("������·����\n");	//��ʾ�û�����
		gets(dir);
		//1.ȥ�ַ������˿ո��ĩβ��'/'
		dirTrim(dir); 
		printf("after dirTrim:\n");
		printf("%s\n",dir);
		//2.Ԥ����
		//��·���е�'//'ת��Ϊ'/'
		dirPreProcess(dir);
		printf("after dirPre:\n");
		printf("%s\n",dir);
		//3.�ж��û�������Ƿ��Ǿ���·��������
		if (!dirFormat(dir))
		{
			printf("����·����ʽ����\n");
			printf("�����������...\n");
			continue;
		}
		
		printf("·����ʽ���ɹ���%s\n",dir);

		printf("�����������...\n");

		getch();
	}

}

char dirFormat(char dir[])		//����True��������Ϊ����·�� 
{
	int length = strlen(dir);
	int index,tempIndex1=0,tempIndex2=0; //tempIndex1 --> /xx �ĸ���-1 tempIndex2 -->  /xx �ĳ���-1
	char tempDir[100][100]={{'\0'},{'\0'}};
	int deleteLen[100];		//��¼ÿ��formatedDir�������ȣ�����/../ʱ����
	int deleteIndex = 0;				//��������
	char formatedDir[10000];
	char *temp = formatedDir;
	if(length==0) return False;
	//����ĸ����'/'�ж�ΪFalse
	if(dir[0] != '/') return False;

	//��ÿ��'/xx/'���д���
	//1.�ȵõ�ÿ�� /xxxx
	for(index=0;index<length;index++)
	{
		if(dir[index]=='/')			//���� '/' ���м�¼
		{
			if(index) tempIndex1++;	//������һ�н��м�¼ ��0�����û���
			tempDir[tempIndex1][tempIndex2] = '\0';
			tempIndex2 = 0;
		}

		//&tempDir[tempIndex1] = /xxxx...
		tempDir[tempIndex1][tempIndex2] = dir[index];	//��¼
		tempIndex2++;
				
	}
	
	for(index=0;index<=tempIndex1;index++){
		length = strlen(tempDir[index]);
		
		//  "xx."��û���ַ� �����Ϲ淶 ֱ�ӷ���False
		if(length!=2 && length!=3 && tempDir[index][length-1]=='.')
			return False;

		//  "/./"��ʾ��ǰĿ¼ ֱ����ȥ����
		if(length ==2 && tempDir[index][0]=='/' && tempDir[index][1]=='.')
		{	
								
			continue;

		}
		
		//  "/../"��ʾ�ϲ�Ŀ¼ ���ϸ�/xxһ����ȥ����
		if(length ==3 && tempDir[index][0]=='/' && tempDir[index][1]=='.'&& tempDir[index][2]=='.')
		{
			if(deleteIndex) deleteIndex --;
			*(formatedDir+strlen(formatedDir)-deleteLen[deleteIndex]) = '\0';  //����
			continue;
		}
		
		
		//�� ʣ�µ� /xx ƴ��
		if(index<=tempIndex1) {
			strncat(formatedDir,tempDir[index],length);
			deleteLen[deleteIndex] = length;				//��¼���ӳ���
			deleteIndex ++;										//����+1

		}
			
	}
	
	
	//����ʽ������ַ�����dir
	 strncpy(dir,formatedDir,strlen(formatedDir));

	 *(dir+strlen(formatedDir)) = '\0';
	printf("after dirFormat:\n");
	printf("%s\n",dir);

	dirTrim(dir);
	return True;
	 
}
	


void dirPreProcess(char dir[])
{	
	int i;
	int wkIndex;
	int len = strlen(dir);
	for(i=1;i<len;i++){
		if(dir[i]=='/' && dir[i-1]=='/')	//���֡�//��
		{
			for(wkIndex=i;wkIndex<len-1;wkIndex++)
			{
				dir[wkIndex] = dir[wkIndex+1]; //�ӵڶ���'/'����������һ���ַ�
			}
			dir[len-1] = '\0';	//��ȥ���һ���ַ�
			len = strlen(dir); 	//�����ַ�������
			i--;
		}			
	}
}
void dirTrim(char dir[])
{
	int len = strlen(dir);
	
	char *p = dir + len - 1;		//�õ��ַ������һ���ַ�
	//ȥ��ĩβ�ո��ĩβ��'/'
	while (p >= dir  && (isspace(*p) || *p == '/'))	//ѭ���ж����һ���ַ��Ƿ�Ϊ�ո��'/'
	{
		*p = '\0';						//���ո��Ϊ���ַ�,�ַ�������һ���ַ�
		--p;							//��ָ��ָ�����ַ���ĩβ

	}

	//ȥ����ʼ�ո�
	while(isspace(*dir))	//ѭ���жϵ�һ���ַ��Ƿ�Ϊ�ո�
	{
		int index;
		for( index= 0;index<len-1;index++)
		{
			*(dir+index) = *(dir+index+1);	//�ַ�����������һ���ַ�
		}
		*(dir+len-1) = '\0';	//��ȥ���һ���ַ�
		len = strlen(dir);			//�����ַ�������
	}
} 


