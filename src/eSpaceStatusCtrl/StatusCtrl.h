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

// StatusCtrl.h : CStatusCtrl 的声明
#pragma once
#include "resource.h"       // 主符号
#include <atlctl.h>
#include "eSpaceStatusCtrl.h"
#include "_IStatusCtrlEvents_CP.h"
#include "TEventHandler.h"
#include "eSDKTool.h"
#include <time.h>
#include "afxole.h"

#define CLIENT_LOGCFG_FILE "eSDKClientLogCfg.ini"
#define CLIENT_LOG_PATH "eSDKLog"
#define INFORMATION_LEN 1024

#define REQ_ASYN_GET_STATUS	(WM_APP + 1)	//请求异步获取状态

#define ECS_MENU_BEGIN 10000
#define ECS_IM_MENU					(ECS_MENU_BEGIN + 1)
#define ECS_CALL_MENU				(ECS_MENU_BEGIN + 2)
#define ECS_MEETING_MENU			(ECS_MENU_BEGIN + 3)
#define ECS_ADDTOFRIEND_MENU		(ECS_MENU_BEGIN + 4)
#define ECS_CALLPCTOPC_MENU			(ECS_MENU_BEGIN + 5)
#define ECS_CALLSIPMOBILE_MENU		(ECS_MENU_BEGIN + 6)
#define ECS_CALLSIPHOMEPHONE_MENU	(ECS_MENU_BEGIN + 7)
#define ECS_CALLSIPOFFICEPHONE_MENU (ECS_MENU_BEGIN + 8)
#define ECS_CALLSIPSHORTPHONE_MENU	(ECS_MENU_BEGIN + 9)
#define ECS_CALLSIPOTHERPHONE_MENU	(ECS_MENU_BEGIN + 10)
#define ECS_CALLSIPIPPHONE1_MENU	(ECS_MENU_BEGIN + 11)
#define ECS_STARTESPACE_MENU		(ECS_MENU_BEGIN + 12)

namespace ecs{
namespace statusctrl{
    //StatusCtrl错误码，和W3 Portal约定
        const static int ERROR_CLIENT_NOTINSTALLED = -1;//客户端没有正确被安装
        const static int ERROR_CLIENT_STARTIMERROR = -2;//启动即时消息失败
        const static int ERROR_CLIENT_STARTCALLERROR = -3;//启动呼叫失败
        const static int ERROR_CLIENT_STARTADDTOCONTACTERROR = -4;//启动添加好友失败
        const static int ERROR_CLIENT_STARTSTATUSERROR = -5;//获取状态失败
        const static int ERROR_CLIENT_STARTMEETINGERROR = -6;//启动会议失败
        const static int ERROR_CLIENT_STARTLOINGERROR = -7;//启动登录失败
}
}

class CStatusCtrl;
typedef TEventHandler<CStatusCtrl, eSpace::IECSEspaceApp> IECSExternEventHandler;

// CStatusCtrl
class ATL_NO_VTABLE CStatusCtrl : //IObjectSafetyImpl
	public CComObjectRootEx<CComMultiThreadModel>,
	public IDispatchImpl<IStatusCtrl, &IID_IStatusCtrl, &LIBID_eSpaceStatusCtrlLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistStreamInitImpl<CStatusCtrl>,
	public IOleControlImpl<CStatusCtrl>,
	public IOleObjectImpl<CStatusCtrl>,
	public IOleInPlaceActiveObjectImpl<CStatusCtrl>,
	public IViewObjectExImpl<CStatusCtrl>,
	public IOleInPlaceObjectWindowlessImpl<CStatusCtrl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CStatusCtrl>,
	public CProxy_IStatusCtrlEvents<CStatusCtrl>, 
	public IObjectWithSiteImpl<CStatusCtrl>,
	public IServiceProviderImpl<CStatusCtrl>,
	public IPersistStorageImpl<CStatusCtrl>,
	public ISpecifyPropertyPagesImpl<CStatusCtrl>,
	public IQuickActivateImpl<CStatusCtrl>,
	public IDataObjectImpl<CStatusCtrl>,
	public IProvideClassInfo2Impl<&CLSID_StatusCtrl, &__uuidof(_IStatusCtrlEvents), &LIBID_eSpaceStatusCtrlLib>,
	public IPropertyNotifySinkCP<CStatusCtrl>,
	public CComCoClass<CStatusCtrl, &CLSID_StatusCtrl>,
	public CComControl<CStatusCtrl>,
    public IObjectSafetyImpl<CStatusCtrl, 
                        INTERFACESAFE_FOR_UNTRUSTED_CALLER | 
                        INTERFACESAFE_FOR_UNTRUSTED_DATA>

