#include "utilForString.h"

/*
 * 将字符串dir的从第startIndex+1位开始长度为size的字串的末尾处的空格和end去掉
 * */
void dirProcess(char *dir,char end,int size)
{

        //去掉末尾空格和末尾的end
        while (size>0 && (isspace(dir[size-1]) || dir[size-1])==end) //循环判断最后一个字符是否为空格或end
        {
                dir[size-1] = '\0';        //将空格变为空字符,字符串缩短一个字符
                size = strlen(dir);                      //更新字符串长度       
        }
        //去掉开始空格
        while(size>0 && isspace(*dir))    //循环判断第一个字符是否为空格
        {
                 int index;
                 for( index= 0;index<size-1;index++)
                 {
                         dir[index] = dir[index+1];     //整体左移一个字符
                 }
                 dir[size-1] = '\0';    //舍去最后一个字符
                 size = strlen(dir);                      //更新字符串长度
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
 * 判断字符串在从指定位置开始size长度内有多少个parameter
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


