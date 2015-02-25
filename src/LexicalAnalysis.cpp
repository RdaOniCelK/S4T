#include "GlobalEnv.h"

WORD _IsConst(char *pWordStart, WORD *pwConstLen)
{
  int nPos;

  if (pWordStart[0]>='0' && pWordStart[0]<='9')
  {//数字常量
    if (pWordStart[0]=='0' && (pWordStart[1]=='x' || pWordStart[1]=='X'))
    {//十六进制常量
      nPos=2;
      while ((pWordStart[nPos]>='0' && pWordStart[nPos]<='9')
        ||(pWordStart[nPos]>='a' && pWordStart[nPos]<='f')
        ||(pWordStart[nPos]>='A' && pWordStart[nPos]<='F'))
      {
        ++nPos;
      }
      *pwConstLen=nPos;
      return S4T_CT_hex;
    }
    else
    {
      nPos=1;
      while ((pWordStart[nPos]>='0' && pWordStart[nPos]<='9'))
      {
        ++nPos;
      }
      *pwConstLen=nPos;
      return S4T_CT_u32;//暂当作是无符号后面语法分析再确认
    }
  }
  else if (pWordStart[0]=='\"')
  {//字符串常量
    nPos=1;
    while (pWordStart[nPos]!='\"' || pWordStart[nPos-1]=='\\')
    {
      if (pWordStart[nPos]==0)
      {//脚本尾,找不到字符串结束右双引号
        g_nEC=S4T_EC_StringFormat;
        return S4T_CT_Undefined;
      }
      ++nPos;
    }
    ++nPos;
    *pwConstLen=nPos;
    return S4T_CT_str;
  }
  else
  {
    return S4T_CT_Undefined;
  }
}

BOOL _IsIdent(char *pWordStart, WORD *pwIdentLen)
{
  int nPos=0;

  if (!((pWordStart[nPos]>='a' && pWordStart[nPos]<='z')
    ||(pWordStart[nPos]>='A' && pWordStart[nPos]<='Z')
    ||pWordStart[nPos]=='_'))
  {
    return FALSE;
  }

  nPos=1;
  while ((pWordStart[nPos]>='0' && pWordStart[nPos]<='9')
    ||(pWordStart[nPos]>='a' && pWordStart[nPos]<='z')
    ||(pWordStart[nPos]>='A' && pWordStart[nPos]<='Z')
    ||pWordStart[nPos]=='_')
  {
    ++nPos;
  }
  *pwIdentLen=nPos;
  return TRUE;
}

