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



int parseAndCompare(char **linePtr, char *cmpStr)
{
  int stepCount = 0; //count how many character counted



  while( **linePtr != '\0' || *cmpStr != '\0')
  {
    if(isspace(**linePtr))
    {
      (*linePtr) ++;
      stepCount++;

      if(*cmpStr == '\0')
      {
        return 1;
      }
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
    else if((**linePtr) == '=')
    {/*
      while(isspace(**linePtr)) // check for space after '=' and move
      {                         //pointer to nearest integer for checking
        (*linePtr) ++;
        stepCount++;
      }*/
      return 1;
    }
    else if((*cmpStr) == '\0') //finish checking string
    {
      if((**linePtr) == '\0') //if linePtr also finish checking
      {                       //which is also true
        return 1;
      }
      else if ((**linePtr) == '=')  //check linePtr whether is "=" after checking
      {                             //finish checking linePtr
        return 1;
      }
      else if(isalpha(**linePtr)) //after checking string if there is
      {                           //still have character return to check variable
        return 1;
      }
      else if(isspace(**linePtr)) //check if there is any space to next character
      {
        (*linePtr) ++;
        stepCount++;
      }
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
  int getVarAmount = 0;

  if(varPtr == NULL) //table is missing
  {
    throwSimpleError(ERR_TABLE_IS_MISSING," Error : Table of variable information is missing.");
  }
  else if(*linePtr == NULL) // command is missing
  {
    return 1;
  }
  else // start checking for line
  {
    if(parseAndCompare(linePtr,"assign"))
    {
        if(parseAndCompare(linePtr,varPtr->name)) //check variable
        {
          if(parseAndCompare(linePtr,"="))// compare =
          {
            if(isdigit(**linePtr))// confirm the is value after '='
            {
              while(varPtr->name != NULL)// if variable not NULL, keep assgin value
              {
                varPtr->storage = parseAndConvertToNum(linePtr);
                varPtr->name++;
                getVarAmount++;
              }
              *varPtr->name = *varPtr->name - getVarAmount;
              if(varPtr->name == NULL && (**linePtr) != '\0')
              {
                throwSimpleError(ERR_UNKNOWN_VARIABLE," Error : Variable is missing or not match with the variable table.");
              }
            }
            else
            {
              throwSimpleError(ERR_NOT_A_NUMBER," Error : No number assign to variable.");
            }
          }
          else
          {
            throwSimpleError(ERR_MALFORM_ASSIGN," Error : Equal sign not found.");
          }
        }
        else
        {
          throwSimpleError(ERR_UNKNOWN_VARIABLE," Error : Variable not found");
        }


    }
    else //no assign word
    {
      throwSimpleError(ERR_UNKNOWN_COMMAND," Error : Unknown command given. 'Space' or missing 'assign' character is illegal.");
    }

  }


}
