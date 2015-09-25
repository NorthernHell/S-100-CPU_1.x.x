/**************************************************************************
File:               evro_tcpc_evro_tcpc_mtcp_di.c
Author:             Umputun
Creation date:      25/02/2013 - 16:08
Device name:        MTCP_DI
***************************************************************************/

#include <dsys0def.h>
#include <dios0def.h>
#include <evro_tcpc_evro_tcpc_mtcp_di.h>
#include <modbus/modbus.h>
/* OEM Parameters */
extern int modbus_tcp_dis;

typedef struct _tag_strMtcp_di
{
    char   IP[16];
    int32  PORT;
    int32  Adress;
    int32  NR;
    int32  TimeOutu;
    int32  TimeOutsec;
} strOemParam;


/****************************************************************************
function    : evro_tcpc_evro_tcpc_mtcp_diIosOpen
description : Level 1 device Open function
parameters  :
   (input) strRtIoSplDvc* pvRtIoDvc :  Run time io struct of the device to open
return value: typSTATUS :  0 if successful, BAD_RET if error
warning     : Returning with an error stops the kernel resource starting
****************************************************************************/

typSTATUS evro_tcpc_evro_tcpc_mtcp_diIosOpen
(
  strRtIoSplDvc* pRtIoSplDvc /* Run time io struct of the device to read */
)
{
    printf("MB TCPC DI init\n");
    return (0);
}

/****************************************************************************
function    : evro_tcpc_evro_tcpc_mtcp_diIosClose
description : Level 1 device Close function
parameters  :
   (input) strRtIoSplDvc* pvRtIoDvc :  Run time io struct of the device to close
return value: None
warning     :
****************************************************************************/

void evro_tcpc_evro_tcpc_mtcp_diIosClose
(
  strRtIoSplDvc* pRtIoSplDvc /* Run time io struct of the device to read */
)
{
    printf("MB TCPC DI Close\n");
    sleep(1);
}

/****************************************************************************
function    : evro_tcpc_evro_tcpc_mtcp_diIosRead
description : Simple device Read function
parameters  :
   (input) void* pvRtIoDvc :  Run time io struct of the device to read
return value: None
warning     :
****************************************************************************/

void evro_tcpc_evro_tcpc_mtcp_diIosRead
(
    strRtIoSplDvc* pRtIoSplDvc /* Run time io struct of the device to read */
)
{
	strRtIoCpxDvc *cpxDev=(strRtIoCpxDvc *)pRtIoSplDvc->pvRtIoLevBack;
	strOemParam *oemCPar=(strOemParam *)cpxDev->pvOemParam;	
    modbus_t *ctx;
    uint8_t tab_reg[150];
    int rc;
    struct timeval response_timeout;
    response_timeout.tv_sec = oemCPar->TimeOutsec;
    response_timeout.tv_usec = oemCPar->TimeOutu;
    ctx = modbus_new_tcp(oemCPar->IP, oemCPar->PORT); //connect
    if (modbus_connect(ctx) == -1)
    {
        printf("Connexion failed (new DI): \n");
        modbus_free(ctx);
    }
    else
    {
        modbus_set_response_timeout(ctx, &response_timeout);
        rc  = modbus_read_input_bits(ctx, oemCPar->Adress, oemCPar->NR, tab_reg);
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
    uchar*              pPhyData;   /* Physical value            */
    uchar*              pLogData;   /* Logical Value               */
    uchar               byElecData; /* Electrical value ('1' or '0') */
    pStaticDef = pRtIoSplDvc->pDfIoSplDvc;
    nbChannel  = pStaticDef->huNbChan;
    pChannel   = pRtIoSplDvc->pRtIoChan;
            cpxDev->luUser =1;
			modbus_close(ctx);
			modbus_free(ctx);
			/* Update all channels */
			  for (nbIndex=0; nbIndex <  nbChannel ; nbIndex++)
    {
        pPhyData = (uchar*)(pChannel->pvKerPhyData);
        pLogData = (uchar*)(pChannel->pvKerData);
        byElecData = tab_reg[nbIndex];
        if((pChannel->pfnCnvCall) != 0)           /* If there is a conversion */
            pChannel->pfnCnvCall( ISA_IO_DIR_INPUT, &byElecData, &byElecData);


        if((pChannel->luCnvMult) != 1)            /* If the input is reversed */
        {
            if( *pPhyData == byElecData) /* If Physic value = Electrical value */
            {
                /* printf ("Input value - channel %d has changed\n",nbIndex); */
                if( byElecData) *pPhyData =0; /* Logic value != Physic value */
                else            *pPhyData =1;
            }
        }
        else                          /* If the input is direct */
        {
            if( byElecData != *pPhyData)
            {
                /* printf ("Input value - channel %d has changed\n",nbIndex); */
                *pPhyData = byElecData;
            }
        }
        /* update the channel if not locked */
        if (!(pChannel->cuIsLocked))  *pLogData = *pPhyData;

        pChannel++;
    }
        }			
        
    }
}

/****************************************************************************
function    : evro_tcpc_evro_tcpc_mtcp_diIosCtl
description : Simple device Control function
parameters  :
   (input) uchar cuSubFunct :          Sub function parameter.
   (input) strRtIoSplDvc* pRtIoSplDvc: Rt io struct of the spl dvc to control.
   (input) uint16 huChanNum :          Channel number if any.
   (input) void* pvReserved :          Reserved.
return value: None
warning     :
****************************************************************************/

void evro_tcpc_evro_tcpc_mtcp_diIosCtl
(
    uchar          cuSubFunct,   /* Sub function parameter */
    strRtIoSplDvc* pRtIoSplDvc,  /* Rt io struct of the spl dvc to control */
    uint16         huChanNum,    /* Channel number if any */
    void*          pvReserved    /* Reserved */
)
{

}