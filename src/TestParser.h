#ifndef _TESTPARSER_H
#define _TESTPARSER_H

typedef struct VariableMapping VariableMapping;
struct VariableMapping{
  char *name;
  int *storage;
};
/*
typedef struct Exception Exception; //for c++ and c
struct Exception
{
  int errorCode;
  char *errorMsg;
};
*/

int parseAndCompare(char **linePtr, char *cmpStr);
int parseAndConvertToNum(char **linePtr);
int parseTextAndAssignValues(char **line, VariableMapping *varPtr);
#endif // _TESTPARSER_H
