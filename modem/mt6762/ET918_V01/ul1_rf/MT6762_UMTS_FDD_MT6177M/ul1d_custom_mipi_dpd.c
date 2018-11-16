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
 * u1ld_custom_mipi_dpd.c
 *
 * Project:
 * --------
 * MT6292
 *
 * Description:
 * ------------
 * WCDMA DPD mipi tpc data.
 *
 * Author:
 * -------
 * -------
 *

===============================================================================*/

#include "kal_general_types.h"
#include "ul1d_custom_mipi.h"
#include "ul1d_custom_mipi_dpd.h"
#include "ul1d_custom_rf.h"
#include "ul1d_custom_rf_dpd.h"
#include "mml1_custom_mipi.h"
#include "ul1d_mipi_public.h"
#include "mml1_drdi.h"

#if defined(L1_SIM)
#include "SymWrap.h"
#endif
/*===============================================================================*/

#if (IS_3G_MIPI_SUPPORT)

const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_DPD_TPC_UMTSBandNone_SetDefault = {{{0}}};

const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_DPD_TPC_UMTSBand1_SetDefault = 
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
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x54}}, {19362, {0x00, 0x54}}, {19500, {0x00, 0x54}}, {19638, {0x00, 0x54}}, {19776, {0x00, 0x54}}}},  /*L7, TPC IDX 0*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x77}}, {19362, {0x01, 0x77}}, {19500, {0x01, 0x77}}, {19638, {0x01, 0x77}}, {19776, {0x01, 0x77}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x88}}, {19362, {0x03, 0x88}}, {19500, {0x03, 0x88}}, {19638, {0x03, 0x88}}, {19776, {0x03, 0x88}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x54}}, {19362, {0x00, 0x54}}, {19500, {0x00, 0x54}}, {19638, {0x00, 0x54}}, {19776, {0x00, 0x54}}}},  /*L6, TPC IDX 2*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x65}}, {19362, {0x01, 0x65}}, {19500, {0x01, 0x65}}, {19638, {0x01, 0x65}}, {19776, {0x01, 0x65}}}}, 
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x88}}, {19362, {0x03, 0x88}}, {19500, {0x03, 0x88}}, {19638, {0x03, 0x88}}, {19776, {0x03, 0x88}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x54}}, {19362, {0x00, 0x54}}, {19500, {0x00, 0x54}}, {19638, {0x00, 0x54}}, {19776, {0x00, 0x54}}}},  /*L5, TPC IDX 4*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x35}}, {19362, {0x01, 0x35}}, {19500, {0x01, 0x35}}, {19638, {0x01, 0x35}}, {19776, {0x01, 0x35}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x88}}, {19362, {0x03, 0x88}}, {19500, {0x03, 0x88}}, {19638, {0x03, 0x88}}, {19776, {0x03, 0x88}}}}, 
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x54}}, {19362, {0x00, 0x54}}, {19500, {0x00, 0x54}}, {19638, {0x00, 0x54}}, {19776, {0x00, 0x54}}}},  /*L4, TPC IDX 6*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x34}}, {19362, {0x01, 0x34}}, {19500, {0x01, 0x34}}, {19638, {0x01, 0x34}}, {19776, {0x01, 0x34}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x88}}, {19362, {0x03, 0x88}}, {19500, {0x03, 0x88}}, {19638, {0x03, 0x00}}, {19776, {0x03, 0x88}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x56}}, {19362, {0x00, 0x56}}, {19500, {0x00, 0x56}}, {19638, {0x00, 0x56}}, {19776, {0x00, 0x56}}}},  /*L3, TPC IDX 9*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x24}}, {19362, {0x01, 0x24}}, {19500, {0x01, 0x24}}, {19638, {0x01, 0x24}}, {19776, {0x01, 0x24}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x80}}, {19362, {0x03, 0x80}}, {19500, {0x03, 0x80}}, {19638, {0x03, 0x80}}, {19776, {0x03, 0x80}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x56}}, {19362, {0x00, 0x56}}, {19500, {0x00, 0x56}}, {19638, {0x00, 0x56}}, {19776, {0x00, 0x56}}}},  /*L2, TPC IDX 15, Hyst1*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x14}}, {19362, {0x01, 0x14}}, {19500, {0x01, 0x14}}, {19638, {0x01, 0x14}}, {19776, {0x01, 0x14}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x80}}, {19362, {0x03, 0x80}}, {19500, {0x03, 0x80}}, {19638, {0x03, 0x80}}, {19776, {0x03, 0x80}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x56}}, {19362, {0x00, 0x56}}, {19500, {0x00, 0x56}}, {19638, {0x00, 0x56}}, {19776, {0x00, 0x56}}}},  /*L1, TPC IDX 18*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x13}}, {19362, {0x01, 0x13}}, {19500, {0x01, 0x13}}, {19638, {0x01, 0x13}}, {19776, {0x01, 0x13}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x80}}, {19362, {0x03, 0x80}}, {19500, {0x03, 0x80}}, {19638, {0x03, 0x80}}, {19776, {0x03, 0x80}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x00, 0x56}}, {19362, {0x00, 0x56}}, {19500, {0x00, 0x56}}, {19638, {0x00, 0x56}}, {19776, {0x00, 0x56}}}},  /*L0, TPC IDX 25, Hyst2*/
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x01, 0x12}}, {19362, {0x01, 0x12}}, {19500, {0x01, 0x12}}, {19638, {0x01, 0x12}}, {19776, {0x01, 0x12}}}},
    {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{19224, {0x03, 0x80}}, {19362, {0x03, 0x80}}, {19500, {0x03, 0x80}}, {19638, {0x03, 0x80}}, {19776, {0x03, 0x80}}}},
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


