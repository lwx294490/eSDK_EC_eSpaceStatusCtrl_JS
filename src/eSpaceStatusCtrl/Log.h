/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

/********************************************************************
filename		: 	Log.h
author			:	z00233055
created		:	2015/01/04
description	:	��־ģ��
copyright		:	Copyright (C) 2014-2016
history			:	2015/01/04 ��ʼ�汾
*********************************************************************/

#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <string>
#include <stdarg.h>
#include <WinBase.h>
#include "eSDKLogAPI.h"
#include "securec_win.h"
using namespace std;

#define MSG_LEN 4096
#define TIME_LEN 256
#define PRODUCT_NAME "eSDK-UC-CTRL-Windows-JS"
#define PARAMETER_LEN 1024

typedef enum
{
	TRACE_INFO,
	TRACE_DEBUG
}TRACE_LEVEL_E;

//lint -e438
//lint -e1788
class CLogTrace
{
public:
	CLogTrace(void);
	CLogTrace(TRACE_LEVEL_E level, const char *file, int line, const char *func, const char *para, const int *ret,const char *fmt, ...)
			:m_Func(func), m_File(file), m_Line(line), m_Level(level),m_Parameter(para),m_RetCode(ret)
	{
		va_list args(NULL);
		va_start(args, fmt);
		memset_s(m_Msg,MSG_LEN,0,MSG_LEN);
		(void)_vsnprintf_s(m_Msg, MSG_LEN - 1, fmt, args);
		va_end(args);

		std::string msg("Enter ");
		msg.append(m_Func);
		if (0 != strlen(m_Msg))
		{
			msg.append(" ");
			msg.append(m_Msg);
		}
		(void)Log_Run_Debug(PRODUCT_NAME,msg.c_str());

		GetLocalTime(&m_ReqTime);
		GetLocalTime(&m_RspTime);
	}

	~CLogTrace()
	{
		try 
		{
			std::string msg("Leave ");
			msg.append(m_Func);
			(void)Log_Run_Debug(PRODUCT_NAME,msg.c_str());

			if (TRACE_INFO == m_Level)
			{
				GetLocalTime(&m_RspTime);
				char reqTime[TIME_LEN] = {0};
				char rspTime[TIME_LEN] = {0};
				char retcode[TIME_LEN] = {0};
				char parameter[PARAMETER_LEN]={0};
				(void)_snprintf_s(reqTime, TIME_LEN-1, "%04d-%02d-%02d %02d:%02d:%02d %03d", m_ReqTime.wYear, m_ReqTime.wMonth, m_ReqTime.wDay, m_ReqTime.wHour, m_ReqTime.wMinute, m_ReqTime.wSecond, m_ReqTime.wMilliseconds);
				(void)_snprintf_s(rspTime, TIME_LEN-1, "%04d-%02d-%02d %02d:%02d:%02d %03d", m_RspTime.wYear, m_RspTime.wMonth, m_RspTime.wDay, m_RspTime.wHour, m_RspTime.wMinute, m_RspTime.wSecond, m_RspTime.wMilliseconds);
				if (m_Parameter)
				{
					strncpy_s(parameter,PARAMETER_LEN*sizeof(char),m_Parameter,_TRUNCATE);
				}
				if (m_RetCode)
				{
					(void)_itoa_s(*m_RetCode, retcode, TIME_LEN, 10);
					if (*m_RetCode == 0)
					{
						Log_Interface_Info(PRODUCT_NAME, "1", "Native C", m_Func, "", "", "", reqTime, rspTime, retcode, "%s", parameter);
					}
					else
					{
						Log_Interface_Error(PRODUCT_NAME, "1", "Native C", m_Func, "", "", "", reqTime, rspTime, retcode, "%s", parameter);
					}
				}
				else
				{
					Log_Interface_Info(PRODUCT_NAME, "1", "Native C", m_Func, "", "", "", reqTime, rspTime, retcode, "%s", parameter);
				}
			}
		} 
		catch(...){} ;

		m_Func = NULL;
		m_File = NULL;
		m_Parameter = NULL;
		m_RetCode = NULL;
	}
private:
	const char *m_Func;
	const char *m_File;
	const char *m_Parameter;
	const int *m_RetCode;
	int         m_Line;
	TRACE_LEVEL_E m_Level;
	SYSTEMTIME m_ReqTime;
	SYSTEMTIME m_RspTime;
	char m_Msg[MSG_LEN];
};

#define INFO_TRACE(para,ret,fmt, ...) CLogTrace trace(TRACE_INFO,__FILE__, __LINE__, __FUNCTION__, para, ret, fmt, ##__VA_ARGS__)
#define DEBUG_TRACE(fmt, ...) CLogTrace trace(TRACE_DEBUG,__FILE__, __LINE__, __FUNCTION__, NULL, NULL, fmt, ##__VA_ARGS__)

static std::string FormatedMsg(const char *fmt, ...)
{
	char msg[MSG_LEN];
	memset_s(msg,MSG_LEN,0,MSG_LEN);
	va_list args;
	va_start(args, fmt);
	(void)_vsnprintf_s(msg, MSG_LEN - 1, fmt, args);
	va_end(args);
	return std::string(msg);
}

#define DEBUG_LOG(fmt, ...)		Log_Run_Debug(PRODUCT_NAME,FormatedMsg(fmt, ##__VA_ARGS__).c_str())
#define INFO_LOG(fmt, ...)		Log_Run_Info(PRODUCT_NAME,FormatedMsg(fmt, ##__VA_ARGS__).c_str())
#define WARN_LOG(fmt, ...)		Log_Run_Warn(PRODUCT_NAME,FormatedMsg(fmt, ##__VA_ARGS__).c_str())
#define ERROR_LOG(fmt, ...)		Log_Run_Error(PRODUCT_NAME,FormatedMsg(fmt, ##__VA_ARGS__).c_str())
//lint +e438

#endif //_LOG_H_
