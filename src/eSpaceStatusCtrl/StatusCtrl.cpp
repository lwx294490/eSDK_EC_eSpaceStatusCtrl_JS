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

// StatusCtrl.cpp : CStatusCtrl 的实现
#include "stdafx.h"
#include "StatusCtrl.h"

#include "ECSEventDef.h"
#include <iostream>
#include <fstream>
#include "Tlhelp32.h"
#include "securec_win.h"
using namespace std;

DWORD WINAPI _GetNumByAccountThread(LPVOID lpParam)
{
	try
	{	
		CStatusCtrl* pCStatusCtrl = reinterpret_cast<CStatusCtrl*>(lpParam);
		EnterCriticalSection(&pCStatusCtrl->g_cs);
		pCStatusCtrl->GetNumByAccount();
		LeaveCriticalSection(&pCStatusCtrl->g_cs);
	}
	catch(...)
	{
	}

	return 1;
}



// CStatusCtrl

STDMETHODIMP CStatusCtrl::ShowUI(VARIANT_BOOL bShow, ULONG x, ULONG y)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int iInterfaceRet = S_OK;
	char strParameter[INFORMATION_LEN]={0};
	sprintf_s(strParameter,INFORMATION_LEN-1,"bShow = %d,x = %d,y = %d",bShow,x,y);
	INFO_TRACE(strParameter,&iInterfaceRet,"");

    // TODO: 在此添加实现代码
    if (!::IsWindow(m_hWnd) ) 	
    {
		iInterfaceRet = S_FALSE;
        return iInterfaceRet;
    }
	
    if (bShow == VARIANT_TRUE)
    {
       SetControlFocus(TRUE);
       EnableWindow(TRUE);
       MoveWindow(x,y,34,23);
       ShowWindow(SW_SHOW);
    }
    else
    {
		ShowWindow(SW_HIDE);
    }
	return iInterfaceRet;
}


LRESULT CStatusCtrl::OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	SetCursor(::LoadCursor(NULL, IDC_HAND));
	return 0;
}
LRESULT CStatusCtrl::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DEBUG_TRACE("");

	if (!iseSpaceExist())
	{
		CMenu m_mMainMenu;
		m_mMainMenu.CreatePopupMenu();
		m_mMainMenu.InsertMenu(1, MF_BYCOMMAND|MF_STRING, ECS_STARTESPACE_MENU, _T("Start eSpace"));
		CRect rect(0,0,0,0);
		GetWindowRect(&rect);
		m_mMainMenu.TrackPopupMenu(TPM_LEFTALIGN, rect.left, rect.bottom, CWnd::FromHandle(m_hWnd));
		return 1;
	}
	///////eSpace离线状态，右击不弹出命令菜单 c00327158  Start/////////
	CComPtr<eSpace::IECSContactInfo> pSelfInfo;
	if (NULL == m_ComeSpaceAPP)
	{
		INFO_LOG("eSpace is not Exit");
		return 0;
	}
	else
	{
		pSelfInfo = m_ComeSpaceAPP->GetSelfInfo();
		if (NULL == pSelfInfo || pSelfInfo->GetStatus())
		{
			INFO_LOG("eSpace is offline");
		}
	}
	///////eSpace离线状态，右击不弹出命令菜单 c00327158 End/////////

	CMenu m_mMainMenu;
    // TODO: 在此添加消息处理程序代码和/或调用默认值	
	//暂时只显示：绑定号码、手机、办公电话
	CString strCall =_T("Call ");
	if(m_strBindNo.Length() != 0)
	{
		m_mMainMenu.CreatePopupMenu();
		m_mMainMenu.InsertMenu(1, MF_BYCOMMAND|MF_STRING, ECS_IM_MENU, _T("Send an Instant Message"));
		CString strBindNoTemp_= strCall + m_strBindNo;
		m_mMainMenu.InsertMenu(2, MF_BYCOMMAND|MF_STRING, ECS_CALLPCTOPC_MENU, strBindNoTemp_);
		/////本地账号，不可以发送及时消息及VOIP呼叫  c00327158 Start///////
		if(IsLocalAccount(m_strAccount.m_str))
		{
			m_mMainMenu.EnableMenuItem(ECS_IM_MENU,MF_BYCOMMAND | MF_GRAYED);
			m_mMainMenu.EnableMenuItem(ECS_CALLPCTOPC_MENU,MF_BYCOMMAND | MF_GRAYED);
		}
		/////本地账号，不可以发送及时消息及VOIP呼叫  c00327158 End///////
	}
	if(m_strMobile.Length() != 0 )
	{
		CString strMobileTemp_ = strCall + m_strMobile;
		m_mMainMenu.InsertMenu(3, MF_BYCOMMAND|MF_STRING, ECS_CALLSIPMOBILE_MENU, strMobileTemp_);
	}
	if(m_strHomePhone.Length() != 0)
	{
		CString strHomePhoneTemp_= strCall + m_strHomePhone;
		m_mMainMenu.InsertMenu(4, MF_BYCOMMAND|MF_STRING, ECS_CALLSIPHOMEPHONE_MENU, strHomePhoneTemp_);
	}
	if(m_strOfficePhone.Length() != 0 )
	{
		CString strOfficePhoneTemp_= strCall + m_strOfficePhone;
		m_mMainMenu.InsertMenu(5, MF_BYCOMMAND|MF_STRING, ECS_CALLSIPOFFICEPHONE_MENU, strOfficePhoneTemp_);
	}
	if(m_strShortPhone.Length() != 0 )
	{
		CString strShortPhoneTemp_= strCall + m_strShortPhone;
		m_mMainMenu.InsertMenu(6, MF_BYCOMMAND|MF_STRING, ECS_CALLSIPSHORTPHONE_MENU, strShortPhoneTemp_);
	}
	if(m_strOtherPhone.Length() != 0 )
	{
		CString strOtherPhoneTemp_= strCall + m_strOtherPhone;
		m_mMainMenu.InsertMenu(7, MF_BYCOMMAND|MF_STRING, ECS_CALLSIPOTHERPHONE_MENU, strOtherPhoneTemp_);
	}
	if(m_strIPPhone1.Length() !=0 && m_strIPPhone1 != m_strOfficePhone )
	{
		CString strIPPhone1Temp_= strCall + m_strIPPhone1;
		m_mMainMenu.InsertMenu(8, MF_BYCOMMAND|MF_STRING, ECS_CALLSIPIPPHONE1_MENU, strIPPhone1Temp_);
	}
	if(m_strBindNo.Length() != 0 )
	{
		m_mMainMenu.InsertMenu(9, MF_BYCOMMAND|MF_STRING, ECS_ADDTOFRIEND_MENU, _T("Add to Contact List"));
		//////查询联系人是否是自己的好友，好友禁用 添加联系人命令 c00327158 Start///////
		m_uIsFriend = S_FALSE;
		if (NULL != m_ComeSpaceAPP)
		{
			if(NULL != m_ComContactMgr)
			{
				if(m_ComContactMgr->IsFriend(m_strAccount.m_str))
				{
					m_uIsFriend = S_OK;
				}
			}
		}
		if (m_uIsFriend == S_OK)
		{
			m_mMainMenu.EnableMenuItem(ECS_ADDTOFRIEND_MENU,MF_BYCOMMAND | MF_GRAYED);
		}
		//////查询联系人是否是自己的好友，好友禁用 添加联系人命令 c00327158 End///////
		CRect rect(0,0,0,0);
		GetWindowRect(&rect);
		m_mMainMenu.TrackPopupMenu(TPM_LEFTALIGN, rect.left, rect.bottom, CWnd::FromHandle(m_hWnd));
	}
    return 0;
}

