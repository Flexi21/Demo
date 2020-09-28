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
#define LOG_TAG "MiscDrvhal"

#include <cutils/log.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <hardware/miscdrv.h>

#ifndef FUN_ENTER
#define FUN_ENTER	 ALOGE("%s Entry!\n",__func__);
#endif

/**
* get the index gpio_num value(out/in) 
* Returns: gpio value
*/
static void hal_miscdrv_dummy(void)
{
    FUN_ENTER
    
    return 0;
}

static int close_miscdrv(struct miscdrv_device_t *dev) {

    if (dev)
        free(dev);
    return 0;
}

static int miscdrv_open(const struct hw_module_t *module, char const *name,
               struct hw_device_t **device) {

    ALOGE("file:%s, func:%s name=%s\n", __FILE__, __func__, name);

    struct miscdrv_device_t *dev = malloc(sizeof(struct miscdrv_device_t));

    memset(dev, 0, sizeof(*dev));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t *)module;
    dev->common.close = (int (*)(struct hw_device_t *))close_miscdrv;
    dev->miscdrv_dummy = hal_miscdrv_dummy;

    *device = (struct hw_device_t *)dev;

    return 0;
}

static struct hw_module_methods_t miscdrv_module_methods = {
    .open = miscdrv_open,
};

/*
 * The lights Module
 */
struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = MISCDRV_HARDWARE_MODULE_ID,
    .name = "miscdrv Module",
    .author = "Leo",
    .methods = &miscdrv_module_methods,
};
