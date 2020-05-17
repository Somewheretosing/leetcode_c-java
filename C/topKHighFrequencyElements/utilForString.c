#include "utilForString.h"

/*
 * ���ַ���dir�Ĵӵ�startIndex+1λ��ʼ����Ϊsize���ִ���ĩβ���Ŀո��endȥ��
 * */
void dirProcess(char *dir,char end,int size)
{

        //ȥ��ĩβ�ո��ĩβ��end
        while (size>0 && (isspace(dir[size-1]) || dir[size-1])==end) //ѭ���ж����һ���ַ��Ƿ�Ϊ�ո��end
        {
                dir[size-1] = '\0';        //���ո��Ϊ���ַ�,�ַ�������һ���ַ�
                size = strlen(dir);                      //�����ַ�������       
        }
        //ȥ����ʼ�ո�
        while(size>0 && isspace(*dir))    //ѭ���жϵ�һ���ַ��Ƿ�Ϊ�ո�
        {
                 int index;
                 for( index= 0;index<size-1;index++)
                 {
                         dir[index] = dir[index+1];     //��������һ���ַ�
                 }
                 dir[size-1] = '\0';    //��ȥ���һ���ַ�
                 size = strlen(dir);                      //�����ַ�������
                                                                                                                   }


}

int isLetter(char temp)
{
        if('a'<=temp<='z'|| 'A'<=temp<='Z')
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
        if('0'<=temp<='9')
        {
                return true;
        }
        else
        {
                return false;
        }
}

/**
 * �ж��ַ����ڴ�ָ��λ�ÿ�ʼsize�������ж��ٸ�parameter
 * */
int paramCount(char *string,char param,int size)
{       int count=0;
        int wkIndex;
        if(size==0)
                return count;
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


