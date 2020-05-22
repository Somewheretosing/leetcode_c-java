#include "stdio.h"

#define true (1)
#define false (0)

int process(char *wkString,int wkLength);
int containsRepeatance(char *wkString,int wkLength);

void main()
{
    char ucInputString[100];    //接收用户输入的字符串
    int wkLength;             //字符串长度
    int wkSubLength;
    while(1)
    {
        memset(ucInputString,0,100);    //初始化
        wkLength = 0;
        wkSubLength = 0;
        printf("请输入字符串：长度不能超过100：\n");
        scanf("%s",ucInputString);

        wkLength = strlen(ucInputString);
        if(wkLength==0)                           //用户输入为空时重新输入
        {
            printf("输入字符串不能为空\n");
            continue;
        }

        wkSubLength = process(ucInputString,wkLength);
        printf("不包含重复子符的最长子串长度为：%d\n",wkSubLength);
    }

}

/**
 * 以原字符串长度作为子串长度，判断子串是否包含重复字符
 * 直至子串不包含重复字符，返回此时子串长度
 * 子串长度最少为1
*/

int process(char *wkString,int wkLength)
{
    int wkStartIndex = 0;        //子串的初始位置，初始为0
    int wkSubLength = wkLength;          //子串长度，初始为原字符串的长度
    int wkResult = false;
    while(wkSubLength)
    {
        for(wkStartIndex=0;wkStartIndex+wkSubLength<=wkLength;wkStartIndex++)       //遍历所有子串
        {
            wkResult = containsRepeatance(&wkString[wkStartIndex],wkSubLength);     //判断子串中是否含有重复字符     
            if(wkResult == false)
            {
                //子串中不含有重复字符,此时子串长度为不含重复字符的最大子串长度
                return wkSubLength;            //返回子串长度
            }
            else
            {
                //子串中含有重复字符，继续判断下一个子串
            }
        }
        //长度为wkLength的所有子串均含有重复字符，缩短子串长度，继续寻找
        wkSubLength --;
        if(wkSubLength==1)
        {
            return wkSubLength;     //子串长度最短为1，不再继续寻找,直接返回
        }
    }
    
}

/**
 * 从初始字符开始判断剩下的字符中是否含有该字符，若含有则判断下个字符，
 * 直至判断至倒数第二个字符扔不会出现重复，则视为字符串不含有重复字符
 * return : false --> 不含重复字符； true -->含有重复字符
*/
int containsRepeatance(char *wkString,int wkLength)
{
    int wkStartIndex;   //参照的起始位置
    int wkTemp;             //与参照字符进行比较的字符位置
    for(wkStartIndex=0;wkStartIndex<wkLength-1;wkStartIndex++)      //startIndex从第0位遍历至第wkLength-1位
    {
        for(wkTemp=wkStartIndex+1;wkTemp<wkLength;wkTemp++)         //拿startIndex后的字符与其比较，判断是否相同
        {
            if(wkString[wkStartIndex]==wkString[wkTemp])
            {
                //出现相同字符，return true
                return true;
            }
        }
    }
    //所有字符均不相同 return false
    return false;
}










