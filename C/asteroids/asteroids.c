#include "stdio.h"
#include "string.h"
#include "math.h"

void deleteAsteroid(char *temp,int ucDltIndex,int ucDltLen);
void process(char *ucAsteroids,int ulSize);
void main()
{
    
    char ucAsteroids[1000];
    int ulSize;
    
    while(1)
    {
        memset(ucAsteroids,0,1000);   //初始化
        ulSize = 0;

        printf("请输入数组：(示例： 100,200,300)\n");   //用户输入
        gets(ucAsteroids);

        ulSize = strlen(ucAsteroids);

        process(ucAsteroids,ulSize);    //对用户的输入进行处理

    }
    return 0;

}

void process(char *ucAsteroids,int ulSize)
{
    char ucFormer[10];
    char ucLatter[10];
    signed int slFormer;
    signed int slLatter;
    int ulEndIndex = 0;         //要删除的子串末尾的所在位置+1
    int ulStartIndex = 0;       //要删除的子串的起始位置
    int ulLength = 0;           //计算已被处理的字符串的长度
    


    
    if(ulSize==0)    
    {
        printf("[]\n");           //用户输入数组长度为0时，直接返回空数组
        return;
    }
    printf("[");
    while(ulLength<strlen(ucAsteroids))              //数组还没有判断完成
    {
        memset(ucFormer,0,10);    //初始化
        memset(ucLatter,0,10);
        slFormer = 0;
        slLatter = 0;

        sscanf(&ucAsteroids[ulLength],"%[^,],%[^,],",ucFormer,ucLatter);            //读取两个数值出来
        if(strlen(ucLatter)==0) 
        {
            //用户输入的数组长度为1
            printf("%s]\n",ucAsteroids);
            return;
        }
        //将比较对象转化为数字
        sscanf(ucFormer,"%d",&slFormer);
        sscanf(ucLatter,"%d",&slLatter);
        if(slFormer<0)  //第一颗行星向左运动，不会发生碰撞
        {
            printf("%s,",ucFormer);              //直接输出
            ulStartIndex = 0;
            ulEndIndex = ulStartIndex + strlen(ucFormer) +1;
            deleteAsteroid(ucAsteroids,ulStartIndex,ulEndIndex); //输出后这个数字直接删除
            ulLength = 0;
            continue;                      //重新开始
        }
        //出现了向右移动的行星，开始寻找后面向左运动的行星
        if(slLatter>0)
        {
            ulLength = ulLength + strlen(ucFormer) + 1;         //下次从latter处开始读取两个数据
        }
        if(slLatter<0)
        {
            //将前面所有质量小于Latter的行星全部消灭
            if(abs(slFormer)<abs(slLatter))
            {
                ulStartIndex = ulLength;
                ulEndIndex = ulStartIndex + strlen(ucFormer) + 1;
                deleteAsteroid(ucAsteroids,ulStartIndex,ulEndIndex);     //Former被消灭
                if(ulLength>0)
                {
                    ulLength = ulLength - strlen(ucFormer) - 1;    //下次从Former的上个数字开始读取，继续比较
                                                                   
                }
                else
                {
                    //此Latter前面没有比它质量更大的天体，下次循环就会直接输出
                }    
                continue;          //继续碰撞
            }
            else if(abs(slFormer)==abs(slLatter))           
            {   
                //两者大小相同，同归于尽
                ulStartIndex = ulLength;
                ulEndIndex = ulStartIndex + strlen(ucFormer) + strlen(ucLatter) + 2;
                deleteAsteroid(ucAsteroids,ulStartIndex,ulEndIndex);     //两个同归于尽
                continue;      //从本次读取的地方继续读取
            }
            else
            {
                //Latter质量较小，被消灭
                ulStartIndex = ulLength + strlen(ucFormer) + 1;
                ulEndIndex = ulStartIndex + strlen(ucLatter) + 1;
                deleteAsteroid(ucAsteroids,ulStartIndex,ulEndIndex);
                
                continue;       //从本次读取的地方继续读取
            }
            
        }
    }    
    
}

//将字符串中段子串删除
void deleteAsteroid(char *temp,int ulStartIndex,int ulEndIndex)
{

    strcpy(&temp[ulStartIndex],&temp[ulEndIndex]);
    
}

    


