/*
 * Copyright (C) 2008 The Android Open Source Project
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

#ifndef ANDROID_HALGPIO_INTERFACE_H
#define ANDROID_HALGPIO_INTERFACE_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <hardware/hardware.h>

__BEGIN_DECLS

#define HALGPIO_HARDWARE_MODULE_ID	"halgpio"

struct halgpio_device_t {
    struct hw_device_t common;   // it must be the first

    /**
     * get the index gpio_num value(out/in) 
     * Returns: gpio value
     */
    int (*get_halgpio_value)(int gpio_num);
    /**
     * set the index gpio_num output value 
     * Returns: 0 success, < 0 failed
     */    
    int (*set_halgpio_value)(int gpio_num, int value);
    /**
     * get the index gpio_num dir (out/in)
     * Returns: gpio dir, 1 for output ,0 for input
     */        
    int (*get_halgpio_dir)(int gpio_num);
     /**
     * set the index gpio_num dir (out/in)
     * Returns: 0 success, < 0 failed
     */
    int (*set_halgpio_dir)(int gpio_num, int dir);
};


__END_DECLS

#endif  // ANDROID_LIGHTS_INTERFACE_H