LRESULT CStatusCtrl::OnClickIMMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DEBUG_TRACE("");

    if (!GetECSFramework())
    {
        return S_FALSE;
    }

    bool isSuccess = false;
    try
    {
        if (NULL != m_ComeSpaceAPP)
        {
			CComPtr<eSpace::IECSMainWindow> pMainWiondow ;
			pMainWiondow = m_ComeSpaceAPP->GetMainWindow();
			if(NULL != pMainWiondow && NULL != m_strAccount.m_str)
			{
				HRESULT hr = pMainWiondow->ShowIMChat(m_strAccount.m_str);
				if(S_OK == hr)
				{
					 isSuccess = true;
				}
			}
           
        }
    }
    catch(...)
	{
    }

    if (!isSuccess)
    {
        FireECSEvent(ecs::statusctrl::ERROR_CLIENT_STARTIMERROR);
    }
    return S_OK;
}

LRESULT CStatusCtrl::OnClickCallMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    return 0;
}

LRESULT CStatusCtrl::OnClickCallPcToPcMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DEBUG_TRACE("");

    CString phoneNum(m_strBindNo);
    CString callNum;

    callNum.Append(_T("*"));
	callNum.Append(phoneNum);

    CallOut(CComBSTR(callNum), CComBSTR(m_strAccount), CComBSTR(m_strName)); //lint !119  //lint !1025
    
    return 0;
}

LRESULT CStatusCtrl::OnClickCallSIPMobileMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CallOut(m_strMobile, CComBSTR(_T("")), m_strMobile);//lint !119  //lint !1025
    return 0;
}

LRESULT CStatusCtrl::OnClickCallSIPHomePhoneMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CallOut(m_strHomePhone, CComBSTR(_T("")), m_strHomePhone);//lint !119  //lint !1025
	return 0;
}

LRESULT CStatusCtrl::OnClickCallSIPOfficePhoneMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CallOut(m_strOfficePhone, CComBSTR(_T("")), m_strOfficePhone);//lint !119  //lint !1025
	return 0;
}

LRESULT CStatusCtrl::OnClickCallSIPShortPhoneMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CallOut(m_strShortPhone, CComBSTR(_T("")), m_strShortPhone);//lint !119  //lint !1025
	return 0;
}

