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
#include <hardware/lights.h>



static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

struct led_prop {
    const char *filename;
    int fd;
};

struct led {
    struct led_prop brightness;
    struct led_prop trigger;
    struct led_prop on_ms;
    struct led_prop off_ms;	
};

/*all lights*/
enum {
    RED_LED = 1,
    GREEN_LED,
    BLUE_LED,
    NUM_LEDS,
};

/*light nodes*/
struct led leds[NUM_LEDS] = {
    [RED_LED] = {
             .brightness = {"/sys/class/leds/g_red/brightness", -1},
             .trigger = {"/sys/class/leds/g_red/trigger",1},
             .on_ms = {"/sys/class/leds/g_red/delay_on", -1},
             .off_ms = {"/sys/class/leds/g_red/delay_off", -1},
             },
    [GREEN_LED] = {
             .brightness = {"/sys/class/leds/g_green/brightness", -1},
             .trigger = {"/sys/class/leds/g_green/trigger",1},
             .on_ms = {"/sys/class/leds/g_green/delay_on", -1},
             .off_ms = {"/sys/class/leds/g_green/delay_off", -1},
               },
    [BLUE_LED] = {
             .brightness = {"/sys/class/leds/g_blue/brightness", -1},
             .trigger = {"/sys/class/leds/g_blue/trigger",1},
             .on_ms = {"/sys/class/leds/g_blue/delay_on", -1},
             .off_ms = {"/sys/class/leds/g_blue/delay_off", -1},
              },
};

void init_g_lock(void) {
    pthread_mutex_init(&g_lock, NULL);
}

/*init one node*/
static int init_prop(struct led_prop *prop) {
    int fd;

    prop->fd = -1;
    if (!prop->filename)
        return 0;
    fd = open(prop->filename, O_RDWR);
    if (fd < 0) {
        ALOGE("init_prop: %s cannot be opened (%s)\n", prop->filename,
              strerror(errno));
        return -errno;
    }

    prop->fd = fd;
    return 0;
}

/*close node*/
static void close_prop(struct led_prop *prop) {
    int fd;

    if (prop->fd > 0)
        close(prop->fd);
}

/*init all nodes*/
void led_init_globals(void) {
    int i;
    init_g_lock();

    for (i = 0; i < NUM_LEDS; ++i) {
        init_prop(&leds[i].brightness);
        init_prop(&leds[i].trigger);
    }
}

static int write_int(struct led_prop *prop, int value) {
    int fd;
    static int already_warned;

    already_warned = 0;

    ALOGE("file:%s, func:%s, path=%s, value=%d\n", __FILE__, __func__,
          prop->filename, value);
    fd = open(prop->filename, O_RDWR);

    if (fd >= 0) {
        char buffer[20];
        int bytes = snprintf(buffer, sizeof(buffer), "%d\n", value);
        int amt = write(fd, buffer, bytes);

        close(fd);

        return amt == -1 ? -errno : 0;
    }

    if (already_warned == 0) {
        ALOGE("file:%s, func:%s, failed to open %s,fd = %d\n",
              __FILE__, __func__, prop->filename, fd);
        already_warned = 1;
    }
    return -errno;
}

static int
write_str(struct led_prop *prop, char *str)
{
    int fd;

	ALOGD("write %s to %s", str, prop->filename);

    fd = open(prop->filename, O_RDWR);
    if (fd >= 0) {
        char buffer[20];
        int bytes = sprintf(buffer, "%s", str);
        int amt = write(fd, buffer, bytes);
        close(fd);
        return amt == -1 ? -errno : 0;
    } else {
        return -errno;
    }
}

int led_close_lights(struct light_device_t *dev) {
    int i;

    ALOGV("file:%s, func:%s\n", __FILE__, __func__);

    for (i = 0; i < NUM_LEDS; ++i) {
        close_prop(&leds[i].brightness);
        close_prop(&leds[i].trigger);
    }
    if (dev)
        free(dev);
    return 0;
}

/*breath led*/
int led_set_breath_light(int type, int brightness,int on_ms, int off_ms) {

    if (brightness > 255) 
         brightness = 255;
    
     if (brightness < 0) 
         brightness = 0;

    pthread_mutex_lock(&g_lock);

    if (on_ms > 0 && off_ms > 0) {
        switch (type) {
            case RED_LED:
                if (brightness) {
                    write_str(&leds[RED_LED].trigger, "timer");
                    system("chmod 777 /sys/class/leds/g_red/delay_on");
                    system("chmod 777 /sys/class/leds/g_red/delay_off");
                    write_int(&leds[RED_LED].on_ms, on_ms);
                    write_int(&leds[RED_LED].off_ms, off_ms);
                    write_int(&leds[RED_LED].brightness, brightness);
                } else {    /*off */
                    write_str(&leds[RED_LED].trigger, "none");
                    write_int(&leds[RED_LED].brightness, 0);
                }
            break;
            case GREEN_LED:
                if (brightness) {
                    write_str(&leds[GREEN_LED].trigger, "timer");
                    system("chmod 777 /sys/class/leds/g_green/delay_on");
                    system("chmod 777 /sys/class/leds/g_green/delay_off");
                    write_int(&leds[GREEN_LED].on_ms, on_ms);
                    write_int(&leds[GREEN_LED].off_ms, off_ms);
                    write_int(&leds[GREEN_LED].brightness, brightness);
                } else {    /*off */
                    write_str(&leds[GREEN_LED].trigger, "none");
                    write_int(&leds[GREEN_LED].brightness, 0);
                }
            break;
            case BLUE_LED:
                if (brightness) {
                    write_str(&leds[BLUE_LED].trigger, "timer");
                    system("chmod 777 /sys/class/leds/g_blue/delay_on");
                    system("chmod 777 /sys/class/leds/g_blue/delay_off");
                    write_int(&leds[BLUE_LED].on_ms, on_ms);
                    write_int(&leds[BLUE_LED].off_ms, off_ms);
                    write_int(&leds[BLUE_LED].brightness, brightness);
                } else {    /*off */
                    write_str(&leds[BLUE_LED].trigger, "none");
                    write_int(&leds[BLUE_LED].brightness, 0);
                }
            break;
            default:
            break;
        }
    } else {
            switch (type) {
                case RED_LED:
                    if (brightness) {
                        write_str(&leds[RED_LED].trigger, "none");
                        write_int(&leds[RED_LED].brightness, brightness);
                    } else {    /*off */
                        write_str(&leds[RED_LED].trigger, "none");
                        write_int(&leds[RED_LED].brightness, 0);
                    }
                break;
                case GREEN_LED:
                   if (brightness) {
                       write_str(&leds[GREEN_LED].trigger, "none");
                       write_int(&leds[GREEN_LED].brightness, brightness);
                   } else {    /*off */
                       write_str(&leds[GREEN_LED].trigger, "none");
                       write_int(&leds[GREEN_LED].brightness, 0);
                   }
                break;
                case BLUE_LED:
                   if (brightness) {
                       write_str(&leds[BLUE_LED].trigger, "none");
                       write_int(&leds[BLUE_LED].brightness, brightness);
                   } else {    /*off */
                       write_str(&leds[BLUE_LED].trigger, "none");
                       write_int(&leds[BLUE_LED].brightness, 0);
                   }
                 break;
                 default:
            
                 break;
           }
    }
    pthread_mutex_unlock(&g_lock);
    
    return 0;
}
