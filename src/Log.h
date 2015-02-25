/*******************************************
--------------------------------------------
|模块名 | 日志输出模块
|-------------------------------------------
|现版本 | V1.1
|-------------------------------------------
|功  能 | Debug模式下控制台输出,Release模式下文件输出
|-------------------------------------------
|依  赖 | WIN32
|-------------------------------------------
|改  进 | 
|-------------------------------------------
|               修改历史
|-------------------------------------------
|版本号 | 操作日期 | 操作者 |  日志
|-------------------------------------------
|V1.0   |2012.07.03|邓丽达  | 创建
|-------------------------------------------
|V1.1   |2012.07.12|邓丽达  | 文件输出路径改为LOG_Init()参数输入
*******************************************/
#ifndef __LOG_H__
#define __LOG_H__
#include <windows.h>
//////////////////////////////////////////////////////////////////////////
//日志模块////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// 日志选项
#define REC_DEBUG (0x1)
#define REC_WARN	(0x2)
#define REC_ERROR	(0x4)
#define REC_FATAL	(0x8)
#define REC_RUN		(0x10)
#define REC_EXPT	(0x20)
#define REC_ALL		(REC_DEBUG|REC_WARN|REC_ERROR|REC_FATAL|REC_RUN|REC_EXPT)

int LOG_Init(const char * szLogFilePath,DWORD dwLevel,BOOL bThreadSafe);
int LOG_Uninit();

// 调试日志
#define LOG_DBG REC_DEBUG,__FILE__,__LINE__
// 警告日志
#define LOG_WRN REC_WARN,__FILE__,__LINE__
// 错误日志
#define LOG_ERR REC_ERROR,__FILE__,__LINE__
// 致命错误日志
#define LOG_FAT REC_FATAL,__FILE__,__LINE__
// 运行日志
#define LOG_RUN REC_RUN,__FILE__,__LINE__
// 异常日志
#define LOG_EXP REC_EXPT,__FILE__,__LINE__
int LOG_Write(DWORD dwType, const char * szFile, int nLine,  const char * szFmt,...);
/************************************************************************/
/* --==用法==--
/* 应用启动时加入: LOG_Init("log\\Nagual",REC_ALL,TRUE);
/* 记录日志时使用: LOG_Write(LOG_DBG,"Test debug log %d %s",100,"hello");
/* 应用退出时加入: LOG_Uninit();
/************************************************************************/

#endif