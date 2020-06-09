/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 *
 * you may not use this file except in compliance with the License.
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
#define LOG_NDEBUG 0
*/
#define LOG_TAG "LIGHTS"

#include <cutils/log.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <hardware/halgpio.h>

#ifndef FUN_ENTER
#define FUN_ENTER	 ALOGE("%s Entry!\n",__func__);
#endif

/**
* get the index gpio_num value(out/in) 
* Returns: gpio value
*/
int get_halgpio_value(int gpio_num)
{
	FUN_ENTER
	return 0;
}


/**
* set the index gpio_num output value 
* Returns: 0 success, < 0 failed
*/
int set_halgpio_value(int gpio_num, int value)
{
	FUN_ENTER
	return 0;
}


/**
* get the index gpio_num dir (out/in)
* Returns: gpio dir, 1 for output ,0 for input
*/
int get_halgpio_dir(int gpio_num)
{
	FUN_ENTER
	return 0;
}


/**
* set the index gpio_num dir (out/in)
* Returns: 0 success, < 0 failed
*/
int set_halgpio_dir(int gpio_num, int dir)
{
	FUN_ENTER

	return 0;
}


static int close_halgpio(struct halgpio_device_t *dev) {

    if (dev)
        free(dev);
    return 0;
}

static int halgpio_open(const struct hw_module_t *module, char const *name,
               struct hw_device_t **device) {

    ALOGE("file:%s, func:%s name=%s\n", __FILE__, __func__, name);

    struct halgpio_device_t *dev = malloc(sizeof(struct halgpio_device_t));

    memset(dev, 0, sizeof(*dev));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t *)module;
    dev->common.close = (int (*)(struct hw_device_t *))close_halgpio;
    dev->get_halgpio_value = get_halgpio_value;
    dev->set_halgpio_value = set_halgpio_value;
    dev->get_halgpio_dir = get_halgpio_dir;
    dev->set_halgpio_dir = set_halgpio_dir;

    *device = (struct hw_device_t *)dev;

    return 0;
}

static struct hw_module_methods_t halgpio_module_methods = {
    .open = halgpio_open,
};

/*
 * The lights Module
 */
struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = HALGPIO_HARDWARE_MODULE_ID,
    .name = "halgpo Module",
    .author = "Leo",
    .methods = &halgpio_module_methods,
};