LRESULT CStatusCtrl::OnClickCallSIPOtherPhoneMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CallOut(m_strOtherPhone, CComBSTR(_T("")), m_strOtherPhone);//lint !119  //lint !1025
	return 0;
}

LRESULT CStatusCtrl::OnClickCallSIPIPPhone1Menu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CallOut(m_strIPPhone1, CComBSTR(_T("")), m_strIPPhone1);//lint !119  //lint !1025
	return 0;
}

LRESULT CStatusCtrl::OnClickStarteSpaceMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DEBUG_TRACE("");

    if (NULL != m_ComeSpaceAPP)
    {
        m_ComeSpaceAPP.Release();
    }
    
    try
    {
        m_ComeSpaceAPP.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp),NULL, CLSCTX_ALL);
    }
    catch(...)
    {
        FireECSEvent(ecs::statusctrl::ERROR_CLIENT_NOTINSTALLED);
        return 0;
    }

	if(NULL != m_ComeSpaceAPP)
	{
		m_ComContactMgr = m_ComeSpaceAPP->GetContactMgr();
	}
	return 0;
}

LRESULT CStatusCtrl::OnClickMeetingMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DEBUG_TRACE("");

    if (!GetECSFramework())
    {
        return S_FALSE;
    }

    bool isSuccess = false;

    try
    {
        if (NULL != m_ComeSpaceAPP)
        {
			//调用eSpace的发起会议接口
			isSuccess = true;
        }
    }
    catch(...)
    {
    }

    if (!isSuccess)
    {
        FireECSEvent(ecs::statusctrl::ERROR_CLIENT_STARTMEETINGERROR);
    }
    return 0;
}

LRESULT CStatusCtrl::OnClickAddFriendMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DEBUG_TRACE("");

    // TODO: 在此添加实现代码
    if (!GetECSFramework())
    {
        return S_FALSE;
    }
    
    bool isSuccess = false;

    try
    {
        if (NULL != m_ComeSpaceAPP)
        {
            //调用eSpace的增加好友的COM接口
			if(NULL != m_ComContactMgr)
			{
				m_ComContactMgr->AddToContactList(m_strAccount.m_str);
				isSuccess = true;
			}
            
        }
    }
    catch(...)
    {
    }

    if (!isSuccess)
    {
        FireECSEvent(ecs::statusctrl::ERROR_CLIENT_STARTADDTOCONTACTERROR);
    }

    return 0;
}

STDMETHODIMP CStatusCtrl::get_OnUserStatusChange(VARIANT* /*pVal*/)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    // TODO: 在此添加实现代码
    return S_OK;
}

STDMETHODIMP CStatusCtrl::put_OnUserStatusChange(VARIANT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: 在此添加实现代码
	if (newVal.vt == VT_DISPATCH)
	{
		m_spCallback = newVal.pdispVal;
	}
	return S_OK;
}

STDMETHODIMP CStatusCtrl::GetStatus(BSTR account, BSTR id)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: 在此添加实现代码
	int iInterfaceRet = S_OK;
	char strParameter[INFORMATION_LEN]={0};
	sprintf_s(strParameter,INFORMATION_LEN-1,"account = %s,id = %s",Bstr2String(account).c_str(),Bstr2String(id).c_str());
	INFO_TRACE(strParameter,&iInterfaceRet,"");

	CString strTempAccount = account;
	strTempAccount.MakeLower();
	m_mapIDAccount.insert(std::make_pair(strTempAccount, id));

	CString* pStrAccountTemp = new CString(strTempAccount);
	CString* pStrIDTemp = new CString(id);

	if (!GetECSFramework())
	{
		iInterfaceRet = S_FALSE;
		/////记录下需要查询的账号，等待eSpace上线后订阅状态///////
		m_mapAccountType[*pStrAccountTemp] = 0;
		SAFE_DELETE(pStrAccountTemp);
		SAFE_DELETE(pStrIDTemp);
		return iInterfaceRet;
	}
	PostMessage(REQ_ASYN_GET_STATUS,(WPARAM)pStrAccountTemp,(LPARAM)pStrIDTemp);
    return iInterfaceRet;
}

bool CStatusCtrl::iseSpaceExist()
{
	DEBUG_TRACE("");
    HANDLE hSnapshot = NULL;   

    hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);   

    PROCESSENTRY32 pe;   
    pe.dwSize   = sizeof(PROCESSENTRY32);     

    Process32First(hSnapshot,&pe);   

    do   
    {   
        if(_tcscmp(pe.szExeFile, _T("eSpace.exe"))==0)   
        {   
            //WaitForSingleObject(hSnapshot, INFINITE);
			::CloseHandle(hSnapshot);
            return true;
        }   
    }   
    while(Process32Next(hSnapshot,&pe)==TRUE);      
	
	::CloseHandle(hSnapshot);

    return false;
}

