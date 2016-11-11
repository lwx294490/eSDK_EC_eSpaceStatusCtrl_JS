

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IStatusCtrl,0xEE967682,0x67F9,0x49FD,0x87,0xA6,0x82,0x63,0x89,0xDA,0xBF,0xDF);


MIDL_DEFINE_GUID(IID, LIBID_eSpaceStatusCtrlLib,0xCB1BFE5C,0xFBEA,0x47D3,0xAC,0x0A,0xD7,0xD0,0x43,0xCA,0x9F,0x04);


MIDL_DEFINE_GUID(IID, DIID__IStatusCtrlEvents,0x6B104C1E,0x4D4E,0x43CE,0xAE,0x36,0xAD,0x20,0x2A,0xF4,0xB5,0x51);


MIDL_DEFINE_GUID(CLSID, CLSID_StatusCtrl,0x93A44D3B,0x7CED,0x454F,0xBB,0xB4,0xEE,0x0A,0xA3,0x40,0xBB,0x78);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



