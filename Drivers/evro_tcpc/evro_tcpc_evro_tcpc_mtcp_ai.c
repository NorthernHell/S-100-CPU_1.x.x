/**************************************************************************
File:               evro_tcpc_evro_tcpc_mtcp_ai.c
Author:             Umputun
Creation date:      25/02/2013 - 16:08
Device name:        MTCP_AI
***************************************************************************/

#include <dsys0def.h>
#include <dios0def.h>
#include <evro_tcpc_evro_tcpc_mtcp_ai.h>
#include <modbus/modbus.h>
/* OEM Parameters */
typedef struct _tag_strMtcp_ai
{
    char   IP[16];
    int32  PORT;
    int32  Adress;
    int32  NR;
    int32  FUNCION;
    int32  TimeOutu;
    int32  TimeOutsec;
} strOemParam;

/****************************************************************************
function    : evro_tcpc_evro_tcpc_mtcp_aiIosOpen
description : Level 1 device Open function
parameters  :
   (input) strRtIoSplDvc* pvRtIoDvc :  Run time io struct of the device to open
return value: typSTATUS :  0 if successful, BAD_RET if error
warning     : Returning with an error stops the kernel resource starting
****************************************************************************/

typSTATUS evro_tcpc_evro_tcpc_mtcp_aiIosOpen
(
  strRtIoSplDvc* pRtIoSplDvc /* Run time io struct of the device to read */
)
{
    printf("MB TCPC AI init\n");
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

void evro_tcpc_evro_tcpc_mtcp_aiIosClose
(
  strRtIoSplDvc* pRtIoSplDvc /* Run time io struct of the device to read */
)
{
    printf("MB TCPC AI Close\n");
    sleep(1);
}

/****************************************************************************
function    : evro_tcpc_evro_tcpc_mtcp_aiIosRead
description : Simple device Read function
parameters  :
   (input) void* pvRtIoDvc :  Run time io struct of the device to read
return value: None
warning     :
****************************************************************************/

void evro_tcpc_evro_tcpc_mtcp_aiIosRead
(
    strRtIoSplDvc* pRtIoSplDvc /* Run time io struct of the device to read */
)
{
	strRtIoCpxDvc *cpxDev=(strRtIoCpxDvc *)pRtIoSplDvc->pvRtIoLevBack;
	strOemParam *oemCPar=(strOemParam *)cpxDev->pvOemParam;	
    modbus_t *ctx;
    uint16_t tab_reg[150];
    int rc;
    struct timeval response_timeout;
    response_timeout.tv_sec = oemCPar->TimeOutsec;
    response_timeout.tv_usec = oemCPar->TimeOutu;
    ctx = modbus_new_tcp(oemCPar->IP, oemCPar->PORT); //connect
    if (modbus_connect(ctx) == -1)
    {
        printf("Connexion failed new version: \n");
        modbus_free(ctx);
    }
    else
    {
        modbus_set_response_timeout(ctx, &response_timeout);
        if (oemCPar->FUNCION==3)
        {
            rc  = modbus_read_registers(ctx, oemCPar->Adress, oemCPar->NR, tab_reg);
        }
        else
        {
            rc  = modbus_read_input_registers(ctx, oemCPar->Adress, oemCPar->NR, tab_reg);
        };
 		
		if (rc == -1)
        {
            cpxDev->luUser =0;
			modbus_close(ctx);
        modbus_free(ctx);
        }
        else
        {
		 strRtIoChan*        pChannel;
    strDfIoSplDvc*      pStaticDef;
    uint16              nbChannel;
    uint16              nbIndex;
    int16*              pPhyData;   /* Physical value */
    int16*              pLogData;   /* Logical Value    */
    int16               fElecData;
    float               fMult,fDiv,fOffset;
    pStaticDef =  pRtIoSplDvc->pDfIoSplDvc;
    nbChannel  =  pStaticDef->huNbChan;
    pChannel   =  pRtIoSplDvc->pRtIoChan;
            cpxDev->luUser =1;
			modbus_close(ctx);
        modbus_free(ctx);
		for( nbIndex = 0; nbIndex < nbChannel; nbIndex++)
    {
        pPhyData = (int16*)(pChannel->pvKerPhyData);
        pLogData = (int16*)(pChannel->pvKerData);
        fElecData=tab_reg[nbIndex];
        if((pChannel->pfnCnvCall) != 0) /* If there is a conversion */
        {
            pChannel->pfnCnvCall( ISA_IO_DIR_INPUT, &fElecData, &fElecData);
        }
        fMult   = *(float *)(&(pChannel->luCnvMult));
        fDiv    = *(float *)(&(pChannel->luCnvDiv ));
        fOffset = *(float *)(&(pChannel->luCnvOfs));
        if (fDiv != 0.0){
			 fElecData = ((fElecData) * fMult  / fDiv) + fOffset;
			}
        if( *pPhyData != fElecData) /* If Physic value != Electrical value */
        {
            *pPhyData = fElecData;
        }


        /* update the channel if not locked */
        if(!(pChannel->cuIsLocked))  *pLogData = *pPhyData;

        pChannel++;
    }
        }	
	
    }

	
    
}

/****************************************************************************
function    : evro_tcpc_evro_tcpc_mtcp_aiIosCtl
description : Simple device Control function
parameters  :
   (input) uchar cuSubFunct :          Sub function parameter.
   (input) strRtIoSplDvc* pRtIoSplDvc: Rt io struct of the spl dvc to control.
   (input) uint16 huChanNum :          Channel number if any.
   (input) void* pvReserved :          Reserved.
return value: None
warning     :
****************************************************************************/

void evro_tcpc_evro_tcpc_mtcp_aiIosCtl
(
    uchar          cuSubFunct,   /* Sub function parameter */
    strRtIoSplDvc* pRtIoSplDvc,  /* Rt io struct of the spl dvc to control */
    uint16         huChanNum,    /* Channel number if any */
    void*          pvReserved    /* Reserved */
)
{

}
