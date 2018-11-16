/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

/*****************************************************************************
 *
 * Filename:
 * ---------
 * u1ld_custom_mipi.c
 *
 * Project:
 * --------
 * TK6291
 *
 * Description:
 * ------------
 *
 *
 * Author:
 * -------
 * -------
 *

===============================================================================*/

#include "kal_general_types.h"
#include "ul1d_custom_mipi.h"
#include "ul1d_custom_rf.h"
#include "mml1_custom_mipi.h"
#include "ul1d_mipi_public.h"
#include "mml1_drdi.h"

#if defined(L1_SIM)
#include "SymWrap.h"
#endif
/*===============================================================================*/

//#define MIPI_INITIAL_CW_NUM 0
#if (IS_3G_MIPI_SUPPORT)

const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_RX_EVENT_UMTSBandNone_SetDefault[UL1_MIPI_RX_EVENT_NUM] = 
{
	 /* No.     elm type , data idx       , evt_type       , evt_offset     */
   /*                    { start, stop },                  ( us )         */
   { /* 0  */ UL1_MIPI_NULL ,{ 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 1  */ UL1_MIPI_NULL ,{ 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 2  */ UL1_MIPI_NULL ,{ 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 3  */ UL1_MIPI_NULL ,{ 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 4  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 5  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 6  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 7  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 8  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 9  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 10 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 11 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 12 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 13 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 14 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 15 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 16 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 17 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 18 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 19 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 20 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 21 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 22 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 23 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
};


const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_RX_EVENT_UMTSBand1_SetDefault[UL1_MIPI_RX_EVENT_NUM] = 
{
   /* No.     elm type , data idx       , evt_type       , evt_offset     */
   /*                    { start, stop },                  ( us )         */
   { /* 0  */ UL1_MIPI_ASM,      { 0    , 0    }, UL1_MIPI_TRX_ON, US2CHIPCNT(200)     },
   //{ /* 1  */ UL1_MIPI_ASM_RXD,  { 1    , 1    }, UL1_MIPI_TRX_ON, US2CHIPCNT(195)     },
   { /* 1  */ UL1_MIPI_ASM,      { 1    , 1    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(10)     },
   //{ /* 3  */ UL1_MIPI_ASM_RXD,  { 3    , 3    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(10)     },
   { /* 2  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 3  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 4  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 5  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   //{ /* 4  */ UL1_MIPI_ANT,      { 4    , 4    }, UL1_MIPI_TRX_ON, US2CHIPCNT(200)    },
   //{ /* 5  */ UL1_MIPI_ANT,      { 5    , 5    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(15)     },
   { /* 6  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 7  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 8  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 9  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 10 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 11 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 12 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 13 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 14 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 15 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 16 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 17 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 18 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 19 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 20 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 21 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 22 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 23 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
};


const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_RX_EVENT_UMTSBand2_SetDefault[UL1_MIPI_RX_EVENT_NUM] = 
{
   /* No.     elm type , data idx       , evt_type       , evt_offset     */
   /*                    { start, stop },                  ( us )         */
   { /* 0  */ UL1_MIPI_ASM,      { 0    , 0    }, UL1_MIPI_TRX_ON, US2CHIPCNT(200)     },
   //{ /* 1  */ UL1_MIPI_ASM_RXD,  { 1    , 1    }, UL1_MIPI_TRX_ON, US2CHIPCNT(195)     },
   { /* 1  */ UL1_MIPI_ASM,      { 1    , 1    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(10)     },
   //{ /* 3  */ UL1_MIPI_ASM_RXD,  { 3    , 3    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(10)     },
   { /* 2  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 3  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 4  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 5  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   //{ /* 4  */ UL1_MIPI_ANT,      { 4    , 4    }, UL1_MIPI_TRX_ON, US2CHIPCNT(200)    },
   //{ /* 5  */ UL1_MIPI_ANT,      { 5    , 5    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(15)     },
   { /* 6  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 7  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 8  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 9  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 10 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 11 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 12 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 13 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 14 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 15 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 16 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 17 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 18 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 19 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 20 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 21 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 22 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 23 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
};

const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_RX_EVENT_UMTSBand4_SetDefault[UL1_MIPI_RX_EVENT_NUM] = 
{
   /* No.     elm type , data idx       , evt_type       , evt_offset     */
   /*                    { start, stop },                  ( us )         */
   { /* 0  */ UL1_MIPI_ASM,      { 0    , 0    }, UL1_MIPI_TRX_ON, US2CHIPCNT(200)     },
   //{ /* 1  */ UL1_MIPI_ASM_RXD,  { 1    , 1    }, UL1_MIPI_TRX_ON, US2CHIPCNT(195)     },
   { /* 1  */ UL1_MIPI_ASM,      { 1    , 1    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(10)     },
   //{ /* 3  */ UL1_MIPI_ASM_RXD,  { 3    , 3    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(10)     },
   { /* 2  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 3  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 4  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 5  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   //{ /* 4  */ UL1_MIPI_ANT,      { 4    , 4    }, UL1_MIPI_TRX_ON, US2CHIPCNT(200)    },
   //{ /* 5  */ UL1_MIPI_ANT,      { 5    , 5    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(15)     },
   { /* 6  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 7  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 8  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 9  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 10 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 11 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 12 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 13 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 14 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 15 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 16 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 17 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 18 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 19 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 20 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 21 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 22 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 23 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
};


const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_RX_EVENT_UMTSBand5_SetDefault[UL1_MIPI_RX_EVENT_NUM] = 
{
   /* No.     elm type , data idx       , evt_type       , evt_offset     */
   /*                    { start, stop },                  ( us )         */
   { /* 0  */ UL1_MIPI_ASM,      { 0    , 0    }, UL1_MIPI_TRX_ON, US2CHIPCNT(200)     },
   //{ /* 1  */ UL1_MIPI_ASM_RXD,  { 1    , 1    }, UL1_MIPI_TRX_ON, US2CHIPCNT(195)     },
   { /* 1  */ UL1_MIPI_ASM,      { 1    , 1    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(10)     },
   //{ /* 3  */ UL1_MIPI_ASM_RXD,  { 3    , 3    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(10)     },
   { /* 2  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 3  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 4  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 5  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   //{ /* 4  */ UL1_MIPI_ANT,      { 4    , 4    }, UL1_MIPI_TRX_ON, US2CHIPCNT(200)    },
   //{ /* 5  */ UL1_MIPI_ANT,      { 5    , 5    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(15)     },
   { /* 6  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 7  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 8  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 9  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 10 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 11 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 12 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 13 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 14 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 15 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 16 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 17 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 18 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 19 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 20 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 21 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 22 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 23 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
};

const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_RX_EVENT_UMTSBand8_SetDefault[UL1_MIPI_RX_EVENT_NUM] = 
{
   /* No.     elm type , data idx       , evt_type       , evt_offset     */
   /*                    { start, stop },                  ( us )         */
   { /* 0  */ UL1_MIPI_ASM,      { 0    , 0    }, UL1_MIPI_TRX_ON, US2CHIPCNT(200)     },
   //{ /* 1  */ UL1_MIPI_ASM_RXD,  { 1    , 1    }, UL1_MIPI_TRX_ON, US2CHIPCNT(195)     },
   { /* 1  */ UL1_MIPI_ASM,      { 1    , 1    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(10)     },
   //{ /* 3  */ UL1_MIPI_ASM_RXD,  { 3    , 3    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(10)     },
   { /* 2  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 3  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 4  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 5  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   //{ /* 4  */ UL1_MIPI_ANT,      { 4    , 4    }, UL1_MIPI_TRX_ON, US2CHIPCNT(200)    },
   //{ /* 5  */ UL1_MIPI_ANT,      { 5    , 5    }, UL1_MIPI_TRX_OFF,US2CHIPCNT(15)     },
   { /* 6  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 7  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 8  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 9  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 10 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 11 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 12 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 13 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 14 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 15 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 16 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 17 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 18 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 19 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 20 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 21 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 22 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 23 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
};

const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_RX_EVENT_UMTSBand3_SetDefault[] = {{0}};
const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_RX_EVENT_UMTSBand6_SetDefault[] = {{0}};
const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_RX_EVENT_UMTSBand9_SetDefault[] = {{0}};
const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_RX_EVENT_UMTSBand11_SetDefault[] = {{0}};
const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_RX_EVENT_UMTSBand19_SetDefault[] = {{0}};

const UL1_MIPI_EVENT_TABLE_T* const UMTS_MIPI_RX_EVENT_TABLE_SetDefault[] =
{
   M_UMTS_RX_EVENT(UMTSBandNone, SetDefault),          /*UMTSBandNone*/          
   M_UMTS_RX_EVENT(RX_BAND_INDICATOR_0_SetDefault, SetDefault),   /*UMTS_Route0*/
   M_UMTS_RX_EVENT(RX_BAND_INDICATOR_1_SetDefault, SetDefault),   /*UMTS_Route1*/
   M_UMTS_RX_EVENT(RX_BAND_INDICATOR_2_SetDefault, SetDefault),   /*UMTS_Route2*/   
   M_UMTS_RX_EVENT(RX_BAND_INDICATOR_3_SetDefault, SetDefault),   /*UMTS_Route3*/   
   M_UMTS_RX_EVENT(RX_BAND_INDICATOR_4_SetDefault, SetDefault),   /*UMTS_Route4*/
#if IS_3G_RF_NCCA_SUPPORT
   M_UMTS_RX_EVENT(MIPI_RX_ROUTE_IND_5, SetDefault),   /*UMTS_Route5*/
   M_UMTS_RX_EVENT(MIPI_RX_ROUTE_IND_6, SetDefault),   /*UMTS_Route6*/
   M_UMTS_RX_EVENT(MIPI_RX_ROUTE_IND_7, SetDefault),   /*UMTS_Route7*/
   M_UMTS_RX_EVENT(MIPI_RX_ROUTE_IND_8, SetDefault),   /*UMTS_Route8*/
   M_UMTS_RX_EVENT(MIPI_RX_ROUTE_IND_9, SetDefault),   /*UMTS_Route9*/
   M_UMTS_RX_EVENT(MIPI_RX_ROUTE_IND_10, SetDefault),  /*UMTS_Route10*/
   M_UMTS_RX_EVENT(MIPI_RX_ROUTE_IND_11, SetDefault),  /*UMTS_Route11*/
   M_UMTS_RX_EVENT(MIPI_RX_ROUTE_IND_12, SetDefault),  /*UMTS_Route12*/
   M_UMTS_RX_EVENT(MIPI_RX_ROUTE_IND_13, SetDefault),  /*UMTS_Route13*/
   M_UMTS_RX_EVENT(MIPI_RX_ROUTE_IND_14, SetDefault),  /*UMTS_Route14*/
#endif
};

const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_RX_DATA_UMTSBandNone_SetDefault[UL1_MIPI_RX_DATA_NUM] = 
{
   //No.      elm type , port_sel      ,  data_seq  , user id,         { { sub 0 ,addr, data },{ sub 1 ,addr, data },{ sub 2 ,addr, data}, { sub 3, addr, data  }, { sub 4, addr data  } },
   { /* 0  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 1  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 2  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 3  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 4  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 5  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 6  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 7  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 8  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 9  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 10 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 11 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 12 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 13 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 14 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 15 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 16 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 17 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 18 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 19 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 20 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 21 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 22 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 23 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 24 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 25 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 26 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
   { /* 27 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}}} },
};

const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_RX_DATA_UMTSBand1_SetDefault[UL1_MIPI_RX_DATA_NUM] = 
{
   //No.      elm type , port_sel      ,  data_seq  , user id,         { { sub 0 ,addr, data }},{ sub 1 ,addr, data }},{ sub 2 ,addr, data}}, { sub 3, addr, data  }}, { sub 4, addr data  } }},
   { /* 0  */ UL1_MIPI_ASM,      UL1_MIPI_PORT1,  UL1_REG_W     , MIPI_USID_ASM0_SetDefault, { { 21124 ,{0x00, 0x0D}}, { 21262 ,{0x00, 0x0D}}, { 21400 ,{0x00, 0x0D}}, { 21538  ,{0x00, 0x0D}}, { 21676 ,{0x00, 0x0D}}} },
   //{ /* 1  */ UL1_MIPI_ASM_RXD,  UL1_MIPI_PORT3,  UL1_REG_W     , MIPI_USID_ASM1_SetDefault, { { 21124 ,{0x00, 0x08}}, { 21262 ,{0x00, 0x08}}, { 21400 ,{0x00, 0x08}}, { 21538  ,{0x00, 0x08}}, { 21676 ,{0x00, 0x08}}} },
   { /* 1  */ UL1_MIPI_ASM,      UL1_MIPI_PORT1,  UL1_REG_W     , MIPI_USID_ASM0_SetDefault, { { 21124 ,{0x00, 0x00}}, { 21262 ,{0x00, 0x00}}, { 21400 ,{0x00, 0x00}}, { 21538  ,{0x00, 0x00}}, { 21676 ,{0x00, 0x00}}} },
   //{ /* 3  */ UL1_MIPI_ASM_RXD,  UL1_MIPI_PORT3,  UL1_REG_W     , MIPI_USID_ASM1_SetDefault, { { 21124 ,{0x00, 0x00}}, { 21262 ,{0x00, 0x00}}, { 21400 ,{0x00, 0x00}}, { 21538  ,{0x00, 0x00}}, { 21676 ,{0x00, 0x00}}} },
   { /* 2  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 3  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 4  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 5  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   //{ /* 4  */ UL1_MIPI_ANT,      UL1_MIPI_PORT2,  UL1_REG_W     , MIPI_USID_ANT0_SetDefault, { { 21124 ,{0x00, 0x01}}, { 21262 ,{0x00, 0x01}}, { 21400 ,{0x00, 0x01}}, { 21538  ,{0x00, 0x01}}, { 21676 ,{0x00, 0x01}}} },
   //{ /* 5  */ UL1_MIPI_ANT,      UL1_MIPI_PORT2,  UL1_REG_W     , MIPI_USID_ANT0_SetDefault, { { 21124 ,{0x00, 0x00}}, { 21262 ,{0x00, 0x00}}, { 21400 ,{0x00, 0x00}}, { 21538  ,{0x00, 0x00}}, { 21676 ,{0x00, 0x00}}} },
   { /* 6  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 7  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 8  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 9  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 10 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 11 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 12 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 13 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 14 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 15 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 16 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 17 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 18 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 19 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 20 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 21 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 22 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 23 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 24 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 25 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 26 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },
   { /* 27 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault,{ { 21124 ,{0x0,  0x0}},  { 21262 ,{0x0,  0x0}},   { 21400 ,{0x0, 0x0}},   { 21538  ,{0x0, 0x0}},   { 21676 ,{0x0,  0x0}}} },

};

const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_RX_DATA_UMTSBand2_SetDefault[UL1_MIPI_RX_DATA_NUM] = 
{
   //No.      elm type , port_sel      ,  data_seq  , user id,         { { sub 0 ,addr, data }},{ sub 1 ,addr, data }},{ sub 2 ,addr, data}}, { sub 3, addr, data  }}, { sub 4, addr data  } }},
   { /* 0  */ UL1_MIPI_ASM,      UL1_MIPI_PORT1,  UL1_REG_W     , MIPI_USID_ASM0_SetDefault,  { { 19324 ,{0x00, 0x11}}, { 19462 ,{0x00, 0x11}}, { 19600 ,{0x00, 0x11}}, { 19738  ,{0x00, 0x11}}, { 19876 ,{0x00, 0x11}}} },
   //{ /* 1  */ UL1_MIPI_ASM_RXD,  UL1_MIPI_PORT3,  UL1_REG_W     , MIPI_USID_ASM1_SetDefault,  { { 19324 ,{0x00, 0x0C}}, { 19462 ,{0x00, 0x0C}}, { 19600 ,{0x00, 0x0C}}, { 19738  ,{0x00, 0x0C}}, { 19876 ,{0x00, 0x0C}}} },
   { /* 1  */ UL1_MIPI_ASM,      UL1_MIPI_PORT1,  UL1_REG_W     , MIPI_USID_ASM0_SetDefault,  { { 19324 ,{0x00, 0x00}}, { 19462 ,{0x00, 0x00}}, { 19600 ,{0x00, 0x00}}, { 19738  ,{0x00, 0x00}}, { 19876 ,{0x00, 0x00}}} },
   //{ /* 3  */ UL1_MIPI_ASM_RXD,  UL1_MIPI_PORT3,  UL1_REG_W     , MIPI_USID_ASM1_SetDefault,  { { 19324 ,{0x00, 0x00}}, { 19462 ,{0x00, 0x00}}, { 19600 ,{0x00, 0x00}}, { 19738  ,{0x00, 0x00}}, { 19876 ,{0x00, 0x00}}} },
   { /* 2  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 3  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 4  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 5  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   //{ /* 4  */ UL1_MIPI_ANT,      UL1_MIPI_PORT2,  UL1_REG_W     , MIPI_USID_ANT0_SetDefault,  { { 19324 ,{0x00, 0x01}}, { 19462 ,{0x00, 0x01}}, { 19600 ,{0x00, 0x01}}, { 19738  ,{0x00, 0x01}}, { 19876 ,{0x00, 0x01}}} },
   //{ /* 5  */ UL1_MIPI_ANT,      UL1_MIPI_PORT2,  UL1_REG_W     , MIPI_USID_ANT0_SetDefault,  { { 19324 ,{0x00, 0x00}}, { 19462 ,{0x00, 0x00}}, { 19600 ,{0x00, 0x00}}, { 19738  ,{0x00, 0x00}}, { 19876 ,{0x00, 0x00}}} },
   { /* 6  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 7  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 8  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 9  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 10 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 11 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 12 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 13 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 14 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 15 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 16 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 17 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 18 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 19 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 20 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 21 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 22 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 23 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 24 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 25 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 26 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
   { /* 27 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 19324 ,{0x0, 0x0}},   { 19462 ,{0x0, 0x0}},   { 19600 ,{0x0, 0x0}},   { 19738  ,{0x0, 0x0}},   { 19876 ,{0x0,  0x0}} } },
};

const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_RX_DATA_UMTSBand4_SetDefault[UL1_MIPI_RX_DATA_NUM] = 
{
   //No.      elm type , port_sel      ,  data_seq  , user id,         { { sub 0 ,addr, data }},{ sub 1 ,addr, data }},{ sub 2 ,addr, data}}, { sub 3, addr, data  }}, { sub 4, addr data  } }},
   { /* 0  */ UL1_MIPI_ASM,      UL1_MIPI_PORT1,  UL1_REG_W     , MIPI_USID_ASM0_SetDefault,  { { 21124 ,{0x00, 0x14}}, { 21227 ,{0x00, 0x14}}, { 21330 ,{0x00, 0x14}}, { 21428  ,{0x00, 0x14}}, { 21526 ,{0x00, 0x14}}} },
   //{ /* 1  */ UL1_MIPI_ASM_RXD,  UL1_MIPI_PORT3,  UL1_REG_W     , MIPI_USID_ASM1_SetDefault,  { { 21124 ,{0x00, 0x08}}, { 21227 ,{0x00, 0x08}}, { 21330 ,{0x00, 0x08}}, { 21428  ,{0x00, 0x08}}, { 21526 ,{0x00, 0x08}}} },
   { /* 1  */ UL1_MIPI_ASM,      UL1_MIPI_PORT1,  UL1_REG_W     , MIPI_USID_ASM0_SetDefault,  { { 21124 ,{0x00, 0x00}}, { 21227 ,{0x00, 0x00}}, { 21330 ,{0x00, 0x00}}, { 21428  ,{0x00, 0x00}}, { 21526 ,{0x00, 0x00}}} },
   //{ /* 3  */ UL1_MIPI_ASM_RXD,  UL1_MIPI_PORT3,  UL1_REG_W     , MIPI_USID_ASM1_SetDefault,  { { 21124 ,{0x00, 0x00}}, { 21227 ,{0x00, 0x00}}, { 21330 ,{0x00, 0x00}}, { 21428  ,{0x00, 0x00}}, { 21526 ,{0x00, 0x00}}} },
   { /* 2  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 3  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 4  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 5  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   //{ /* 4  */ UL1_MIPI_ANT,      UL1_MIPI_PORT2,  UL1_REG_W     , MIPI_USID_ANT0_SetDefault,  { { 21124 ,{0x00, 0x01}}, { 21227 ,{0x00, 0x01}}, { 21330 ,{0x00, 0x01}}, { 21428  ,{0x00, 0x01}}, { 21526 ,{0x00, 0x01}}} },
   //{ /* 5  */ UL1_MIPI_ANT,      UL1_MIPI_PORT2,  UL1_REG_W     , MIPI_USID_ANT0_SetDefault,  { { 21124 ,{0x00, 0x00}}, { 21227 ,{0x00, 0x00}}, { 21330 ,{0x00, 0x00}}, { 21428  ,{0x00, 0x00}}, { 21526 ,{0x00, 0x00}}} },
   { /* 6  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 7  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 8  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 9  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 10 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 11 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 12 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 13 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 14 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 15 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 16 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 17 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 18 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 19 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 20 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 21 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 22 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 23 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 24 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 25 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 26 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },
   { /* 27 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 21124 ,{0x0, 0x0}},   { 21227 ,{0x0, 0x0}},   { 21330 ,{0x0, 0x0}},   { 21428  ,{0x0, 0x0}},   { 21526 ,{0x0,   0x0}}} },

};

const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_RX_DATA_UMTSBand5_SetDefault[UL1_MIPI_RX_DATA_NUM] = 
{
   //No.      elm type , port_sel      ,  data_seq  , user id,         { { sub 0 ,addr, data }},{ sub 1 ,addr, data }},{ sub 2 ,addr, data}}, { sub 3, addr, data  }}, { sub 4, addr data  } }},
   { /* 0  */ UL1_MIPI_ASM,      UL1_MIPI_PORT1,  UL1_REG_W     , MIPI_USID_ASM0_SetDefault,  { { 8714 ,{0x00, 0x01}}, { 8764 ,{0x00, 0x01}},   { 8815 ,{0x00, 0x01}},  { 8865  ,{0x00, 0x01}},   { 8916 ,{0x00, 0x01}} }},
   //{ /* 1  */ UL1_MIPI_ASM_RXD,  UL1_MIPI_PORT3,  UL1_REG_W     , MIPI_USID_ASM1_SetDefault,  { { 8714 ,{0x00, 0x05}}, { 8764 ,{0x00, 0x05}},   { 8815 ,{0x00, 0x05}},  { 8865  ,{0x00, 0x05}},   { 8916 ,{0x00, 0x05}} }},
   { /* 1  */ UL1_MIPI_ASM,      UL1_MIPI_PORT1,  UL1_REG_W     , MIPI_USID_ASM0_SetDefault,  { { 8714 ,{0x00, 0x00}}, { 8764 ,{0x00, 0x00}},   { 8815 ,{0x00, 0x00}},  { 8865  ,{0x00, 0x00}},   { 8916 ,{0x00, 0x00}} }},
   //{ /* 3  */ UL1_MIPI_ASM_RXD,  UL1_MIPI_PORT3,  UL1_REG_W     , MIPI_USID_ASM1_SetDefault,  { { 8714 ,{0x00, 0x00}}, { 8764 ,{0x00, 0x00}},   { 8815 ,{0x00, 0x00}},  { 8865  ,{0x00, 0x00}},   { 8916 ,{0x00, 0x00}} }},
   { /* 2  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 3  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 4  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 5  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 6  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 7  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 8  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 9  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 10 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 11 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 12 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 13 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 14 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 15 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 16 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 17 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 18 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 19 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 20 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 21 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 22 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 23 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 24 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 25 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 26 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
   { /* 27 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 8714 ,{0x0, 0x0}},   { 8764 ,{0x0, 0x0}},     { 8815 ,{0x0, 0x0}},    { 8865  ,{0x0, 0x0}},     { 8916 ,{0x0,   0x0}} }},
};


const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_RX_DATA_UMTSBand8_SetDefault[UL1_MIPI_RX_DATA_NUM] = 
{
   //No.      elm type , port_sel      ,  data_seq  , user id,         { { sub 0 ,addr, data }},{ sub 1 ,addr, data }},{ sub 2 ,addr, data}}, { sub 3, addr, data  }}, { sub 4, addr data  } }},
   { /* 0  */ UL1_MIPI_ASM,      UL1_MIPI_PORT1,  UL1_REG_W     , MIPI_USID_ASM0_SetDefault,  { { 9274 ,{0x00, 0x10}}, { 9349 ,{0x00, 0x10}},   { 9425 ,{0x00, 0x10}},  { 9500  ,{0x00, 0x10}},   { 9576 ,{0x00, 0x10}} }},
   //{ /* 1  */ UL1_MIPI_ASM_RXD,  UL1_MIPI_PORT3,  UL1_REG_W     , MIPI_USID_ASM1_SetDefault,  { { 9274 ,{0x00, 0x07}}, { 9349 ,{0x00, 0x07}},   { 9425 ,{0x00, 0x07}},  { 9500  ,{0x00, 0x07}},   { 9576 ,{0x00, 0x07}} }},
   { /* 2  */ UL1_MIPI_ASM,      UL1_MIPI_PORT1,  UL1_REG_W     , MIPI_USID_ASM0_SetDefault,  { { 9274 ,{0x00, 0x00}}, { 9349 ,{0x00, 0x00}},   { 9425 ,{0x00, 0x00}},  { 9500  ,{0x00, 0x00}},   { 9576 ,{0x00, 0x00}} }},
   //{ /* 3  */ UL1_MIPI_ASM_RXD,  UL1_MIPI_PORT3,  UL1_REG_W     , MIPI_USID_ASM1_SetDefault,  { { 9274 ,{0x00, 0x00}}, { 9349 ,{0x00, 0x00}},   { 9425 ,{0x00, 0x00}},  { 9500  ,{0x00, 0x00}},   { 9576 ,{0x00, 0x00}} }},
   { /* 2  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 3  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 4  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 5  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 6  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 7  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 8  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 9  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 10 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 11 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 12 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 13 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 14 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 15 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 16 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 17 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 18 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 19 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 20 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 21 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 22 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 23 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 24 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 25 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 26 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
   { /* 27 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL  , MIPI_USID_INIT0_SetDefault, { { 9274 ,{0x0, 0x0}},   { 9349 ,{0x0, 0x0}},     { 9425 ,{0x0, 0x0}},    { 9500  ,{0x0, 0x0}},     { 9576 ,{0x0,   0x0}} }},
};

const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_RX_DATA_UMTSBand3_SetDefault[] = {{0}};
const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_RX_DATA_UMTSBand6_SetDefault[] = {{0}};
const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_RX_DATA_UMTSBand9_SetDefault[] = {{0}};
const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_RX_DATA_UMTSBand11_SetDefault[] = {{0}};
const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_RX_DATA_UMTSBand19_SetDefault[] = {{0}};

const UL1_MIPI_DATA_SUBBAND_TABLE_T* const UMTS_MIPI_RX_DATA_TABLE_SetDefault[] = 
{
   M_UMTS_RX_DATA(UMTSBandNone,SetDefault),          /*UMTSBandNone*/          
   M_UMTS_RX_DATA(RX_BAND_INDICATOR_0_SetDefault,SetDefault),   /*UMTS_Route0*/
   M_UMTS_RX_DATA(RX_BAND_INDICATOR_1_SetDefault,SetDefault),   /*UMTS_Route1*/
   M_UMTS_RX_DATA(RX_BAND_INDICATOR_2_SetDefault,SetDefault),   /*UMTS_Route2*/
   M_UMTS_RX_DATA(RX_BAND_INDICATOR_3_SetDefault,SetDefault),   /*UMTS_Route3*/ 
   M_UMTS_RX_DATA(RX_BAND_INDICATOR_4_SetDefault,SetDefault),   /*UMTS_Route4*/
#if IS_3G_RF_NCCA_SUPPORT
   M_UMTS_RX_DATA(MIPI_RX_ROUTE_IND_5,SetDefault),   /*UMTS_Route5*/
   M_UMTS_RX_DATA(MIPI_RX_ROUTE_IND_6,SetDefault),   /*UMTS_Route6*/
   M_UMTS_RX_DATA(MIPI_RX_ROUTE_IND_7,SetDefault),   /*UMTS_Route7*/
   M_UMTS_RX_DATA(MIPI_RX_ROUTE_IND_8,SetDefault),   /*UMTS_Route8*/
   M_UMTS_RX_DATA(MIPI_RX_ROUTE_IND_9,SetDefault),   /*UMTS_Route9*/
   M_UMTS_RX_DATA(MIPI_RX_ROUTE_IND_10,SetDefault),  /*UMTS_Route10*/
   M_UMTS_RX_DATA(MIPI_RX_ROUTE_IND_11,SetDefault),  /*UMTS_Route11*/
   M_UMTS_RX_DATA(MIPI_RX_ROUTE_IND_12,SetDefault),  /*UMTS_Route12*/
   M_UMTS_RX_DATA(MIPI_RX_ROUTE_IND_13,SetDefault),  /*UMTS_Route13*/
   M_UMTS_RX_DATA(MIPI_RX_ROUTE_IND_14,SetDefault),  /*UMTS_Route14*/
#endif
};

const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_TX_EVENT_UMTSBandNone_SetDefault[UL1_MIPI_TX_EVENT_NUM] = 
{
   /* No.     elm type , data idx       , evt_type       , evt_offset     */
   /*                     { start, stop },                  ( us )         */
   { /* 0  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 1  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 2  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 3  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 4  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 5  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 6  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 7  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 8  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 9  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 10 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 11 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 12 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 13 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 14 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 15 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
};

const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_TX_EVENT_UMTSBand1_SetDefault[UL1_MIPI_TX_EVENT_NUM] = 
{
	 /* No.     elm type , data idx       , evt_type       , evt_offset     */
   /*                     { start, stop },                  ( us )         */
   { /* 0  */ UL1_MIPI_PA,   { 0    , 1   }, UL1_MIPI_TRX_ON,     US2CHIPCNT(195) },
   { /* 1  */ UL1_MIPI_PA,   { 2    , 4   }, UL1_MIPI_TRX_OFF,    US2CHIPCNT(10)  },
   { /* 2  */ UL1_MIPI_ASM,  { 5    , 5   }, UL1_MIPI_TRX_ON,     US2CHIPCNT(195) },
   //{ /* 3  */ UL1_MIPI_ANT,  { 5    , 5   }, UL1_MIPI_TRX_ON,     US2CHIPCNT(200) },
   { /* 3  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 4  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 5  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 6  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 7  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 8  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 9  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 10 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 11 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 12 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 13 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 14 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 15 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
};

const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_TX_EVENT_UMTSBand2_SetDefault[UL1_MIPI_TX_EVENT_NUM] = 
{
	 /* No.     elm type , data idx       , evt_type       , evt_offset     */
   /*                     { start, stop },                  ( us )         */
   { /* 0  */ UL1_MIPI_PA,   { 0    , 1    }, UL1_MIPI_TRX_ON,    US2CHIPCNT(195) },
   { /* 1  */ UL1_MIPI_PA,   { 2    , 4    }, UL1_MIPI_TRX_OFF,   US2CHIPCNT(10)  },
   { /* 2  */ UL1_MIPI_ASM,  { 5    , 5    }, UL1_MIPI_TRX_ON,    US2CHIPCNT(195) },
   //{ /* 3  */ UL1_MIPI_ANT,  { 5    , 5    }, UL1_MIPI_TRX_ON,     US2CHIPCNT(200) },
   { /* 3  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 4  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 5  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 6  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 7  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 8  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 9  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 10 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 11 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 12 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 13 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 14 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 15 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
};

const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_TX_EVENT_UMTSBand4_SetDefault[UL1_MIPI_TX_EVENT_NUM] = 
{
	 /* No.     elm type , data idx       , evt_type       , evt_offset     */
   /*                     { start, stop },                  ( us )         */
   { /* 0  */ UL1_MIPI_PA,   { 0    , 1    }, UL1_MIPI_TRX_ON,    US2CHIPCNT(195) },
   { /* 1  */ UL1_MIPI_PA,   { 2    , 4    }, UL1_MIPI_TRX_OFF,   US2CHIPCNT(10)  },
   { /* 2  */ UL1_MIPI_ASM,  { 5    , 5    }, UL1_MIPI_TRX_ON,    US2CHIPCNT(195) },
   //{ /* 3  */ UL1_MIPI_ANT,  { 5    , 5    }, UL1_MIPI_TRX_ON,     US2CHIPCNT(200) },
   { /* 3  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 4  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 5  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 6  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 7  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 8  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 9  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 10 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 11 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 12 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 13 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 14 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 15 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
};


const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_TX_EVENT_UMTSBand5_SetDefault[UL1_MIPI_TX_EVENT_NUM] = 
{
	 /* No.     elm type , data idx       , evt_type       , evt_offset     */
   /*                     { start, stop },                  ( us )         */
   { /* 0  */ UL1_MIPI_PA,   { 0    , 1    }, UL1_MIPI_TRX_ON,    US2CHIPCNT(195) },
   { /* 1  */ UL1_MIPI_PA,   { 2    , 4    }, UL1_MIPI_TRX_OFF,   US2CHIPCNT(10)  },
   { /* 2  */ UL1_MIPI_ASM,  { 5    , 5    }, UL1_MIPI_TRX_ON,    US2CHIPCNT(195) },
   //{ /* 3  */ UL1_MIPI_ANT,  { 5    , 5    }, UL1_MIPI_TRX_ON,     US2CHIPCNT(200) },
   { /* 3  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 4  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 5  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 6  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 7  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 8  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 9  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 10 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 11 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 12 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 13 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 14 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 15 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
};

const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_TX_EVENT_UMTSBand8_SetDefault[UL1_MIPI_TX_EVENT_NUM] = 
{
	 /* No.     elm type , data idx       , evt_type       , evt_offset     */
   /*                     { start, stop },                  ( us )         */
   { /* 0  */ UL1_MIPI_PA,   { 0    , 1    }, UL1_MIPI_TRX_ON,    US2CHIPCNT(195) },
   { /* 1  */ UL1_MIPI_PA,   { 2    , 4    }, UL1_MIPI_TRX_OFF,   US2CHIPCNT(10)  },
   { /* 2  */ UL1_MIPI_ASM,  { 5    , 5    }, UL1_MIPI_TRX_ON,    US2CHIPCNT(195) },
   //{ /* 3  */ UL1_MIPI_ANT,  { 5    , 5    }, UL1_MIPI_TRX_ON,     US2CHIPCNT(200) },
   { /* 3  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 4  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 5  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 6  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 7  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 8  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 9  */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 10 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 11 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 12 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 13 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 14 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
   { /* 15 */ UL1_MIPI_NULL, { 0    , 0    }, UL1_MIPI_EVENT_NULL, 0              },
};

const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_TX_EVENT_UMTSBand3_SetDefault[]  = {{0}};
const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_TX_EVENT_UMTSBand6_SetDefault[]  = {{0}};
const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_TX_EVENT_UMTSBand9_SetDefault[]  = {{0}};
const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_TX_EVENT_UMTSBand11_SetDefault[] = {{0}};
const UL1_MIPI_EVENT_TABLE_T UMTS_MIPI_TX_EVENT_UMTSBand19_SetDefault[] = {{0}};

const UL1_MIPI_EVENT_TABLE_T* const UMTS_MIPI_TX_EVENT_TABLE_SetDefault[] =
{
   M_UMTS_TX_EVENT(UMTSBandNone,SetDefault),                       /*UMTSUMTSBandNone*/          
   M_UMTS_TX_EVENT(RX_BAND_INDICATOR_0_SetDefault,SetDefault),     /*RX_BAND_INDICATOR_0_SetDefault*/
   M_UMTS_TX_EVENT(RX_BAND_INDICATOR_1_SetDefault,SetDefault),     /*RX_BAND_INDICATOR_1_SetDefault*/
   M_UMTS_TX_EVENT(RX_BAND_INDICATOR_2_SetDefault,SetDefault),     /*RX_BAND_INDICATOR_2_SetDefault*/
   M_UMTS_TX_EVENT(RX_BAND_INDICATOR_3_SetDefault,SetDefault),     /*RX_BAND_INDICATOR_3_SetDefault*/ 
   M_UMTS_TX_EVENT(RX_BAND_INDICATOR_4_SetDefault,SetDefault),     /*RX_BAND_INDICATOR_4_SetDefault*/ 
};

const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_TX_DATA_UMTSBandNone_SetDefault[UL1_MIPI_TX_DATA_NUM] = 
{
   //No.      elm type , port_sel      ,  data_seq  , user id,         { { sub 0 ,addr, data }},{ sub 1 ,addr, data }},{ sub 2 ,addr, data}}, { sub 3, addr, data  }}, { sub 4, addr data  } }},
   { /* 0  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 1  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 2  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 3  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 4  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 5  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 6  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 7  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 8  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 9  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 10 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 11 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 12 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 13 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 14 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 15 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 16 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
   { /* 17 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},     { 0x0 ,{0x0, 0x0}},       { 0x0 ,{0x0, 0x0}} }},
};

const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_TX_DATA_UMTSBand1_SetDefault[UL1_MIPI_TX_DATA_NUM] = 
{
   //No.      elm type , port_sel      ,  data_seq  , user id,         { { sub 0 ,addr, data }},{ sub 1 ,addr, data }},{ sub 2 ,addr, data}}, { sub 3, addr, data}}, { sub 4, addr data  } }},   
   { /* 0  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault   , { { 19224 ,{0x00, 0x64}}, { 19362 ,{0x00, 0x64}}, { 19500 ,{0x00, 0x64}}, { 19638 ,{0x00, 0x64}}, { 19776 ,{0x00, 0x64}}}},
   { /* 1  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault   , { { 19224 ,{0x02, 0xD0}}, { 19362 ,{0x02, 0xD0}}, { 19500 ,{0x02, 0xD0}}, { 19638 ,{0x02, 0xD0}}, { 19776 ,{0x02, 0xD0}}}},
   { /* 2  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault   , { { 19224 ,{0x00, 0x00}}, { 19362 ,{0x00, 0x00}}, { 19500 ,{0x00, 0x00}}, { 19638 ,{0x00, 0x00}}, { 19776 ,{0x00, 0x00}}}},
   { /* 3  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault   , { { 19224 ,{0x01, 0x00}}, { 19362 ,{0x01, 0x00}}, { 19500 ,{0x01, 0x00}}, { 19638 ,{0x01, 0x00}}, { 19776 ,{0x01, 0x00}}}},
   { /* 4  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault   , { { 19224 ,{0x03, 0x00}}, { 19362 ,{0x03, 0x00}}, { 19500 ,{0x03, 0x00}}, { 19638 ,{0x03, 0x00}}, { 19776 ,{0x03, 0x00}}}},
   { /* 5  */ UL1_MIPI_ASM , UL1_MIPI_PORT1, UL1_REG_W  ,    MIPI_USID_ASM0_SetDefault  , { { 19224 ,{0x00, 0x0D}}, { 19362 ,{0x00, 0x0D}}, { 19500 ,{0x00, 0x0D}}, { 19638 ,{0x00, 0x0D}}, { 19776 ,{0x00, 0x0D}}}},
   //{ /* 5  */ UL1_MIPI_ANT , UL1_MIPI_PORT2, UL1_REG_W  ,    MIPI_USID_ANT0_SetDefault  , { { 19224 ,{0x00, 0x01}}, { 19362 ,{0x00, 0x01}}, { 19500 ,{0x00, 0x01}}, { 19638 ,{0x00, 0x01}}, { 19776 ,{0x00, 0x01}}}},
   { /* 6  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 19224 ,{0x0, 0x0}}, 	{ 19362 ,{0x0, 0x0}}, 	{ 19500 ,{0x0, 0x0}}, 	{ 19638 ,{0x0, 0x0}}, 	  { 19776 ,{0x0, 0x0}} }},
   { /* 7  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 19224 ,{0x00, 0x00}}, { 19362 ,{0x00, 0x00}}, { 19500 ,{0x00, 0x00}}, { 19638 ,{0x00, 0x00}}, { 19776 ,{0x00, 0x00}}}},
   { /* 8  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 19224 ,{0x00, 0x00}}, { 19362 ,{0x00, 0x00}}, { 19500 ,{0x00, 0x00}}, { 19638 ,{0x00, 0x00}}, { 19776 ,{0x00, 0x00}}}},
   { /* 9  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 19224 ,{0x00, 0x00}}, { 19362 ,{0x00, 0x00}}, { 19500 ,{0x00, 0x00}}, { 19638 ,{0x00, 0x00}}, { 19776 ,{0x00, 0x00}}}},
   { /* 10 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 19224 ,{0x00, 0x00}}, { 19362 ,{0x00, 0x00}}, { 19500 ,{0x00, 0x00}}, { 19638 ,{0x00, 0x00}}, { 19776 ,{0x00, 0x00}}}},
   { /* 11 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 19224 ,{0x00, 0x00}}, { 19362 ,{0x00, 0x00}}, { 19500 ,{0x00, 0x00}}, { 19638 ,{0x00, 0x00}}, { 19776 ,{0x00, 0x00}}}},
   { /* 12 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 19224 ,{0x00, 0x00}}, { 19362 ,{0x00, 0x00}}, { 19500 ,{0x00, 0x00}}, { 19638 ,{0x00, 0x00}}, { 19776 ,{0x00, 0x00}}}},
   { /* 13 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 19224 ,{0x00, 0x00}}, { 19362 ,{0x00, 0x00}}, { 19500 ,{0x00, 0x00}}, { 19638 ,{0x00, 0x00}}, { 19776 ,{0x00, 0x00}}}},
   { /* 14 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 19224 ,{0x00, 0x00}}, { 19362 ,{0x00, 0x00}}, { 19500 ,{0x00, 0x00}}, { 19638 ,{0x00, 0x00}}, { 19776 ,{0x00, 0x00}}}},
   { /* 15 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 19224 ,{0x00, 0x00}}, { 19362 ,{0x00, 0x00}}, { 19500 ,{0x00, 0x00}}, { 19638 ,{0x00, 0x00}}, { 19776 ,{0x00, 0x00}}}},
   { /* 16 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 19224 ,{0x00, 0x00}}, { 19362 ,{0x00, 0x00}}, { 19500 ,{0x00, 0x00}}, { 19638 ,{0x00, 0x00}}, { 19776 ,{0x00, 0x00}}}},
   { /* 17 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 19224 ,{0x00, 0x00}}, { 19362 ,{0x00, 0x00}}, { 19500 ,{0x00, 0x00}}, { 19638 ,{0x00, 0x00}}, { 19776 ,{0x00, 0x00}}}},
};


const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_TX_DATA_UMTSBand2_SetDefault[UL1_MIPI_TX_DATA_NUM] = 
{
   //No.      elm type , port_sel      ,  data_seq  , user id,         { { sub 0 ,addr, data }},{ sub 1 ,addr, data }},{ sub 2 ,addr, data}}, { sub 3, addr, data}}, { sub 4, addr data  } }},   
   { /* 0  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 18524 ,{0x00, 0x4C}}, { 18662 ,{0x00, 0x4C}}, { 18800 ,{0x00, 0x4C}}, { 18938 ,{0x00, 0x4C}}, { 19076 ,{0x00, 0x4C}} }},
   { /* 1  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 18524 ,{0x02, 0xA0}}, { 18662 ,{0x02, 0xA0}}, { 18800 ,{0x02, 0xA0}}, { 18938 ,{0x02, 0xA0}}, { 19076 ,{0x02, 0xA0}} }},
   { /* 2  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 18524 ,{0x00, 0x00}}, { 18662 ,{0x00, 0x00}}, { 18800 ,{0x00, 0x00}}, { 18938 ,{0x00, 0x00}}, { 19076 ,{0x00, 0x00}} }},
   { /* 3  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 18524 ,{0x01, 0x00}}, { 18662 ,{0x01, 0x00}}, { 18800 ,{0x01, 0x00}}, { 18938 ,{0x01, 0x00}}, { 19076 ,{0x01, 0x00}} }},
   { /* 4  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 18524 ,{0x03, 0x00}}, { 18662 ,{0x03, 0x00}}, { 18800 ,{0x03, 0x00}}, { 18938 ,{0x03, 0x00}}, { 19076 ,{0x03, 0x00}} }},
   { /* 5  */ UL1_MIPI_ASM , UL1_MIPI_PORT1, UL1_REG_W  ,    MIPI_USID_ASM0_SetDefault   , { { 18524 ,{0x00, 0x11}}, { 18662 ,{0x00, 0x11}}, { 18800 ,{0x00, 0x11}}, { 18938 ,{0x00, 0x11}}, { 19076 ,{0x00, 0x11}} }},
   { /* 6  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 18524 ,{0x00, 0x00}}, { 18662 ,{0x00, 0x00}}, { 18800 ,{0x00, 0x00}}, { 18938 ,{0x00, 0x00}}, { 19076 ,{0x00, 0x00}} }},
   { /* 7  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 18524 ,{0x00, 0x00}}, { 18662 ,{0x00, 0x00}}, { 18800 ,{0x00, 0x00}}, { 18938 ,{0x00, 0x00}}, { 19076 ,{0x00, 0x00}} }},
   { /* 8  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 18524 ,{0x00, 0x00}}, { 18662 ,{0x00, 0x00}}, { 18800 ,{0x00, 0x00}}, { 18938 ,{0x00, 0x00}}, { 19076 ,{0x00, 0x00}} }},
   { /* 9  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 18524 ,{0x00, 0x00}}, { 18662 ,{0x00, 0x00}}, { 18800 ,{0x00, 0x00}}, { 18938 ,{0x00, 0x00}}, { 19076 ,{0x00, 0x00}} }},
   { /* 10 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 18524 ,{0x00, 0x00}}, { 18662 ,{0x00, 0x00}}, { 18800 ,{0x00, 0x00}}, { 18938 ,{0x00, 0x00}}, { 19076 ,{0x00, 0x00}} }},
   { /* 11 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 18524 ,{0x00, 0x00}}, { 18662 ,{0x00, 0x00}}, { 18800 ,{0x00, 0x00}}, { 18938 ,{0x00, 0x00}}, { 19076 ,{0x00, 0x00}} }},
   { /* 12 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 18524 ,{0x00, 0x00}}, { 18662 ,{0x00, 0x00}}, { 18800 ,{0x00, 0x00}}, { 18938 ,{0x00, 0x00}}, { 19076 ,{0x00, 0x00}} }},
   { /* 13 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 18524 ,{0x00, 0x00}}, { 18662 ,{0x00, 0x00}}, { 18800 ,{0x00, 0x00}}, { 18938 ,{0x00, 0x00}}, { 19076 ,{0x00, 0x00}} }},
   { /* 14 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 18524 ,{0x00, 0x00}}, { 18662 ,{0x00, 0x00}}, { 18800 ,{0x00, 0x00}}, { 18938 ,{0x00, 0x00}}, { 19076 ,{0x00, 0x00}} }},
   { /* 15 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 18524 ,{0x00, 0x00}}, { 18662 ,{0x00, 0x00}}, { 18800 ,{0x00, 0x00}}, { 18938 ,{0x00, 0x00}}, { 19076 ,{0x00, 0x00}} }},
   { /* 16 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 18524 ,{0x00, 0x00}}, { 18662 ,{0x00, 0x00}}, { 18800 ,{0x00, 0x00}}, { 18938 ,{0x00, 0x00}}, { 19076 ,{0x00, 0x00}} }},
   { /* 17 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 18524 ,{0x00, 0x00}}, { 18662 ,{0x00, 0x00}}, { 18800 ,{0x00, 0x00}}, { 18938 ,{0x00, 0x00}}, { 19076 ,{0x00, 0x00}} }},
};

const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_TX_DATA_UMTSBand4_SetDefault[UL1_MIPI_TX_DATA_NUM] = 
{
   //No.      elm type , port_sel      ,  data_seq  , user id,         { { sub 0 ,addr, data }},{ sub 1 ,addr, data }},{ sub 2 ,addr, data}}, { sub 3, addr, data}}, { sub 4, addr data  } }},   
   { /* 0  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 17124 ,{0x00, 0x5C}}, { 17224 ,{0x00, 0x5C}}, { 17324 ,{0x00, 0x5C}}, { 17425 ,{0x00, 0x5C}}, { 17526 ,{0x00, 0x5C}} }},
   { /* 1  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 17124 ,{0x02, 0xC0}}, { 17224 ,{0x02, 0xC0}}, { 17324 ,{0x02, 0xC0}}, { 17425 ,{0x02, 0xC0}}, { 17526 ,{0x02, 0xC0}} }},
   { /* 2  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 17124 ,{0x00, 0x00}}, { 17224 ,{0x00, 0x00}}, { 17324 ,{0x00, 0x00}}, { 17425 ,{0x00, 0x00}}, { 17526 ,{0x00, 0x00}} }},
   { /* 3  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 17124 ,{0x01, 0x00}}, { 17224 ,{0x01, 0x00}}, { 17324 ,{0x01, 0x00}}, { 17425 ,{0x01, 0x00}}, { 17526 ,{0x01, 0x00}} }},
   { /* 4  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 17124 ,{0x03, 0x00}}, { 17224 ,{0x03, 0x00}}, { 17324 ,{0x03, 0x00}}, { 17425 ,{0x03, 0x00}}, { 17526 ,{0x03, 0x00}} }},
   { /* 5  */ UL1_MIPI_ASM , UL1_MIPI_PORT1, UL1_REG_W  ,    MIPI_USID_ASM0_SetDefault   , { { 17124 ,{0x00, 0x14}}, { 17224 ,{0x00, 0x14}}, { 17324 ,{0x00, 0x14}}, { 17425 ,{0x00, 0x14}}, { 17526 ,{0x00, 0x14}} }},
   //{ /* 5  */ UL1_MIPI_ANT , UL1_MIPI_PORT2, UL1_REG_W  ,    MIPI_USID_ANT0_SetDefault   , { { 17124 ,{0x00, 0x01}}, { 17224 ,{0x00, 0x01}}, { 17324 ,{0x00, 0x01}}, { 17425 ,{0x00, 0x01}}, { 17526 ,{0x00, 0x01}} }},
   { /* 6  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 17124 ,{0x0, 0x0}}, 	{ 17224 ,{0x0, 0x0}}, 	{ 17324 ,{0x0, 0x0}}, 	{ 17425 ,{0x0, 0x0}}, 	  { 17526 ,{0x0, 0x0}} }},
   { /* 7  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 17124 ,{0x00, 0x00}}, { 17224 ,{0x00, 0x00}}, { 17324 ,{0x00, 0x00}}, { 17425 ,{0x00, 0x00}}, { 17526 ,{0x00, 0x00}} }},
   { /* 8  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 17124 ,{0x00, 0x00}}, { 17224 ,{0x00, 0x00}}, { 17324 ,{0x00, 0x00}}, { 17425 ,{0x00, 0x00}}, { 17526 ,{0x00, 0x00}} }},
   { /* 9  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 17124 ,{0x00, 0x00}}, { 17224 ,{0x00, 0x00}}, { 17324 ,{0x00, 0x00}}, { 17425 ,{0x00, 0x00}}, { 17526 ,{0x00, 0x00}} }},
   { /* 10 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 17124 ,{0x00, 0x00}}, { 17224 ,{0x00, 0x00}}, { 17324 ,{0x00, 0x00}}, { 17425 ,{0x00, 0x00}}, { 17526 ,{0x00, 0x00}} }},
   { /* 11 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 17124 ,{0x00, 0x00}}, { 17224 ,{0x00, 0x00}}, { 17324 ,{0x00, 0x00}}, { 17425 ,{0x00, 0x00}}, { 17526 ,{0x00, 0x00}} }},
   { /* 12 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 17124 ,{0x00, 0x00}}, { 17224 ,{0x00, 0x00}}, { 17324 ,{0x00, 0x00}}, { 17425 ,{0x00, 0x00}}, { 17526 ,{0x00, 0x00}} }},
   { /* 13 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 17124 ,{0x00, 0x00}}, { 17224 ,{0x00, 0x00}}, { 17324 ,{0x00, 0x00}}, { 17425 ,{0x00, 0x00}}, { 17526 ,{0x00, 0x00}} }},
   { /* 14 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 17124 ,{0x00, 0x00}}, { 17224 ,{0x00, 0x00}}, { 17324 ,{0x00, 0x00}}, { 17425 ,{0x00, 0x00}}, { 17526 ,{0x00, 0x00}} }},
   { /* 15 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 17124 ,{0x00, 0x00}}, { 17224 ,{0x00, 0x00}}, { 17324 ,{0x00, 0x00}}, { 17425 ,{0x00, 0x00}}, { 17526 ,{0x00, 0x00}} }},
   { /* 16 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 17124 ,{0x00, 0x00}}, { 17224 ,{0x00, 0x00}}, { 17324 ,{0x00, 0x00}}, { 17425 ,{0x00, 0x00}}, { 17526 ,{0x00, 0x00}} }},
   { /* 17 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 17124 ,{0x00, 0x00}}, { 17224 ,{0x00, 0x00}}, { 17324 ,{0x00, 0x00}}, { 17425 ,{0x00, 0x00}}, { 17526 ,{0x00, 0x00}} }},
};

const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_TX_DATA_UMTSBand5_SetDefault[UL1_MIPI_TX_DATA_NUM] = 
{
   //No.      elm type , port_sel      ,  data_seq  , user id,         { { sub 0 ,addr, data }},{ sub 1 ,addr, data }},{ sub 2 ,addr, data}}, { sub 3, addr, data}}, { sub 4, addr data  } }},   
   { /* 0  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 8264 ,{0x00, 0x3C}}, { 8314 ,{0x00, 0x3C}}, { 8365 ,{0x00, 0x3C}}, { 8415 ,{0x00, 0x3C}}, { 8466 ,{0x00, 0x3C}} }},
   { /* 0  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 8264 ,{0x02, 0x50}}, { 8314 ,{0x02, 0x50}}, { 8365 ,{0x02, 0x50}}, { 8415 ,{0x02, 0x50}}, { 8466 ,{0x02, 0x50}} }},
   { /* 1  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 8264 ,{0x00, 0x00}}, { 8314 ,{0x00, 0x00}}, { 8365 ,{0x00, 0x00}}, { 8415 ,{0x00, 0x00}}, { 8466 ,{0x00, 0x00}} }},
   { /* 2  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 8264 ,{0x01, 0x00}}, { 8314 ,{0x01, 0x00}}, { 8365 ,{0x01, 0x00}}, { 8415 ,{0x01, 0x00}}, { 8466 ,{0x01, 0x00}} }},
   { /* 3  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 8264 ,{0x03, 0x00}}, { 8314 ,{0x03, 0x00}}, { 8365 ,{0x03, 0x00}}, { 8415 ,{0x03, 0x00}}, { 8466 ,{0x03, 0x00}} }},
   { /* 4  */ UL1_MIPI_ASM , UL1_MIPI_PORT1, UL1_REG_W  ,    MIPI_USID_ASM0_SetDefault   , { { 8264 ,{0x00, 0x01}}, { 8314 ,{0x00, 0x01}}, { 8365 ,{0x00, 0x01}}, { 8415 ,{0x00, 0x01}}, { 8466 ,{0x00, 0x01}} }},
   //{ /* 5  */ UL1_MIPI_ANT , UL1_MIPI_PORT2, UL1_REG_W  ,    MIPI_USID_ANT0_SetDefault   , { { 8264 ,{0x00, 0x02}}, { 8314 ,{0x00, 0x02}}, { 8365 ,{0x00, 0x02}}, { 8415 ,{0x00, 0x02}}, { 8466 ,{0x00, 0x02}} }},
   { /* 6  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 8264 ,{0x0, 0x0}}, 	{ 8314 ,{0x0, 0x0}}, 	{ 8365 ,{0x0, 0x0}}, 	{ 8415 ,{0x0, 0x0}}, 	  { 8466 ,{0x0, 0x0}} }},
   { /* 7  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8264 ,{0x00, 0x00}}, { 8314 ,{0x00, 0x00}}, { 8365 ,{0x00, 0x00}}, { 8415 ,{0x00, 0x00}}, { 8466 ,{0x00, 0x00}} }},
   { /* 8  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8264 ,{0x00, 0x00}}, { 8314 ,{0x00, 0x00}}, { 8365 ,{0x00, 0x00}}, { 8415 ,{0x00, 0x00}}, { 8466 ,{0x00, 0x00}} }},
   { /* 9  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8264 ,{0x00, 0x00}}, { 8314 ,{0x00, 0x00}}, { 8365 ,{0x00, 0x00}}, { 8415 ,{0x00, 0x00}}, { 8466 ,{0x00, 0x00}} }},
   { /* 10 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8264 ,{0x00, 0x00}}, { 8314 ,{0x00, 0x00}}, { 8365 ,{0x00, 0x00}}, { 8415 ,{0x00, 0x00}}, { 8466 ,{0x00, 0x00}} }},
   { /* 11 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8264 ,{0x00, 0x00}}, { 8314 ,{0x00, 0x00}}, { 8365 ,{0x00, 0x00}}, { 8415 ,{0x00, 0x00}}, { 8466 ,{0x00, 0x00}} }},
   { /* 12 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8264 ,{0x00, 0x00}}, { 8314 ,{0x00, 0x00}}, { 8365 ,{0x00, 0x00}}, { 8415 ,{0x00, 0x00}}, { 8466 ,{0x00, 0x00}} }},
   { /* 13 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8264 ,{0x00, 0x00}}, { 8314 ,{0x00, 0x00}}, { 8365 ,{0x00, 0x00}}, { 8415 ,{0x00, 0x00}}, { 8466 ,{0x00, 0x00}} }},
   { /* 14 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8264 ,{0x00, 0x00}}, { 8314 ,{0x00, 0x00}}, { 8365 ,{0x00, 0x00}}, { 8415 ,{0x00, 0x00}}, { 8466 ,{0x00, 0x00}} }},
   { /* 15 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8264 ,{0x00, 0x00}}, { 8314 ,{0x00, 0x00}}, { 8365 ,{0x00, 0x00}}, { 8415 ,{0x00, 0x00}}, { 8466 ,{0x00, 0x00}} }},
   { /* 16 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8264 ,{0x00, 0x00}}, { 8314 ,{0x00, 0x00}}, { 8365 ,{0x00, 0x00}}, { 8415 ,{0x00, 0x00}}, { 8466 ,{0x00, 0x00}} }},
   { /* 17 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8264 ,{0x00, 0x00}}, { 8314 ,{0x00, 0x00}}, { 8365 ,{0x00, 0x00}}, { 8415 ,{0x00, 0x00}}, { 8466 ,{0x00, 0x00}} }},
};


const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_TX_DATA_UMTSBand8_SetDefault[UL1_MIPI_TX_DATA_NUM] = 
{
   //No.      elm type , port_sel      ,  data_seq  , user id,         { { sub 0 ,addr, data }},{ sub 1 ,addr, data }},{ sub 2 ,addr, data}}, { sub 3, addr, data}}, { sub 4, addr data  } }},   
   { /* 0  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 8824 ,{0x00, 0x74}}, { 8899 ,{0x00, 0x74}}, { 8975 ,{0x00, 0x74}}, { 9050 ,{0x00, 0x74}}, { 9126 ,{0x00, 0x74}} }},
   { /* 0  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 8824 ,{0x02, 0x60}}, { 8899 ,{0x02, 0x60}}, { 8975 ,{0x02, 0x60}}, { 9050 ,{0x02, 0x60}}, { 9126 ,{0x02, 0x60}} }},
   { /* 1  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 8824 ,{0x00, 0x00}}, { 8899 ,{0x00, 0x00}}, { 8975 ,{0x00, 0x00}}, { 9050 ,{0x00, 0x00}}, { 9126 ,{0x00, 0x00}} }},
   { /* 2  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 8824 ,{0x01, 0x00}}, { 8899 ,{0x01, 0x00}}, { 8975 ,{0x01, 0x00}}, { 9050 ,{0x01, 0x00}}, { 9126 ,{0x01, 0x00}} }},
   { /* 3  */ UL1_MIPI_PA  , UL1_MIPI_PORT0, UL1_REG_W  ,    MIPI_USID_PA1_SetDefault    , { { 8824 ,{0x03, 0x00}}, { 8899 ,{0x03, 0x00}}, { 8975 ,{0x03, 0x00}}, { 9050 ,{0x03, 0x00}}, { 9126 ,{0x03, 0x00}} }},
   { /* 4  */ UL1_MIPI_ASM , UL1_MIPI_PORT1, UL1_REG_W  ,    MIPI_USID_ASM0_SetDefault   , { { 8824 ,{0x00, 0x10}}, { 8899 ,{0x00, 0x10}}, { 8975 ,{0x00, 0x10}}, { 9050 ,{0x00, 0x10}}, { 9126 ,{0x00, 0x10}} }},
   //{ /* 5  */ UL1_MIPI_ANT , UL1_MIPI_PORT2, UL1_REG_W  ,    MIPI_USID_ANT0_SetDefault   , { { 8824 ,{0x00, 0x01}}, { 8899 ,{0x00, 0x01}}, { 8975 ,{0x00, 0x01}}, { 9050 ,{0x00, 0x01}}, { 9126 ,{0x00, 0x01}} }},
   { /* 6  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL,  UL1_SEQ_NULL , MIPI_USID_INIT0_SetDefault , { { 8824 ,{0x0, 0x0}}, 	{ 8899 ,{0x0, 0x0}}, 	{ 8975 ,{0x0, 0x0}}, 	{ 9050 ,{0x0, 0x0}}, 	  { 9126 ,{0x0, 0x0}} }},
   { /* 7  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8824 ,{0x00, 0x00}}, { 8899 ,{0x00, 0x00}}, { 8975 ,{0x00, 0x00}}, { 9050 ,{0x00, 0x00}}, { 9126 ,{0x00, 0x00}} }},
   { /* 8  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8824 ,{0x00, 0x00}}, { 8899 ,{0x00, 0x00}}, { 8975 ,{0x00, 0x00}}, { 9050 ,{0x00, 0x00}}, { 9126 ,{0x00, 0x00}} }},
   { /* 9  */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8824 ,{0x00, 0x00}}, { 8899 ,{0x00, 0x00}}, { 8975 ,{0x00, 0x00}}, { 9050 ,{0x00, 0x00}}, { 9126 ,{0x00, 0x00}} }},
   { /* 10 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8824 ,{0x00, 0x00}}, { 8899 ,{0x00, 0x00}}, { 8975 ,{0x00, 0x00}}, { 9050 ,{0x00, 0x00}}, { 9126 ,{0x00, 0x00}} }},
   { /* 11 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8824 ,{0x00, 0x00}}, { 8899 ,{0x00, 0x00}}, { 8975 ,{0x00, 0x00}}, { 9050 ,{0x00, 0x00}}, { 9126 ,{0x00, 0x00}} }},
   { /* 12 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8824 ,{0x00, 0x00}}, { 8899 ,{0x00, 0x00}}, { 8975 ,{0x00, 0x00}}, { 9050 ,{0x00, 0x00}}, { 9126 ,{0x00, 0x00}} }},
   { /* 13 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8824 ,{0x00, 0x00}}, { 8899 ,{0x00, 0x00}}, { 8975 ,{0x00, 0x00}}, { 9050 ,{0x00, 0x00}}, { 9126 ,{0x00, 0x00}} }},
   { /* 14 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8824 ,{0x00, 0x00}}, { 8899 ,{0x00, 0x00}}, { 8975 ,{0x00, 0x00}}, { 9050 ,{0x00, 0x00}}, { 9126 ,{0x00, 0x00}} }},
   { /* 15 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8824 ,{0x00, 0x00}}, { 8899 ,{0x00, 0x00}}, { 8975 ,{0x00, 0x00}}, { 9050 ,{0x00, 0x00}}, { 9126 ,{0x00, 0x00}} }},
   { /* 16 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8824 ,{0x00, 0x00}}, { 8899 ,{0x00, 0x00}}, { 8975 ,{0x00, 0x00}}, { 9050 ,{0x00, 0x00}}, { 9126 ,{0x00, 0x00}} }},
   { /* 17 */ UL1_MIPI_NULL, UL1_MIPI_DATA_NULL, UL1_SEQ_NULL,   MIPI_USID_INIT0_SetDefault , { { 8824 ,{0x00, 0x00}}, { 8899 ,{0x00, 0x00}}, { 8975 ,{0x00, 0x00}}, { 9050 ,{0x00, 0x00}}, { 9126 ,{0x00, 0x00}} }},
};

const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_TX_DATA_UMTSBand3_SetDefault[]  = {{0}};
const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_TX_DATA_UMTSBand6_SetDefault[]  = {{0}};
const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_TX_DATA_UMTSBand9_SetDefault[]  = {{0}};
const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_TX_DATA_UMTSBand11_SetDefault[] = {{0}};
const UL1_MIPI_DATA_SUBBAND_TABLE_T UMTS_MIPI_TX_DATA_UMTSBand19_SetDefault[] = {{0}};

const UL1_MIPI_DATA_SUBBAND_TABLE_T* const UMTS_MIPI_TX_DATA_TABLE_SetDefault[] = 
{
   M_UMTS_TX_DATA(UMTSBandNone,SetDefault),                     /*UMTSUMTSBandNone*/
   M_UMTS_TX_DATA(RX_BAND_INDICATOR_0_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_0_SetDefault*/
   M_UMTS_TX_DATA(RX_BAND_INDICATOR_1_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_1_SetDefault*/
   M_UMTS_TX_DATA(RX_BAND_INDICATOR_2_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_2_SetDefault*/
   M_UMTS_TX_DATA(RX_BAND_INDICATOR_3_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_3_SetDefault*/
   M_UMTS_TX_DATA(RX_BAND_INDICATOR_4_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_4_SetDefault*/
};

const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_TPC_UMTSBandNone_SetDefault = {{{0}}};

const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_TPC_UMTSBand1_SetDefault = 
{
   /* Event */
  {
   /* No.           elm type , data idx       , evt_type       , evt_offset     */
   /*                           { start, stop },                  ( us )         */
    { /* 0, Prf_7  */ UL1_MIPI_PA, { 0    , 2     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },  /*highest power*/
    { /* 1, Prf_6  */ UL1_MIPI_PA, { 3    , 5     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
    { /* 2, Prf_5  */ UL1_MIPI_PA, { 6    , 8     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
    { /* 3, Prf_4  */ UL1_MIPI_PA, { 9    , 11    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
    { /* 4, Prf_3  */ UL1_MIPI_PA, { 12   , 14    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
    { /* 5, Prf_2  */ UL1_MIPI_PA, { 15   , 17    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
    { /* 6, Prf_1  */ UL1_MIPI_PA, { 18   , 20    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
    { /* 7, Prf_0  */ UL1_MIPI_PA, { 21   , 23    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },  /*lowest power*/
  },

  /* Data */
  {
   //elm type  , port_sel       , data_seq, user id,         {{sub 0, addr, data}}, {{sub 1, addr, data}}, {{sub 2, addr, data} , {{sub 3, addr, data}}, {{sub 4, addr, data}
#if defined(USE_VC7643_12) //xjl 20180607
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x64}}, {19362, {0x00, 0x64}}, {19500, {0x00, 0x64}}, {19638, {0x00, 0x64}}, {19776, {0x00, 0x64}}}},  /*L7, TPC IDX 0*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x44}}, {19362, {0x01, 0x44}}, {19500, {0x01, 0x44}}, {19638, {0x01, 0x44}}, {19776, {0x01, 0x44}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x88}}, {19362, {0x03, 0x88}}, {19500, {0x03, 0x88}}, {19638, {0x03, 0x88}}, {19776, {0x03, 0x88}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x64}}, {19362, {0x00, 0x64}}, {19500, {0x00, 0x64}}, {19638, {0x00, 0x64}}, {19776, {0x00, 0x64}}}},  /*L6, TPC IDX 2*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x44}}, {19362, {0x01, 0x44}}, {19500, {0x01, 0x44}}, {19638, {0x01, 0x44}}, {19776, {0x01, 0x44}}}}, 
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x88}}, {19362, {0x03, 0x88}}, {19500, {0x03, 0x88}}, {19638, {0x03, 0x88}}, {19776, {0x03, 0x88}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x64}}, {19362, {0x00, 0x64}}, {19500, {0x00, 0x64}}, {19638, {0x00, 0x64}}, {19776, {0x00, 0x64}}}},  /*L5, TPC IDX 4*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x33}}, {19362, {0x01, 0x33}}, {19500, {0x01, 0x33}}, {19638, {0x01, 0x33}}, {19776, {0x01, 0x33}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x88}}, {19362, {0x03, 0x88}}, {19500, {0x03, 0x88}}, {19638, {0x03, 0x88}}, {19776, {0x03, 0x88}}}}, 
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x64}}, {19362, {0x00, 0x64}}, {19500, {0x00, 0x64}}, {19638, {0x00, 0x64}}, {19776, {0x00, 0x64}}}},  /*L4, TPC IDX 6*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x33}}, {19362, {0x01, 0x33}}, {19500, {0x01, 0x33}}, {19638, {0x01, 0x33}}, {19776, {0x01, 0x33}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x88}}, {19362, {0x03, 0x88}}, {19500, {0x03, 0x88}}, {19638, {0x03, 0x00}}, {19776, {0x03, 0x88}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x66}}, {19362, {0x00, 0x66}}, {19500, {0x00, 0x66}}, {19638, {0x00, 0x66}}, {19776, {0x00, 0x66}}}},  /*L3, TPC IDX 9*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x32}}, {19362, {0x01, 0x32}}, {19500, {0x01, 0x32}}, {19638, {0x01, 0x32}}, {19776, {0x01, 0x32}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x80}}, {19362, {0x03, 0x80}}, {19500, {0x03, 0x80}}, {19638, {0x03, 0x80}}, {19776, {0x03, 0x80}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x66}}, {19362, {0x00, 0x66}}, {19500, {0x00, 0x66}}, {19638, {0x00, 0x66}}, {19776, {0x00, 0x66}}}},  /*L2, TPC IDX 15, Hyst1*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x32}}, {19362, {0x01, 0x32}}, {19500, {0x01, 0x32}}, {19638, {0x01, 0x32}}, {19776, {0x01, 0x32}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x80}}, {19362, {0x03, 0x80}}, {19500, {0x03, 0x80}}, {19638, {0x03, 0x80}}, {19776, {0x03, 0x80}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x66}}, {19362, {0x00, 0x66}}, {19500, {0x00, 0x66}}, {19638, {0x00, 0x66}}, {19776, {0x00, 0x66}}}},  /*L1, TPC IDX 18*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x21}}, {19362, {0x01, 0x21}}, {19500, {0x01, 0x21}}, {19638, {0x01, 0x21}}, {19776, {0x01, 0x21}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x80}}, {19362, {0x03, 0x80}}, {19500, {0x03, 0x80}}, {19638, {0x03, 0x80}}, {19776, {0x03, 0x80}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x66}}, {19362, {0x00, 0x66}}, {19500, {0x00, 0x66}}, {19638, {0x00, 0x66}}, {19776, {0x00, 0x66}}}},  /*L0, TPC IDX 25, Hyst2*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x11}}, {19362, {0x01, 0x11}}, {19500, {0x01, 0x11}}, {19638, {0x01, 0x11}}, {19776, {0x01, 0x11}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x80}}, {19362, {0x03, 0x80}}, {19500, {0x03, 0x80}}, {19638, {0x03, 0x80}}, {19776, {0x03, 0x80}}}},
#else
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x64}}, {19362, {0x00, 0x64}}, {19500, {0x00, 0x64}}, {19638, {0x00, 0x64}}, {19776, {0x00, 0x64}}}},  /*L7, TPC IDX 0*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x77}}, {19362, {0x01, 0x77}}, {19500, {0x01, 0x77}}, {19638, {0x01, 0x77}}, {19776, {0x01, 0x77}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x88}}, {19362, {0x03, 0x88}}, {19500, {0x03, 0x88}}, {19638, {0x03, 0x88}}, {19776, {0x03, 0x88}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x64}}, {19362, {0x00, 0x64}}, {19500, {0x00, 0x64}}, {19638, {0x00, 0x64}}, {19776, {0x00, 0x64}}}},  /*L6, TPC IDX 2*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x65}}, {19362, {0x01, 0x65}}, {19500, {0x01, 0x65}}, {19638, {0x01, 0x65}}, {19776, {0x01, 0x65}}}}, 
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x88}}, {19362, {0x03, 0x88}}, {19500, {0x03, 0x88}}, {19638, {0x03, 0x88}}, {19776, {0x03, 0x88}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x64}}, {19362, {0x00, 0x64}}, {19500, {0x00, 0x64}}, {19638, {0x00, 0x64}}, {19776, {0x00, 0x64}}}},  /*L5, TPC IDX 4*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x35}}, {19362, {0x01, 0x35}}, {19500, {0x01, 0x35}}, {19638, {0x01, 0x35}}, {19776, {0x01, 0x35}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x88}}, {19362, {0x03, 0x88}}, {19500, {0x03, 0x88}}, {19638, {0x03, 0x88}}, {19776, {0x03, 0x88}}}}, 
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x64}}, {19362, {0x00, 0x64}}, {19500, {0x00, 0x64}}, {19638, {0x00, 0x64}}, {19776, {0x00, 0x64}}}},  /*L4, TPC IDX 6*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x34}}, {19362, {0x01, 0x34}}, {19500, {0x01, 0x34}}, {19638, {0x01, 0x34}}, {19776, {0x01, 0x34}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x88}}, {19362, {0x03, 0x88}}, {19500, {0x03, 0x88}}, {19638, {0x03, 0x00}}, {19776, {0x03, 0x88}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x66}}, {19362, {0x00, 0x66}}, {19500, {0x00, 0x66}}, {19638, {0x00, 0x66}}, {19776, {0x00, 0x66}}}},  /*L3, TPC IDX 9*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x24}}, {19362, {0x01, 0x24}}, {19500, {0x01, 0x24}}, {19638, {0x01, 0x24}}, {19776, {0x01, 0x24}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x80}}, {19362, {0x03, 0x80}}, {19500, {0x03, 0x80}}, {19638, {0x03, 0x80}}, {19776, {0x03, 0x80}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x66}}, {19362, {0x00, 0x66}}, {19500, {0x00, 0x66}}, {19638, {0x00, 0x66}}, {19776, {0x00, 0x66}}}},  /*L2, TPC IDX 15, Hyst1*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x14}}, {19362, {0x01, 0x14}}, {19500, {0x01, 0x14}}, {19638, {0x01, 0x14}}, {19776, {0x01, 0x14}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x80}}, {19362, {0x03, 0x80}}, {19500, {0x03, 0x80}}, {19638, {0x03, 0x80}}, {19776, {0x03, 0x80}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x66}}, {19362, {0x00, 0x66}}, {19500, {0x00, 0x66}}, {19638, {0x00, 0x66}}, {19776, {0x00, 0x66}}}},  /*L1, TPC IDX 18*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x13}}, {19362, {0x01, 0x13}}, {19500, {0x01, 0x13}}, {19638, {0x01, 0x13}}, {19776, {0x01, 0x13}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x80}}, {19362, {0x03, 0x80}}, {19500, {0x03, 0x80}}, {19638, {0x03, 0x80}}, {19776, {0x03, 0x80}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x66}}, {19362, {0x00, 0x66}}, {19500, {0x00, 0x66}}, {19638, {0x00, 0x66}}, {19776, {0x00, 0x66}}}},  /*L0, TPC IDX 25, Hyst2*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x12}}, {19362, {0x01, 0x12}}, {19500, {0x01, 0x12}}, {19638, {0x01, 0x12}}, {19776, {0x01, 0x12}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x80}}, {19362, {0x03, 0x80}}, {19500, {0x03, 0x80}}, {19638, {0x03, 0x80}}, {19776, {0x03, 0x80}}}},
#endif
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}},
    {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{19224, {0x00, 0x00}}, {19362, {0x00, 0x00}}, {19500, {0x00, 0x00}}, {19638, {0x00, 0x00}}, {19776, {0x00, 0x00}}}} 
  }
};


const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_TPC_UMTSBand2_SetDefault = 
{
   /* Event */
   {
    /* No.           elm type , data idx       , evt_type       , evt_offset     */
    /*                           { start, stop },                  ( us )         */
     { /* 0, Prf_7  */ UL1_MIPI_PA, { 0    , 2     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },  /*highest power*/
     { /* 1, Prf_6  */ UL1_MIPI_PA, { 3    , 5     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 2, Prf_5  */ UL1_MIPI_PA, { 6    , 8     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 3, Prf_4  */ UL1_MIPI_PA, { 9    , 11    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 4, Prf_3  */ UL1_MIPI_PA, { 12   , 14    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 5, Prf_2  */ UL1_MIPI_PA, { 15   , 17    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 6, Prf_1  */ UL1_MIPI_PA, { 18   , 20    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 7, Prf_0  */ UL1_MIPI_PA, { 21   , 23    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },  /*lowest power*/
   },
   
   /* Data */
   {
      //elm type  , port_sel     , data_seq, user id,         {{sub 0, addr, data}}, {{sub 1, addr, data}}, {{sub 2, addr, data} , {{sub 3, addr, data}}, {{sub 4, addr, data}  
#if defined(USE_VC7643_12) //xjl 20180607
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4C}}, {18662, {0x00, 0x4C}}, {18800, {0x00, 0x4C}}, {18938, {0x00, 0x4C}}, {19076, {0x00, 0x4C}} }},  /*L7, TPC IDX 0*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x44}}, {18662, {0x01, 0x44}}, {18800, {0x01, 0x44}}, {18938, {0x01, 0x44}}, {19076, {0x01, 0x44}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4C}}, {18662, {0x00, 0x4C}}, {18800, {0x00, 0x4C}}, {18938, {0x00, 0x4C}}, {19076, {0x00, 0x4C}} }},  /*L6, TPC IDX 2*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x44}}, {18662, {0x01, 0x44}}, {18800, {0x01, 0x44}}, {18938, {0x01, 0x44}}, {19076, {0x01, 0x44}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4C}}, {18662, {0x00, 0x4C}}, {18800, {0x00, 0x4C}}, {18938, {0x00, 0x4C}}, {19076, {0x00, 0x4C}} }},  /*L5, TPC IDX 4*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x33}}, {18662, {0x01, 0x33}}, {18800, {0x01, 0x33}}, {18938, {0x01, 0x33}}, {19076, {0x01, 0x33}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4E}}, {18662, {0x00, 0x4E}}, {18800, {0x00, 0x4E}}, {18938, {0x00, 0x4E}}, {19076, {0x00, 0x4E}} }},  /*L4, TPC IDX 6*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x33}}, {18662, {0x01, 0x33}}, {18800, {0x01, 0x33}}, {18938, {0x01, 0x33}}, {19076, {0x01, 0x33}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4E}}, {18662, {0x00, 0x4E}}, {18800, {0x00, 0x4E}}, {18938, {0x00, 0x4E}}, {19076, {0x00, 0x4E}} }},  /*L3, TPC IDX 9*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x32}}, {18662, {0x01, 0x32}}, {18800, {0x01, 0x32}}, {18938, {0x01, 0x32}}, {19076, {0x01, 0x32}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4E}}, {18662, {0x00, 0x4E}}, {18800, {0x00, 0x4E}}, {18938, {0x00, 0x4E}}, {19076, {0x00, 0x4E}} }},  /*L2, TPC IDX 15, Hyst1*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x32}}, {18662, {0x01, 0x32}}, {18800, {0x01, 0x32}}, {18938, {0x01, 0x32}}, {19076, {0x01, 0x32}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x80}}, {18662, {0x03, 0x80}}, {18800, {0x03, 0x80}}, {18938, {0x03, 0x80}}, {19076, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4E}}, {18662, {0x00, 0x4E}}, {18800, {0x00, 0x4E}}, {18938, {0x00, 0x4E}}, {19076, {0x00, 0x4E}} }},  /*L1, TPC IDX 18*/       
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x21}}, {18662, {0x01, 0x21}}, {18800, {0x01, 0x21}}, {18938, {0x01, 0x21}}, {19076, {0x01, 0x21}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x80}}, {18662, {0x03, 0x80}}, {18800, {0x03, 0x80}}, {18938, {0x03, 0x80}}, {19076, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4E}}, {18662, {0x00, 0x4E}}, {18800, {0x00, 0x4E}}, {18938, {0x00, 0x4E}}, {19076, {0x00, 0x4E}} }},  /*L0, TPC IDX 25, Hyst2*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x11}}, {18662, {0x01, 0x11}}, {18800, {0x01, 0x11}}, {18938, {0x01, 0x11}}, {19076, {0x01, 0x11}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x80}}, {18662, {0x03, 0x80}}, {18800, {0x03, 0x80}}, {18938, {0x03, 0x80}}, {19076, {0x03, 0x80}} }},  
#else 
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4C}}, {18662, {0x00, 0x4C}}, {18800, {0x00, 0x4C}}, {18938, {0x00, 0x4C}}, {19076, {0x00, 0x4C}} }},  /*L7, TPC IDX 0*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x76}}, {18662, {0x01, 0x76}}, {18800, {0x01, 0x76}}, {18938, {0x01, 0x76}}, {19076, {0x01, 0x76}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4C}}, {18662, {0x00, 0x4C}}, {18800, {0x00, 0x4C}}, {18938, {0x00, 0x4C}}, {19076, {0x00, 0x4C}} }},  /*L6, TPC IDX 2*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x65}}, {18662, {0x01, 0x65}}, {18800, {0x01, 0x65}}, {18938, {0x01, 0x65}}, {19076, {0x01, 0x65}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4C}}, {18662, {0x00, 0x4C}}, {18800, {0x00, 0x4C}}, {18938, {0x00, 0x4C}}, {19076, {0x00, 0x4C}} }},  /*L5, TPC IDX 4*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x44}}, {18662, {0x01, 0x44}}, {18800, {0x01, 0x44}}, {18938, {0x01, 0x44}}, {19076, {0x01, 0x44}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4C}}, {18662, {0x00, 0x4C}}, {18800, {0x00, 0x4C}}, {18938, {0x00, 0x4C}}, {19076, {0x00, 0x4C}} }},  /*L4, TPC IDX 6*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x34}}, {18662, {0x01, 0x34}}, {18800, {0x01, 0x34}}, {18938, {0x01, 0x34}}, {19076, {0x01, 0x34}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4E}}, {18662, {0x00, 0x4E}}, {18800, {0x00, 0x4E}}, {18938, {0x00, 0x4E}}, {19076, {0x00, 0x4E}} }},  /*L3, TPC IDX 9*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x24}}, {18662, {0x01, 0x24}}, {18800, {0x01, 0x24}}, {18938, {0x01, 0x24}}, {19076, {0x01, 0x24}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4E}}, {18662, {0x00, 0x4E}}, {18800, {0x00, 0x4E}}, {18938, {0x00, 0x4E}}, {19076, {0x00, 0x4E}} }},  /*L2, TPC IDX 15, Hyst1*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x14}}, {18662, {0x01, 0x14}}, {18800, {0x01, 0x14}}, {18938, {0x01, 0x14}}, {19076, {0x01, 0x14}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x80}}, {18662, {0x03, 0x80}}, {18800, {0x03, 0x80}}, {18938, {0x03, 0x80}}, {19076, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4E}}, {18662, {0x00, 0x4E}}, {18800, {0x00, 0x4E}}, {18938, {0x00, 0x4E}}, {19076, {0x00, 0x4E}} }},  /*L1, TPC IDX 18*/       
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x13}}, {18662, {0x01, 0x13}}, {18800, {0x01, 0x13}}, {18938, {0x01, 0x13}}, {19076, {0x01, 0x13}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x80}}, {18662, {0x03, 0x80}}, {18800, {0x03, 0x80}}, {18938, {0x03, 0x80}}, {19076, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x4E}}, {18662, {0x00, 0x4E}}, {18800, {0x00, 0x4E}}, {18938, {0x00, 0x4E}}, {19076, {0x00, 0x4E}} }},  /*L0, TPC IDX 25, Hyst2*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x12}}, {18662, {0x01, 0x12}}, {18800, {0x01, 0x12}}, {18938, {0x01, 0x12}}, {19076, {0x01, 0x12}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x80}}, {18662, {0x03, 0x80}}, {18800, {0x03, 0x80}}, {18938, {0x03, 0x80}}, {19076, {0x03, 0x80}} }},    
#endif                     
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{18524, {0x00, 0x00}}, {18662, {0x00, 0x00}}, {18800, {0x00, 0x00}}, {18938, {0x00, 0x00}}, {19076, {0x00, 0x00}} }}
   }
};

const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_TPC_UMTSBand4_SetDefault = 
{
   /* Event */
   {
    /* No.           elm type , data idx       , evt_type       , evt_offset     */
    /*                           { start, stop },                  ( us )         */
     { /* 0, Prf_7  */ UL1_MIPI_PA, { 0    , 2     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },  /*highest power*/
     { /* 1, Prf_6  */ UL1_MIPI_PA, { 3    , 5     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 2, Prf_5  */ UL1_MIPI_PA, { 6    , 8     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 3, Prf_4  */ UL1_MIPI_PA, { 9    , 11    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 4, Prf_3  */ UL1_MIPI_PA, { 12   , 14    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 5, Prf_2  */ UL1_MIPI_PA, { 15   , 17    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 6, Prf_1  */ UL1_MIPI_PA, { 18   , 20    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 7, Prf_0  */ UL1_MIPI_PA, { 21   , 23    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },  /*lowest power*/
   },
   
   /* Data */
   {                                                                                                                                                                               
      //elm type  , port_sel     , data_seq, user id,         {{sub 0, addr, data}}, {{sub 1, addr, data}}, {{sub 2, addr, data} , {{sub 3, addr, data}}, {{sub 4, addr, data}  
#if defined(USE_VC7643_12) //xjl 20180607
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5C}}, {17224, {0x00, 0x5C}}, {17324, {0x00, 0x5C}}, {17425, {0x00, 0x5C}}, {17526, {0x00, 0x5C}} }},  /*L7, TPC IDX 0*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x44}}, {17224, {0x01, 0x44}}, {17324, {0x01, 0x44}}, {17425, {0x01, 0x44}}, {17526, {0x01, 0x44}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x89}}, {17224, {0x03, 0x89}}, {17324, {0x03, 0x89}}, {17425, {0x03, 0x89}}, {17526, {0x03, 0x89}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5C}}, {17224, {0x00, 0x5C}}, {17324, {0x00, 0x5C}}, {17425, {0x00, 0x5C}}, {17526, {0x00, 0x5C}} }},  /*L6, TPC IDX 2*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x44}}, {17224, {0x01, 0x44}}, {17324, {0x01, 0x44}}, {17425, {0x01, 0x44}}, {17526, {0x01, 0x44}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x89}}, {17224, {0x03, 0x89}}, {17324, {0x03, 0x89}}, {17425, {0x03, 0x89}}, {17526, {0x03, 0x89}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5C}}, {17224, {0x00, 0x5C}}, {17324, {0x00, 0x5C}}, {17425, {0x00, 0x5C}}, {17526, {0x00, 0x5C}} }},  /*L5, TPC IDX 4*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x33}}, {17224, {0x01, 0x33}}, {17324, {0x01, 0x33}}, {17425, {0x01, 0x33}}, {17526, {0x01, 0x33}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x89}}, {17224, {0x03, 0x89}}, {17324, {0x03, 0x89}}, {17425, {0x03, 0x89}}, {17526, {0x03, 0x89}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5C}}, {17224, {0x00, 0x5C}}, {17324, {0x00, 0x5C}}, {17425, {0x00, 0x5C}}, {17526, {0x00, 0x5C}} }},  /*L4, TPC IDX 6*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x33}}, {17224, {0x01, 0x33}}, {17324, {0x01, 0x33}}, {17425, {0x01, 0x33}}, {17526, {0x01, 0x33}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x89}}, {17224, {0x03, 0x89}}, {17324, {0x03, 0x89}}, {17425, {0x03, 0x89}}, {17526, {0x03, 0x89}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5E}}, {17224, {0x00, 0x5E}}, {17324, {0x00, 0x5E}}, {17425, {0x00, 0x5E}}, {17526, {0x00, 0x5E}} }},  /*L3, TPC IDX 9*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x32}}, {17224, {0x01, 0x32}}, {17324, {0x01, 0x32}}, {17425, {0x01, 0x32}}, {17526, {0x01, 0x32}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x80}}, {17224, {0x03, 0x80}}, {17324, {0x03, 0x80}}, {17425, {0x03, 0x80}}, {17526, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5E}}, {17224, {0x00, 0x5E}}, {17324, {0x00, 0x5E}}, {17425, {0x00, 0x5E}}, {17526, {0x00, 0x5E}} }},  /*L2, TPC IDX 15, Hyst1*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x32}}, {17224, {0x01, 0x32}}, {17324, {0x01, 0x32}}, {17425, {0x01, 0x32}}, {17526, {0x01, 0x32}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x80}}, {17224, {0x03, 0x80}}, {17324, {0x03, 0x80}}, {17425, {0x03, 0x80}}, {17526, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5E}}, {17224, {0x00, 0x5E}}, {17324, {0x00, 0x5E}}, {17425, {0x00, 0x5E}}, {17526, {0x00, 0x5E}} }},  /*L1, TPC IDX 18*/       
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x21}}, {17224, {0x01, 0x21}}, {17324, {0x01, 0x21}}, {17425, {0x01, 0x21}}, {17526, {0x01, 0x21}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x80}}, {17224, {0x03, 0x80}}, {17324, {0x03, 0x80}}, {17425, {0x03, 0x80}}, {17526, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5E}}, {17224, {0x00, 0x5E}}, {17324, {0x00, 0x5E}}, {17425, {0x00, 0x5E}}, {17526, {0x00, 0x5E}} }},  /*L0, TPC IDX 25, Hyst2*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x11}}, {17224, {0x01, 0x11}}, {17324, {0x01, 0x11}}, {17425, {0x01, 0x11}}, {17526, {0x01, 0x11}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x80}}, {17224, {0x03, 0x80}}, {17324, {0x03, 0x80}}, {17425, {0x03, 0x80}}, {17526, {0x03, 0x80}} }},
#else   
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5C}}, {17224, {0x00, 0x5C}}, {17324, {0x00, 0x5C}}, {17425, {0x00, 0x5C}}, {17526, {0x00, 0x5C}} }},  /*L7, TPC IDX 0*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0xA7}}, {17224, {0x01, 0xA7}}, {17324, {0x01, 0xA7}}, {17425, {0x01, 0xA7}}, {17526, {0x01, 0xA7}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x89}}, {17224, {0x03, 0x89}}, {17324, {0x03, 0x89}}, {17425, {0x03, 0x89}}, {17526, {0x03, 0x89}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5C}}, {17224, {0x00, 0x5C}}, {17324, {0x00, 0x5C}}, {17425, {0x00, 0x5C}}, {17526, {0x00, 0x5C}} }},  /*L6, TPC IDX 2*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x76}}, {17224, {0x01, 0x76}}, {17324, {0x01, 0x76}}, {17425, {0x01, 0x76}}, {17526, {0x01, 0x76}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x89}}, {17224, {0x03, 0x89}}, {17324, {0x03, 0x89}}, {17425, {0x03, 0x89}}, {17526, {0x03, 0x89}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5C}}, {17224, {0x00, 0x5C}}, {17324, {0x00, 0x5C}}, {17425, {0x00, 0x5C}}, {17526, {0x00, 0x5C}} }},  /*L5, TPC IDX 4*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x55}}, {17224, {0x01, 0x55}}, {17324, {0x01, 0x55}}, {17425, {0x01, 0x55}}, {17526, {0x01, 0x55}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x89}}, {17224, {0x03, 0x89}}, {17324, {0x03, 0x89}}, {17425, {0x03, 0x89}}, {17526, {0x03, 0x89}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5C}}, {17224, {0x00, 0x5C}}, {17324, {0x00, 0x5C}}, {17425, {0x00, 0x5C}}, {17526, {0x00, 0x5C}} }},  /*L4, TPC IDX 6*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x45}}, {17224, {0x01, 0x45}}, {17324, {0x01, 0x45}}, {17425, {0x01, 0x45}}, {17526, {0x01, 0x45}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x89}}, {17224, {0x03, 0x89}}, {17324, {0x03, 0x89}}, {17425, {0x03, 0x89}}, {17526, {0x03, 0x89}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5E}}, {17224, {0x00, 0x5E}}, {17324, {0x00, 0x5E}}, {17425, {0x00, 0x5E}}, {17526, {0x00, 0x5E}} }},  /*L3, TPC IDX 9*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x34}}, {17224, {0x01, 0x34}}, {17324, {0x01, 0x34}}, {17425, {0x01, 0x34}}, {17526, {0x01, 0x34}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x80}}, {17224, {0x03, 0x80}}, {17324, {0x03, 0x80}}, {17425, {0x03, 0x80}}, {17526, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5E}}, {17224, {0x00, 0x5E}}, {17324, {0x00, 0x5E}}, {17425, {0x00, 0x5E}}, {17526, {0x00, 0x5E}} }},  /*L2, TPC IDX 15, Hyst1*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x24}}, {17224, {0x01, 0x24}}, {17324, {0x01, 0x24}}, {17425, {0x01, 0x24}}, {17526, {0x01, 0x24}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x80}}, {17224, {0x03, 0x80}}, {17324, {0x03, 0x80}}, {17425, {0x03, 0x80}}, {17526, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5E}}, {17224, {0x00, 0x5E}}, {17324, {0x00, 0x5E}}, {17425, {0x00, 0x5E}}, {17526, {0x00, 0x5E}} }},  /*L1, TPC IDX 18*/       
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x14}}, {17224, {0x01, 0x14}}, {17324, {0x01, 0x14}}, {17425, {0x01, 0x14}}, {17526, {0x01, 0x14}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x80}}, {17224, {0x03, 0x80}}, {17324, {0x03, 0x80}}, {17425, {0x03, 0x80}}, {17526, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x5E}}, {17224, {0x00, 0x5E}}, {17324, {0x00, 0x5E}}, {17425, {0x00, 0x5E}}, {17526, {0x00, 0x5E}} }},  /*L0, TPC IDX 25, Hyst2*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x13}}, {17224, {0x01, 0x13}}, {17324, {0x01, 0x13}}, {17425, {0x01, 0x13}}, {17526, {0x01, 0x13}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x80}}, {17224, {0x03, 0x80}}, {17324, {0x03, 0x80}}, {17425, {0x03, 0x80}}, {17526, {0x03, 0x80}} }},
#endif
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},   
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL ,MIPI_USID_INIT0_SetDefault, {{17124, {0x00, 0x00}}, {17224, {0x00, 0x00}}, {17324, {0x00, 0x00}}, {17425, {0x00, 0x00}}, {17526, {0x00, 0x00}} }}                            
   }                                                                            
};


const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_TPC_UMTSBand5_SetDefault = 
{
   /* Event */
   {
    /* No.           elm type , data idx       , evt_type       , evt_offset     */
    /*                           { start, stop },                  ( us )         */
     { /* 0, Prf_7  */ UL1_MIPI_PA, { 0    , 2     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },  /*highest power*/
     { /* 1, Prf_6  */ UL1_MIPI_PA, { 3    , 5     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 2, Prf_5  */ UL1_MIPI_PA, { 6    , 8     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 3, Prf_4  */ UL1_MIPI_PA, { 9    , 11    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 4, Prf_3  */ UL1_MIPI_PA, { 12   , 14    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 5, Prf_2  */ UL1_MIPI_PA, { 15   , 17    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 6, Prf_1  */ UL1_MIPI_PA, { 18   , 20    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 7, Prf_0  */ UL1_MIPI_PA, { 21   , 23    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },  /*lowest power*/
   },
   
   /* Data */
   {                                                                                                                                                                               
      //elm type  , port_sel     , data_seq, user id,         {{sub 0, addr, data}}, {{sub 1, addr, data}}, {{sub 2, addr, data} , {{sub 3, addr, data}}, {{sub 4, addr, data}  
#if defined(USE_VC7643_12) //xjl 20180607
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3C}}, {8314, {0x00, 0x3C}}, {8365, {0x00, 0x3C}}, {8415, {0x00, 0x3C}}, {8466, {0x00, 0x3C}} }},  /*L7, TPC IDX 0*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x55}}, {8314, {0x01, 0x55}}, {8365, {0x01, 0x55}}, {8415, {0x01, 0x55}}, {8466, {0x01, 0x55}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3C}}, {8314, {0x00, 0x3C}}, {8365, {0x00, 0x3C}}, {8415, {0x00, 0x3C}}, {8466, {0x00, 0x3C}} }},  /*L6, TPC IDX 2*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x55}}, {8314, {0x01, 0x55}}, {8365, {0x01, 0x55}}, {8415, {0x01, 0x55}}, {8466, {0x01, 0x55}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3C}}, {8314, {0x00, 0x3C}}, {8365, {0x00, 0x3C}}, {8415, {0x00, 0x3C}}, {8466, {0x00, 0x3C}} }},  /*L5, TPC IDX 4*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x44}}, {8314, {0x01, 0x44}}, {8365, {0x01, 0x44}}, {8415, {0x01, 0x44}}, {8466, {0x01, 0x44}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3C}}, {8314, {0x00, 0x3C}}, {8365, {0x00, 0x3C}}, {8415, {0x00, 0x3C}}, {8466, {0x00, 0x3C}} }},  /*L4, TPC IDX 6*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x44}}, {8314, {0x01, 0x44}}, {8365, {0x01, 0x44}}, {8415, {0x01, 0x44}}, {8466, {0x01, 0x44}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3E}}, {8314, {0x00, 0x3E}}, {8365, {0x00, 0x3E}}, {8415, {0x00, 0x3E}}, {8466, {0x00, 0x3E}} }},  /*L3, TPC IDX 9*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x33}}, {8314, {0x01, 0x33}}, {8365, {0x01, 0x33}}, {8415, {0x01, 0x33}}, {8466, {0x01, 0x33}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3E}}, {8314, {0x00, 0x3E}}, {8365, {0x00, 0x3E}}, {8415, {0x00, 0x3E}}, {8466, {0x00, 0x3E}} }},  /*L2, TPC IDX 15, Hyst1*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x22}}, {8314, {0x01, 0x22}}, {8365, {0x01, 0x22}}, {8415, {0x01, 0x22}}, {8466, {0x01, 0x22}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x80}}, {8314, {0x03, 0x80}}, {8365, {0x03, 0x80}}, {8415, {0x03, 0x80}}, {8466, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3E}}, {8314, {0x00, 0x3E}}, {8365, {0x00, 0x3E}}, {8415, {0x00, 0x3E}}, {8466, {0x00, 0x3E}} }},  /*L1, TPC IDX 18*/       
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x12}}, {8314, {0x01, 0x12}}, {8365, {0x01, 0x12}}, {8415, {0x01, 0x12}}, {8466, {0x01, 0x12}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x80}}, {8314, {0x03, 0x80}}, {8365, {0x03, 0x80}}, {8415, {0x03, 0x80}}, {8466, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3E}}, {8314, {0x00, 0x3E}}, {8365, {0x00, 0x3E}}, {8415, {0x00, 0x3E}}, {8466, {0x00, 0x3E}} }},  /*L0, TPC IDX 25, Hyst2*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x11}}, {8314, {0x01, 0x11}}, {8365, {0x01, 0x11}}, {8415, {0x01, 0x11}}, {8466, {0x01, 0x11}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x80}}, {8314, {0x03, 0x80}}, {8365, {0x03, 0x80}}, {8415, {0x03, 0x80}}, {8466, {0x03, 0x80}} }},     
#else   
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3C}}, {8314, {0x00, 0x3C}}, {8365, {0x00, 0x3C}}, {8415, {0x00, 0x3C}}, {8466, {0x00, 0x3C}} }},  /*L7, TPC IDX 0*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x58}}, {8314, {0x01, 0x58}}, {8365, {0x01, 0x58}}, {8415, {0x01, 0x58}}, {8466, {0x01, 0x58}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3C}}, {8314, {0x00, 0x3C}}, {8365, {0x00, 0x3C}}, {8415, {0x00, 0x3C}}, {8466, {0x00, 0x3C}} }},  /*L6, TPC IDX 2*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x48}}, {8314, {0x01, 0x48}}, {8365, {0x01, 0x48}}, {8415, {0x01, 0x48}}, {8466, {0x01, 0x48}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3C}}, {8314, {0x00, 0x3C}}, {8365, {0x00, 0x3C}}, {8415, {0x00, 0x3C}}, {8466, {0x00, 0x3C}} }},  /*L5, TPC IDX 4*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x36}}, {8314, {0x01, 0x36}}, {8365, {0x01, 0x36}}, {8415, {0x01, 0x36}}, {8466, {0x01, 0x36}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3C}}, {8314, {0x00, 0x3C}}, {8365, {0x00, 0x3C}}, {8415, {0x00, 0x3C}}, {8466, {0x00, 0x3C}} }},  /*L4, TPC IDX 6*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x25}}, {8314, {0x01, 0x25}}, {8365, {0x01, 0x25}}, {8415, {0x01, 0x25}}, {8466, {0x01, 0x25}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3E}}, {8314, {0x00, 0x3E}}, {8365, {0x00, 0x3E}}, {8415, {0x00, 0x3E}}, {8466, {0x00, 0x3E}} }},  /*L3, TPC IDX 9*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x15}}, {8314, {0x01, 0x15}}, {8365, {0x01, 0x15}}, {8415, {0x01, 0x15}}, {8466, {0x01, 0x15}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3E}}, {8314, {0x00, 0x3E}}, {8365, {0x00, 0x3E}}, {8415, {0x00, 0x3E}}, {8466, {0x00, 0x3E}} }},  /*L2, TPC IDX 15, Hyst1*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x14}}, {8314, {0x01, 0x14}}, {8365, {0x01, 0x14}}, {8415, {0x01, 0x14}}, {8466, {0x01, 0x14}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x80}}, {8314, {0x03, 0x80}}, {8365, {0x03, 0x80}}, {8415, {0x03, 0x80}}, {8466, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3E}}, {8314, {0x00, 0x3E}}, {8365, {0x00, 0x3E}}, {8415, {0x00, 0x3E}}, {8466, {0x00, 0x3E}} }},  /*L1, TPC IDX 18*/       
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x13}}, {8314, {0x01, 0x13}}, {8365, {0x01, 0x13}}, {8415, {0x01, 0x13}}, {8466, {0x01, 0x13}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x80}}, {8314, {0x03, 0x80}}, {8365, {0x03, 0x80}}, {8415, {0x03, 0x80}}, {8466, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x3E}}, {8314, {0x00, 0x3E}}, {8365, {0x00, 0x3E}}, {8415, {0x00, 0x3E}}, {8466, {0x00, 0x3E}} }},  /*L0, TPC IDX 25, Hyst2*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x12}}, {8314, {0x01, 0x12}}, {8365, {0x01, 0x12}}, {8415, {0x01, 0x12}}, {8466, {0x01, 0x12}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x80}}, {8314, {0x03, 0x80}}, {8365, {0x03, 0x80}}, {8415, {0x03, 0x80}}, {8466, {0x03, 0x80}} }},  
#endif                         
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},      
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8264, {0x00, 0x00}}, {8314, {0x00, 0x00}}, {8365, {0x00, 0x00}}, {8415, {0x00, 0x00}}, {8466, {0x00, 0x00}} }}                            
   }                                                                            
};

const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_TPC_UMTSBand8_SetDefault = 
{
   /* Event */
   {
    /* No.           elm type , data idx       , evt_type       , evt_offset     */
    /*                           { start, stop },                  ( us )         */
     { /* 0, Prf_7  */ UL1_MIPI_PA, { 0    , 2     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },  /*highest power*/
     { /* 1, Prf_6  */ UL1_MIPI_PA, { 3    , 5     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 2, Prf_5  */ UL1_MIPI_PA, { 6    , 8     }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 3, Prf_4  */ UL1_MIPI_PA, { 9    , 11    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 4, Prf_3  */ UL1_MIPI_PA, { 12   , 14    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 5, Prf_2  */ UL1_MIPI_PA, { 15   , 17    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 6, Prf_1  */ UL1_MIPI_PA, { 18   , 20    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },
     { /* 7, Prf_0  */ UL1_MIPI_PA, { 21   , 23    }, UL1_MIPI_TPC_SET   , US2CHIPCNT(20)  },  /*lowest power*/
   },
   
   /* Data */
   {                                                                                                                                                                               
      //elm type  , port_sel     , data_seq, user id,         {{sub 0, addr, data}}, {{sub 1, addr, data}}, {{sub 2, addr, data} , {{sub 3, addr, data}}, {{sub 4, addr, data}  
#if defined(USE_VC7643_12) //xjl 20180607
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x74}}, {8899, {0x00, 0x74}}, {8975, {0x00, 0x74}}, {9050, {0x00, 0x74}}, {9126, {0x00, 0x74}} }},  /*L7, TPC IDX 0*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x55}}, {8899, {0x01, 0x55}}, {8975, {0x01, 0x55}}, {9050, {0x01, 0x55}}, {9126, {0x01, 0x55}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x74}}, {8899, {0x00, 0x74}}, {8975, {0x00, 0x74}}, {9050, {0x00, 0x74}}, {9126, {0x00, 0x74}} }},  /*L6, TPC IDX 2*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x55}}, {8899, {0x01, 0x55}}, {8975, {0x01, 0x55}}, {9050, {0x01, 0x55}}, {9126, {0x01, 0x55}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x74}}, {8899, {0x00, 0x74}}, {8975, {0x00, 0x74}}, {9050, {0x00, 0x74}}, {9126, {0x00, 0x74}} }},  /*L5, TPC IDX 4*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x44}}, {8899, {0x01, 0x44}}, {8975, {0x01, 0x44}}, {9050, {0x01, 0x44}}, {9126, {0x01, 0x44}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x74}}, {8899, {0x00, 0x74}}, {8975, {0x00, 0x74}}, {9050, {0x00, 0x74}}, {9126, {0x00, 0x74}} }},  /*L4, TPC IDX 6*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x44}}, {8899, {0x01, 0x44}}, {8975, {0x01, 0x44}}, {9050, {0x01, 0x44}}, {9126, {0x01, 0x44}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x76}}, {8899, {0x00, 0x76}}, {8975, {0x00, 0x76}}, {9050, {0x00, 0x76}}, {9126, {0x00, 0x76}} }},  /*L3, TPC IDX 9*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x33}}, {8899, {0x01, 0x33}}, {8975, {0x01, 0x33}}, {9050, {0x01, 0x33}}, {9126, {0x01, 0x33}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x76}}, {8899, {0x00, 0x76}}, {8975, {0x00, 0x76}}, {9050, {0x00, 0x76}}, {9126, {0x00, 0x76}} }},  /*L2, TPC IDX 15, Hyst1*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x22}}, {8899, {0x01, 0x22}}, {8975, {0x01, 0x22}}, {9050, {0x01, 0x22}}, {9126, {0x01, 0x22}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x80}}, {8899, {0x03, 0x80}}, {8975, {0x03, 0x80}}, {9050, {0x03, 0x80}}, {9126, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x76}}, {8899, {0x00, 0x76}}, {8975, {0x00, 0x76}}, {9050, {0x00, 0x76}}, {9126, {0x00, 0x76}} }},  /*L1, TPC IDX 18*/       
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x12}}, {8899, {0x01, 0x12}}, {8975, {0x01, 0x12}}, {9050, {0x01, 0x12}}, {9126, {0x01, 0x12}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x80}}, {8899, {0x03, 0x80}}, {8975, {0x03, 0x80}}, {9050, {0x03, 0x80}}, {9126, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x76}}, {8899, {0x00, 0x76}}, {8975, {0x00, 0x76}}, {9050, {0x00, 0x76}}, {9126, {0x00, 0x76}} }},  /*L0, TPC IDX 25, Hyst2*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x11}}, {8899, {0x01, 0x11}}, {8975, {0x01, 0x11}}, {9050, {0x01, 0x11}}, {9126, {0x01, 0x11}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x80}}, {8899, {0x03, 0x80}}, {8975, {0x03, 0x80}}, {9050, {0x03, 0x80}}, {9126, {0x03, 0x80}} }},
#else   
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x74}}, {8899, {0x00, 0x74}}, {8975, {0x00, 0x74}}, {9050, {0x00, 0x74}}, {9126, {0x00, 0x74}} }},  /*L7, TPC IDX 0*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x59}}, {8899, {0x01, 0x59}}, {8975, {0x01, 0x59}}, {9050, {0x01, 0x59}}, {9126, {0x01, 0x59}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x74}}, {8899, {0x00, 0x74}}, {8975, {0x00, 0x74}}, {9050, {0x00, 0x74}}, {9126, {0x00, 0x74}} }},  /*L6, TPC IDX 2*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x37}}, {8899, {0x01, 0x37}}, {8975, {0x01, 0x37}}, {9050, {0x01, 0x37}}, {9126, {0x01, 0x37}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x74}}, {8899, {0x00, 0x74}}, {8975, {0x00, 0x74}}, {9050, {0x00, 0x74}}, {9126, {0x00, 0x74}} }},  /*L5, TPC IDX 4*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x36}}, {8899, {0x01, 0x36}}, {8975, {0x01, 0x36}}, {9050, {0x01, 0x36}}, {9126, {0x01, 0x36}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x74}}, {8899, {0x00, 0x74}}, {8975, {0x00, 0x74}}, {9050, {0x00, 0x74}}, {9126, {0x00, 0x74}} }},  /*L4, TPC IDX 6*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x35}}, {8899, {0x01, 0x35}}, {8975, {0x01, 0x35}}, {9050, {0x01, 0x35}}, {9126, {0x01, 0x35}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x76}}, {8899, {0x00, 0x76}}, {8975, {0x00, 0x76}}, {9050, {0x00, 0x76}}, {9126, {0x00, 0x76}} }},  /*L3, TPC IDX 9*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x25}}, {8899, {0x01, 0x25}}, {8975, {0x01, 0x25}}, {9050, {0x01, 0x25}}, {9126, {0x01, 0x25}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x76}}, {8899, {0x00, 0x76}}, {8975, {0x00, 0x76}}, {9050, {0x00, 0x76}}, {9126, {0x00, 0x76}} }},  /*L2, TPC IDX 15, Hyst1*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x15}}, {8899, {0x01, 0x15}}, {8975, {0x01, 0x15}}, {9050, {0x01, 0x15}}, {9126, {0x01, 0x15}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x80}}, {8899, {0x03, 0x80}}, {8975, {0x03, 0x80}}, {9050, {0x03, 0x80}}, {9126, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x76}}, {8899, {0x00, 0x76}}, {8975, {0x00, 0x76}}, {9050, {0x00, 0x76}}, {9126, {0x00, 0x76}} }},  /*L1, TPC IDX 18*/       
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x14}}, {8899, {0x01, 0x14}}, {8975, {0x01, 0x14}}, {9050, {0x01, 0x14}}, {9126, {0x01, 0x14}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x80}}, {8899, {0x03, 0x80}}, {8975, {0x03, 0x80}}, {9050, {0x03, 0x80}}, {9126, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x76}}, {8899, {0x00, 0x76}}, {8975, {0x00, 0x76}}, {9050, {0x00, 0x76}}, {9126, {0x00, 0x76}} }},  /*L0, TPC IDX 25, Hyst2*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x13}}, {8899, {0x01, 0x13}}, {8975, {0x01, 0x13}}, {9050, {0x01, 0x13}}, {9126, {0x01, 0x13}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x80}}, {8899, {0x03, 0x80}}, {8975, {0x03, 0x80}}, {9050, {0x03, 0x80}}, {9126, {0x03, 0x80}} }},
#endif
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},     
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }},                           
     {UL1_MIPI_NULL , UL1_MIPI_DATA_NULL , UL1_SEQ_NULL, MIPI_USID_INIT0_SetDefault, {{8824, {0x00, 0x00}}, {8899, {0x00, 0x00}}, {8975, {0x00, 0x00}}, {9050, {0x00, 0x00}}, {9126, {0x00, 0x00}} }}                            
   }                                                                          
};

const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_TPC_UMTSBand3_SetDefault  = {{{0}}};
const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_TPC_UMTSBand6_SetDefault  = {{{0}}};
const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_TPC_UMTSBand9_SetDefault  = {{{0}}};
const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_TPC_UMTSBand11_SetDefault = {{{0}}};
const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_TPC_UMTSBand19_SetDefault = {{{0}}};

const UL1_UMTS_MIPI_TPC_T* const UMTS_MIPI_TPC_TABLE_SetDefault[] =
{
   M_UMTS_TPC(UMTSBandNone,SetDefault),                     /*UMTSUMTSBandNone*/          
   M_UMTS_TPC(RX_BAND_INDICATOR_0_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_0_SetDefault*/
   M_UMTS_TPC(RX_BAND_INDICATOR_1_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_1_SetDefault*/
   M_UMTS_TPC(RX_BAND_INDICATOR_2_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_2_SetDefault*/
   M_UMTS_TPC(RX_BAND_INDICATOR_3_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_3_SetDefault */ 
   M_UMTS_TPC(RX_BAND_INDICATOR_4_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_4_SetDefault */ 
};



/*special handle for T/Rx calibration, we should force ASM to isolation mode */
/*Users just need to provide the ASM isolation CW, DSP may use immediate mode*/
/*to control the MIPI ASM                                                    */
const UL1_MIPI_DATA_TABLE_T UMTS_MIPI_ASM_ISOLATION_DATA_UMTSBandNone_SetDefault[MIPI_MAX_ASM_ISOLATION_IMM_BSI_CW_NUM] = {{0}};
const UL1_MIPI_DATA_TABLE_T UMTS_MIPI_ASM_ISOLATION_DATA_UMTSBand1_SetDefault[MIPI_MAX_ASM_ISOLATION_IMM_BSI_CW_NUM] = {{0}};
const UL1_MIPI_DATA_TABLE_T UMTS_MIPI_ASM_ISOLATION_DATA_UMTSBand2_SetDefault[MIPI_MAX_ASM_ISOLATION_IMM_BSI_CW_NUM] = {{0}};
const UL1_MIPI_DATA_TABLE_T UMTS_MIPI_ASM_ISOLATION_DATA_UMTSBand4_SetDefault[MIPI_MAX_ASM_ISOLATION_IMM_BSI_CW_NUM] = {{0}};
const UL1_MIPI_DATA_TABLE_T UMTS_MIPI_ASM_ISOLATION_DATA_UMTSBand5_SetDefault[MIPI_MAX_ASM_ISOLATION_IMM_BSI_CW_NUM] = {{0}};
const UL1_MIPI_DATA_TABLE_T UMTS_MIPI_ASM_ISOLATION_DATA_UMTSBand8_SetDefault[MIPI_MAX_ASM_ISOLATION_IMM_BSI_CW_NUM] = {{0}};
const UL1_MIPI_DATA_TABLE_T UMTS_MIPI_ASM_ISOLATION_DATA_UMTSBand3_SetDefault[MIPI_MAX_ASM_ISOLATION_IMM_BSI_CW_NUM] = {{0}};
const UL1_MIPI_DATA_TABLE_T UMTS_MIPI_ASM_ISOLATION_DATA_UMTSBand6_SetDefault[MIPI_MAX_ASM_ISOLATION_IMM_BSI_CW_NUM] = {{0}};
const UL1_MIPI_DATA_TABLE_T UMTS_MIPI_ASM_ISOLATION_DATA_UMTSBand9_SetDefault[MIPI_MAX_ASM_ISOLATION_IMM_BSI_CW_NUM] = {{0}};
const UL1_MIPI_DATA_TABLE_T UMTS_MIPI_ASM_ISOLATION_DATA_UMTSBand11_SetDefault[MIPI_MAX_ASM_ISOLATION_IMM_BSI_CW_NUM] = {{0}};
const UL1_MIPI_DATA_TABLE_T UMTS_MIPI_ASM_ISOLATION_DATA_UMTSBand19_SetDefault[MIPI_MAX_ASM_ISOLATION_IMM_BSI_CW_NUM] = {{0}};

const UL1_MIPI_DATA_TABLE_T* const UMTS_MIPI_ASM_ISOLATION_DATA_TABLE_SetDefault[] = 
{
   M_UMTS_ASM_ISO(UMTSBandNone,SetDefault),                        /*UMTSUMTSBandNone*/          
   M_UMTS_ASM_ISO(RX_BAND_INDICATOR_0_SetDefault,SetDefault),      /*RX_BAND_INDICATOR_0_SetDefault*/  
   M_UMTS_ASM_ISO(RX_BAND_INDICATOR_1_SetDefault,SetDefault),      /*RX_BAND_INDICATOR_1_SetDefault*/  
   M_UMTS_ASM_ISO(RX_BAND_INDICATOR_2_SetDefault,SetDefault),      /*RX_BAND_INDICATOR_2_SetDefault*/  
   M_UMTS_ASM_ISO(RX_BAND_INDICATOR_3_SetDefault,SetDefault),      /*RX_BAND_INDICATOR_3_SetDefault*/   
   M_UMTS_ASM_ISO(RX_BAND_INDICATOR_4_SetDefault,SetDefault),      /*RX_BAND_INDICATOR_4_SetDefault*/   
};

/////////////////////////////////////////////

#endif

