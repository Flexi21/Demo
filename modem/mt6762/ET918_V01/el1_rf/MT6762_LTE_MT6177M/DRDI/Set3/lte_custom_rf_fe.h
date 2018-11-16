/*******************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2001
*
*******************************************************************************/

/*******************************************************************************
 *
 * Filename:
 * ---------
 *   lte_custom_rf_fe.h
 *
 * Project:
 * --------
 *   MT6177L
 *
 * Description:
 * ------------
 *   MT6177L LTE FDD/TDD RF
 *
 * Author:
 * -------
 *
 *
 *******************************************************************************/

#ifndef  _LTE_CUSTOM_RF_FE_Set3_H_
#define  _LTE_CUSTOM_RF_FE_Set3_H_
/* ------------------------------------------------------------------------- */
#if !defined(MT6177M_LTE_RF)
   #error "rf files mismatch with compile option!"
#endif

#include "el1d_rf_custom_data.h"

/*--------------------------------------------------------*/
/*   FDD Mode Event Timing Define                         */
/*--------------------------------------------------------*/
#define  TC_FPR1_Set3  MICROSECOND_TO_26M(105)
#define  TC_FPR2_Set3  MICROSECOND_TO_26M(26)
#define  TC_FPR3_Set3  MICROSECOND_TO_26M(5)

#define  TC_FPT1_Set3  MICROSECOND_TO_26M(9)
#define  TC_FPT2_Set3  MICROSECOND_TO_26M(8)
#define  TC_FPT3_Set3  MICROSECOND_TO_26M(5)

/*--------------------------------------------------------*/
/*   TDD Mode Event Timing Define                         */
/*--------------------------------------------------------*/
#define  TC_TPR1_Set3  MICROSECOND_TO_26M(21)
#define  TC_TPR2_Set3  MICROSECOND_TO_26M(20)
#define  TC_TPR3_Set3  MICROSECOND_TO_26M(1)

#define  TC_TPT1_Set3  MICROSECOND_TO_26M(9)
#define  TC_TPT2_Set3  MICROSECOND_TO_26M(8)
#define  TC_TPT3_Set3  MICROSECOND_TO_26M(4)


#endif /* _LTE_CUSTOM_RF_FE_Set3_H_ */