bool CStatusCtrl::GetECSFramework()
{
	DEBUG_TRACE("");
    //如果进程不存在,则不创建接口,避免启动eSpace客户端.
    if (!iseSpaceExist())
    {
		INFO_LOG("eSpaceExist is not exit");
        return false;
    }

	/////eSpace被拉起，但是未登录，导致eSpace卡死   by c00327158  Start/////
	if (IseSpaceLogin())
	{
		INFO_LOG("eSpaceExist is not login");
		return false;
	}
    if (NULL != m_ComeSpaceAPP)
    {
		INFO_LOG("m_ComeSpaceAPP is exist");
        m_ComeSpaceAPP.Release();
    }
	/////eSpace被拉起，但是未登录，导致eSpace卡死   by c00327158  End/////
    try
    {
        HRESULT hr = m_ComeSpaceAPP.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp),NULL, CLSCTX_ALL);
	    INFO_LOG("CoCreateInstance errorcode  is %d",hr);
    }
    catch(...)
    {
        FireECSEvent(ecs::statusctrl::ERROR_CLIENT_NOTINSTALLED);
        return false;
    }
	

    if(NULL != m_ComeSpaceAPP)
    {
		m_ComContactMgr = m_ComeSpaceAPP->GetContactMgr();
        return true;
    }
    else
    {
        FireECSEvent(ecs::statusctrl::ERROR_CLIENT_NOTINSTALLED);
        return false;
    }
}

LRESULT CStatusCtrl::OnReqAsynGetStatus(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	DEBUG_TRACE("");
	CString* pStrAccountTemp = (CString*)wParam;
	CString* pStrIDTemp = (CString*)lParam;
	BSTR account = _bstr_t(*pStrAccountTemp).Detach();
	BSTR id = _bstr_t(*pStrIDTemp).Detach();

	bool isSuccess = false;
	try
	{
		if (NULL != m_ComeSpaceAPP)
		{
			if(m_eventHandler.get() == NULL)
			{
				std::auto_ptr<IECSExternEventHandler> pEventHandler(new IECSExternEventHandler(*this, m_ComeSpaceAPP, &CStatusCtrl::OnEventOccured));
				m_eventHandler = pEventHandler;
			}

			CString strAccountTemp = account;
			m_strAccount = account;
			strAccountTemp.MakeLower();
			account = _bstr_t(strAccountTemp).Detach();
			CComPtr<eSpace::IECSContactInfo> pContactInfo;
			CComPtr<eSpace::IECSContactMgr> pContactMgr;
			pContactMgr = m_ComeSpaceAPP->GetContactMgr();
			if(NULL != pContactMgr)
			{
				INFO_LOG("GetContactInfo Begin");
				pContactInfo = pContactMgr->GetContactInfo(account);
				INFO_LOG("GetContactInfo End");
				if(NULL != pContactInfo)
				{
					INFO_LOG("GetStatus Begin");
					m_iStatus = pContactInfo->GetStatus();
					INFO_LOG("GetStatus End");
					_bstr_t device = pContactInfo->GetLoginDevice();					
					if((_bstr_t)("m") == device)
					{
						m_iClientType = 1;
					}
					else if(device == (_bstr_t)("ip"))
					{
						m_iClientType = 2;
					}
					else if(device == (_bstr_t)("w"))
					{
						m_iClientType = 3;
					}
					else
					{
						m_iClientType = 0; // 默认PC
					}
					isSuccess = true;
				}
			}
		}
	}
	catch(...)
	{		
	}	

	if (!isSuccess)
	{
		FireECSEvent(ecs::statusctrl::ERROR_CLIENT_STARTSTATUSERROR);
	}
	else
	{
		NotifyStatusChange(account,m_iStatus,m_iClientType);
	}

	SAFE_DELETE(pStrAccountTemp);
	SAFE_DELETE(pStrIDTemp);

	return 0L;
}