//词法分析:提取单词,识别关键字,常量,标识符
int S4T_PickWord()
{
  DWORD dwPos,dwRet;
  WORD wRow,wCol,wRet;
  WORD wCurWordLen;
  g_dwWordCnt=0;
  g_wCurConstValBuffPos=0;
#define NextLine  ++wRow;wCol=0;if(wCurWordLen!=0){/*pick end*/++g_dwWordCnt;};wCurWordLen=0
#define Step(n) dwPos+=n;wCol+=n

  wRow=0,wCol=0,dwPos=0,wCurWordLen=0;
  while (dwPos<g_dwScriptSize)
  {
    if (g_szScript[dwPos]=='\n')
    {
      Step(1);
      NextLine;
      goto CONTINUE_L;
    }
    if (g_szScript[dwPos]=='\r')
    {
      Step(1);
      if (g_szScript[dwPos]=='\n')
      {
        Step(1);
      }
      NextLine;
      goto CONTINUE_L;
    }
    
    if (wCurWordLen==0)
    {
      if(g_szScript[dwPos]==' ' || g_szScript[dwPos]=='\t')
      {//trim
        Step(1);
        goto CONTINUE_L;
      }
      else
      {//start to pick
        //init new word
        g_staAllWord[g_dwWordCnt].dwType=0;
        g_staAllWord[g_dwWordCnt].wPos=dwPos;
        g_staAllWord[g_dwWordCnt].wLen=0;
        g_staAllWord[g_dwWordCnt].wRow=wRow;
        g_staAllWord[g_dwWordCnt].wCol=wCol;
        
        //判断是不是关键字
        if ((dwRet=_IsKeyWord(g_szScript+dwPos,&g_staAllWord[g_dwWordCnt].wLen)) != S4T_KWT_Undefined)
        {//是关键字.pick end
          LOG_Write(LOG_DBG, "Found key-word[%.*s]", g_staAllWord[g_dwWordCnt].wLen, g_szScript+dwPos);
          g_staAllWord[g_dwWordCnt].dwType=S4T_WT_KeyWord;
          g_staAllWord[g_dwWordCnt].dwKeyWordType=dwRet;
          Step(g_staAllWord[g_dwWordCnt].wLen);
          wCurWordLen=0;
          ++g_dwWordCnt;
          goto CONTINUE_L;
        }//判断是不是常量
        else if((wRet=_IsConst(g_szScript+dwPos, &g_staAllWord[g_dwWordCnt].wLen)) != S4T_CT_Undefined)
        {//是常量.pick end
          LOG_Write(LOG_DBG, "Found const-var[%.*s]", g_staAllWord[g_dwWordCnt].wLen, g_szScript+dwPos);
          if (wRet==S4T_CT_u32)
          {//检查前面是否有负号
            if (g_dwWordCnt>1 
              && g_staAllWord[g_dwWordCnt-2].dwType==S4T_WT_KeyWord && g_staAllWord[g_dwWordCnt-2].dwKeyWordType==S4T_KWT_eval
              && g_staAllWord[g_dwWordCnt-1].dwType==S4T_WT_KeyWord && g_staAllWord[g_dwWordCnt-1].dwKeyWordType==S4T_KWT_sub)
            {//合并为负数
              g_staAllWord[g_dwWordCnt].wCol-=1;g_staAllWord[g_dwWordCnt].wPos-=1;g_staAllWord[g_dwWordCnt].wLen+=1;g_szScript[g_staAllWord[g_dwWordCnt].wPos]='-';
              g_staAllWord[g_dwWordCnt-1]=g_staAllWord[g_dwWordCnt];
              g_staAllWord[g_dwWordCnt-1].dwType=S4T_WT_Const;
              g_staAllWord[g_dwWordCnt-1].wConstType=S4T_CT_s32;
              LOG_Write(LOG_DBG, "combine to const-var[%.*s]", g_staAllWord[g_dwWordCnt-1].wLen, g_szScript+g_staAllWord[g_dwWordCnt].wPos);
              Step(g_staAllWord[g_dwWordCnt].wLen-1);
              wCurWordLen=0;
              goto CONTINUE_L;
            }
          }
          g_staAllWord[g_dwWordCnt].dwType=S4T_WT_Const;
          g_staAllWord[g_dwWordCnt].wConstType=wRet;
          Step(g_staAllWord[g_dwWordCnt].wLen);
          wCurWordLen=0;
          ++g_dwWordCnt;
          goto CONTINUE_L;
        }//判断是不是标识符
        else if (_IsIdent(g_szScript+dwPos, &g_staAllWord[g_dwWordCnt].wLen))
        {
          LOG_Write(LOG_DBG, "Found ident[%.*s]", g_staAllWord[g_dwWordCnt].wLen, g_szScript+dwPos);
          g_staAllWord[g_dwWordCnt].dwType=S4T_WT_Ident;
          Step(g_staAllWord[g_dwWordCnt].wLen);
          wCurWordLen=0;
          ++g_dwWordCnt;
          goto CONTINUE_L;
        }
        else
        {//无法识别的单词
          _SetErrSrc(wRow,wCol,dwPos);
          return S4T_EC_WordUnrecognized;
        }
      }
    }

CONTINUE_L:
    ;
  }
  return 0;
#undef Step
#undef NextLine
}