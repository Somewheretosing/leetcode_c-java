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
		
		printf("请输入路径：\n");	//提示用户输入
		gets(dir);
		//1.去字符串两端空格和末尾的'/'
		dirTrim(dir); 
		printf("after dirTrim:\n");
		printf("%s\n",dir);
		//2.预处理
		//将路径中的'//'转化为'/'
		dirPreProcess(dir);
		printf("after dirPre:\n");
		printf("%s\n",dir);
		//3.判断用户输入的是否是绝对路径并处理
		if (!dirFormat(dir))
		{
			printf("输入路径格式不对\n");
			printf("按任意键继续...\n");
			continue;
		}
		
		printf("路径格式化成功：%s\n",dir);

		printf("按任意键继续...\n");

		getch();
	}

}

char dirFormat(char dir[])		//返回True代表输入为绝对路径 
{
	int length = strlen(dir);
	int index,tempIndex1=0,tempIndex2=0; //tempIndex1 --> /xx 的个数-1 tempIndex2 -->  /xx 的长度-1
	char tempDir[100][100]={{'\0'},{'\0'}};
	int deleteLen[100];		//记录每次formatedDir增长长度，遇到/../时回退
	int deleteIndex = 0;				//回退索引
	char formatedDir[10000];
	char *temp = formatedDir;
	if(length==0) return False;
	//首字母不是'/'判定为False
	if(dir[0] != '/') return False;

	//对每个'/xx/'进行处理
	//1.先得到每个 /xxxx
	for(index=0;index<length;index++)
	{
		if(dir[index]=='/')			//遇到 '/' 换行记录
		{
			if(index) tempIndex1++;	//进入下一行进行记录 第0个不用换行
			tempDir[tempIndex1][tempIndex2] = '\0';
			tempIndex2 = 0;
		}

		//&tempDir[tempIndex1] = /xxxx...
		tempDir[tempIndex1][tempIndex2] = dir[index];	//记录
		tempIndex2++;
				
	}
	
	for(index=0;index<=tempIndex1;index++){
		length = strlen(tempDir[index]);
		
		//  "xx."后没有字符 不符合规范 直接返回False
		if(length!=2 && length!=3 && tempDir[index][length-1]=='.')
			return False;

		//  "/./"表示当前目录 直接舍去即可
		if(length ==2 && tempDir[index][0]=='/' && tempDir[index][1]=='.')
		{	
								
			continue;

		}
		
		//  "/../"表示上层目录 连上个/xx一并舍去即可
		if(length ==3 && tempDir[index][0]=='/' && tempDir[index][1]=='.'&& tempDir[index][2]=='.')
		{
			if(deleteIndex) deleteIndex --;
			*(formatedDir+strlen(formatedDir)-deleteLen[deleteIndex]) = '\0';  //回退
			continue;
		}
		
		
		//将 剩下的 /xx 拼接
		if(index<=tempIndex1) {
			strncat(formatedDir,tempDir[index],length);
			deleteLen[deleteIndex] = length;				//记录增加长度
			deleteIndex ++;										//索引+1

		}
			
	}
	
	
	//将格式化后的字符串给dir
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
		if(dir[i]=='/' && dir[i-1]=='/')	//出现“//”
		{
			for(wkIndex=i;wkIndex<len-1;wkIndex++)
			{
				dir[wkIndex] = dir[wkIndex+1]; //从第二个'/'处整体左移一个字符
			}
			dir[len-1] = '\0';	//舍去最后一个字符
			len = strlen(dir); 	//更新字符串长度
			i--;
		}			
	}
}
void dirTrim(char dir[])
{
	int len = strlen(dir);
	
	char *p = dir + len - 1;		//得到字符串最后一个字符
	//去掉末尾空格和末尾的'/'
	while (p >= dir  && (isspace(*p) || *p == '/'))	//循环判断最后一个字符是否为空格或'/'
	{
		*p = '\0';						//将空格变为空字符,字符串缩短一个字符
		--p;							//将指针指向新字符串末尾

	}

	//去掉开始空格
	while(isspace(*dir))	//循环判断第一个字符是否为空格
	{
		int index;
		for( index= 0;index<len-1;index++)
		{
			*(dir+index) = *(dir+index+1);	//字符串整体左移一个字符
		}
		*(dir+len-1) = '\0';	//舍去最后一个字符
		len = strlen(dir);			//更新字符串长度
	}
} 


