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
        memset(string,'\0',1000);   //初始化数组
        memset(tempK,'\0',1000);
        printf("请输入数组，以\",\"分隔，输入回车表示结束\n");
        printf("例：8,9,10\n");
        scanf("%s",string);
        printf("请输入K的值\n");
        scanf("%s",tempK);
        //1.预处理
        //1.1字符串中含有数字、‘,’以外的字符，重新输入
        if(containsOthers(string,strlen(string)))
            continue;
        //1.2不以数字为起始和结尾 重新输入
        if((string[0]<'0'||string[0]>'9') || (string[strlen(string)-1]<'0'||string[strlen(string)-1]>'9'))
            continue;
        //1.3 K的值不是数字，重新输入
        while(flag)
        {
            flag = false;   //所有字符都是数字
            for(i=0;i<strlen(tempK);i++)
            {
                if(!isDigit(tempK[i]))
                {
                    printf("K必须是整数，请重新输入\n");
                    scanf("%s",tempK);
                    flag = true;        //出现非数字，重新输入
                    break;  
                }
            }
            
        }
        
        sscanf(tempK,"%d",&K);      //字符串K转换为数字K
        //2.将字符中的数字存到数组中
        //2.1判断字符串中有多少个数字                           
        size = paramCount(string,',',strlen(string))+1;
        if(K>size||K<=0)  continue;   //K的最大值为数组尺寸,最小值为1
        //2.2为数组分配内存大小
        num = (int *)malloc(size * sizeof(int));
        memset(num,0,size);     //初始化
        //2.3将字符串中的数字存入数组
        stringToNum(string,num);
        //3.将数组按照从大到小的顺序进行冒泡排序
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
        //4.输出第K大的数值，即num[K-1]
        printf("第%d大的数值： %d\n",K,num[K-1]);

        free(num);       //释放内存空间
    }
    
    return 0;
}

//判断是否含有数字、‘,'以外的字符
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
            //将大值往前移
            if(num[wkIndex2]>num[wkIndex1]) //后面大于前面
            {        
                temp = num[wkIndex1];               //交换
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
 * 判断字符串在从指定位置开始size长度内有多少个param
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
    char temp[20];          //设定单个数字最多20位                  
    int tempSize =0;        //单个数字的位数
    int tempNum;
    memset(temp,'\0',20);           //将temp初始化，设为空字符串
    while(wkIndexOfString<len)
    {
        
        //1.将单个数字分别分离出来
        if(string[wkIndexOfString]!=',')
        {
            temp[tempSize] = string[wkIndexOfString];       //将数字单独存储至temp中
            tempSize++;
        }
        else            //遇到‘,’
        {
            temp[tempSize] = '\0';                          //该数字存储结束
                
            //2.将','前面的数字转化为字符串
            if(tempSize)
            {
                if(sscanf(temp,"%d",&num[wkIndexOfNum])<0)              //转化失败，表示输入数字有误
                {
                    return false;
                }
                
                wkIndexOfNum++;
                memset(temp,'\0',20);           //将temp初始化，设为空字符串
            }
            else
            {
                //可能同时出现两个',' 导致tempsize=0
                return false;
            }    

            tempSize = 0;                                   //reset,为下次存储做准备
            
        }
        wkIndexOfString++;                              //判断下个字符

    }
    if(sscanf(temp,"%d",&num[wkIndexOfNum])<0)              //最后一个数字后没有逗号，循环外单独转换
    {
        return false;
    }
    return true;
}

