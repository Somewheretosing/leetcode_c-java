#include "stdio.h"
#include "stdlib.h "
#include "math.h"

typedef unsigned char BOOL;
void process(int **wkMatrix,int wkRows,int wkColumns);
void printMatrixOneCycle(int **wkMatrix, int wkStartX, int wkStartY, int wkEndX,int wkEndY);
void main()
{
	int ulRows;
	int ulColumns;
	int **ulMatrix;
	int ulIndexCols;
	int ulIndexRows;
	
	while (1)
	{
		//���ڻ�
		ulRows = 0;
		ulColumns = 0;
		ulIndexCols = 0;
		ulIndexRows = 0;

		//�û���ʾ�������size
		printf("���������������\n");
		scanf_s("%d",&ulRows);
		printf("���������������\n");
		scanf_s("%d", &ulColumns);

		//Ϊ����̬�����ڴ�ռ䲢���ڻ�
		ulMatrix = (int *)malloc(sizeof(int)*ulRows);
		for (ulIndexRows = 0; ulIndexRows < ulRows; ulIndexRows++)
		{
			ulMatrix[ulIndexRows] = (int*)malloc(sizeof(int)*ulColumns);
			memset(ulMatrix[ulIndexCols],0,ulColumns);
		}	

		//�û��������
		printf("���������\n");
		for (ulIndexRows = 0; ulIndexRows < ulRows; ulIndexRows++)
		{
			for (ulIndexCols = 0; ulIndexCols < ulColumns; ulIndexCols++)
			{
				scanf_s("%d",&ulMatrix[ulIndexRows][ulIndexCols]);

			}
		}
		//���û�����ľ����Ծ�����ʽ���
		for (ulIndexRows = 0; ulIndexRows < ulRows; ulIndexRows++)
		{
			for (ulIndexCols = 0; ulIndexCols < ulColumns; ulIndexCols++)
			{
				printf("%5d ", ulMatrix[ulIndexRows][ulIndexCols]);
			}
			if (ulIndexCols == ulColumns)
				printf("\n");
		}
		//���û�������д���
		printf("˳ʱ���������\n");
		process(ulMatrix,ulRows,ulColumns);

		//�ͷ��ڴ�
		for (ulIndexRows = 0; ulIndexRows < ulRows; ulIndexRows++)
		{
			free(ulMatrix[ulIndexRows]);
		}
		free(ulMatrix);
	}

}

void printMatrixOneCycle(int **wkMatrix, int wkStartX, int wkStartY, int wkEndX, int wkEndY)
{
	int ulIndexX = wkStartX;
	int ulIndexY = wkStartY;	//��λ����һ�е�һ��
	//���Ҵ�ӡ
	while (ulIndexX <= wkEndX)
	{
		printf("%d ", wkMatrix[ulIndexY][ulIndexX]);
		ulIndexX++;
	}

	

	//���´�ӡ
	if (wkEndY>wkStartY)
	{
		ulIndexX--;
		ulIndexY++;			//��ֹ���䴦�ظ����
		while (ulIndexY <= wkEndY)
		{
			printf("%d ", wkMatrix[ulIndexY][ulIndexX]);
			ulIndexY++;
		}
	}

	//�������ϴ�ӡ
	if (wkEndX > wkStartX && wkEndY > wkStartY)
	{
		//����
		ulIndexX--;
		ulIndexY--;			//��ֹ���䴦�ظ����
		while (ulIndexX>wkStartX)
		{
			printf("%d ", wkMatrix[ulIndexY][ulIndexX]);
			ulIndexX--;
		}

		//����
		while (ulIndexY > wkStartY)
		{
			printf("%d ", wkMatrix[ulIndexY][ulIndexX]);
			ulIndexY--;
		}
	}
	return;
}

void process(int **wkMatrix, int wkRows, int wkColumns)
{
	int ulStartX = 0;				//��Ȧ�����Խ����յ�
	int ulStartY = 0;
	int ulEndX = wkColumns - 1;
	int ulEndY = wkRows - 1;

	//˳ʱ�������ÿ��ֻ�����Ȧ
	while (ulEndX >= ulStartX && ulEndY >= ulStartY)		//��Ȧ����Ҫ��һ��Ԫ��
	{
		printMatrixOneCycle(wkMatrix,ulStartX,ulStartY,ulEndX,ulEndY);

		ulStartX = ulStartX + 1;	//����Ȧ��£
		ulStartY = ulStartY + 1;
		ulEndX = ulEndX - 1;
		ulEndY = ulEndY - 1;
	}
	printf("\n");
	return;

}



