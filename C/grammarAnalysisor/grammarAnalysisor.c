#include "stdio.h"

#define false (0)
#define true (1)

int containsParam(char *string,char param,int size);
int paramCount(char *string,char param,int size);
void process(char *unNestedInteger,int ulLayer);
void prefix(int ulLayer);

void main()
{
    char ucNestedInteger[1000];

    while(1)
    {
        memset(ucNestedInteger,0,1000);     //初始化

        printf("请输入nestedInteger对象：\n");          //用户输入
        printf("例：[123,[123,[[123,234],[234,234]]]\n");
        scanf("%s",ucNestedInteger);

        process(ucNestedInteger,0);             //进行处理
    }


}

void process(char *unNestedInteger,int ulLayer)
{
    
    int wkResult = 0;
    char wkTempFom[100];
    char wkTempLat[100];
    int wkElements;
    memset(wkTempFom,0,100);   //初始化
    memset(wkTempLat,0,100);

    //1.先将两端的[]去掉
    strcpy(unNestedInteger,unNestedInteger+1);  //去开头[
    unNestedInteger[strlen(unNestedInteger)-1] = '\0';   //去末尾]

    wkResult = containsParam(unNestedInteger,'[',strlen(unNestedInteger));    //看剩下字符串中是否有嵌套数组
    //2.判断递归是否结束
    if(wkResult == 0)         //设定递归条件，没有[] ,代表进入最后一层, 视为递归结束
    {
        prefix(ulLayer);          //缩近及标号
        wkElements = paramCount(unNestedInteger,',',strlen(unNestedInteger));    //看剩下字符串中有1个或2个元素
        printf("%d个Integer包含值%s\n",wkElements+1, unNestedInteger);   
        return;
    }
    //3.递归没有结束，继续处理
    if(unNestedInteger[0]=='[')
    {
        sscanf(unNestedInteger,"%[^]]],%s",wkTempFom,wkTempLat);               //获取嵌套对象的全部两个元素
        wkTempFom[strlen(wkTempFom)] = ']';                            //将最后的']'补上
        
    }    
    else
    {
        sscanf(unNestedInteger,"%[^,],%s",wkTempFom,wkTempLat);               //获取嵌套对象的全部两个元素
        
        
    }
    //4.输出信息并递归
    prefix(ulLayer);
    printf("一个含有两个元素的嵌套列表:\n");
    if(wkTempFom[0]=='[' && wkTempLat[0]=='[')
    {
        //递归
        process(wkTempFom,ulLayer+1);
        process(wkTempLat,ulLayer+1);
    }
    else if(wkTempFom[0]=='[' && wkTempLat[0]!='[')
    {
        //后者信息直接输出
        prefix(ulLayer+1);
        printf("1个Integer包含值%s\n",wkTempLat);
        //递归处理前者
        process(wkTempFom,ulLayer+1);
    }
    else
    {
        //前者信息直接输出
        prefix(ulLayer+1);
        printf("1个Integer包含值%s\n",wkTempFom);
        //递归处理后者
        process(wkTempLat,ulLayer+1);
    }   
    
}




void prefix(int ulLayer)
{
    int wkIndex;
    for(wkIndex=0;wkIndex<ulLayer;wkIndex++)
    {
        printf("    ");
    }

}

/**
 * 判断字符串在从指定位置开始size长度内有多少个parameter
 * */
int paramCount(char *string,char param,int size)
{       
    int count=0;
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
/**
 * 判断字符串在从指定位置开始size长度内是否有param
 * */
int containsParam(char *string,char param,int size)
{
    int flag = false;
    int wkIndex;
    for(wkIndex=0;wkIndex<size;wkIndex++)
    {
            if(string[wkIndex]==param)
            {
                    flag = true;
                    break;
            }
    }
    return flag;
}


