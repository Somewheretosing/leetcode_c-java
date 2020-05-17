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
        memset(ucAsteroids,0,1000);   //��ʼ��
        ulSize = 0;

        printf("���������飺(ʾ���� 100,200,300)\n");   //�û�����
        gets(ucAsteroids);

        ulSize = strlen(ucAsteroids);

        process(ucAsteroids,ulSize);    //���û���������д���

    }
    return 0;

}

void process(char *ucAsteroids,int ulSize)
{
    char ucFormer[10];
    char ucLatter[10];
    signed int slFormer;
    signed int slLatter;
    int ulEndIndex = 0;         //Ҫɾ�����Ӵ�ĩβ������λ��+1
    int ulStartIndex = 0;       //Ҫɾ�����Ӵ�����ʼλ��
    int ulLength = 0;           //�����ѱ�������ַ����ĳ���
    


    
    if(ulSize==0)    
    {
        printf("[]\n");           //�û��������鳤��Ϊ0ʱ��ֱ�ӷ��ؿ�����
        return;
    }
    printf("[");
    while(ulLength<strlen(ucAsteroids))              //���黹û���ж����
    {
        memset(ucFormer,0,10);    //��ʼ��
        memset(ucLatter,0,10);
        slFormer = 0;
        slLatter = 0;

        sscanf(&ucAsteroids[ulLength],"%[^,],%[^,],",ucFormer,ucLatter);            //��ȡ������ֵ����
        if(strlen(ucLatter)==0) 
        {
            //�û���������鳤��Ϊ1
            printf("%s]\n",ucAsteroids);
            return;
        }
        //���Ƚ϶���ת��Ϊ����
        sscanf(ucFormer,"%d",&slFormer);
        sscanf(ucLatter,"%d",&slLatter);
        if(slFormer<0)  //��һ�����������˶������ᷢ����ײ
        {
            printf("%s,",ucFormer);              //ֱ�����
            ulStartIndex = 0;
            ulEndIndex = ulStartIndex + strlen(ucFormer) +1;
            deleteAsteroid(ucAsteroids,ulStartIndex,ulEndIndex); //������������ֱ��ɾ��
            ulLength = 0;
            continue;                      //���¿�ʼ
        }
        //�����������ƶ������ǣ���ʼѰ�Һ��������˶�������
        if(slLatter>0)
        {
            ulLength = ulLength + strlen(ucFormer) + 1;         //�´δ�latter����ʼ��ȡ��������
        }
        if(slLatter<0)
        {
            //��ǰ����������С��Latter������ȫ������
            if(abs(slFormer)<abs(slLatter))
            {
                ulStartIndex = ulLength;
                ulEndIndex = ulStartIndex + strlen(ucFormer) + 1;
                deleteAsteroid(ucAsteroids,ulStartIndex,ulEndIndex);     //Former������
                if(ulLength>0)
                {
                    ulLength = ulLength - strlen(ucFormer) - 1;    //�´δ�Former���ϸ����ֿ�ʼ��ȡ�������Ƚ�
                                                                   
                }
                else
                {
                    //��Latterǰ��û�б���������������壬�´�ѭ���ͻ�ֱ�����
                }    
                continue;          //������ײ
            }
            else if(abs(slFormer)==abs(slLatter))           
            {   
                //���ߴ�С��ͬ��ͬ���ھ�
                ulStartIndex = ulLength;
                ulEndIndex = ulStartIndex + strlen(ucFormer) + strlen(ucLatter) + 2;
                deleteAsteroid(ucAsteroids,ulStartIndex,ulEndIndex);     //����ͬ���ھ�
                continue;      //�ӱ��ζ�ȡ�ĵط�������ȡ
            }
            else
            {
                //Latter������С��������
                ulStartIndex = ulLength + strlen(ucFormer) + 1;
                ulEndIndex = ulStartIndex + strlen(ucLatter) + 1;
                deleteAsteroid(ucAsteroids,ulStartIndex,ulEndIndex);
                
                continue;       //�ӱ��ζ�ȡ�ĵط�������ȡ
            }
            
        }
    }    
    
}

//���ַ����ж��Ӵ�ɾ��
void deleteAsteroid(char *temp,int ulStartIndex,int ulEndIndex)
{

    strcpy(&temp[ulStartIndex],&temp[ulEndIndex]);
    
}

    


