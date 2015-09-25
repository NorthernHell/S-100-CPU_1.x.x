/**************************************************************************
File:               evro_tcpc_evro_tcpc_modbus_tcp_client_do.c
Author:             Umputun
Creation date:      25/02/2013 - 16:09
Device name:        MODBUS_TCP_CLIENT_DO
***************************************************************************/

#include <dsys0def.h>
#include <dios0def.h>
#include <evro_tcpc_evro_tcpc_modbus_tcp_client_do.h>
#include <evro_tcpc_evro_tcpc_modbus_tcp_status.h>
#include <evro_tcpc_evro_tcpc_mtcp_do.h>
/* OEM Parameters of complex device */



/* OEM Parameters of linked simple devices */


typedef struct _tag_strModbus_tcp_client_do
{
    char   IP[16];
    int32  PORT;
    int32  Adress;
    int32  NR;
    int32  TimeOutu;
    int32  TimeOutsec;
} strModbus_tcp_client_do;

/****************************************************************************
function    : evro_tcpc_evro_tcpc_modbus_tcp_client_doIosOpen
description : Level 1 device Open function
parameters  :
   (input) strRtIoCpxDvc* pvRtIoDvc :  Run time io struct of the device to open
return value: typSTATUS :  0 if successful, BAD_RET if error
warning     : Returning with an error stops the kernel resource starting
****************************************************************************/

typSTATUS evro_tcpc_evro_tcpc_modbus_tcp_client_doIosOpen
(
    strRtIoCpxDvc* pvRtIoDvc /* Run time io struct of the device to open */
)
{
    strRtIoSplDvc* pRtIoSplDvc;
    pRtIoSplDvc = pvRtIoDvc->pRtIoSplDvc;
    if (evro_tcpc_evro_tcpc_mtcp_doIosOpen (pRtIoSplDvc) != 0)
    {
        printf("Error opening\n");
        return(BAD_RET);
    }
    pRtIoSplDvc = (strRtIoSplDvc*)(pRtIoSplDvc->pvDrvRtIoDvcNxt);
    if (evro_tcpc_evro_tcpc_modbus_tcp_statusIosOpen(pRtIoSplDvc) != 0)
    {
        printf("Error opening\n");
        return(BAD_RET);
    }
    return (0);
}

/****************************************************************************
function    : evro_tcpc_evro_tcpc_modbus_tcp_client_doIosClose
description : Level 1 device Close function
parameters  :
   (input) strRtIoCpxDvc* pvRtIoDvc :  Run time io struct of the device to close
return value: None
warning     :
****************************************************************************/

void evro_tcpc_evro_tcpc_modbus_tcp_client_doIosClose
(
    strRtIoCpxDvc* pvRtIoDvc /* Run time io struct of the device to close */
)
{
    strRtIoSplDvc* pRtIoSplDvc;
    pRtIoSplDvc = pvRtIoDvc->pRtIoSplDvc;
    evro_tcpc_evro_tcpc_mtcp_doIosClose (pRtIoSplDvc);
    pRtIoSplDvc = (strRtIoSplDvc*)(pRtIoSplDvc->pvDrvRtIoDvcNxt);
    evro_tcpc_evro_tcpc_modbus_tcp_statusIosClose(pRtIoSplDvc);
}

/****************************************************************************
function    : evro_tcpc_evro_tcpc_modbus_tcp_client_domodbus_tcp_statusIosRead
description : Simple device Read function
parameters  :
   (input) void* pvRtIoDvc :  Run time io struct of the device to read
return value: None
warning     :
****************************************************************************/

void evro_tcpc_evro_tcpc_modbus_tcp_client_domodbus_tcp_statusIosRead
(
    strRtIoSplDvc* pRtIoSplDvc /* Run time io struct of the device to read */
)
{
    evro_tcpc_evro_tcpc_modbus_tcp_statusIosRead(pRtIoSplDvc);
}

/****************************************************************************
function    : evro_tcpc_evro_tcpc_modbus_tcp_client_domodbus_tcp_statusIosCtl
description : Simple device Control function
parameters  :
   (input) uchar cuSubFunct :          Sub function parameter.
   (input) strRtIoSplDvc* pRtIoSplDvc: Rt io struct of the spl dvc to control.
   (input) uint16 huChanNum :          Channel number if any.
   (input) void* pvReserved :          Reserved.
return value: None
warning     :
****************************************************************************/

void evro_tcpc_evro_tcpc_modbus_tcp_client_domodbus_tcp_statusIosCtl
(
    uchar          cuSubFunct,   /* Sub function parameter */
    strRtIoSplDvc* pRtIoSplDvc,  /* Rt io struct of the spl dvc to control */
    uint16         huChanNum,    /* Channel number if any */
    void*          pvReserved    /* Reserved */
)
{

}

/****************************************************************************
function    : evro_tcpc_evro_tcpc_modbus_tcp_client_domtcp_doIosWrite
description : Simple device Write function
parameters  :
   (input) void* pvRtIoDvc :  Run time io struct of the device to write
return value: None
warning     :
****************************************************************************/

void evro_tcpc_evro_tcpc_modbus_tcp_client_domtcp_doIosWrite
(
    strRtIoSplDvc* pRtIoSplDvc /* Run time io struct of the device to write */
)
{
    evro_tcpc_evro_tcpc_mtcp_doIosWrite(pRtIoSplDvc);
}

/****************************************************************************
function    : evro_tcpc_evro_tcpc_modbus_tcp_client_domtcp_doIosCtl
description : Simple device Control function
parameters  :
   (input) uchar cuSubFunct :          Sub function parameter.
   (input) strRtIoSplDvc* pRtIoSplDvc: Rt io struct of the spl dvc to control.
   (input) uint16 huChanNum :          Channel number if any.
   (input) void* pvReserved :          Reserved.
return value: None
warning     :
****************************************************************************/

void evro_tcpc_evro_tcpc_modbus_tcp_client_domtcp_doIosCtl
(
    uchar          cuSubFunct,   /* Sub function parameter */
    strRtIoSplDvc* pRtIoSplDvc,  /* Rt io struct of the spl dvc to control */
    uint16         huChanNum,    /* Channel number if any */
    void*          pvReserved    /* Reserved */
)
{
    evro_tcpc_evro_tcpc_mtcp_doIosCtl(cuSubFunct,pRtIoSplDvc,huChanNum,pvReserved);
}

