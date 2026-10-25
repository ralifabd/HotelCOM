

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for HotelServer.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
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

#ifndef __HotelServer_i_h__
#define __HotelServer_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IHotelService_FWD_DEFINED__
#define __IHotelService_FWD_DEFINED__
typedef interface IHotelService IHotelService;

#endif 	/* __IHotelService_FWD_DEFINED__ */


#ifndef __HotelService_FWD_DEFINED__
#define __HotelService_FWD_DEFINED__

#ifdef __cplusplus
typedef class HotelService HotelService;
#else
typedef struct HotelService HotelService;
#endif /* __cplusplus */

#endif 	/* __HotelService_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IHotelService_INTERFACE_DEFINED__
#define __IHotelService_INTERFACE_DEFINED__

/* interface IHotelService */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IHotelService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5aa88d9e-fae9-407e-a7fa-7a3396394736")
    IHotelService : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CheckRoom( 
            /* [in] */ LONG roomId,
            /* [retval][out] */ VARIANT_BOOL *available) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE BookRoom( 
            /* [in] */ LONG roomId,
            /* [in] */ BSTR guestName,
            /* [retval][out] */ VARIANT_BOOL *success) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CancelBooking( 
            /* [in] */ LONG roomId,
            /* [retval][out] */ VARIANT_BOOL *success) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetRoomInfo( 
            /* [in] */ LONG roomId,
            /* [retval][out] */ BSTR *roomJson) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetRoomsByType( 
            /* [in] */ BSTR roomType,
            /* [retval][out] */ BSTR *roomsJson) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetRoomStatus( 
            /* [in] */ LONG roomId,
            /* [in] */ BSTR status,
            /* [retval][out] */ VARIANT_BOOL *success) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateBooking( 
            /* [in] */ LONG roomId,
            /* [in] */ BSTR guestName,
            /* [in] */ BSTR checkIn,
            /* [in] */ BSTR checkOut,
            /* [retval][out] */ LONG *bookingId) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetBookingInfo( 
            /* [in] */ LONG bookingId,
            /* [retval][out] */ BSTR *bookingJson) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UpdateBooking( 
            /* [in] */ LONG bookingId,
            /* [in] */ BSTR newCheckIn,
            /* [in] */ BSTR newCheckOut,
            /* [retval][out] */ VARIANT_BOOL *success) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FindAvailableRooms( 
            /* [in] */ BSTR checkIn,
            /* [in] */ BSTR checkOut,
            /* [in] */ BSTR roomType,
            /* [retval][out] */ BSTR *roomsJson) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CalculateBookingPrice( 
            /* [in] */ LONG bookingId,
            /* [retval][out] */ DOUBLE *totalPrice) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ApplyDiscount( 
            /* [in] */ LONG bookingId,
            /* [in] */ DOUBLE discount,
            /* [retval][out] */ VARIANT_BOOL *success) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AddRoom( 
            /* [in] */ BSTR roomJson,
            /* [retval][out] */ VARIANT_BOOL *success) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UpdateRoom( 
            /* [in] */ LONG roomId,
            /* [in] */ BSTR roomJson,
            /* [retval][out] */ VARIANT_BOOL *success) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveRoom( 
            /* [in] */ LONG roomId,
            /* [retval][out] */ VARIANT_BOOL *success) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CheckIn( 
            /* [in] */ LONG bookingId,
            /* [retval][out] */ VARIANT_BOOL *success) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CheckOut( 
            /* [in] */ LONG bookingId,
            /* [retval][out] */ VARIANT_BOOL *success) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetHotelStatistics( 
            /* [retval][out] */ BSTR *statisticsJson) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IHotelServiceVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHotelService * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHotelService * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHotelService * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IHotelService * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IHotelService * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IHotelService * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IHotelService * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(IHotelService, CheckRoom)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CheckRoom )( 
            IHotelService * This,
            /* [in] */ LONG roomId,
            /* [retval][out] */ VARIANT_BOOL *available);
        
        DECLSPEC_XFGVIRT(IHotelService, BookRoom)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *BookRoom )( 
            IHotelService * This,
            /* [in] */ LONG roomId,
            /* [in] */ BSTR guestName,
            /* [retval][out] */ VARIANT_BOOL *success);
        
        DECLSPEC_XFGVIRT(IHotelService, CancelBooking)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CancelBooking )( 
            IHotelService * This,
            /* [in] */ LONG roomId,
            /* [retval][out] */ VARIANT_BOOL *success);
        
        DECLSPEC_XFGVIRT(IHotelService, GetRoomInfo)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetRoomInfo )( 
            IHotelService * This,
            /* [in] */ LONG roomId,
            /* [retval][out] */ BSTR *roomJson);
        
        DECLSPEC_XFGVIRT(IHotelService, GetRoomsByType)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetRoomsByType )( 
            IHotelService * This,
            /* [in] */ BSTR roomType,
            /* [retval][out] */ BSTR *roomsJson);
        
        DECLSPEC_XFGVIRT(IHotelService, SetRoomStatus)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetRoomStatus )( 
            IHotelService * This,
            /* [in] */ LONG roomId,
            /* [in] */ BSTR status,
            /* [retval][out] */ VARIANT_BOOL *success);
        
        DECLSPEC_XFGVIRT(IHotelService, CreateBooking)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateBooking )( 
            IHotelService * This,
            /* [in] */ LONG roomId,
            /* [in] */ BSTR guestName,
            /* [in] */ BSTR checkIn,
            /* [in] */ BSTR checkOut,
            /* [retval][out] */ LONG *bookingId);
        
        DECLSPEC_XFGVIRT(IHotelService, GetBookingInfo)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetBookingInfo )( 
            IHotelService * This,
            /* [in] */ LONG bookingId,
            /* [retval][out] */ BSTR *bookingJson);
        
        DECLSPEC_XFGVIRT(IHotelService, UpdateBooking)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UpdateBooking )( 
            IHotelService * This,
            /* [in] */ LONG bookingId,
            /* [in] */ BSTR newCheckIn,
            /* [in] */ BSTR newCheckOut,
            /* [retval][out] */ VARIANT_BOOL *success);
        
        DECLSPEC_XFGVIRT(IHotelService, FindAvailableRooms)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *FindAvailableRooms )( 
            IHotelService * This,
            /* [in] */ BSTR checkIn,
            /* [in] */ BSTR checkOut,
            /* [in] */ BSTR roomType,
            /* [retval][out] */ BSTR *roomsJson);
        
        DECLSPEC_XFGVIRT(IHotelService, CalculateBookingPrice)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CalculateBookingPrice )( 
            IHotelService * This,
            /* [in] */ LONG bookingId,
            /* [retval][out] */ DOUBLE *totalPrice);
        
        DECLSPEC_XFGVIRT(IHotelService, ApplyDiscount)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ApplyDiscount )( 
            IHotelService * This,
            /* [in] */ LONG bookingId,
            /* [in] */ DOUBLE discount,
            /* [retval][out] */ VARIANT_BOOL *success);
        
        DECLSPEC_XFGVIRT(IHotelService, AddRoom)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AddRoom )( 
            IHotelService * This,
            /* [in] */ BSTR roomJson,
            /* [retval][out] */ VARIANT_BOOL *success);
        
        DECLSPEC_XFGVIRT(IHotelService, UpdateRoom)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UpdateRoom )( 
            IHotelService * This,
            /* [in] */ LONG roomId,
            /* [in] */ BSTR roomJson,
            /* [retval][out] */ VARIANT_BOOL *success);
        
        DECLSPEC_XFGVIRT(IHotelService, RemoveRoom)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RemoveRoom )( 
            IHotelService * This,
            /* [in] */ LONG roomId,
            /* [retval][out] */ VARIANT_BOOL *success);
        
        DECLSPEC_XFGVIRT(IHotelService, CheckIn)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CheckIn )( 
            IHotelService * This,
            /* [in] */ LONG bookingId,
            /* [retval][out] */ VARIANT_BOOL *success);
        
        DECLSPEC_XFGVIRT(IHotelService, CheckOut)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CheckOut )( 
            IHotelService * This,
            /* [in] */ LONG bookingId,
            /* [retval][out] */ VARIANT_BOOL *success);
        
        DECLSPEC_XFGVIRT(IHotelService, GetHotelStatistics)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetHotelStatistics )( 
            IHotelService * This,
            /* [retval][out] */ BSTR *statisticsJson);
        
        END_INTERFACE
    } IHotelServiceVtbl;

    interface IHotelService
    {
        CONST_VTBL struct IHotelServiceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHotelService_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHotelService_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHotelService_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHotelService_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IHotelService_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IHotelService_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IHotelService_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IHotelService_CheckRoom(This,roomId,available)	\
    ( (This)->lpVtbl -> CheckRoom(This,roomId,available) ) 

#define IHotelService_BookRoom(This,roomId,guestName,success)	\
    ( (This)->lpVtbl -> BookRoom(This,roomId,guestName,success) ) 

#define IHotelService_CancelBooking(This,roomId,success)	\
    ( (This)->lpVtbl -> CancelBooking(This,roomId,success) ) 

#define IHotelService_GetRoomInfo(This,roomId,roomJson)	\
    ( (This)->lpVtbl -> GetRoomInfo(This,roomId,roomJson) ) 

#define IHotelService_GetRoomsByType(This,roomType,roomsJson)	\
    ( (This)->lpVtbl -> GetRoomsByType(This,roomType,roomsJson) ) 

#define IHotelService_SetRoomStatus(This,roomId,status,success)	\
    ( (This)->lpVtbl -> SetRoomStatus(This,roomId,status,success) ) 

#define IHotelService_CreateBooking(This,roomId,guestName,checkIn,checkOut,bookingId)	\
    ( (This)->lpVtbl -> CreateBooking(This,roomId,guestName,checkIn,checkOut,bookingId) ) 

#define IHotelService_GetBookingInfo(This,bookingId,bookingJson)	\
    ( (This)->lpVtbl -> GetBookingInfo(This,bookingId,bookingJson) ) 

#define IHotelService_UpdateBooking(This,bookingId,newCheckIn,newCheckOut,success)	\
    ( (This)->lpVtbl -> UpdateBooking(This,bookingId,newCheckIn,newCheckOut,success) ) 

#define IHotelService_FindAvailableRooms(This,checkIn,checkOut,roomType,roomsJson)	\
    ( (This)->lpVtbl -> FindAvailableRooms(This,checkIn,checkOut,roomType,roomsJson) ) 

#define IHotelService_CalculateBookingPrice(This,bookingId,totalPrice)	\
    ( (This)->lpVtbl -> CalculateBookingPrice(This,bookingId,totalPrice) ) 

#define IHotelService_ApplyDiscount(This,bookingId,discount,success)	\
    ( (This)->lpVtbl -> ApplyDiscount(This,bookingId,discount,success) ) 

#define IHotelService_AddRoom(This,roomJson,success)	\
    ( (This)->lpVtbl -> AddRoom(This,roomJson,success) ) 

#define IHotelService_UpdateRoom(This,roomId,roomJson,success)	\
    ( (This)->lpVtbl -> UpdateRoom(This,roomId,roomJson,success) ) 

#define IHotelService_RemoveRoom(This,roomId,success)	\
    ( (This)->lpVtbl -> RemoveRoom(This,roomId,success) ) 

#define IHotelService_CheckIn(This,bookingId,success)	\
    ( (This)->lpVtbl -> CheckIn(This,bookingId,success) ) 

#define IHotelService_CheckOut(This,bookingId,success)	\
    ( (This)->lpVtbl -> CheckOut(This,bookingId,success) ) 

#define IHotelService_GetHotelStatistics(This,statisticsJson)	\
    ( (This)->lpVtbl -> GetHotelStatistics(This,statisticsJson) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHotelService_INTERFACE_DEFINED__ */



#ifndef __HotelServerLib_LIBRARY_DEFINED__
#define __HotelServerLib_LIBRARY_DEFINED__

/* library HotelServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_HotelServerLib;

EXTERN_C const CLSID CLSID_HotelService;

#ifdef __cplusplus

class DECLSPEC_UUID("4f72097e-cf14-45d3-9232-ca002e541fff")
HotelService;
#endif
#endif /* __HotelServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


