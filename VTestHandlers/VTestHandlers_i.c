

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat Nov 26 16:38:15 2011
 */
/* Compiler settings for VTestHandlers.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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

MIDL_DEFINE_GUID(IID, IID_IPreview,0xF455D785,0x654B,0x4502,0x84,0x56,0x19,0x2F,0xCD,0xB1,0xB2,0x76);


MIDL_DEFINE_GUID(IID, IID_IThumbnail,0x94D22978,0xE165,0x4C0D,0x94,0x87,0x83,0x7B,0x1F,0xCB,0x7E,0x66);


MIDL_DEFINE_GUID(IID, LIBID_VTestHandlersLib,0xCD786645,0x023D,0x4E59,0x9C,0x03,0x3A,0x26,0x45,0x4A,0x9E,0xD3);


MIDL_DEFINE_GUID(CLSID, CLSID_Preview,0x73B00FF3,0x0EB4,0x4832,0x9A,0x54,0x95,0x78,0x25,0x66,0x19,0x2B);


MIDL_DEFINE_GUID(CLSID, CLSID_Thumbnail,0x11F7EE73,0x0322,0x4457,0x90,0xEC,0xE8,0x45,0x67,0xA1,0xF9,0xBB);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



