#include "TestParser.h"
#include "Exception.h"
#include "unity.h"
#include "Error.h"
#include "CExceptionConfig.h"
#include "CException.h"
#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>
#include <ctype.h>


/*
typedef struct VariableMapping VariableMapping;
struct VariableMapping{
  char *name;
  int *storage;
};
*/
/*
* Parse and compare string. It ignores all spaces, If
* the strings are equal, i returns non-zero, otherwise
* zero value.

*/

int parseAndCompare(char **linePtr, char *cmpStr)
{
  int stepCount = 0; //count how many character counted
  
  while( **linePtr != '\0' || *cmpStr != '\0')
  {
    if(isspace(**linePtr))
    {
      (*linePtr) ++;
      //cmpStr++;
      stepCount++;
    }
    else if(toupper(**linePtr) == toupper(*cmpStr))
    {
      (*linePtr)++;
      cmpStr++;
      stepCount++;
    }
    else if((**linePtr) == '\0' && isspace(*cmpStr)) //for more space character than cpmstr
    {
      return 1;
    }
    else
    {
      *linePtr = *linePtr - stepCount;
      return 0;
    }
  }
  
  return 1;
}
/**
* parse amd connect the first string number to value
* the value is returned if the number is successfully
* connected. If thre is no number, ERR_NOT_A_NUMBER
* is thrown
*/
int parseAndConvertToNum(char **linePtr)
{
  int num = 0,stepCount = 0;
  while(isdigit(**linePtr) || isspace(**linePtr))
  {
    if(isspace(**linePtr))
    {      
      (*linePtr)++;
      stepCount++;
    }
    else if(isdigit(**linePtr)) 
    {
      num = num * 10 + (**linePtr - '0');
      (*linePtr)++;
      stepCount++;
    }
    
    if(isalpha(**linePtr))
    {
      *linePtr = *linePtr - stepCount;
      return 0;
    }
  }
  return num;
}

int parseTextAndAssignValues(char **linePtr, VariableMapping *varPtr)
{
  if(varPtr == NULL)
  {
    throwSimpleError(ERR_TABLE_IS_MISSING,"Table of variable is missing.");
  }
  else if(*linePtr == NULL)
  {
    throwSimpleError(ERR_UNKNOWN_COMMAND,"No command given.");
  }
  //return 0;
}