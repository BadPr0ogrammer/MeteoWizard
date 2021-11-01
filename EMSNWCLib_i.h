

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for EMSNWCLib.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __EMSNWCLib_i_h__
#define __EMSNWCLib_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IHritObject_FWD_DEFINED__
#define __IHritObject_FWD_DEFINED__
typedef interface IHritObject IHritObject;

#endif 	/* __IHritObject_FWD_DEFINED__ */


#ifndef __HritObject_FWD_DEFINED__
#define __HritObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class HritObject HritObject;
#else
typedef struct HritObject HritObject;
#endif /* __cplusplus */

#endif 	/* __HritObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IHritObject_INTERFACE_DEFINED__
#define __IHritObject_INTERFACE_DEFINED__

/* interface IHritObject */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IHritObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5c1dbaa3-38f3-4841-ae9e-853e3eec998c")
    IHritObject : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ReadMSGInfo( 
            /* [in] */ BSTR fName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CalibrationTbl( 
            /* [retval][out] */ SAFEARRAY * *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IHritObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHritObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHritObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHritObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *ReadMSGInfo )( 
            IHritObject * This,
            /* [in] */ BSTR fName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CalibrationTbl )( 
            IHritObject * This,
            /* [retval][out] */ SAFEARRAY * *pVal);
        
        END_INTERFACE
    } IHritObjectVtbl;

    interface IHritObject
    {
        CONST_VTBL struct IHritObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHritObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHritObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHritObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHritObject_ReadMSGInfo(This,fName)	\
    ( (This)->lpVtbl -> ReadMSGInfo(This,fName) ) 

#define IHritObject_get_CalibrationTbl(This,pVal)	\
    ( (This)->lpVtbl -> get_CalibrationTbl(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHritObject_INTERFACE_DEFINED__ */



#ifndef __EMSNWCLibLib_LIBRARY_DEFINED__
#define __EMSNWCLibLib_LIBRARY_DEFINED__

/* library EMSNWCLibLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_EMSNWCLibLib;

EXTERN_C const CLSID CLSID_HritObject;

#ifdef __cplusplus

class DECLSPEC_UUID("1b1dae13-552f-4539-b948-274b3240bb83")
HritObject;
#endif
#endif /* __EMSNWCLibLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize64(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal64(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal64(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree64(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


