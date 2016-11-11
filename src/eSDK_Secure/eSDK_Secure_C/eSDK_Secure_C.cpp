/********************************************************************
filename	: 	eSDK_Secure_C.cpp
author		:	zwx211831
created		:	2015/9/17	
description	:	ʵ�� DLL Ӧ�ó���ĵ�������;
copyright	:	Copyright (C) 2014-2016 Huawei Tech.Co.,Ltd
history		:	2015/9/17 ��ʼ�汾;
*********************************************************************/

#include "stdafx.h"
#include "securec_win.h"
#include "securectype.h"
#include "securecutil.h"

//�ڴ��ʼ������
errno_t __SECUREC_CALL memset_s(void* dest, size_t destMax, int c, size_t count)
{
	if (destMax == 0 || destMax > SECUREC_MEM_MAX_LEN )
	{
		SECUREC_ERROR_INVALID_RANGE("memset_s");
		return ERANGE;
	}
	if (dest == NULL)
	{
		SECUREC_ERROR_INVALID_PARAMTER("memset_s");
		return EINVAL;
	}
	if (count > destMax)
	{
		(void)memset(dest, c, destMax);   /*set entire buffer to value c*/
		SECUREC_ERROR_INVALID_RANGE("memset_s");
		return ERANGE_AND_RESET;
	}

#ifdef CALL_LIBC_COR_API
	/*use underlying memcpy for performance consideration*/
	(void)memset(dest, c, count);
#else
	util_memset(dest, c, count);
#endif

	return EOK;
}
