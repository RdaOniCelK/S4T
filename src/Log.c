#include <windows.h>
#include <stdio.h>
#include "Log.h"
//////////////////////////////////////////////////////////////////////////
//ÈÕÖ¾Ä£¿é////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
static DWORD _dwLogMask=0;
static FILE * _pLogFile=NULL;
static char _szLogFilePath[MAX_PATH]={0};
static char * _szLogFileDate=NULL;
static BOOL _bLogThreadSafe=FALSE;
static CRITICAL_SECTION _csLog={0};

int LOG_Init(const char * szLogFilePath,DWORD dwLogMask,BOOL bThreadSafe)
{
	_szLogFileDate = _szLogFilePath + sprintf(_szLogFilePath, "%s", szLogFilePath);
	_dwLogMask = dwLogMask;
	_bLogThreadSafe = bThreadSafe;
	if (_bLogThreadSafe)
	{
		InitializeCriticalSection(&_csLog);
	}
	return 0;
}
int LOG_Uninit()
{
	if (_bLogThreadSafe)
	{
		DeleteCriticalSection(&_csLog);
		memset(&_csLog, 0, sizeof(CRITICAL_SECTION));
	}
	return 0;
}
int LOG_Write(DWORD dwType, const char * szFile, int nLine,  const char * szFmt,...)
{
	va_list pArgs=NULL;
	SYSTEMTIME stNow={0};
	char szFileDate[64]={0};
	char * pTmp=NULL;
	int nRet=0;
	
	if ((_dwLogMask & dwType) == 0)
	{
		return 0;
	}

	GetLocalTime(&stNow);
	
	if (_bLogThreadSafe)
	{
		EnterCriticalSection(&_csLog);
	}
#ifndef _DEBUG
	__try
	{
	sprintf(szFileDate,"_%04d_%02d_%02d.log", stNow.wYear, stNow.wMonth, stNow.wDay);

	if ((strcmp(_szLogFileDate,szFileDate) != 0) || (_pLogFile == NULL))
	{
		if (_pLogFile != NULL)
		{
			fclose(_pLogFile);
			_pLogFile=NULL;
		}
		strcpy(_szLogFileDate, szFileDate);
		if ((_pLogFile=fopen(_szLogFilePath,"a+")) == NULL)
		{
			nRet = -1;
			goto END_L;
		}
	}
	
	fprintf(_pLogFile, "[%s][%02d:%02d:%02d:%03d][%15.15s][%5d]=>",
		(dwType==REC_DEBUG)? "DEBUG ":
		(dwType==REC_WARN) ? "WARN  ":
		(dwType==REC_ERROR)? "ERROR ":
		(dwType==REC_FATAL)? "FATAL ":
		(dwType==REC_RUN)  ? "RUN   ":
		(dwType==REC_EXPT) ? "EXCEPT":"??????",
		stNow.wHour,stNow.wMinute,stNow.wSecond,stNow.wMilliseconds,
		((pTmp=strrchr(szFile,'\\'))==NULL)?szFile:pTmp+1,
		nLine);
	va_start(pArgs, szFmt);
	vfprintf(_pLogFile, szFmt, pArgs);
	va_end(pArgs); 
	fprintf(_pLogFile, "\r\n");
	fflush(_pLogFile);
	
	}
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
  }
	
#else
	printf("[%s][%02d:%02d:%02d:%03d][%15.15s][%5d]=>",
		(dwType==REC_DEBUG)? "DEBUG ":
		(dwType==REC_WARN) ? "WARN  ":
		(dwType==REC_ERROR)? "ERROR ":
		(dwType==REC_FATAL)? "FATAL ":
		(dwType==REC_RUN)  ? "RUN   ":
		(dwType==REC_EXPT) ? "EXCEPT":"??????",
		stNow.wHour,stNow.wMinute,stNow.wSecond,stNow.wMilliseconds,
		((pTmp=strrchr(szFile,'\\'))==NULL)?szFile:pTmp+1,
		nLine);
	va_start(pArgs, szFmt);
	vprintf(szFmt, pArgs);
	va_end(pArgs); 
	printf("\r\n");
#endif

	nRet=0;
END_L:
	if (_bLogThreadSafe)
	{
		LeaveCriticalSection(&_csLog);
	}
	
	return nRet;
}
