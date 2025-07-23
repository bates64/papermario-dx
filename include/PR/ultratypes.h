#ifndef _ULTRATYPES_H_
#define _ULTRATYPES_H_


/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1995, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/


/*************************************************************************
 *
 *  File: ultratypes.h
 *
 *  This file contains various types used in Ultra64 interfaces.
 *
 *  $Revision: 1.6 $
 *  $Date: 1997/12/17 04:02:06 $
 *  $Source: /hosts/gate3/exdisk2/cvs/N64OS/Master/cvsmdev2/PR/include/ultratypes.h,v $
 *
 **************************************************************************/



/**********************************************************************
 * General data types for R4300
 */
#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

#include <stdint.h>
#include <stddef.h>

typedef uint8_t             u8;   /* unsigned  8-bit */
typedef uint16_t            u16;  /* unsigned 16-bit */
typedef uint32_t            u32;  /* unsigned 32-bit */
typedef uint64_t            u64;  /* unsigned 64-bit */

typedef int8_t              s8;   /* signed  8-bit */
typedef int16_t             s16;  /* signed 16-bit */
typedef int32_t             s32;  /* signed 32-bit */
typedef int64_t             s64;  /* signed 64-bit */

typedef volatile uint8_t    vu8;  /* volatile unsigned  8-bit */
typedef volatile uint16_t   vu16; /* volatile unsigned 16-bit */
typedef volatile uint32_t   vu32; /* volatile unsigned 32-bit */
typedef volatile uint64_t   vu64; /* volatile unsigned 64-bit */

typedef volatile int8_t     vs8;  /* volatile signed  8-bit */
typedef volatile int16_t    vs16; /* volatile signed 16-bit */
typedef volatile int32_t    vs32; /* volatile signed 32-bit */
typedef volatile int64_t    vs64; /* volatile signed 64-bit */

typedef float               f32;  /* single precision floating point */
typedef double              f64;  /* double precision floating point */

#if !defined(_SIZE_T) && !defined(_SIZE_T_) && !defined(_SIZE_T_DEF)
#define _SIZE_T
#define _SIZE_T_DEF			/* exeGCC size_t define label */
#if (_MIPS_SZLONG == 32)
typedef unsigned int    size_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef unsigned long   size_t;
#endif
#endif

#endif  /* _LANGUAGE_C */


/*************************************************************************
 * Common definitions
 */
#ifndef TRUE
#define TRUE    true
#endif

#ifndef FALSE
#define FALSE   false
#endif

#ifndef NULL
#define NULL    nullptr
#endif

#endif  /* _ULTRATYPES_H_ */