{
private:
    //TODO:要找一个合适的地方注册菜单
    CComPtr<IDispatch> m_spCallback;//状态改变回调给JS的接口
    CComPtr<IDispatch> m_spEventCallback;//ECS事件回调给JS的接口
	std::auto_ptr<IECSExternEventHandler>  m_eventHandler;//控件对应的回调事件监听器

public:

    CStatusCtrl():m_strAccount("")
		,m_strStaffNO(static_cast< LPCOLESTR>(NULL)) //lint !119 //lint !1025
		,m_strName(static_cast< LPCOLESTR>(NULL))  //lint !119 //lint !1025
		,m_iStatus(0)
		,m_iClientType(0)
		,m_strBindNo(static_cast< LPCOLESTR>(NULL)) //lint !119 //lint !1025
		,m_strMobile(static_cast< LPCOLESTR>(NULL))
		,m_strHomePhone(static_cast< LPCOLESTR>(NULL)) //lint !119 //lint !1025
		,m_strOfficePhone(static_cast< LPCOLESTR>(NULL)) //lint !119 //lint !1025
		,m_strShortPhone(static_cast< LPCOLESTR>(NULL)) //lint !119 //lint !1025
		,m_strOtherPhone(static_cast< LPCOLESTR>(NULL)) //lint !119 //lint !1025
		,m_strIPPhone1(static_cast< LPCOLESTR>(NULL)) //lint !119 //lint !1025
		,m_eventHandler(NULL)//,m_hIEServerWnd(0) 
		,m_HWnd(NULL)
		,m_curTime(CTime::GetCurrentTime())
	{
		InitializeCriticalSection(&g_cs);
	}

	~CStatusCtrl()
	{
		DeleteCriticalSection(&g_cs);
	}
DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE | 
	OLEMISC_CANTLINKINSIDE | 
	OLEMISC_INSIDEOUT | 
	OLEMISC_ACTIVATEWHENVISIBLE | 
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_STATUSCTRL)