const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_DPD_TPC_UMTSBand2_SetDefault = 
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
#if defined(B3_USE_SINGLE_PCS1900_PATH) //SawLess path
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
#else     
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x5C}}, {18662, {0x00, 0x5C}}, {18800, {0x00, 0x5C}}, {18938, {0x00, 0x5C}}, {19076, {0x00, 0x5C}} }},  /*L7, TPC IDX 0*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x76}}, {18662, {0x01, 0x76}}, {18800, {0x01, 0x76}}, {18938, {0x01, 0x76}}, {19076, {0x01, 0x76}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x5C}}, {18662, {0x00, 0x5C}}, {18800, {0x00, 0x5C}}, {18938, {0x00, 0x5C}}, {19076, {0x00, 0x5C}} }},  /*L6, TPC IDX 2*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x65}}, {18662, {0x01, 0x65}}, {18800, {0x01, 0x65}}, {18938, {0x01, 0x65}}, {19076, {0x01, 0x65}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x5C}}, {18662, {0x00, 0x5C}}, {18800, {0x00, 0x5C}}, {18938, {0x00, 0x5C}}, {19076, {0x00, 0x5C}} }},  /*L5, TPC IDX 4*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x44}}, {18662, {0x01, 0x44}}, {18800, {0x01, 0x44}}, {18938, {0x01, 0x44}}, {19076, {0x01, 0x44}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x5C}}, {18662, {0x00, 0x5C}}, {18800, {0x00, 0x5C}}, {18938, {0x00, 0x5C}}, {19076, {0x00, 0x5C}} }},  /*L4, TPC IDX 6*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x34}}, {18662, {0x01, 0x34}}, {18800, {0x01, 0x34}}, {18938, {0x01, 0x34}}, {19076, {0x01, 0x34}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x5E}}, {18662, {0x00, 0x5E}}, {18800, {0x00, 0x5E}}, {18938, {0x00, 0x5E}}, {19076, {0x00, 0x5E}} }},  /*L3, TPC IDX 9*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x24}}, {18662, {0x01, 0x24}}, {18800, {0x01, 0x24}}, {18938, {0x01, 0x24}}, {19076, {0x01, 0x24}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x88}}, {18662, {0x03, 0x88}}, {18800, {0x03, 0x88}}, {18938, {0x03, 0x88}}, {19076, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x5E}}, {18662, {0x00, 0x5E}}, {18800, {0x00, 0x5E}}, {18938, {0x00, 0x5E}}, {19076, {0x00, 0x5E}} }},  /*L2, TPC IDX 15, Hyst1*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x14}}, {18662, {0x01, 0x14}}, {18800, {0x01, 0x14}}, {18938, {0x01, 0x14}}, {19076, {0x01, 0x14}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x80}}, {18662, {0x03, 0x80}}, {18800, {0x03, 0x80}}, {18938, {0x03, 0x80}}, {19076, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x5E}}, {18662, {0x00, 0x5E}}, {18800, {0x00, 0x5E}}, {18938, {0x00, 0x5E}}, {19076, {0x00, 0x5E}} }},  /*L1, TPC IDX 18*/       
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x01, 0x13}}, {18662, {0x01, 0x13}}, {18800, {0x01, 0x13}}, {18938, {0x01, 0x13}}, {19076, {0x01, 0x13}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x03, 0x80}}, {18662, {0x03, 0x80}}, {18800, {0x03, 0x80}}, {18938, {0x03, 0x80}}, {19076, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{18524, {0x00, 0x5E}}, {18662, {0x00, 0x5E}}, {18800, {0x00, 0x5E}}, {18938, {0x00, 0x5E}}, {19076, {0x00, 0x5E}} }},  /*L0, TPC IDX 25, Hyst2*/
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

