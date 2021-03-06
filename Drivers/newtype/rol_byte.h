/**************************************************************************
File:               rol_byte.h
Author:             ICS Triplex ISaGRAF
Creation date:      21/03/2007 - 16:38
POU name:           ROL_BYTE
***************************************************************************
Attached documents: 

***************************************************************************
Description:        

***************************************************************************
Modifications: (who / date / description)

***************************************************************************/

#ifndef _ROL_BYTE_H /* nested Headers management */
#define _ROL_BYTE_H

/* function prototype */

ISANDTDLL void rol_byteUsfCall
   (
   void*       pvBfData,     /* In: Data */
   strParamVa* InParam,      /* In: Input parameters */
   uchar       cuNbInParam,  /* In: Number of input parameters */
#ifdef ITGTDEF_NEW_ARRAY_AND_FB
   strParamVa* OutParam,     /* In: Output parameter */
   void*       pvAdi         /* In: Pointer to ADI table */
#else
   strParamVa* OutParam      /* In: Output parameter */
#endif /* ITGTDEF_NEW_ARRAY_AND_FB */
   );

#endif /* _ROL_BYTE_H */

/* eof ********************************************************************/