void CStatusCtrl::FireECSEvent(int eventID)
{
	char strParameter[INFORMATION_LEN] = {0};
	sprintf_s(strParameter, INFORMATION_LEN-1, "eventID = %d",eventID);
	INFO_TRACE(strParameter, NULL, "");

	CComVariant varResult;
	CComVariant avarParams[1];
	avarParams[0] = eventID;                                 // nCurrentProgress
	avarParams[0].vt = VT_I4;
	DISPPARAMS params = { avarParams, NULL, 1, 0 };

	try
	{
		if(NULL != m_spEventCallback)
		{
		   m_spEventCallback->Invoke(0, 
				 IID_NULL, 
				 LOCALE_USER_DEFAULT, 
				 DISPATCH_METHOD, 
				 &params, &varResult, NULL, NULL);
		}
	}
	catch(...)
	{
	}
}
void CStatusCtrl::NotifyStatusChange(BSTR account, LONG status, LONG clientType)
{
	char strParameter[INFORMATION_LEN] = {0};
	sprintf_s(strParameter, INFORMATION_LEN-1, "Account = %s,Status = %d,clientType = %d",Bstr2String(account).c_str(),status,clientType);
	INFO_TRACE(strParameter, NULL, "");

	std::multimap<CString, CString>::iterator lFindResultItor = m_mapIDAccount.find(account);
	if(lFindResultItor == m_mapIDAccount.end())
	{
		ERROR_LOG("NotifyStatusChange failed.");
		return;
	}

	std::multimap<CString, CString>::iterator lItor = m_mapIDAccount.lower_bound(account);
	std::multimap<CString, CString>::iterator hItor = m_mapIDAccount.upper_bound(account);

	for (std::multimap<CString, CString>::iterator itor = lItor;itor != hItor;++itor)
	{
		if (itor->second.IsEmpty())
		{
			////解决CHECK_CONTAINER_EMPTY错误/////
			continue;
		}
		CString imageID = itor->second;
		BSTR bstrImageID = _bstr_t(imageID).Detach();
		CComVariant varResult;
		CComVariant avarParams[4];
		avarParams[3] = account;			
		avarParams[3].vt = VT_BSTR;
		avarParams[2] = status;				
		avarParams[2].vt = VT_I4;
		avarParams[1] = imageID;									
		avarParams[1].vt = VT_BSTR;
		avarParams[0] = clientType;       
		avarParams[0].vt = VT_I4;
		m_mapAccountType[account] = clientType;

		DISPPARAMS params = { avarParams, NULL, 4, 0 };

		try
		{
			if(NULL != m_spCallback)
			{
				INFO_LOG("NotifyStatusChange:imageID = %s,account = %s,status = %d,clientType= %d."	,
					_com_util::ConvertBSTRToString(bstrImageID),
					_com_util::ConvertBSTRToString(account),
					status,
					clientType);
				(void)m_spCallback->Invoke(0,
					IID_NULL, 
					LOCALE_USER_DEFAULT, 
					DISPATCH_METHOD, 
					&params, &varResult, NULL, NULL);
			}
		}
		catch(...)
		{

		}
	}
}
HRESULT CStatusCtrl::OnEventOccured(eSpace::ECSEventType eventType,const _variant_t & param1,const _variant_t & param2,const _variant_t & param3)
{
	DEBUG_TRACE("");

	if(eventType == eSpace::APP_SHUTDOWN)
	{
		/////将本地联系人状态全部设置为离线///////
		std::map<CString, int>::iterator iter = m_mapAccountType.begin();
		for (;iter!=m_mapAccountType.end();iter++)
		{
			BSTR bsName = iter->first.AllocSysString();
			NotifyStatusChange(bsName,0,iter->second);
			SysFreeString(bsName);
		}
		m_ComeSpaceAPP->GetContactMgr().Release();
		m_ComeSpaceAPP.Release();
		FinalRelease();
	}
	else if(eventType == eSpace::LOGIN_STATE_CHANGE)
	{
		if(param1.intVal == 0)//本地账号从离线变上线
		{
			//////重新连接com//////
			if (NULL != m_ComeSpaceAPP)
			{
				m_ComeSpaceAPP.Release();
			}
			try
			{
				m_ComeSpaceAPP.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp),NULL, CLSCTX_ALL);
			}
			catch(...)
			{
				FireECSEvent(ecs::statusctrl::ERROR_CLIENT_NOTINSTALLED);
				return false;
			}

			if (m_ComeSpaceAPP)
			{
				if(m_eventHandler.get() == NULL)
				{
					std::auto_ptr<IECSExternEventHandler> pEventHandler(new IECSExternEventHandler(*this, m_ComeSpaceAPP, &CStatusCtrl::OnEventOccured));
					m_eventHandler = pEventHandler;
				}
				if(NULL != m_ComContactMgr)
				{
					/////重新订阅查询所得联系人状态//////
					std::map<CString, int>::iterator iter = m_mapAccountType.begin();
					for (;iter!=m_mapAccountType.end();iter++)
					{
						BSTR bsName = iter->first.AllocSysString();
						if(NULL != m_ComContactMgr)
						{
							 m_ComContactMgr->SubscribeContactStatus(bsName, 0);
						}
						SysFreeString(bsName);
 					}

				}
			}
			/////上报一下自己的状态/////
			CComPtr<eSpace::IECSContactInfo> pSelfInfo;
			if(NULL != m_ComContactMgr)
			{
				pSelfInfo = m_ComeSpaceAPP->GetSelfInfo();
				if (NULL!= pSelfInfo)
				{
					NotifyStatusChange(pSelfInfo->GetUcAccount(),pSelfInfo->GetStatus(),0);
				}

			}
		}
		else if(param1.intVal == 1)//本地账号从上线变离线
		{
			//////本地账号下线，将需要将控件查询的账号全部变为离线状态/////
			std::map<CString, int>::iterator iter = m_mapAccountType.begin();
			for (;iter!=m_mapAccountType.end();iter++)
			{
				BSTR bsName = iter->first.AllocSysString();
				NotifyStatusChange(bsName,0,iter->second);
				SysFreeString(bsName);
			}
			/////释放com/////
			if (NULL != m_ComeSpaceAPP)
			{
				m_ComeSpaceAPP.Release();
			}
		}
		else
		{
			ERROR_LOG("eventType == eSpace::LOGIN_STATE_CHANGE param1.intVal is %d",param1.intVal);
		}

	}
	else if(eventType == eSpace::CONTACT_STATE_CHANGE)
	{		
		BSTR contactAcct = param1.bstrVal;
		long lStatus =  param2.intVal;
		BSTR ucDevice = param3.bstrVal;

		long iClientType = 0;
		if (m_ComeSpaceAPP)
		{
            _bstr_t device(ucDevice);
			if((_bstr_t)("m") == device)
			{
				iClientType = 1;
			}
			else if(device == (_bstr_t)("ip"))
			{
				iClientType = 2;
			}
			else if(device == (_bstr_t)("w"))
			{
				iClientType = 3;
			}
            else
            {
                iClientType = 0;
            }
		}
			//状态改变的uc账号和控件绑定的uc账号不一致
		NotifyStatusChange(contactAcct,lStatus,iClientType);
	}

	return S_OK;
}

