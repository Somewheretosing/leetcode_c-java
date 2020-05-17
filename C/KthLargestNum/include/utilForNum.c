#include "utilForNum.h"

void arrayOrderBToS(int *num,int size)
{
    int wkIndex1,wkIndex2;
    int temp;
    for(wkIndex1=0;wkIndex1<size-1;wkIndex1++)
    {
        for(wkIndex2=wkIndex1+1;wkIndex2<size;wkIndex2++)
        {
            //将大值往前移
            if(num[wkIndex2]>num[wkIndex1]){        //后面大于前面
                temp = num[wkIndex1];               //交换
                num[wkIndex1] = num[wkIndex2];
                num[wkIndex2] = temp;
            }
            
        }

    }
}



