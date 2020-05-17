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
        memset(ucNestedInteger,0,1000);     //��ʼ��

        printf("������nestedInteger����\n");          //�û�����
        printf("����[123,[123,[[123,234],[234,234]]]\n");
        scanf("%s",ucNestedInteger);

        process(ucNestedInteger,0);             //���д���
    }


}

void process(char *unNestedInteger,int ulLayer)
{
    
    int wkResult = 0;
    char wkTempFom[100];
    char wkTempLat[100];
    int wkElements;
    memset(wkTempFom,0,100);   //��ʼ��
    memset(wkTempLat,0,100);

    //1.�Ƚ����˵�[]ȥ��
    strcpy(unNestedInteger,unNestedInteger+1);  //ȥ��ͷ[
    unNestedInteger[strlen(unNestedInteger)-1] = '\0';   //ȥĩβ]

    wkResult = containsParam(unNestedInteger,'[',strlen(unNestedInteger));    //��ʣ���ַ������Ƿ���Ƕ������
    //2.�жϵݹ��Ƿ����
    if(wkResult == 0)         //�趨�ݹ�������û��[] ,����������һ��, ��Ϊ�ݹ����
    {
        prefix(ulLayer);          //���������
        wkElements = paramCount(unNestedInteger,',',strlen(unNestedInteger));    //��ʣ���ַ�������1����2��Ԫ��
        printf("%d��Integer����ֵ%s\n",wkElements+1, unNestedInteger);   
        return;
    }
    //3.�ݹ�û�н�������������
    if(unNestedInteger[0]=='[')
    {
        sscanf(unNestedInteger,"%[^]]],%s",wkTempFom,wkTempLat);               //��ȡǶ�׶����ȫ������Ԫ��
        wkTempFom[strlen(wkTempFom)] = ']';                            //������']'����
        
    }    
    else
    {
        sscanf(unNestedInteger,"%[^,],%s",wkTempFom,wkTempLat);               //��ȡǶ�׶����ȫ������Ԫ��
        
        
    }
    //4.�����Ϣ���ݹ�
    prefix(ulLayer);
    printf("һ����������Ԫ�ص�Ƕ���б�:\n");
    if(wkTempFom[0]=='[' && wkTempLat[0]=='[')
    {
        //�ݹ�
        process(wkTempFom,ulLayer+1);
        process(wkTempLat,ulLayer+1);
    }
    else if(wkTempFom[0]=='[' && wkTempLat[0]!='[')
    {
        //������Ϣֱ�����
        prefix(ulLayer+1);
        printf("1��Integer����ֵ%s\n",wkTempLat);
        //�ݹ鴦��ǰ��
        process(wkTempFom,ulLayer+1);
    }
    else
    {
        //ǰ����Ϣֱ�����
        prefix(ulLayer+1);
        printf("1��Integer����ֵ%s\n",wkTempFom);
        //�ݹ鴦�����
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
 * �ж��ַ����ڴ�ָ��λ�ÿ�ʼsize�������ж��ٸ�parameter
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
 * �ж��ַ����ڴ�ָ��λ�ÿ�ʼsize�������Ƿ���param
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


