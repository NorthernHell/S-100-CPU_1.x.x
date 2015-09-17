/**************************************************************************
File:               evro_tcpc_evro_tcpc_mtcp_ao.c
Author:             Umputun
Creation date:      25/02/2013 - 16:08
Device name:        MTCP_AO
***************************************************************************/

#include <dsys0def.h>
#include <dios0def.h>
#include <evro_tcpc_evro_tcpc_mtcp_ao.h>
#include <modbus/modbus.h>
/* OEM Parameters */
extern int modbus_tcp_aos;

typedef struct _tag_strMtcp_ao
{
    char   IP[16];
    int32  PORT;
    int32  Adress;
    int32  NR;
    int32	FUNCION;
    int32  TimeOutu;
    int32  TimeOutsec;
} strMtcp_ao;
/****************************************************************************
function    : evro_tcpc_evro_tcpc_mtcp_aiIosOpen
description : Level 1 device Open function
parameters  :
   (input) strRtIoSplDvc* pvRtIoDvc :  Run time io struct of the device to open
return value: typSTATUS :  0 if successful, BAD_RET if error
warning     : Returning with an error stops the kernel resource starting
****************************************************************************/

typSTATUS evro_tcpc_evro_tcpc_mtcp_aoIosOpen
(
    strRtIoSplDvc* pvRtIoDvc /* Run time io struct of the device to open */
)
{
    printf("MB TCPC AO init\n");
    return (0);
}

/****************************************************************************
function    : evro_tcpc_evro_tcpc_mtcp_aiIosClose
description : Level 1 device Close function
parameters  :
   (input) strRtIoSplDvc* pvRtIoDvc :  Run time io struct of the device to close
return value: None
warning     :
****************************************************************************/

void evro_tcpc_evro_tcpc_mtcp_aoIosClose
(
    strRtIoSplDvc* pvRtIoDvc /* Run time io struct of the device to close */
)
{

}
/****************************************************************************
function    : evro_tcpc_evro_tcpc_mtcp_aoIosWrite
description : Simple device Write function
parameters  :
   (input) void* pvRtIoDvc :  Run time io struct of the device to write
return value: None
warning     :
****************************************************************************/

void evro_tcpc_evro_tcpc_mtcp_aoIosWrite
(
    strRtIoSplDvc* pRtIoSplDvc /* Run time io struct of the device to write */
)
{
    strRtIoChan*     pChannel;
    strDfIoSplDvc*   pStaticDef;
    uint16           nbChannel;
    uint16           nbIndex;
    uint16_t tab_reg[128];

    uint16*           pPhyData;  /* Physical value */
    uint16*           pLogData;  /* Logic Value */
    uint16            iElecData; /* Electrical value */
    int              iCountChange =0, okChange;
    pStaticDef =  pRtIoSplDvc->pDfIoSplDvc;
    nbChannel  =  pStaticDef->huNbChan;
    pChannel   =  pRtIoSplDvc->pRtIoChan;
    strMtcp_ao* pOemParam;
    pOemParam=(strMtcp_ao*)(pRtIoSplDvc->pvOemParam);
    /* Update all channel  */
    for( nbIndex = 0; nbIndex < nbChannel; nbIndex++)
    {
        /* update the channel if not locked  */
        if(!(pChannel->cuIsLocked))
        {
            pPhyData = (uint16*)(pChannel->pvKerPhyData);
            pLogData = (uint16*)(pChannel->pvKerData);
            okChange = 0;
            /* if value has changed or 1rst cycle */
            *pPhyData = *pLogData; /* Logic value = Physic Value */

            if((pChannel->pfnCnvCall) != 0) /* If there is a cnv */
                pChannel->pfnCnvCall( ISA_IO_DIR_OUTPUT, pPhyData, &iElecData);
            else
                iElecData = *pPhyData;

            /* Apply gain and offset  */
            if (pChannel->luCnvDiv != 0)
                iElecData = ((iElecData) * (uint16)(pChannel->luCnvMult)
                             / (uint16)(pChannel->luCnvDiv)) + (uint16)(pChannel->luCnvOfs);
            tab_reg[nbIndex]=iElecData;
            /* If the variable has changed, we print in the file the new value */
            if (okChange)
            {
                tab_reg[nbIndex]=iElecData;
                iCountChange++;
            }
        }
        pChannel++; /* Go to the next channel */
    }
    /* if at least one channel has changed */

    /*  pFile = fopen( sFileName, "at");
    printf( "%s\n", sNewMsg);
    fclose( pFile);
    */
    modbus_t *ctx;
    int rc;
    struct timeval response_timeout;
    response_timeout.tv_sec = pOemParam->TimeOutsec;
    response_timeout.tv_usec = pOemParam->TimeOutu;
    ctx = modbus_new_tcp(pOemParam->IP, pOemParam->PORT); //connect
    if (modbus_connect(ctx) == -1)
    {
        printf("Connexion failed: \n");
        modbus_tcp_aos=0;
        modbus_free(ctx);
    }
    else
    {
        modbus_tcp_aos=1;
        modbus_set_response_timeout(ctx, &response_timeout);
        if (pOemParam->FUNCION!=6)
        {
            rc  = modbus_write_registers(ctx, pOemParam->Adress, pOemParam->NR, tab_reg);
        }
        else
        {
            int i;
            for (i=0; i<pOemParam->NR; i++)
            {
                rc =modbus_write_register(ctx, pOemParam->Adress+i,tab_reg[i]);
                if (rc==-1)
                {
                    break;
                    modbus_tcp_aos=0;
                }
            }
        }
        modbus_close(ctx);
        modbus_free(ctx);
    };
}

