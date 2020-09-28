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

#ifndef ANDROID_MISCDRV_INTERFACE_H
#define ANDROID_MISCDRV_INTERFACE_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <hardware/hardware.h>

__BEGIN_DECLS

#define MISCDRV_HARDWARE_MODULE_ID	"miscdrv"

struct miscdrv_device_t {
    struct hw_device_t common;   // it must be the first

    /**
     * get the index gpio_num value(out/in) 
     * Returns: gpio value
     */
    void (*miscdrv_dummy)(void);
};


__END_DECLS

#endif  

