#include "Exception.h"
#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>
#include "CException.h"
#include "unity.h"
#include "Error.h"


void throwSimpleError(int errorCode, char *errorMsg) {
  Exception *ex = (Exception *)malloc(sizeof(Exception));
	ex->errorCode = errorCode;
	ex->errorMsg = errorMsg;
	Throw(ex);
}
/*
void throwError(int errorCode,char *format,...)
{
  va_list valist;
  int neededSize = 0;
  char *buffer;
  Exception *ex = (Exception *)malloc(sizeof(Exception));
  ex->errorCode = errorCode;

  va_start(valist,format);
  neededSize = vsnprintf(NULL,0,format,valist)+1;
  buffer = malloc(neededSize);
  vsnprintf(buffer,neededSize,format,valist);

  va_end(valist);

  ex->errorMsg = buffer;

  printf(buffer);

  Throw(ex);
}
*/
void freeError(Exception *ex)
{
  if(ex)
  {
    if(ex->errorMsg)
    {
      //free(ex->errorMsg);
      free(ex);
    }

  }
}