/****************************************************************************
function    : evro_tcpc_evro_tcpc_mtcp_aoIosCtl
description : Simple device Control function
parameters  :
   (input) uchar cuSubFunct :          Sub function parameter.
   (input) strRtIoSplDvc* pRtIoSplDvc: Rt io struct of the spl dvc to control.
   (input) uint16 huChanNum :          Channel number if any.
   (input) void* pvReserved :          Reserved.
return value: None
warning     :
****************************************************************************/

void evro_tcpc_evro_tcpc_mtcp_aoIosCtl
(
    uchar          cuSubFunct,   /* Sub function parameter */
    strRtIoSplDvc* pRtIoSplDvc,  /* Rt io struct of the spl dvc to control */
    uint16         huChanNum,    /* Channel number if any */
    void*          pvReserved    /* Reserved */
)
{
    /*
     * cuSubFunct parameter gives a function code.
     * An important one is ISA_IO_CTL_CHANOUTFORCE to force the output
     *  specified by huChanNum.
     * In this case a typical implementation is:
        - if cuSubFunct equal ISA_IO_CTL_CHANOUTFORCE
           - If a conversion is required, convert physical data (pvKerPhyData)
             The info is in channel structures in following fields:
                cuCnvGainTyp != 0 ==> Gain/Offset to applied
                pfnCnvCall != 0   ==> 'C' conversion to applied
           - Apply just computed electrical value to the actuator
     */
    uint16*        pPhyData;      /* Physical value */
    strRtIoChan*  pChannel;
    uint16         iElecData;     /* Electrical value */
    pChannel  =  pRtIoSplDvc->pRtIoChan;
    pChannel += huChanNum;
    pPhyData  = (uint16*)(pChannel->pvKerPhyData);

    switch( cuSubFunct)
    {
    case ISA_IO_CTL_CHANLOCK:
        break;
    case ISA_IO_CTL_CHANUNLOCK:
        break;
    case ISA_IO_CTL_CHANOUTFORCE:
        if((pChannel->pfnCnvCall) != 0) /* If there is a cnv */
            pChannel->pfnCnvCall( ISA_IO_DIR_OUTPUT, pPhyData, &iElecData);
        else
            iElecData = *pPhyData;
        /* Apply gain and offset  */
        if (pChannel->luCnvDiv != 0)
            iElecData = ((iElecData) * (uint16)(pChannel->luCnvMult)
                         / (uint16)(pChannel->luCnvDiv)) + (uint16)(pChannel->luCnvOfs);
        break;
    }


}