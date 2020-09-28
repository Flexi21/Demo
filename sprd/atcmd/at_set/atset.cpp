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

#define LOG_TAG "atset"
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


int main(int argc, char *argv[])
{
	char wristr[100] = {0};
	int retry = 5;
	int resultValue;
	char result[MAX_COMMAND_BYTES] = {0};

	if (argc == 2) {
		printf("%d atcmd:%s \n", argc, argv[1]);
		ALOGI("%d atcmd:%s \n", argc, argv[1]);
		
		sprintf(wristr, argv[1], strlen(argv[1]));
		retry = 5;
		do {
			memset(result, 0, sizeof(result));
			resultValue = sendATCmd(SIM_CHANNEL_ID, 
								wristr, result, MAX_COMMAND_BYTES);
			if (resultValue != 0) {
				retry -= 1;
				printf("atset %s error,ret %d", wristr, resultValue);
				ALOGE("atset %s error,ret %d", wristr, resultValue);
			} else {
				if (strstr(result, SUCCESS_STR) == NULL) {
					retry -= 1;
					printf("atset %s error: %s", wristr, result);
					ALOGE("atset %s error: %s", wristr, result);
				}
			}
		
		} while (((resultValue != 0) 
					|| (strstr(result, SUCCESS_STR) == NULL))
				 && (retry != 0));
		printf("atset result: %s", result);
		ALOGE("atset result: %s", result);
	} else {
		printf("Invaild Param, only support one param !!!\n");
		ALOGE("Invaild Param, only support one param !!!\n");
	}

	return 0;
}