const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_DPD_TPC_UMTSBand4_SetDefault = 
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
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x54}}, {17224, {0x00, 0x54}}, {17324, {0x00, 0x54}}, {17425, {0x00, 0x54}}, {17526, {0x00, 0x54}} }},  /*L7, TPC IDX 0*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0xA7}}, {17224, {0x01, 0xA7}}, {17324, {0x01, 0xA7}}, {17425, {0x01, 0xA7}}, {17526, {0x01, 0xA7}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x89}}, {17224, {0x03, 0x89}}, {17324, {0x03, 0x89}}, {17425, {0x03, 0x89}}, {17526, {0x03, 0x89}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x54}}, {17224, {0x00, 0x54}}, {17324, {0x00, 0x54}}, {17425, {0x00, 0x54}}, {17526, {0x00, 0x54}} }},  /*L6, TPC IDX 2*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x76}}, {17224, {0x01, 0x76}}, {17324, {0x01, 0x76}}, {17425, {0x01, 0x76}}, {17526, {0x01, 0x76}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x89}}, {17224, {0x03, 0x89}}, {17324, {0x03, 0x89}}, {17425, {0x03, 0x89}}, {17526, {0x03, 0x89}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x54}}, {17224, {0x00, 0x54}}, {17324, {0x00, 0x54}}, {17425, {0x00, 0x54}}, {17526, {0x00, 0x54}} }},  /*L5, TPC IDX 4*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x55}}, {17224, {0x01, 0x55}}, {17324, {0x01, 0x55}}, {17425, {0x01, 0x55}}, {17526, {0x01, 0x55}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x89}}, {17224, {0x03, 0x89}}, {17324, {0x03, 0x89}}, {17425, {0x03, 0x89}}, {17526, {0x03, 0x89}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x54}}, {17224, {0x00, 0x54}}, {17324, {0x00, 0x54}}, {17425, {0x00, 0x54}}, {17526, {0x00, 0x54}} }},  /*L4, TPC IDX 6*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x45}}, {17224, {0x01, 0x45}}, {17324, {0x01, 0x45}}, {17425, {0x01, 0x45}}, {17526, {0x01, 0x45}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x89}}, {17224, {0x03, 0x89}}, {17324, {0x03, 0x89}}, {17425, {0x03, 0x89}}, {17526, {0x03, 0x89}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x56}}, {17224, {0x00, 0x56}}, {17324, {0x00, 0x56}}, {17425, {0x00, 0x56}}, {17526, {0x00, 0x56}} }},  /*L3, TPC IDX 9*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x34}}, {17224, {0x01, 0x34}}, {17324, {0x01, 0x34}}, {17425, {0x01, 0x34}}, {17526, {0x01, 0x34}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x80}}, {17224, {0x03, 0x80}}, {17324, {0x03, 0x80}}, {17425, {0x03, 0x80}}, {17526, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x56}}, {17224, {0x00, 0x56}}, {17324, {0x00, 0x56}}, {17425, {0x00, 0x56}}, {17526, {0x00, 0x56}} }},  /*L2, TPC IDX 15, Hyst1*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x24}}, {17224, {0x01, 0x24}}, {17324, {0x01, 0x24}}, {17425, {0x01, 0x24}}, {17526, {0x01, 0x24}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x80}}, {17224, {0x03, 0x80}}, {17324, {0x03, 0x80}}, {17425, {0x03, 0x80}}, {17526, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x56}}, {17224, {0x00, 0x56}}, {17324, {0x00, 0x56}}, {17425, {0x00, 0x56}}, {17526, {0x00, 0x56}} }},  /*L1, TPC IDX 18*/       
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x14}}, {17224, {0x01, 0x14}}, {17324, {0x01, 0x14}}, {17425, {0x01, 0x14}}, {17526, {0x01, 0x14}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x80}}, {17224, {0x03, 0x80}}, {17324, {0x03, 0x80}}, {17425, {0x03, 0x80}}, {17526, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x00, 0x56}}, {17224, {0x00, 0x56}}, {17324, {0x00, 0x56}}, {17425, {0x00, 0x56}}, {17526, {0x00, 0x56}} }},  /*L0, TPC IDX 25, Hyst2*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x01, 0x13}}, {17224, {0x01, 0x13}}, {17324, {0x01, 0x13}}, {17425, {0x01, 0x13}}, {17526, {0x01, 0x13}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{17124, {0x03, 0x80}}, {17224, {0x03, 0x80}}, {17324, {0x03, 0x80}}, {17425, {0x03, 0x80}}, {17526, {0x03, 0x80}} }},                           
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


const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_DPD_TPC_UMTSBand5_SetDefault = 
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
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x34}}, {8314, {0x00, 0x34}}, {8365, {0x00, 0x34}}, {8415, {0x00, 0x34}}, {8466, {0x00, 0x34}} }},  /*L7, TPC IDX 0*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x58}}, {8314, {0x01, 0x58}}, {8365, {0x01, 0x58}}, {8415, {0x01, 0x58}}, {8466, {0x01, 0x58}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x34}}, {8314, {0x00, 0x34}}, {8365, {0x00, 0x34}}, {8415, {0x00, 0x34}}, {8466, {0x00, 0x34}} }},  /*L6, TPC IDX 2*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x48}}, {8314, {0x01, 0x48}}, {8365, {0x01, 0x48}}, {8415, {0x01, 0x48}}, {8466, {0x01, 0x48}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x34}}, {8314, {0x00, 0x34}}, {8365, {0x00, 0x34}}, {8415, {0x00, 0x34}}, {8466, {0x00, 0x34}} }},  /*L5, TPC IDX 4*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x36}}, {8314, {0x01, 0x36}}, {8365, {0x01, 0x36}}, {8415, {0x01, 0x36}}, {8466, {0x01, 0x36}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x34}}, {8314, {0x00, 0x34}}, {8365, {0x00, 0x34}}, {8415, {0x00, 0x34}}, {8466, {0x00, 0x34}} }},  /*L4, TPC IDX 6*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x25}}, {8314, {0x01, 0x25}}, {8365, {0x01, 0x25}}, {8415, {0x01, 0x25}}, {8466, {0x01, 0x25}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x36}}, {8314, {0x00, 0x36}}, {8365, {0x00, 0x36}}, {8415, {0x00, 0x36}}, {8466, {0x00, 0x36}} }},  /*L3, TPC IDX 9*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x15}}, {8314, {0x01, 0x15}}, {8365, {0x01, 0x15}}, {8415, {0x01, 0x15}}, {8466, {0x01, 0x15}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x88}}, {8314, {0x03, 0x88}}, {8365, {0x03, 0x88}}, {8415, {0x03, 0x88}}, {8466, {0x03, 0x88}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x36}}, {8314, {0x00, 0x36}}, {8365, {0x00, 0x36}}, {8415, {0x00, 0x36}}, {8466, {0x00, 0x36}} }},  /*L2, TPC IDX 15, Hyst1*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x14}}, {8314, {0x01, 0x14}}, {8365, {0x01, 0x14}}, {8415, {0x01, 0x14}}, {8466, {0x01, 0x14}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x80}}, {8314, {0x03, 0x80}}, {8365, {0x03, 0x80}}, {8415, {0x03, 0x80}}, {8466, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x36}}, {8314, {0x00, 0x36}}, {8365, {0x00, 0x36}}, {8415, {0x00, 0x36}}, {8466, {0x00, 0x36}} }},  /*L1, TPC IDX 18*/       
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x13}}, {8314, {0x01, 0x13}}, {8365, {0x01, 0x13}}, {8415, {0x01, 0x13}}, {8466, {0x01, 0x13}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x80}}, {8314, {0x03, 0x80}}, {8365, {0x03, 0x80}}, {8415, {0x03, 0x80}}, {8466, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x00, 0x36}}, {8314, {0x00, 0x36}}, {8365, {0x00, 0x36}}, {8415, {0x00, 0x36}}, {8466, {0x00, 0x36}} }},  /*L0, TPC IDX 25, Hyst2*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x01, 0x12}}, {8314, {0x01, 0x12}}, {8365, {0x01, 0x12}}, {8415, {0x01, 0x12}}, {8466, {0x01, 0x12}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8264, {0x03, 0x80}}, {8314, {0x03, 0x80}}, {8365, {0x03, 0x80}}, {8415, {0x03, 0x80}}, {8466, {0x03, 0x80}} }},                           
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

const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_DPD_TPC_UMTSBand8_SetDefault = 
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
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x24}}, {8899, {0x00, 0x24}}, {8975, {0x00, 0x24}}, {9050, {0x00, 0x24}}, {9126, {0x00, 0x24}} }},  /*L7, TPC IDX 0*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x59}}, {8899, {0x01, 0x59}}, {8975, {0x01, 0x59}}, {9050, {0x01, 0x59}}, {9126, {0x01, 0x59}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x24}}, {8899, {0x00, 0x24}}, {8975, {0x00, 0x24}}, {9050, {0x00, 0x24}}, {9126, {0x00, 0x24}} }},  /*L6, TPC IDX 2*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x37}}, {8899, {0x01, 0x37}}, {8975, {0x01, 0x37}}, {9050, {0x01, 0x37}}, {9126, {0x01, 0x37}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x24}}, {8899, {0x00, 0x24}}, {8975, {0x00, 0x24}}, {9050, {0x00, 0x24}}, {9126, {0x00, 0x24}} }},  /*L5, TPC IDX 4*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x36}}, {8899, {0x01, 0x36}}, {8975, {0x01, 0x36}}, {9050, {0x01, 0x36}}, {9126, {0x01, 0x36}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x24}}, {8899, {0x00, 0x24}}, {8975, {0x00, 0x24}}, {9050, {0x00, 0x24}}, {9126, {0x00, 0x24}} }},  /*L4, TPC IDX 6*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x35}}, {8899, {0x01, 0x35}}, {8975, {0x01, 0x35}}, {9050, {0x01, 0x35}}, {9126, {0x01, 0x35}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x26}}, {8899, {0x00, 0x26}}, {8975, {0x00, 0x26}}, {9050, {0x00, 0x26}}, {9126, {0x00, 0x26}} }},  /*L3, TPC IDX 9*/        
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x25}}, {8899, {0x01, 0x25}}, {8975, {0x01, 0x25}}, {9050, {0x01, 0x25}}, {9126, {0x01, 0x25}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x87}}, {8899, {0x03, 0x87}}, {8975, {0x03, 0x87}}, {9050, {0x03, 0x87}}, {9126, {0x03, 0x87}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x26}}, {8899, {0x00, 0x26}}, {8975, {0x00, 0x26}}, {9050, {0x00, 0x26}}, {9126, {0x00, 0x26}} }},  /*L2, TPC IDX 15, Hyst1*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x15}}, {8899, {0x01, 0x15}}, {8975, {0x01, 0x15}}, {9050, {0x01, 0x15}}, {9126, {0x01, 0x15}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x80}}, {8899, {0x03, 0x80}}, {8975, {0x03, 0x80}}, {9050, {0x03, 0x80}}, {9126, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x26}}, {8899, {0x00, 0x26}}, {8975, {0x00, 0x26}}, {9050, {0x00, 0x26}}, {9126, {0x00, 0x26}} }},  /*L1, TPC IDX 18*/       
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x14}}, {8899, {0x01, 0x14}}, {8975, {0x01, 0x14}}, {9050, {0x01, 0x14}}, {9126, {0x01, 0x14}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x80}}, {8899, {0x03, 0x80}}, {8975, {0x03, 0x80}}, {9050, {0x03, 0x80}}, {9126, {0x03, 0x80}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x00, 0x26}}, {8899, {0x00, 0x26}}, {8975, {0x00, 0x26}}, {9050, {0x00, 0x26}}, {9126, {0x00, 0x26}} }},  /*L0, TPC IDX 25, Hyst2*/
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x01, 0x13}}, {8899, {0x01, 0x13}}, {8975, {0x01, 0x13}}, {9050, {0x01, 0x13}}, {9126, {0x01, 0x13}} }},                           
     {UL1_MIPI_PA   , UL1_MIPI_PORT0 , UL1_REG_W ,   MIPI_USID_PA1_SetDefault,   {{8824, {0x03, 0x80}}, {8899, {0x03, 0x80}}, {8975, {0x03, 0x80}}, {9050, {0x03, 0x80}}, {9126, {0x03, 0x80}} }},                           
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

