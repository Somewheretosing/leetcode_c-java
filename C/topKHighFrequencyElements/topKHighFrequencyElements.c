#include "stdio.h"
#include "stdlib.h"
#include "utilForString.h"
#include "utilForNum.h"

#define true (1);
#define false (0);

typedef struct{
    int num;            //Ԫ��
    int time;           //���ִ���
    int rank;           //��Ƶ�����������ʣ���������������
}varAndTime;

int timesCount(int *num,varAndTime *varsAndTimes,int size);
void orderByTime(varAndTime *varsAndTimes,int size);
void rankByTime(varAndTime *varsAndTimes,int size);
int main()
{
    while(1)
    {
        char string[1000];
        int *num;
        int size;
        int K=0;
        char tempK[1000];
        int i,flag = true;
        int numCount;                   //��¼��ͬ���ֵĸ���
        memset(string,'\0',1000);   //��ʼ������
        memset(tempK,'\0',1000);
        printf("���������飬��\",\"�ָ�������س���ʾ����\n");
        printf("����8,9,10\n");
        scanf("%s",string);
        printf("������K��ֵ\n");
        scanf("%s",tempK);
        //1.Ԥ����
        //1.1�ַ����к������֡���,��������ַ�����������
        if(containsOthers(string,strlen(string)))
            continue;
        //1.2��������Ϊ��ʼ�ͽ�β ��������
        if((string[0]<'0'||string[0]>'9') || (string[strlen(string)-1]<'0'||string[strlen(string)-1]>'9'))
            continue;

        //2.���ַ��е����ִ浽������
        //2.1�ж��ַ������ж��ٸ�����                           
        size = paramCount(string,',',strlen(string))+1;
    
        //2.2Ϊ��������ڴ��С
        num = (int *)malloc(size * sizeof(int));
        memset(num,0,size);     //��ʼ��

        //2.3���ַ����е����ִ�������
        stringToNum(string,num);

        //3.����ÿ�����ֳ��ֵĴ���
        varAndTime varsAndTimes[100];         //�趨��ദ��100����ͬ������
        for(i=0;i<100;i++)
        {
            varsAndTimes[i].time = 0;       //��ʼ��
            varsAndTimes[i].num = 0;
            varsAndTimes[i].rank = 0;
        }
        numCount = timesCount(num,varsAndTimes,size);
        
        //4.K��ֵ�������֣�����K��ֵ����numCount,��������
        while(flag)
        {
            flag = false;   //�����ַ���������
            for(i=0;i<strlen(tempK);i++)
            {
                if(!isDigit(tempK[i]))
                {
                    printf("K����������������������K��ֵ��\n");
                    scanf("%s",tempK);
                    flag = true;        //���ַ����֣���������
                    break;  
                }
            }
            if(flag)    continue;       //K�������֣�����������У��
            sscanf(tempK,"%d",&K);      //�ַ���Kת��Ϊ����K
            if(K>numCount)
            {
                flag = true;        //K��ֵ������������
                printf("һ��ֻ��%d����ͬԪ�أ�K��ֵ���ܴ���%d,����������K��ֵ��\n",numCount,numCount);
                scanf("%s",tempK);
            }
        }
        printf("afterTiemsCount:\n");
        for(i=0;i<numCount;i++)
        {
            printf("%10d: %2d��\n",varsAndTimes[i].num,varsAndTimes[i].time);
        }
        
        //5. ����time��varsAndTimes��������,�Ӵ�С
        orderByTime(varsAndTimes,numCount);
        printf("afterOrderByTime:\n");
        for(i=0;i<numCount;i++)
        {
            printf("%10d: %2d��\n",varsAndTimes[i].num,varsAndTimes[i].time);
        }

        //6. ����time�Ӵ�С��varsAndTimes���л��ֵȼ���time��ͬ��Ϊͬһ��
        rankByTime(varsAndTimes,numCount);

        //7.������
        printf("���Ƶ��ǰ%d�ߵ�Ԫ��Ϊ��\n",K);
        for(i=0;varsAndTimes[i].rank<=K;i++)
        {
            printf("%10d: %2d��\n",varsAndTimes[i].num,varsAndTimes[i].time);
        }
        free(num);       //�ͷ��ڴ�ռ�
    }
    
    return 0;
}


int timesCount(int *num,varAndTime *varsAndTimes,int size)
{
    int wkIndexForNum;
    int wkIndexForVar=0;                //��¼��ͬԪ�صĸ���
    int wkIndex;
    int flag = false;
    //����num���ж�ÿһ��Ԫ����֮ǰ�Ƿ���ֹ������ֹ���time+1��num���ټ�¼;
    for(wkIndexForNum=0;wkIndexForNum<size;wkIndexForNum++)
    {
        if(wkIndexForNum==0)                                //��һ��Ԫ��ֱ�Ӽ�¼����
        {
            varsAndTimes[wkIndexForVar].num = num[wkIndexForNum];
            varsAndTimes[wkIndexForVar].time++;
            wkIndexForVar++;
            continue;
        }
        //�ӵڶ���Ԫ�ؿ�ʼ�ж��Ƿ���ֹ�
        for(wkIndex=0;wkIndex<wkIndexForVar;wkIndex++)
        {
            if(varsAndTimes[wkIndex].num==num[wkIndexForNum])       //���Ԫ���Ѿ�����¼�����Ѿ����ֹ�������time+1;
            {
                varsAndTimes[wkIndex].time++;
                flag = true;
                break;
            }
            
        }
        if(!flag)                   //û�г��ֹ�
        {
            varsAndTimes[wkIndexForVar].num = num[wkIndexForNum];
            varsAndTimes[wkIndexForVar].time++;
            wkIndexForVar++;                                    //����+1
        }

        flag = false;
    }
    return wkIndexForVar;

}

void orderByTime(varAndTime *varsAndTimes,int size)
{
    int wkIndex1,wkIndex2;
    varAndTime temp;
    for(wkIndex1=0;wkIndex1<size-1;wkIndex1++)
    {
        for(wkIndex2=wkIndex1+1;wkIndex2<size;wkIndex2++)
        {
            //��timeֵ�ϴ�Ľṹ����ǰ��
            if(varsAndTimes[wkIndex2].time>varsAndTimes[wkIndex1].time){        //�������ǰ��
                temp = varsAndTimes[wkIndex1];               //����
                varsAndTimes[wkIndex1] = varsAndTimes[wkIndex2];
                varsAndTimes[wkIndex2] = temp;
            }
            
        }

    }

}

void rankByTime(varAndTime *varsAndTimes,int size)
{
    int wkIndex,time;
    int rank = 1;
    varAndTime temp;
    //��һ��Ԫ��time���ֱ����Ϊ��һ��,��time��Ϊ����
    time = varsAndTimes[0].time;
    varsAndTimes[0].rank = rank;

    //����Ԫ�ص�time���������time�Աȣ����зֵ�
    for(wkIndex=1;wkIndex<size;wkIndex++)
    {
        if(varsAndTimes[wkIndex].time==time)        //Ԫ��time�������ͬ���������������ͬ
        {
            varsAndTimes[wkIndex].rank = rank;
        }    
        else                                        //Ԫ��timeС�ڲ�����ͬ��������Ϊ���Ӧ�±�+1��
        {
            varsAndTimes[wkIndex].rank = wkIndex+1;
            time = varsAndTimes[wkIndex].time;      //���²���
        }
        
    }

}



