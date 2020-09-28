/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "nvset"
#include "utils/Log.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cutils/properties.h>

#define MAX_COMMAND_BYTES               (8 * 1024)

extern "C" {
#include "sprd_atci.h"
#include "at_tok.h"
}


#define SUCCESS_STR                   "OK"
#define SIM_CHANNEL_ID                0
#define W_BAND_OFF                    0
#define W_BAND_ON                     1
#define GET_WCDMA_BAND                "AT+SPFDDBAND=0,"  //eg: AT+SPFDDBAND=0,2 band2
#define SET_WCDMA_BAND                "AT+SPFDDBAND=1"  //eg: AT+SPFDDBAND=0,2 band2
#define SET_LTE_BAND                  "AT+SPLBAND=1,0,0,0,"
#define GET_LTE_BAND                  "AT+SPLBAND=0"
#define LTE_BAND1_MASK                0x1
#define ENABLE_STR                    "persist.nvset.enabled"


#define LTE_BAND_MASK                   LTE_BAND1_MASK

enum w_band {
	w_band1 = 1,
	w_band2 = 2,
	w_band5 = 5,
	w_band8 = 8,
};

int str_shift(char *s_str,int c, int n)
{
	int count = 0;
	int pos = 0;
	char *p = s_str;
	do {
		while((*p++ != c) || (*p == '\0')){
			pos++;
		}
		pos++;
		count++;
	} while(count < n);

	if (count < n)
		pos = 0;
	
	ALOGI("nvset :str_shift:%s pos:%d", s_str,pos);
	return pos;
}

static int get_wcdma_band_info(enum w_band band)
{
	int status;
	int retry = 5;
	int resultValue;
	char revstr[100] = {0};
	char wristr[100] = {0};
	char result[MAX_COMMAND_BYTES] = {0};
	
	sprintf(wristr,"%s%d",GET_WCDMA_BAND, band);	
	ALOGI("nvset: leo w_band%s",wristr);
	do {
		memset(result, 0, sizeof(result));
		resultValue = sendATCmd(SIM_CHANNEL_ID, 
						wristr, result, MAX_COMMAND_BYTES);
		if (resultValue != 0) {
			retry -= 1;
			ALOGE("nvset %s error,ret %d", wristr, resultValue);
		} else {
			if (strstr(result, SUCCESS_STR) == NULL) {
				retry -= 1;
				ALOGE("nvset %s error: %s", wristr, result);
			}
		}
		
	} while (((resultValue != 0) 
				|| (strstr(result, SUCCESS_STR) == NULL))
			 && (retry != 0));

	if (retry == 0) {
		status = -1;
		goto out;
	}

	strncpy(revstr, result+str_shift(result, ',', 2), sizeof(char));
	status = atoi(revstr);
	
	ALOGI("nvset: w_band%d value:rev:%s status:%d",
								band, revstr , atoi(revstr));
	
	if (retry == 0)
		status = -1;

out:
	return status;
}

static void get_wcdma_band_set_str(char *wristr,enum w_band band, int status)
{
	memset(wristr, 0, strlen(wristr));
	sprintf(wristr,"%s,%d,%d",SET_WCDMA_BAND, band,status);	
	ALOGI("nvset:w_band writestr:%s",wristr);
}

void vl01_mcx_nv_mask(void)
{
	int retry = 5;
	int resultValue;
	char result[MAX_COMMAND_BYTES] = {0};
	char prop[200];
	int recval = 0;
	int wrival = 0;
	char revstr[100] = {0};
	char wristr[100] = {0};
	int pos;
	int str_size;
	int flag;

	if (property_get(ENABLE_STR, prop, NULL) == 0) {
		ALOGE("nvset getprop failed!\n");
	} else {
		ALOGI("nvset getprop:%s %d",prop,atoi(prop));
	}
	
	if (!atoi(prop)){
		ALOGI("nvset: getprop persist.nvset.enabled= 0,return!\n");
		return;	
	}
	
	if (get_wcdma_band_info(w_band1)) {
		retry = 5;
		memset(wristr, 0, sizeof(wristr));
		get_wcdma_band_set_str(wristr, w_band1, W_BAND_OFF);
		do {
			memset(result, 0, sizeof(result));
			resultValue = sendATCmd(SIM_CHANNEL_ID, 
								wristr, result, MAX_COMMAND_BYTES);
			if (resultValue != 0) {
				retry -= 1;
				ALOGE("nvset %s error,ret %d", wristr, resultValue);
			} else {
				if (strstr(result, SUCCESS_STR) == NULL) {
					retry -= 1;
					ALOGE("nvset result %s error: %s", wristr, result);
				}
			}
		} while (((resultValue != 0) 
		 			|| (strstr(result, SUCCESS_STR) == NULL))
		 		 && (retry != 0));
		ALOGI("nvset %s: %s", wristr, result);
	}
	if (retry > 0)
		flag = flag | 0x1;

	//get LTE Band information	
	retry = 5;
	do {
		memset(result, 0, sizeof(result));
		resultValue = sendATCmd(SIM_CHANNEL_ID, 
						GET_LTE_BAND, result, MAX_COMMAND_BYTES);
		if (resultValue != 0) {
			retry -= 1;
			ALOGE("nvset %s error,ret %d", GET_LTE_BAND, resultValue);
		} else {
			if (strstr(result, SUCCESS_STR) == NULL) {
				retry -= 1;
				ALOGE("nvset %s error: %s", GET_LTE_BAND, result);
			}
		}
		
	} while (((resultValue != 0) 
				|| (strstr(result, SUCCESS_STR) == NULL))
			 && (retry != 0));
	if (retry > 0)
		flag = flag | 0x10;

	memset(revstr, 0, sizeof(revstr));
	memset(wristr, 0, sizeof(wristr));
	pos = str_shift(result, ',', 3);
	str_size = str_shift(result, ',', 4) - pos - 1;
	strncpy(revstr, result+pos, str_size);
	sprintf(wristr,"%s%d", SET_LTE_BAND,(atoi(revstr) & ~LTE_BAND_MASK));
	ALOGI("nvset: value:rev:%s %d wri:%s",revstr , atoi(revstr),wristr);
	
	retry = 5;
	do {
		memset(result, 0, sizeof(result));
		resultValue = sendATCmd(SIM_CHANNEL_ID, 
							wristr, result, MAX_COMMAND_BYTES);
		if (resultValue != 0) {
			retry -= 1;
			ALOGE("nvset %s error,ret %d", wristr, resultValue);
		} else {
			if (strstr(result, SUCCESS_STR) == NULL) {
				retry -= 1;
				ALOGE("nvset result %s error: %s", wristr, result);
			}
		}
	} while (((resultValue != 0) 
	 			|| (strstr(result, SUCCESS_STR) == NULL))
	 		 && (retry != 0));
	ALOGI("nvset %s: %s", wristr, result);

	if (retry > 0)
		flag = flag | 0x100;

	
	//only do once
	if (flag == 0x111) {
		property_set(ENABLE_STR, "0");
	}
}

int main(void)
{
	vl01_mcx_nv_mask();

	return 0;
}
