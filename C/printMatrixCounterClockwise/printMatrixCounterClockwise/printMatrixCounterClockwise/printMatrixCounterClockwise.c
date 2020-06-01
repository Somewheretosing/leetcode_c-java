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
		//初期化
		ulRows = 0;
		ulColumns = 0;
		ulIndexCols = 0;
		ulIndexRows = 0;

		//用户提示输入矩阵size
		printf("请输入矩阵行数：\n");
		scanf_s("%d",&ulRows);
		printf("请输入矩阵列数：\n");
		scanf_s("%d", &ulColumns);

		//为矩阵动态分配内存空间并初期化
		ulMatrix = (int *)malloc(sizeof(int)*ulRows);
		for (ulIndexRows = 0; ulIndexRows < ulRows; ulIndexRows++)
		{
			ulMatrix[ulIndexRows] = (int*)malloc(sizeof(int)*ulColumns);
			memset(ulMatrix[ulIndexCols],0,ulColumns);
		}	

		//用户输入矩阵
		printf("请输入矩阵\n");
		for (ulIndexRows = 0; ulIndexRows < ulRows; ulIndexRows++)
		{
			for (ulIndexCols = 0; ulIndexCols < ulColumns; ulIndexCols++)
			{
				scanf_s("%d",&ulMatrix[ulIndexRows][ulIndexCols]);

			}
		}
		//将用户输入的矩阵以矩阵形式输出
		for (ulIndexRows = 0; ulIndexRows < ulRows; ulIndexRows++)
		{
			for (ulIndexCols = 0; ulIndexCols < ulColumns; ulIndexCols++)
			{
				printf("%5d ", ulMatrix[ulIndexRows][ulIndexCols]);
			}
			if (ulIndexCols == ulColumns)
				printf("\n");
		}
		//将用户输入进行处理
		printf("顺时针输出矩阵：\n");
		process(ulMatrix,ulRows,ulColumns);

		//释放内存
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
	int ulIndexY = wkStartY;	//定位至第一行第一个
	//向右打印
	while (ulIndexX <= wkEndX)
	{
		printf("%d ", wkMatrix[ulIndexY][ulIndexX]);
		ulIndexX++;
	}

	

	//向下打印
	if (wkEndY>wkStartY)
	{
		ulIndexX--;
		ulIndexY++;			//防止角落处重复输出
		while (ulIndexY <= wkEndY)
		{
			printf("%d ", wkMatrix[ulIndexY][ulIndexX]);
			ulIndexY++;
		}
	}

	//向左、向上打印
	if (wkEndX > wkStartX && wkEndY > wkStartY)
	{
		//向左
		ulIndexX--;
		ulIndexY--;			//防止角落处重复输出
		while (ulIndexX>wkStartX)
		{
			printf("%d ", wkMatrix[ulIndexY][ulIndexX]);
			ulIndexX--;
		}

		//向上
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
	int ulStartX = 0;				//外圈起点与对角线终点
	int ulStartY = 0;
	int ulEndX = wkColumns - 1;
	int ulEndY = wkRows - 1;

	//顺时针输出，每次只输出外圈
	while (ulEndX >= ulStartX && ulEndY >= ulStartY)		//外圈最少要有一个元素
	{
		printMatrixOneCycle(wkMatrix,ulStartX,ulStartY,ulEndX,ulEndY);

		ulStartX = ulStartX + 1;	//向内圈靠拢
		ulStartY = ulStartY + 1;
		ulEndX = ulEndX - 1;
		ulEndY = ulEndY - 1;
	}
	printf("\n");
	return;

}



