#include "stdio.h"
#include "stdlib.h"


void dirProcess(char *dir,char end,int size);
int isLetter(char temp);
int isDigit(char temp);
int paramCount(char *string,char param,int size);
int stringToNum(char *string,int *num);
int containsOthers(char *string,int size);
void arrayOrderBToS(int *num,int size);

#define true (1);
#define false (0);

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
        //1.3 K��ֵ�������֣���������
        while(flag)
        {
            flag = false;   //�����ַ���������
            for(i=0;i<strlen(tempK);i++)
            {
                if(!isDigit(tempK[i]))
                {
                    printf("K����������������������\n");
                    scanf("%s",tempK);
                    flag = true;        //���ַ����֣���������
                    break;  
                }
            }
            
        }
        
        sscanf(tempK,"%d",&K);      //�ַ���Kת��Ϊ����K
        //2.���ַ��е����ִ浽������
        //2.1�ж��ַ������ж��ٸ�����                           
        size = paramCount(string,',',strlen(string))+1;
        if(K>size||K<=0)  continue;   //K�����ֵΪ����ߴ�,��СֵΪ1
        //2.2Ϊ��������ڴ��С
        num = (int *)malloc(size * sizeof(int));
        memset(num,0,size);     //��ʼ��
        //2.3���ַ����е����ִ�������
        stringToNum(string,num);
        //3.�����鰴�մӴ�С��˳�����ð������
        arrayOrderBToS(num,size);
        printf("afterOrder:\n");
        for(i=0;i<size;i++)
        {
            if(i==size-1)
            {
                printf("%d\n",num[i]);
                break;
            }
            printf("%d, ",num[i]);
        }
        //4.�����K�����ֵ����num[K-1]
        printf("��%d�����ֵ�� %d\n",K,num[K-1]);

        free(num);       //�ͷ��ڴ�ռ�
    }
    
    return 0;
}

//�ж��Ƿ������֡���,'������ַ�
int containsOthers(char *string,int size)
{
    int wkIndex;
    for(wkIndex=0;wkIndex<size;wkIndex++)
    {
        if(!isDigit(string[wkIndex]) && !string[wkIndex]==',')
        {
            return true;
        }        
      
    }
    return false;

}

void arrayOrderBToS(int *num,int size)
{
    int wkIndex1,wkIndex2;
    int temp;
    for(wkIndex1=0;wkIndex1<size-1;wkIndex1++)
    {
        for(wkIndex2=wkIndex1+1;wkIndex2<size;wkIndex2++)
        {
            //����ֵ��ǰ��
            if(num[wkIndex2]>num[wkIndex1]) //�������ǰ��
            {        
                temp = num[wkIndex1];               //����
                num[wkIndex1] = num[wkIndex2];
                num[wkIndex2] = temp;
            }
            
        }

    }
}


int isLetter(char temp)
{
    if(('a'<=temp&&temp<='z')|| ('A'<=temp&&temp<='Z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int isDigit(char temp)
{
    if('0'<=temp && temp<='9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * �ж��ַ����ڴ�ָ��λ�ÿ�ʼsize�������ж��ٸ�param
 * */
int paramCount(char *string,char param,int size)
{   
    int count=0;
    int wkIndex;
    if(size==0)
    {
        return count;
    }   
    for(wkIndex=0;wkIndex<size;wkIndex++)
    {
        if(string[wkIndex]==param)
            count++;
    }
    return count;
}

int stringToNum(char* string,int *num)
{
    int len = strlen(string);
    int wkIndexOfNum = 0;
    int wkIndexOfString = 0;
    char temp[20];          //�趨�����������20λ                  
    int tempSize =0;        //�������ֵ�λ��
    int tempNum;
    memset(temp,'\0',20);           //��temp��ʼ������Ϊ���ַ���
    while(wkIndexOfString<len)
    {
        
        //1.���������ֱַ�������
        if(string[wkIndexOfString]!=',')
        {
            temp[tempSize] = string[wkIndexOfString];       //�����ֵ����洢��temp��
            tempSize++;
        }
        else            //������,��
        {
            temp[tempSize] = '\0';                          //�����ִ洢����
                
            //2.��','ǰ�������ת��Ϊ�ַ���
            if(tempSize)
            {
                if(sscanf(temp,"%d",&num[wkIndexOfNum])<0)              //ת��ʧ�ܣ���ʾ������������
                {
                    return false;
                }
                
                wkIndexOfNum++;
                memset(temp,'\0',20);           //��temp��ʼ������Ϊ���ַ���
            }
            else
            {
                //����ͬʱ��������',' ����tempsize=0
                return false;
            }    

            tempSize = 0;                                   //reset,Ϊ�´δ洢��׼��
            
        }
        wkIndexOfString++;                              //�ж��¸��ַ�

    }
    if(sscanf(temp,"%d",&num[wkIndexOfNum])<0)              //���һ�����ֺ�û�ж��ţ�ѭ���ⵥ��ת��
    {
        return false;
    }
    return true;
}

