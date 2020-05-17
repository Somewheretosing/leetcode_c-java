#include "stdio.h"
#include "stdlib.h"
#include "utilForString.h"
#include "utilForNum.h"

#define true (1);
#define false (0);

typedef struct{
    int num;            //元素
    int time;           //出现次数
    int rank;           //按频率排序后的名词（包含并列排名）
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
        int numCount;                   //记录不同数字的个数
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

        //2.将字符中的数字存到数组中
        //2.1判断字符串中有多少个数字                           
        size = paramCount(string,',',strlen(string))+1;
    
        //2.2为数组分配内存大小
        num = (int *)malloc(size * sizeof(int));
        memset(num,0,size);     //初始化

        //2.3将字符串中的数字存入数组
        stringToNum(string,num);

        //3.计算每个数字出现的次数
        varAndTime varsAndTimes[100];         //设定最多处理100个不同的数字
        for(i=0;i<100;i++)
        {
            varsAndTimes[i].time = 0;       //初始化
            varsAndTimes[i].num = 0;
            varsAndTimes[i].rank = 0;
        }
        numCount = timesCount(num,varsAndTimes,size);
        
        //4.K的值不是数字，或者K的值超过numCount,重新输入
        while(flag)
        {
            flag = false;   //所有字符都是数字
            for(i=0;i<strlen(tempK);i++)
            {
                if(!isDigit(tempK[i]))
                {
                    printf("K必须是整数，请重新输入K的值：\n");
                    scanf("%s",tempK);
                    flag = true;        //出现非数字，重新输入
                    break;  
                }
            }
            if(flag)    continue;       //K不是数字，不进行以下校验
            sscanf(tempK,"%d",&K);      //字符串K转换为数字K
            if(K>numCount)
            {
                flag = true;        //K的值过大，重新输入
                printf("一共只有%d个不同元素，K的值不能大于%d,请重新输入K的值：\n",numCount,numCount);
                scanf("%s",tempK);
            }
        }
        printf("afterTiemsCount:\n");
        for(i=0;i<numCount;i++)
        {
            printf("%10d: %2d次\n",varsAndTimes[i].num,varsAndTimes[i].time);
        }
        
        //5. 根据time对varsAndTimes重新排序,从大到小
        orderByTime(varsAndTimes,numCount);
        printf("afterOrderByTime:\n");
        for(i=0;i<numCount;i++)
        {
            printf("%10d: %2d次\n",varsAndTimes[i].num,varsAndTimes[i].time);
        }

        //6. 根据time从大到小对varsAndTimes进行划分等级，time相同的为同一级
        rankByTime(varsAndTimes,numCount);

        //7.输出结果
        printf("输出频率前%d高的元素为：\n",K);
        for(i=0;varsAndTimes[i].rank<=K;i++)
        {
            printf("%10d: %2d次\n",varsAndTimes[i].num,varsAndTimes[i].time);
        }
        free(num);       //释放内存空间
    }
    
    return 0;
}


int timesCount(int *num,varAndTime *varsAndTimes,int size)
{
    int wkIndexForNum;
    int wkIndexForVar=0;                //记录不同元素的个数
    int wkIndex;
    int flag = false;
    //遍历num，判断每一个元素在之前是否出现过，出现过则time+1，num不再记录;
    for(wkIndexForNum=0;wkIndexForNum<size;wkIndexForNum++)
    {
        if(wkIndexForNum==0)                                //第一个元素直接记录下来
        {
            varsAndTimes[wkIndexForVar].num = num[wkIndexForNum];
            varsAndTimes[wkIndexForVar].time++;
            wkIndexForVar++;
            continue;
        }
        //从第二个元素开始判断是否出现过
        for(wkIndex=0;wkIndex<wkIndexForVar;wkIndex++)
        {
            if(varsAndTimes[wkIndex].num==num[wkIndexForNum])       //这个元素已经被记录，即已经出现过，将其time+1;
            {
                varsAndTimes[wkIndex].time++;
                flag = true;
                break;
            }
            
        }
        if(!flag)                   //没有出现过
        {
            varsAndTimes[wkIndexForVar].num = num[wkIndexForNum];
            varsAndTimes[wkIndexForVar].time++;
            wkIndexForVar++;                                    //个数+1
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
            //将time值较大的结构体往前移
            if(varsAndTimes[wkIndex2].time>varsAndTimes[wkIndex1].time){        //后面大于前面
                temp = varsAndTimes[wkIndex1];               //交换
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
    //第一个元素time最大，直接排为第一等,其time作为参照
    time = varsAndTimes[0].time;
    varsAndTimes[0].rank = rank;

    //后面元素的time依次与参照time对比，进行分等
    for(wkIndex=1;wkIndex<size;wkIndex++)
    {
        if(varsAndTimes[wkIndex].time==time)        //元素time与参照相同，则名次与参照相同
        {
            varsAndTimes[wkIndex].rank = rank;
        }    
        else                                        //元素time小于参照相同，则名次为其对应下标+1；
        {
            varsAndTimes[wkIndex].rank = wkIndex+1;
            time = varsAndTimes[wkIndex].time;      //更新参照
        }
        
    }

}