STDMETHODIMP CStatusCtrl::SetUserInfo(BSTR strAccount, BSTR staffNo, BSTR strName, LONG status)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int iInterfaceRet = S_OK;
	char strParameter[INFORMATION_LEN]={0};
	sprintf_s(strParameter,INFORMATION_LEN-1,"strAccount = %s,staffNo = %s,strName = %s,status = %d",Bstr2String(strAccount).c_str(),Bstr2String(staffNo).c_str(),Bstr2String(strName).c_str(),status);
	INFO_TRACE(strParameter,&iInterfaceRet,"");

	if(!GetECSFramework())
	{
		iInterfaceRet = S_FALSE;
		m_iStatus = 0;////查询eSpace元素不存在，默认是离线的
		INFO_LOG("GetECSFramework() Failed");
		return iInterfaceRet;
	}
    // TODO: 在此添加实现代码
	CString strAccountTemp = (TCHAR*)COLE2T(strAccount);
	strAccountTemp.MakeLower();
	strAccount = _bstr_t(strAccountTemp).Detach();
	m_strAccount = strAccount;
	m_strStaffNO = staffNo;
	m_strName = strName;
	m_iStatus = status;
    m_iClientType = m_mapAccountType[strAccountTemp];

	if(g_strAccout != m_strAccount)
	{
		INFO_LOG("g_strAccout != m_strAccount");
		HANDLE hThread = CreateThread(NULL,0,_GetNumByAccountThread,this,0,NULL);
		CloseHandle(hThread);	
		g_strAccout = m_strAccount;
	}
	if(m_eventHandler.get() == NULL)
	{
		std::auto_ptr<IECSExternEventHandler> pEventHandler(new IECSExternEventHandler(*this, m_ComeSpaceAPP, &CStatusCtrl::OnEventOccured));
		m_eventHandler = pEventHandler;
	}

    return iInterfaceRet;
}

STDMETHODIMP CStatusCtrl::get_OneSpaceEvent(VARIANT* /*pVal*/)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    // TODO: 在此添加实现代码
    return S_OK;
}

STDMETHODIMP CStatusCtrl::put_OneSpaceEvent(VARIANT newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    // TODO: 在此添加实现代码
    if (newVal.vt == VT_DISPATCH)
    {
        m_spEventCallback = newVal.pdispVal;
    }

    return S_OK;
}

void CStatusCtrl::CallOut(BSTR phoneNum, BSTR account, BSTR name)
{
	char strParameter[INFORMATION_LEN] = {0};
	sprintf_s(strParameter, INFORMATION_LEN-1, "phoneNum = %s,Account = %s,Name = %s",Bstr2String(phoneNum).c_str(),Bstr2String(account).c_str(),Bstr2String(name).c_str());
	INFO_TRACE(strParameter, NULL, "");

    if (!GetECSFramework())
    {
        return;
    }

    bool isSuccess = false;

    try
    {
        if (NULL != m_ComeSpaceAPP)
        {
			CComPtr<eSpace::IECSContactInfo> pContactInfo;
			if(NULL != m_ComContactMgr)
			{
				CComPtr<eSpace::IECSMainWindow>	pMainWindow;
				pMainWindow = m_ComeSpaceAPP->GetMainWindow();
				pContactInfo = m_ComContactMgr->GetContactInfo(account);
				if(NULL != pContactInfo && Bstr2String(account).length())
				{
					_bstr_t ucuri = pContactInfo->GetUcUri();					
					if(NULL != pMainWindow)
					{
						pMainWindow->MakeCall(ucuri,"");
					}
				}
				else
				{
					if(NULL != pMainWindow)
					{
						pMainWindow->MakeCall("", phoneNum);
					}
				}
			}
            isSuccess = true;
        }
    }
    catch(...)
    {
    }

    if (!isSuccess)
    {
        FireECSEvent(ecs::statusctrl::ERROR_CLIENT_STARTCALLERROR);
    }
}

