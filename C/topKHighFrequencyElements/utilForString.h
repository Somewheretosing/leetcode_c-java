#include "stdio.h"
#include "string.h"

#define true (1);
#define false (0);

void dirProcess(char *dir,char end,int size);
int isLetter(char temp);
int isDigit(char temp);
int paramCount(char *string,char param,int size);
int stringToNum(char *string,int *num);
int containsOthers(char *string,int size);

