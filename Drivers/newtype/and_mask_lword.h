/**************************************************************************
File:               and_mask_lword.h
Author:             ICS Triplex ISaGRAF
Creation date:      27/03/2007 - 18:15
POU name:           AND_MASK_LWORD
***************************************************************************
Attached documents: 

***************************************************************************
Description:        

***************************************************************************
Modifications: (who / date / description)

***************************************************************************/

#ifndef _AND_MASK_LWORD_H /* nested Headers management */
#define _AND_MASK_LWORD_H

/* function prototype */

ISANDTDLL void and_mask_lwordUsfCall
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

#endif /* _AND_MASK_LWORD_H */

/* eof ********************************************************************/