LRESULT CStatusCtrl::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    return CComControlBase::OnPaint(uMsg, wParam, lParam, bHandled);
}

HRESULT CStatusCtrl::OnDraw(ATL_DRAWINFO& di)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_bInPlaceActive)
	{
        CBitmap bitmap;
        bitmap.LoadBitmap(IDB_BITMAP_OFFLINE);
        HDC hdcMem = CreateCompatibleDC(di.hdcDraw) ;
        SelectObject (hdcMem, bitmap) ;
        BitBlt(di.hdcDraw, 0, 0, 20, 20, hdcMem, 0, 0, SRCCOPY) ;
        DeleteDC(hdcMem) ;
	}
    else
    {
        long width = di.prcBounds->right - di.prcBounds->left;
        long height = di.prcBounds->bottom - di.prcBounds->top;

        CBitmap backgroup;
        backgroup.LoadBitmap(IDB_BITMAP_BACKGROUPND);

        HDC dc = ::CreateCompatibleDC(di.hdcDraw);
        HGDIOBJ bmp = ::SelectObject(dc, (HBITMAP)backgroup);    
        BitBlt(di.hdcDraw, 0, 0, width, height, dc, 0, 0 ,   SRCCOPY );
        ::SelectObject(dc, bmp);    
        ::DeleteDC(dc);

        CBitmap bitmap;
        if (m_iStatus == 0)//离线
        {
            bitmap.LoadBitmap(IDB_BITMAP_OFFLINE);
        }
        else if (m_iStatus == 1)//在线
        {
            if (m_iClientType == 0)
            {
                bitmap.LoadBitmap(IDB_BITMAP_ONLINE);
            }
            else if(m_iClientType == 1)
            {
                bitmap.LoadBitmap(IDB_BITMAP_MOBILEONLINE);
            }
			else if(m_iClientType == 2)
			{
				bitmap.LoadBitmap(IDB_BITMAP_IPPhoneOnline);
			}
			else
			{
				bitmap.LoadBitmap(IDB_BITMAP_WebOnline);
			}
        }
        else if (m_iStatus == 2)//隐身
        {
            bitmap.LoadBitmap(IDB_BITMAP_OFFLINE);
        }
        else if (m_iStatus == 3)//忙碌
        {
            if (m_iClientType == 0)
            {
                bitmap.LoadBitmap(IDB_BITMAP_BUSY);
            }
			else if(m_iClientType == 1)
			{
				bitmap.LoadBitmap(IDB_BITMAP_MOBILEBUSY);
			}
			else if(m_iClientType == 2)
			{
				bitmap.LoadBitmap(IDB_BITMAP_IPPhoneBusy);
			}
			else
			{
				bitmap.LoadBitmap(IDB_BITMAP_WebBusy);
			}
        }
        else if (m_iStatus == 4)//离开
        {
            if (m_iClientType == 0)
            {
                bitmap.LoadBitmap(IDB_BITMAP_AWAY);
            }
			else if(m_iClientType == 1)
			{
				bitmap.LoadBitmap(IDB_BITMAP_MOBILEAWAY);
			}
			else if(m_iClientType == 2)
			{
				bitmap.LoadBitmap(IDB_BITMAP_IPPhoneAway);
			}
            else
            {
                bitmap.LoadBitmap(IDB_BITMAP_WebAway);
            }
        }
		else if (m_iStatus == 5)//免打扰
		{
			if (m_iClientType == 0)
			{
				bitmap.LoadBitmap(IDB_BITMAP_DND);
			}
			else if(m_iClientType == 1)
			{
				bitmap.LoadBitmap(IDB_BITMAP_MOBILEDND);
			}
			else if(m_iClientType == 2)
			{
				bitmap.LoadBitmap(IDB_BITMAP_IPPhoneDnd);
			}
			else
			{
				bitmap.LoadBitmap(IDB_BITMAP_WebDnd);
			}
		}
        else
        {
            bitmap.LoadBitmap(IDB_BITMAP_OFFLINE);
        }

        HDC statusDC = ::CreateCompatibleDC(di.hdcDraw);
        HGDIOBJ statusBMPObj = ::SelectObject(statusDC, (HBITMAP)bitmap);    
        BitBlt(di.hdcDraw, 1, 1, 20, 20, statusDC, 0, 0, SRCCOPY );
        ::SelectObject(statusDC, statusBMPObj);    
        ::DeleteDC(statusDC);
    }
	return S_OK;
}
STDMETHODIMP CStatusCtrl::Login(BSTR account, BSTR pwd, LONG type)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int iInterfaceRet = S_OK;
	char strParameter[INFORMATION_LEN]={0};
	sprintf_s(strParameter,INFORMATION_LEN-1,"account = %s,pwd = %s,type = %d",Bstr2String(account).c_str(),Bstr2String(pwd).c_str(),type);
	INFO_TRACE(strParameter,&iInterfaceRet,"");
    // TODO: 在此添加实现代码
    if (!GetECSFramework())
    {
		iInterfaceRet = S_FALSE;
        return iInterfaceRet;
    }

    try
    {
        if (NULL != m_ComeSpaceAPP)
        {
            //调用eSpace的登陆接口，页面暂时未调用
        }
    }
    catch(...)
    {
        FireECSEvent(ecs::statusctrl::ERROR_CLIENT_STARTLOINGERROR);
    }

    return iInterfaceRet;
}

