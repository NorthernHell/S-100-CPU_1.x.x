/**************************************************************************
File:               rol_word.h
Author:             ICS Triplex ISaGRAF
Creation date:      27/03/2007 - 10:27
POU name:           ROL_WORD
***************************************************************************
Attached documents: 

***************************************************************************
Description:        

***************************************************************************
Modifications: (who / date / description)

***************************************************************************/

#ifndef _ROL_WORD_H /* nested Headers management */
#define _ROL_WORD_H

/* function prototype */

ISANDTDLL void rol_wordUsfCall
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

#endif /* _ROL_WORD_H */

/* eof ********************************************************************/

