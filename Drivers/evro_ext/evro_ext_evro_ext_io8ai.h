/**************************************************************************
File:               evro_ext_evro_ext_io8ai.h
Author:             Umputun
Creation date:      19/07/2012 - 11:31
Device name:        IO8AI
***************************************************************************/

#ifndef _EVRO_EXT_EVRO_EXT_IO8AI_H /* nested Headers management */
#define _EVRO_EXT_EVRO_EXT_IO8AI_H

/* prototypes */

typSTATUS  evro_ext_evro_ext_IosInit
(
    strRtIoDrv* pRtIoDrv /* Run time io struct of the driver to init */
);

void evro_ext_evro_ext_IosExit
(
    strRtIoDrv* pRtIoDrv /* Run time io struct of the driver to exit */
);

typSTATUS evro_ext_evro_ext_io8aiIosOpen
(
    strRtIoSplDvc* pvRtIoDvc /* Run time io struct of the device to open */
);

void evro_ext_evro_ext_io8aiIosClose
(
    strRtIoSplDvc* pvRtIoDvc /* Run time io struct of the device to close */
);

void evro_ext_evro_ext_io8aiIosRead
(
    strRtIoSplDvc* pRtIoSplDvc /* Run time io struct of the device to read */
);

void evro_ext_evro_ext_io8aiIosCtl
(
    uchar          cuSubFunct,   /* Sub function parameter */
    strRtIoSplDvc* pRtIoSplDvc,  /* Rt io struct of the spl dvc to control */
    uint16         huChanNum,    /* Channel number if any */
    void*          pvReserved    /* Reserved */
);


#endif /* _EVRO_EXT_EVRO_EXT_IO8AI_H */

/* eof ********************************************************************/

