/**************************************************************************
File:               ror_lword.h
Author:             ICS Triplex ISaGRAF
Creation date:      27/03/2007 - 18:15
POU name:           ROR_LWORD
***************************************************************************
Attached documents: 

***************************************************************************
Description:        

***************************************************************************
Modifications: (who / date / description)

***************************************************************************/

#ifndef _ROR_LWORD_H /* nested Headers management */
#define _ROR_LWORD_H

/* function prototype */

ISANDTDLL void ror_lwordUsfCall
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

#endif /* _ROR_LWORD_H */

/* eof ********************************************************************/

