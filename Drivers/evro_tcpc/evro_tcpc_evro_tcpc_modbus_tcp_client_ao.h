/**************************************************************************
File:               evro_tcpc_evro_tcpc_modbus_tcp_client_ao.h
Author:             Umputun
Creation date:      25/02/2013 - 16:09
Device name:        MODBUS_TCP_CLIENT_AO
***************************************************************************/

#ifndef _EVRO_TCPC_EVRO_TCPC_MODBUS_TCP_CLIENT_AO_H /* nested Headers management */
#define _EVRO_TCPC_EVRO_TCPC_MODBUS_TCP_CLIENT_AO_H

/* prototypes */

typSTATUS  evro_tcpc_evro_tcpc_IosInit
   (
   strRtIoDrv* pRtIoDrv /* Run time io struct of the driver to init */
   );

void evro_tcpc_evro_tcpc_IosExit
   (
   strRtIoDrv* pRtIoDrv /* Run time io struct of the driver to exit */
   );

typSTATUS evro_tcpc_evro_tcpc_modbus_tcp_client_aoIosOpen
   (
   strRtIoCpxDvc* pvRtIoDvc /* Run time io struct of the device to open */
   );

void evro_tcpc_evro_tcpc_modbus_tcp_client_aoIosClose
   (
   strRtIoCpxDvc* pvRtIoDvc /* Run time io struct of the device to close */
   );

void evro_tcpc_evro_tcpc_modbus_tcp_client_aomodbus_tcp_statusIosRead
   (
   strRtIoSplDvc* pRtIoSplDvc /* Run time io struct of the device to read */
   );

void evro_tcpc_evro_tcpc_modbus_tcp_client_aomodbus_tcp_statusIosCtl
   (
   uchar          cuSubFunct,   /* Sub function parameter */
   strRtIoSplDvc* pRtIoSplDvc,  /* Rt io struct of the spl dvc to control */
   uint16         huChanNum,    /* Channel number if any */
   void*          pvReserved    /* Reserved */
   );

void evro_tcpc_evro_tcpc_modbus_tcp_client_aomtcp_aoIosWrite
   (
   strRtIoSplDvc* pRtIoSplDvc /* Run time io struct of the device to write */
   );

void evro_tcpc_evro_tcpc_modbus_tcp_client_aomtcp_aoIosCtl
   (
   uchar          cuSubFunct,   /* Sub function parameter */
   strRtIoSplDvc* pRtIoSplDvc,  /* Rt io struct of the spl dvc to control */
   uint16         huChanNum,    /* Channel number if any */
   void*          pvReserved    /* Reserved */
   );


typSTATUS evro_tcpc_evro_tcpc_IosMdf
   (
   uchar          cuSubFunc,    /* Sub function switch */
   strRtIoDrv*    pRtIoDrv,     /* Driver run time io struct */
   uint32         luMdfType,    /* On line modification types */
   void*          pvRtIoDvc     /* Reserved for future extensions */
   );

typSTATUS evro_tcpc_evro_tcpc_modbus_tcp_client_aoIosMdf
   (
   uchar          cuSubFunc,   /* Sub function switch */
   strRtIoCpxDvc* pRtIoCpxDvc, /* Complex device run time io struct */
   uint32         luMdfType,   /* On line modification types */
   strDfIoCpxDvc* pDfIoCpxDvc, /* New complex device default struct */
   void*          pvOemParam   /* New complex device OEM parameters */
   );

typSTATUS evro_tcpc_evro_tcpc_modbus_tcp_client_aomodbus_tcp_statusIosMdf
   (
   uchar          cuSubFunc,  /* Sub function switch */
   strRtIoSplDvc* pRtIoSplDvc,/* Simple device run time io struct */
   uint32         luMdfType,  /* On line modification types */
   strDfIoSplDvc* pDfIoSplDvc,/* New simple device default struct */
   void*          pvOemSplDvc,/* New simple device OEM parameters */
   strDfIoChan*   pDfIoChan,  /* New first channel default struct */
   void*          pvOemChan   /* New first channel OEM parameters */
   );

typSTATUS evro_tcpc_evro_tcpc_modbus_tcp_client_aomtcp_aoIosMdf
   (
   uchar          cuSubFunc,  /* Sub function switch */
   strRtIoSplDvc* pRtIoSplDvc,/* Simple device run time io struct */
   uint32         luMdfType,  /* On line modification types */
   strDfIoSplDvc* pDfIoSplDvc,/* New simple device default struct */
   void*          pvOemSplDvc,/* New simple device OEM parameters */
   strDfIoChan*   pDfIoChan,  /* New first channel default struct */
   void*          pvOemChan   /* New first channel OEM parameters */
   );



#endif /* _EVRO_TCPC_EVRO_TCPC_MODBUS_TCP_CLIENT_AO_H */

/* eof ********************************************************************/