BEGIN_COM_MAP(CStatusCtrl)
	COM_INTERFACE_ENTRY(IStatusCtrl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IServiceProvider)
    COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_PROP_MAP(CStatusCtrl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// 示例项
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CStatusCtrl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(__uuidof(_IStatusCtrlEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CStatusCtrl)
    MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(REQ_ASYN_GET_STATUS,OnReqAsynGetStatus)	
    MESSAGE_HANDLER(WM_PAINT, OnPaint)
	CHAIN_MSG_MAP(CComControl<CStatusCtrl>)
    COMMAND_ID_HANDLER(ECS_IM_MENU , OnClickIMMenu)
    COMMAND_ID_HANDLER(ECS_CALL_MENU , OnClickCallMenu)
    COMMAND_ID_HANDLER(ECS_MEETING_MENU , OnClickMeetingMenu)
    COMMAND_ID_HANDLER(ECS_ADDTOFRIEND_MENU , OnClickAddFriendMenu)
    COMMAND_ID_HANDLER(ECS_CALLPCTOPC_MENU , OnClickCallPcToPcMenu)
	COMMAND_ID_HANDLER(ECS_CALLSIPMOBILE_MENU , OnClickCallSIPMobileMenu)
	COMMAND_ID_HANDLER(ECS_CALLSIPHOMEPHONE_MENU , OnClickCallSIPHomePhoneMenu)
	COMMAND_ID_HANDLER(ECS_CALLSIPOFFICEPHONE_MENU , OnClickCallSIPOfficePhoneMenu)
	COMMAND_ID_HANDLER(ECS_CALLSIPSHORTPHONE_MENU , OnClickCallSIPShortPhoneMenu)
	COMMAND_ID_HANDLER(ECS_CALLSIPOTHERPHONE_MENU , OnClickCallSIPOtherPhoneMenu)
	COMMAND_ID_HANDLER(ECS_CALLSIPIPPHONE1_MENU , OnClickCallSIPIPPhone1Menu)
	COMMAND_ID_HANDLER(ECS_STARTESPACE_MENU , OnClickStarteSpaceMenu)
	
    
END_MSG_MAP()
// 处理程序原型: 
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

BEGIN_SINK_MAP(CStatusCtrl)
	//请确保事件处理程序含有 __stdcall 调用约定
END_SINK_MAP()

	//STDMETHOD(OnAmbientPropertyChange)(DISPID dispid)
	//{
	//	if (dispid == DISPID_AMBIENT_BACKCOLOR)
	//	{
	//		SetBackgroundColorFromAmbient();
	//		FireViewChange();
	//	}
	//	return IOleControlImpl<CStatusCtrl>::OnAmbientPropertyChange(dispid);
	//}
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		DEBUG_TRACE("");
		static const IID* arr[] = 
		{
			&IID_IStatusCtrl,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IStatusCtrl

	enum { IDD = IDD_STATUSCTRL };
	STDMETHOD(_InternalQueryService)(REFGUID guidService, REFIID riid, void** ppvObject)
	{
        CComPtr<IOleClientSite> pocs;
        GetSite(IID_IOleClientSite,(void**)&pocs);

        CComPtr<IServiceProvider> sp;
        if (m_spUnkSite)
        {
            m_spUnkSite->QueryInterface(IID_IServiceProvider, (void**)&sp);
        }

        if (sp)
        {
            sp->QueryService(guidService, riid,  ppvObject);
        }

		return S_OK;
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	// 返回 %appdata%\\eSpace_Desktop\\ ；
	std::string GetAppDataDirA()
	{
		DEBUG_TRACE("");
		static std::string writeableDir;
		if ( !writeableDir.empty() )
		{
			return writeableDir;
		}

		char path[MAX_PATH+1] = {0};
		std::string configFilePath = ("%appdata%\\eSpace_Desktop\\");


		//扩展环境变量
		char expandArray[MAX_PATH+1] = {0};
		::ExpandEnvironmentStringsA(configFilePath.c_str(), expandArray, MAX_PATH);

		writeableDir = expandArray;
		if ( !PathFileExistsA(writeableDir.c_str()) )
		{
			SHCreateDirectoryExA(NULL, writeableDir.c_str(), NULL);
		}
		return writeableDir;
	}

	HRESULT FinalConstruct()
	{
		DEBUG_TRACE("");
		//初始化日志
		std::string path;
		eSDKTool::getCurrentPath(path);
		std::string strLogCfgFile = path + "\\" + CLIENT_LOGCFG_FILE;
		std::string strLogStorePath = GetAppDataDirA()+ "\\" + CLIENT_LOG_PATH;;
		unsigned int logLevel[LOG_CATEGORY] = {INVALID_LOG_LEVEL,INVALID_LOG_LEVEL,INVALID_LOG_LEVEL};
		LogInit(PRODUCT_NAME,strLogCfgFile.c_str(),logLevel,strLogStorePath.c_str());
		INFO_LOG("eSDKlog path is %s",strLogStorePath.c_str());

		return S_OK;
	}
	
	void FinalRelease() 
	{
		DEBUG_TRACE("");	
		LogFini(PRODUCT_NAME);
	}

    

    /************************************************************************************
    Function:       // void FireECSEvent
    Description:    // 将事件抛给JS，JS去处理
    Calls:          // 
    Called By:      // 
    Input:          // 
    :               // int eventID -
    Output:         // 
    Return:         // int eventID
    Others:         //
    **************************************************************************************/
    void FireECSEvent(int eventID);


    /************************************************************************************
    Function:       // GetECSFramework
    Description:    // 获取客户端框架接口，如果成功会赋值给m_ComeSpaceAPP
    Calls:          // 
    Called By:      // 
    Input:          // 
    Output:         // 
    Return:         // bool 获取客户端框架接口是否成功
    Others:         // 如果失败，会抛出ERROR_CLIENT_NOTINSTALLED事件
    **************************************************************************************/
    bool GetECSFramework();

    /************************************************************************************
    Function:       // CallOut
    Description:    // 调用客户端提供的呼叫能力
    Calls:          // 
    Called By:      // 
    Input:          // 
    :               // BSTR phoneNum - 电话号码
    Output:         // 
    Return:         // void
    Others:         //
    **************************************************************************************/
    void CallOut(BSTR phoneNum, BSTR account, BSTR name);

	/************************************************************************************
    Function:       // OnEventOccured
    Description:    // eSpace.exe进程通知消息到本COM对象
    Calls:          // 
    Called By:      // 
    Input:          // 
    Output:         // 
    Return:         // 
    Others:         // 
    **************************************************************************************/
	HRESULT OnEventOccured//事件处理程序
		(
		eSpace::ECSEventType eventId,
		const _variant_t & param1,
		const _variant_t & param2,
		const _variant_t & param3
		);

	/************************************************************************************
    Function:       // NotifyStatusChange
    Description:    // 通知某个账户的状态
    Calls:          // 
    Called By:      // 
    Input:          // 
    :               // BSTR account - uc账户
	:               // LONG status  - uc状态
    Output:         // 
    Return:         // void
    Others:         //
    **************************************************************************************/
    void NotifyStatusChange(BSTR account, LONG status, LONG clientType);
	/************************************************************************************
    Function:       // IseSpaceLogin
    Description:    // 检查eSpace是不是处于有进程但是未登录状态
    Calls:          // 
    Called By:      // 
    Input:          // 无
    :               //
	:               // 
    Output:         // 
    Return:         // bool
    Others:         //
    **************************************************************************************/
	bool IseSpaceLogin(void);

    //客户端框架接口
	CComPtr<eSpace::IECSEspaceApp> m_ComeSpaceAPP;
	//客户端联系人管理接口
	CComPtr<eSpace::IECSContactMgr> m_ComContactMgr;
    
    //保存img ID和帐号的对应关系，方便回调给JS
	std::multimap<CString, CString> m_mapIDAccount;

    //帐号：客户端类型
    std::map<CString, int> m_mapAccountType;

    //JS传过来的当前选中人员的帐号
    CComBSTR m_strAccount,g_strAccout;
    //JS传过来的当前选中人员的工号
    CComBSTR m_strStaffNO;
    //JS传过来的当前选中人员的姓名
    CComBSTR m_strName;
    LONG m_iStatus;
    LONG m_iClientType; // 0表示PC，1表示移动；2 IPPHone；3 Mobile
	short m_uIsFriend;
	CTime m_curTime ;

	HWND m_HWnd;

	//绑定号码、手机、家庭电话、办公电话、短号、其他电话
	CComBSTR m_strBindNo;
	CComBSTR m_strMobile;
	CComBSTR m_strHomePhone;
	CComBSTR m_strOfficePhone;
	CComBSTR m_strShortPhone;
	CComBSTR m_strOtherPhone;
	CComBSTR m_strIPPhone1;
	CRITICAL_SECTION g_cs;

    //菜单事件
    LRESULT OnClickIMMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnClickCallPcToPcMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnClickCallMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnClickMeetingMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnClickAddFriendMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnClickCallSIPMobileMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnClickCallSIPHomePhoneMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnClickCallSIPOfficePhoneMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnClickCallSIPShortPhoneMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnClickCallSIPOtherPhoneMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnClickCallSIPIPPhone1Menu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnClickStarteSpaceMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    //................    
   
    LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnReqAsynGetStatus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	STDMETHOD(ShowUI)(VARIANT_BOOL bShow, ULONG x, ULONG y);
    STDMETHOD(get_OnUserStatusChange)(VARIANT* pVal);
    STDMETHOD(put_OnUserStatusChange)(VARIANT newVal);
  
    STDMETHOD(GetStatus)(BSTR account, BSTR id);
    STDMETHOD(SetUserInfo)(BSTR strAccount, BSTR staffNo, BSTR strName, LONG status);
    STDMETHOD(get_OneSpaceEvent)(VARIANT* pVal);
    STDMETHOD(put_OneSpaceEvent)(VARIANT newVal);
    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    bool iseSpaceExist();

    HRESULT OnDraw(ATL_DRAWINFO& di);

    STDMETHOD(Login)(BSTR account, BSTR pwd, LONG type);

	//IE在初始化或者退出页面的时候会调用页面中的ActiveX控件的IOleObject::SetClientSite的实现
	//无论控件是否被本地激活。
	//在初始化页面的时候，传递的指针是宿主的IOleClientSite 接口指针;
	//在离开或者关闭页面的时候，传递的指针是空指针。
	//可以根据这个指针来判断控件的状态，并且执行初始化或者清除的代码。
	//CMyControl is derived from CComControl   
    STDMETHOD(SetClientSite)(IOleClientSite *pClientSite)   
    { 
		DEBUG_TRACE("");
		if(pClientSite)   
		{ 
			INFO_LOG("pClientSite is not NUll");
			RECT rc = {0,0,0,0};
			//   Don't   have   access   to   the   container's   window   so   just   use   the   
			//   desktop.     Window   will   be   resized   correctly   during   in-place   
			//   activation.   
			HWND hWnd = CreateControlWindow(::GetDesktopWindow(), rc);   
			m_HWnd = hWnd;
			_ASSERT(hWnd);
		}
		else
		{
			INFO_LOG("pClientSite is  NUll");
			/////采纳产品线的意见，将UnregistEventListener放在这边，减少野指针 c00327158 Start/////
			if (NULL != m_ComeSpaceAPP)
			{
				if(m_eventHandler.get())
				{
					m_eventHandler->UnregistEventListener();
				}
			}
			/////采纳产品线的意见，将UnregistEventListener放在这边，减少野指针 c00327158 End/////
		}
		return   IOleObjectImpl<CStatusCtrl>::SetClientSite(pClientSite);   
    }   
    
	HRESULT   InPlaceActivate(LONG   iVerb,   const   RECT*   prcPosRect)   
	{
		//Get the container's window.
		DEBUG_TRACE("");
		_ASSERT(m_spClientSite);   
		CComPtr<IOleInPlaceSite>  pInPlaceSite;
		HRESULT	hr	=	m_spClientSite->QueryInterface(IID_IOleInPlaceSite, (void **)&pInPlaceSite); 
		INFO_LOG("QueryInterface errorcode is %d",hr);
		if(SUCCEEDED   (hr)   &&   pInPlaceSite)
		{
			HWND   hParent   =   NULL;
			hr   =   pInPlaceSite->GetWindow(&hParent);
			INFO_LOG("GetWindow errorcode is %d",hr);
			if(SUCCEEDED   (hr)   &&   hParent)
			{
				//Set   container   window   as   our   parent   window   
				SetParent(hParent);   
			}
		}

		return   CComControlBase::InPlaceActivate(iVerb,   prcPosRect);   
	}

	HWND GetHWnd(void) {return m_HWnd;}

	void GetNumByAccount();
	std::string Bstr2String(BSTR m_bstr);
	bool IsLocalAccount(BSTR m_bstr);
};

OBJECT_ENTRY_AUTO(__uuidof(StatusCtrl), CStatusCtrl)