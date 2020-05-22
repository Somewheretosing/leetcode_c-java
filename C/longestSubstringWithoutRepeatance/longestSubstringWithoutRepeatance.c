#include "stdio.h"

#define true (1)
#define false (0)

int process(char *wkString,int wkLength);
int containsRepeatance(char *wkString,int wkLength);

void main()
{
    char ucInputString[100];    //�����û�������ַ���
    int wkLength;             //�ַ�������
    int wkSubLength;
    while(1)
    {
        memset(ucInputString,0,100);    //��ʼ��
        wkLength = 0;
        wkSubLength = 0;
        printf("�������ַ��������Ȳ��ܳ���100��\n");
        scanf("%s",ucInputString);

        wkLength = strlen(ucInputString);
        if(wkLength==0)                           //�û�����Ϊ��ʱ��������
        {
            printf("�����ַ�������Ϊ��\n");
            continue;
        }

        wkSubLength = process(ucInputString,wkLength);
        printf("�������ظ��ӷ�����Ӵ�����Ϊ��%d\n",wkSubLength);
    }

}

/**
 * ��ԭ�ַ���������Ϊ�Ӵ����ȣ��ж��Ӵ��Ƿ�����ظ��ַ�
 * ֱ���Ӵ��������ظ��ַ������ش�ʱ�Ӵ�����
 * �Ӵ���������Ϊ1
*/

int process(char *wkString,int wkLength)
{
    int wkStartIndex = 0;        //�Ӵ��ĳ�ʼλ�ã���ʼΪ0
    int wkSubLength = wkLength;          //�Ӵ����ȣ���ʼΪԭ�ַ����ĳ���
    int wkResult = false;
    while(wkSubLength)
    {
        for(wkStartIndex=0;wkStartIndex+wkSubLength<=wkLength;wkStartIndex++)       //���������Ӵ�
        {
            wkResult = containsRepeatance(&wkString[wkStartIndex],wkSubLength);     //�ж��Ӵ����Ƿ����ظ��ַ�     
            if(wkResult == false)
            {
                //�Ӵ��в������ظ��ַ�,��ʱ�Ӵ�����Ϊ�����ظ��ַ�������Ӵ�����
                return wkSubLength;            //�����Ӵ�����
            }
            else
            {
                //�Ӵ��к����ظ��ַ��������ж���һ���Ӵ�
            }
        }
        //����ΪwkLength�������Ӵ��������ظ��ַ��������Ӵ����ȣ�����Ѱ��
        wkSubLength --;
        if(wkSubLength==1)
        {
            return wkSubLength;     //�Ӵ��������Ϊ1�����ټ���Ѱ��,ֱ�ӷ���
        }
    }
    
}

/**
 * �ӳ�ʼ�ַ���ʼ�ж�ʣ�µ��ַ����Ƿ��и��ַ������������ж��¸��ַ���
 * ֱ���ж��������ڶ����ַ��Ӳ�������ظ�������Ϊ�ַ����������ظ��ַ�
 * return : false --> �����ظ��ַ��� true -->�����ظ��ַ�
*/
int containsRepeatance(char *wkString,int wkLength)
{
    int wkStartIndex;   //���յ���ʼλ��
    int wkTemp;             //������ַ����бȽϵ��ַ�λ��
    for(wkStartIndex=0;wkStartIndex<wkLength-1;wkStartIndex++)      //startIndex�ӵ�0λ��������wkLength-1λ
    {
        for(wkTemp=wkStartIndex+1;wkTemp<wkLength;wkTemp++)         //��startIndex����ַ�����Ƚϣ��ж��Ƿ���ͬ
        {
            if(wkString[wkStartIndex]==wkString[wkTemp])
            {
                //������ͬ�ַ���return true
                return true;
            }
        }
    }
    //�����ַ�������ͬ return false
    return false;
}










