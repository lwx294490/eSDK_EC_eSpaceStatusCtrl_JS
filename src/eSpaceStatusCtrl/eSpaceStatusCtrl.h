

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Fri Nov 11 18:18:27 2016
 */
/* Compiler settings for .\eSpaceStatusCtrl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __eSpaceStatusCtrl_h__
#define __eSpaceStatusCtrl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IStatusCtrl_FWD_DEFINED__
#define __IStatusCtrl_FWD_DEFINED__
typedef interface IStatusCtrl IStatusCtrl;
#endif 	/* __IStatusCtrl_FWD_DEFINED__ */


#ifndef ___IStatusCtrlEvents_FWD_DEFINED__
#define ___IStatusCtrlEvents_FWD_DEFINED__
typedef interface _IStatusCtrlEvents _IStatusCtrlEvents;
#endif 	/* ___IStatusCtrlEvents_FWD_DEFINED__ */


#ifndef __StatusCtrl_FWD_DEFINED__
#define __StatusCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class StatusCtrl StatusCtrl;
#else
typedef struct StatusCtrl StatusCtrl;
#endif /* __cplusplus */

#endif 	/* __StatusCtrl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IStatusCtrl_INTERFACE_DEFINED__
#define __IStatusCtrl_INTERFACE_DEFINED__

/* interface IStatusCtrl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IStatusCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EE967682-67F9-49FD-87A6-826389DABFDF")
    IStatusCtrl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowUI( 
            /* [in] */ VARIANT_BOOL bShow,
            /* [in] */ ULONG x,
            /* [in] */ ULONG y) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OnUserStatusChange( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OnUserStatusChange( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStatus( 
            /* [in] */ BSTR account,
            /* [in] */ BSTR id) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUserInfo( 
            /* [in] */ BSTR strAccount,
            /* [in] */ BSTR staffNo,
            /* [in] */ BSTR strName,
            /* [in] */ LONG status) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OneSpaceEvent( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OneSpaceEvent( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Login( 
            /* [in] */ BSTR account,
            /* [in] */ BSTR pwd,
            /* [in] */ LONG type) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStatusCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStatusCtrl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStatusCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStatusCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IStatusCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IStatusCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IStatusCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IStatusCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowUI )( 
            IStatusCtrl * This,
            /* [in] */ VARIANT_BOOL bShow,
            /* [in] */ ULONG x,
            /* [in] */ ULONG y);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OnUserStatusChange )( 
            IStatusCtrl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OnUserStatusChange )( 
            IStatusCtrl * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetStatus )( 
            IStatusCtrl * This,
            /* [in] */ BSTR account,
            /* [in] */ BSTR id);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetUserInfo )( 
            IStatusCtrl * This,
            /* [in] */ BSTR strAccount,
            /* [in] */ BSTR staffNo,
            /* [in] */ BSTR strName,
            /* [in] */ LONG status);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OneSpaceEvent )( 
            IStatusCtrl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OneSpaceEvent )( 
            IStatusCtrl * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Login )( 
            IStatusCtrl * This,
            /* [in] */ BSTR account,
            /* [in] */ BSTR pwd,
            /* [in] */ LONG type);
        
        END_INTERFACE
    } IStatusCtrlVtbl;

    interface IStatusCtrl
    {
        CONST_VTBL struct IStatusCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStatusCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStatusCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStatusCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStatusCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IStatusCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IStatusCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IStatusCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IStatusCtrl_ShowUI(This,bShow,x,y)	\
    ( (This)->lpVtbl -> ShowUI(This,bShow,x,y) ) 

#define IStatusCtrl_get_OnUserStatusChange(This,pVal)	\
    ( (This)->lpVtbl -> get_OnUserStatusChange(This,pVal) ) 

#define IStatusCtrl_put_OnUserStatusChange(This,newVal)	\
    ( (This)->lpVtbl -> put_OnUserStatusChange(This,newVal) ) 

#define IStatusCtrl_GetStatus(This,account,id)	\
    ( (This)->lpVtbl -> GetStatus(This,account,id) ) 

#define IStatusCtrl_SetUserInfo(This,strAccount,staffNo,strName,status)	\
    ( (This)->lpVtbl -> SetUserInfo(This,strAccount,staffNo,strName,status) ) 

#define IStatusCtrl_get_OneSpaceEvent(This,pVal)	\
    ( (This)->lpVtbl -> get_OneSpaceEvent(This,pVal) ) 

#define IStatusCtrl_put_OneSpaceEvent(This,newVal)	\
    ( (This)->lpVtbl -> put_OneSpaceEvent(This,newVal) ) 

#define IStatusCtrl_Login(This,account,pwd,type)	\
    ( (This)->lpVtbl -> Login(This,account,pwd,type) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStatusCtrl_INTERFACE_DEFINED__ */



#ifndef __eSpaceStatusCtrlLib_LIBRARY_DEFINED__
#define __eSpaceStatusCtrlLib_LIBRARY_DEFINED__

/* library eSpaceStatusCtrlLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_eSpaceStatusCtrlLib;

#ifndef ___IStatusCtrlEvents_DISPINTERFACE_DEFINED__
#define ___IStatusCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IStatusCtrlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IStatusCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6B104C1E-4D4E-43CE-AE36-AD202AF4B551")
    _IStatusCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IStatusCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IStatusCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IStatusCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IStatusCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IStatusCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IStatusCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IStatusCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IStatusCtrlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IStatusCtrlEventsVtbl;

    interface _IStatusCtrlEvents
    {
        CONST_VTBL struct _IStatusCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IStatusCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IStatusCtrlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IStatusCtrlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IStatusCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IStatusCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IStatusCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IStatusCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IStatusCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_StatusCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("93A44D3B-7CED-454F-BBB4-EE0AA340BB78")
StatusCtrl;
#endif
#endif /* __eSpaceStatusCtrlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