std::string GetNoFromUri(const std::string & uri)
{
	size_t nSip = uri.find("sip:");

	if (nSip != 0) //必须以sip:开头
	{
		return "";
	}

	size_t nAt = uri.find('@');
	if (std::string::npos == nAt) //必须含有@字符
	{
		return "";
	}
	//取sip:与@之间的字符串，注意要除去长度为4的"sip:"
	std::string strNum = uri.substr(/*nSip +*/ 4, (nAt /*- nSip*/) - 4); //程序执行到此行时，nSip==0

	if (strNum.find('+') != std::string::npos)
	{
		strNum = strNum.substr(1);
	}

	return strNum;
}


void CStatusCtrl::GetNumByAccount()
{  
	DEBUG_TRACE("");
	m_uIsFriend = S_FALSE;
	if (!iseSpaceExist())
	{
		return;
	}
	try
	{
		CComPtr<eSpace::IECSEspaceApp> comeSpaceAppThread;
		CoInitialize(NULL); 
		comeSpaceAppThread.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp),NULL, CLSCTX_ALL);
		if (comeSpaceAppThread)
		{
			BSTR strAccount = m_strAccount.m_str;
			CComPtr<eSpace::IECSContactInfo> pContactInfo;
			CComPtr<eSpace::IECSContactMgr> pContactMgr;
			pContactMgr = comeSpaceAppThread->GetContactMgr();
			if(NULL != pContactMgr)
			{
				long isFriend = pContactMgr->IsFriend(strAccount);
				if(1 == isFriend)
				{
					m_uIsFriend = S_OK;
				}
				pContactInfo = pContactMgr->GetContactInfo(strAccount);
				if(NULL != pContactInfo)
				{
					_bstr_t bstrUri = pContactInfo->GetUcUri();
					CHECK_POINTER(bstrUri.GetBSTR());
					char* chUri(bstrUri);
					std::string strUri = chUri;
					std::string strBindNum = GetNoFromUri(strUri);
					m_strBindNo = strBindNum.c_str();
					m_strMobile = pContactInfo->GetMobile().GetBSTR();
					m_strOfficePhone = pContactInfo->GetOfficePhone().GetBSTR();
					m_strOtherPhone = pContactInfo->GetOtherPhone().GetBSTR();
					m_strIPPhone1 = pContactInfo->GetIPPhone1().GetBSTR();

					//获取UC信息成功的话就订阅
					pContactMgr->SubscribeContactStatus(strAccount, 0);
				}
				else
				{
					m_strBindNo = "";
					m_strMobile = "";
					m_strOfficePhone = "";
					m_strOtherPhone = "";
					m_strIPPhone1 = "";
				}
			}
		}
	}
	catch(...)
	{
	}
	CoUninitialize();  
}

bool CStatusCtrl::IseSpaceLogin(void)
{
	DEBUG_TRACE("");
	if (::FindWindowEx(NULL, NULL, _T("#32770"), _T("eSpace Login")))
	{
		return true;
	}
	return false;
}

std::string CStatusCtrl::Bstr2String(BSTR m_bstr)
{
	std::string m_str("");
	char tmpchar[PARAMETER_LEN];
	memset_s(tmpchar,PARAMETER_LEN,0,PARAMETER_LEN);
	char *str = _com_util::ConvertBSTRToString(m_bstr);
	if(str)
	{
		strncpy_s(tmpchar,PARAMETER_LEN,str,_TRUNCATE);
		SAFE_DELETE_ARRAY(str);
	}
	m_str = tmpchar;
	return m_str;
}
bool CStatusCtrl::IsLocalAccount(BSTR m_bstr)
{
	bool Result = false;
	if (NULL != m_ComeSpaceAPP)
	{
		m_ComeSpaceAPP.Release();
	}
	try
	{
		m_ComeSpaceAPP.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp),NULL, CLSCTX_ALL);
	}
	catch(...)
	{
		FireECSEvent(ecs::statusctrl::ERROR_CLIENT_NOTINSTALLED);
		return Result;
	}
	if (m_ComeSpaceAPP)
	{
		CComPtr<eSpace::IECSContactInfo> pSelfInfo;
		pSelfInfo = m_ComeSpaceAPP->GetSelfInfo();
		BSTR   Name(NULL);
		if (NULL!= pSelfInfo)
		{
			Name =  pSelfInfo->GetUcAccount();
		}
		if (NULL != Name && !wcscmp(Name,m_bstr))
		{
			Result = true;
		}
	}

	return Result;

}

