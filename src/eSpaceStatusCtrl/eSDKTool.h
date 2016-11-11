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

#ifndef _ESDKTOOL_H
#define _ESDKTOOL_H
#include <string>
using namespace std;
//工具类
class eSDKTool
{
private:
	eSDKTool(void);
	~eSDKTool(void);
public:
	static void getCurrentPath(std::string& cstrPath);				//获取当前程序可执行路径	
	static void Int10ToStr(std::string& strNum,int num);			//获取10进制的字符串
	static unsigned short StrToInt10(const std::string& strNum);	//字符串转数字
	static std::string CreateGuidStr();

};

#define CHECK_POINTER(pPoint) if(NULL == pPoint)\
{\
	return;\
}

#define SAFE_DELETE(pPoint) 	if(NULL != pPoint)\
{\
	delete pPoint;\
	pPoint = NULL;\
}
#define SAFE_DELETE_ARRAY(pPoint) 	if(NULL != pPoint)\
{\
	delete[] pPoint;\
	pPoint = NULL;\
}

#endif

