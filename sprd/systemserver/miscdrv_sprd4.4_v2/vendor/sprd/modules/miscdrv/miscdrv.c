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
#include <linux/rtc.h>

#ifndef FUN_ENTER
#define FUN_ENTER	 ALOGE("%s Entry!\n",__func__);
#endif


//#define MISCDRV_DEBUG
#define LED_SUPPORT
#define RED_LED      0x01
#define GREEN_LED    0x02
#define YELLOW_LED   0x03

#define BL5372_RTC   "dev/rtc1"
#define CUSTGPIO     "dev/cgpio_device"

#define CGPIO_IOC_MAGIC                   'c'
#define  CGPIO_IOC_RLED_SET              _IOW(CGPIO_IOC_MAGIC, 1, int)
#define  CGPIO_IOC_RLED_GET              _IOW(CGPIO_IOC_MAGIC, 2, int)
#define  CGPIO_IOC_GLED_SET              _IOW(CGPIO_IOC_MAGIC, 3, int)
#define  CGPIO_IOC_GLED_GET              _IOW(CGPIO_IOC_MAGIC, 4, int)
#define  CGPIO_IOC_BLED_SET              _IOW(CGPIO_IOC_MAGIC, 5, int)
#define  CGPIO_IOC_BLED_GET              _IOW(CGPIO_IOC_MAGIC, 6, int)
#define  CGPIO_IOC_RF24_RSV_SET          _IOW(CGPIO_IOC_MAGIC, 7, int)
#define  CGPIO_IOC_RF24_RSV_GET          _IOW(CGPIO_IOC_MAGIC, 8, int)
#define  CGPIO_IOC_WD_CLK_SET            _IOW(CGPIO_IOC_MAGIC, 9, int)
#define  CGPIO_IOC_WD_CLK_GET            _IOW(CGPIO_IOC_MAGIC, 10, int)

#if defined(LED_SUPPORT)
extern int led_close_lights(void);
extern void led_init_globals(void);
extern int led_set_breath_light(int type, int brightness,int on_ms, int off_ms);
#endif


static void hal_miscdrv_dummy(void)
{
    FUN_ENTER
    
}

static int hal_miscdrv_led_ctrl(int type, int brightness, int on_ms, int off_ms)
{
    FUN_ENTER
    
    led_set_breath_light(type, brightness, on_ms, off_ms);
    
    return 0;
}


static int hal_miscdrv_rtc_readtime(struct tm *tm)
{
    int fd = -1;
    
    FUN_ENTER

    fd = open(BL5372_RTC, O_RDWR);
    if(fd < 0) {
        ALOGE("open dev/rtc1 error!\n");
        return -1;
    }
    
    if (ioctl(fd, RTC_RD_TIME, tm)) {
        ALOGE("ioctl read rtc  time failed!\n");
        close(fd);
        return -1;
    }

    #if defined(MISCDRV_DEBUG)
    ALOGE("readtime: %d:%d:%d  %d:%d:%d", tm->tm_year, tm->tm_mon, tm->tm_mday,
                                             tm->tm_hour, tm->tm_min, tm->tm_sec);
    #endif
    close(fd);
    return 0;
}

static int hal_miscdrv_rtc_settime(struct tm tm)
{
    int fd = -1;
    
    FUN_ENTER

    fd = open(BL5372_RTC, O_RDWR);
    if(fd < 0) {
        ALOGE("open dev/rtc1 error!\n");
        return -1;
    }
    
    if (ioctl(fd, RTC_SET_TIME, &tm)) {
        ALOGE("ioctl set rtc  time failed!\n");
        close(fd);
        return -1;
    }

    #if defined(MISCDRV_DEBUG)
    ALOGE("settime: %d:%d:%d  %d:%d:%d", tm.tm_year, tm.tm_mon, tm.tm_mday,
                                             tm.tm_hour, tm.tm_min, tm.tm_sec);
    #endif
    close(fd);

    return 0;
}

static int hal_miscdrv_wdt_clk(int val)
{
    int fd;
    int ret;
    fd = open(CUSTGPIO, O_RDWR);
    if(fd < 0) {
        ALOGE("open %s error!\n",CUSTGPIO);
        return -1;
    }
    
    /*TODO*/
    // feed the dog logic
    
    ret = ioctl(fd, CGPIO_IOC_WD_CLK_SET, &val);
    if (ret)
        ALOGE("ioctl CGPIO_IOC_WD_CLK_SET failed!");
   
    #if 0//defined(MISCDRV_DEBUG)
    ret = ioctl(fd, CGPIO_IOC_WD_CLK_GET, NULL);
    if (ret)
        ALOGE("ioctl CGPIO_IOC_WD_CLK_GET failed!");
    #endif
    
	return ret;
}

static int close_miscdrv(struct miscdrv_device_t *dev) {

    if (dev)
        free(dev);

    #if defined(LED_SUPPORT)
    led_close_lights();
    #endif

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
    //JM-Y140
    dev->miscdrv_led_ctrl = hal_miscdrv_led_ctrl;
    dev->miscdrv_rtc_readtime = hal_miscdrv_rtc_readtime;
    dev->miscdrv_rtc_settime = hal_miscdrv_rtc_settime;
    dev->miscdrv_wdt_clk = hal_miscdrv_wdt_clk;
    *device = (struct hw_device_t *)dev;

    #if defined(LED_SUPPORT)
    led_init_globals();
    #endif

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