const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_DPD_TPC_UMTSBand3_SetDefault  = {{{0}}};
const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_DPD_TPC_UMTSBand6_SetDefault  = {{{0}}};
const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_DPD_TPC_UMTSBand9_SetDefault  = {{{0}}};
const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_DPD_TPC_UMTSBand11_SetDefault = {{{0}}};
const UL1_UMTS_MIPI_TPC_T UMTS_MIPI_DPD_TPC_UMTSBand19_SetDefault = {{{0}}};

const UL1_UMTS_MIPI_TPC_T* UMTS_MIPI_DPD_TPC_TABLE_SetDefault[] =
{
   M_UMTS_DPD_TPC(UMTSBandNone,SetDefault),                         /*UMTSUMTSBandNone*/          
   M_UMTS_DPD_TPC(RX_BAND_INDICATOR_0_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_0_SetDefault*/
   M_UMTS_DPD_TPC(RX_BAND_INDICATOR_1_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_1_SetDefault*/
   M_UMTS_DPD_TPC(RX_BAND_INDICATOR_2_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_2_SetDefault*/
   M_UMTS_DPD_TPC(RX_BAND_INDICATOR_3_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_3_SetDefault*/ 
   M_UMTS_DPD_TPC(RX_BAND_INDICATOR_4_SetDefault,SetDefault),   /*RX_BAND_INDICATOR_4_SetDefault*/ 
};

#endif

