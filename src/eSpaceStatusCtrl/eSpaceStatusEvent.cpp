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

// eSpaceStatusEvent.cpp : CeSpaceStatusEvent µÄÊµÏÖ

#include "stdafx.h"
#include "eSpaceStatusEvent.h"
#include ".\espacestatusevent.h"


// CeSpaceStatusEvent



// CeSpaceStatusEvent
STDMETHODIMP CeSpaceStatusEvent::GetName(/*[out,retval]*/BSTR* pStrName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	return E_NOTIMPL;
}

STDMETHODIMP CeSpaceStatusEvent::GetIcon(/*[out,retval]*/BSTR* pStrPath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    return E_NOTIMPL;
}


STDMETHODIMP CeSpaceStatusEvent::Initialize(/*[in]*/IDispatch* pFramework,/*[out,retval]*/VARIANT_BOOL* pbResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	return E_NOTIMPL;
}

STDMETHODIMP CeSpaceStatusEvent::Create(/*[in]*/LONG hWndParent,/*[in]*/VARIANT_BOOL bPopupWindow,/*[out,retval]*/LONG* pHwndResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    return E_NOTIMPL;
}

STDMETHODIMP CeSpaceStatusEvent::UnInitial(/*[out,retval]*/VARIANT_BOOL* pbResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return E_NOTIMPL;
}

STDMETHODIMP CeSpaceStatusEvent::GetSafeHwnd(/*[out,retval]*/LONG* pHwndResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return E_NOTIMPL;
}

STDMETHODIMP CeSpaceStatusEvent::Show(/*[in]*/VARIANT_BOOL bShow,/*[out,retval]*/VARIANT_BOOL* pbResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    return E_NOTIMPL;
}

STDMETHODIMP CeSpaceStatusEvent::Destroy(/*[out,retval]*/VARIANT_BOOL* pbResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return E_NOTIMPL;
}

STDMETHODIMP CeSpaceStatusEvent::SetWindowStyle(/*[in]*/VARIANT_BOOL bPopup,/*[out,retval]*/VARIANT_BOOL* pbResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    return E_NOTIMPL;
}



STDMETHODIMP CeSpaceStatusEvent::DoNotify(/*[in]*/ ULONG eventID, /*[in]*/ IDispatch* pSender, /*[in]*/ ULONG ulParam1, /*[in]*/ ULONG ulParam2)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    AfxMessageBox(_T("123"));


	return S_OK;
}

