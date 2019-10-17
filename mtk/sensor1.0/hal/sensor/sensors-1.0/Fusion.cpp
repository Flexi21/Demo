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
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/select.h>
#include <log/log.h>
#include <utils/SystemClock.h>
#include <utils/Timers.h>
#include <string.h>
#include "Fusion.h"
#include <inttypes.h>

#undef LOG_TAG
#define LOG_TAG "Fusion"


#define IGNORE_EVENT_TIME 0
#define DEVICE_PATH           "/dev/m_fusion_misc"

#ifdef FUSION_ALGORITHM_IN_SENSORHUB
FusionSensor::FusionSensor()
    : mSensorReader(BATCH_SENSOR_MAX_READ_INPUT_NUMEVENTS) {
    mPendingEvent.version = 0;
    mPendingEvent.sensor = 0;
    mPendingEvent.type = 0;
    memset(mPendingEvent.data, 0x00, sizeof(mPendingEvent.data));
    mPendingEvent.flags = 0;
    mPendingEvent.reserved0 = 0;
    mPendingEvent.timestamp = 0;

    memset(mEnabledTime, 0, sizeof(mEnabledTime));
    memset(mEnabled, 0, sizeof(mEnabled));
    memset(mFlushCnt, 0, sizeof(mFlushCnt));
    memset(mDataDiv, 0, sizeof(mDataDiv));
    input_sysfs_path_len = 0;

    if (mSensorReader.selectSensorEventFd(DEVICE_PATH) >= 0) {
        strlcpy(input_sysfs_path, "/sys/class/sensor/m_fusion_misc/", sizeof(input_sysfs_path));
        input_sysfs_path_len = strlen(input_sysfs_path);
    }

    char datapath[64]={"/sys/class/sensor/m_fusion_misc/fusionactive"};
    int fd = TEMP_FAILURE_RETRY(open(datapath, O_RDWR));
    char buf[64];
    int len;

    if (fd >= 0) {
        len = TEMP_FAILURE_RETRY(read(fd, buf, sizeof(buf)-1));
        if (len <= 0) {
            ALOGD("read div err buf(%s)", buf);
        } else {
            buf[len] = '\0';
            sscanf(buf, "%d,%d,%d,%d,%d,%d,%d,%d,%d", &mDataDiv[orientation], &mDataDiv[grv], &mDataDiv[gmrv],
                &mDataDiv[rv], &mDataDiv[la], &mDataDiv[grav], &mDataDiv[ungyro], &mDataDiv[unmag], &mDataDiv[pdr]);
        }
        close(fd);
    } else {
        ALOGE("open fusion misc path %s fail ", datapath);
    }
}

FusionSensor::~FusionSensor() {
}

int FusionSensor::HandleToIndex(int handle) {
    int index = -1;

    switch (handle) {
    case ID_ORIENTATION:
        index = orientation;
        break;
    case ID_GAME_ROTATION_VECTOR:
        index = grv;
        break;
    case ID_GEOMAGNETIC_ROTATION_VECTOR:
        index = gmrv;
        break;
    case ID_ROTATION_VECTOR:
        index = rv;
        break;
    case ID_LINEAR_ACCELERATION:
        index = la;
        break;
    case ID_GRAVITY:
        index = grav;
        break;
    case ID_GYROSCOPE_UNCALIBRATED:
        index = ungyro;
        break;
    case ID_MAGNETIC_UNCALIBRATED:
        index = unmag;
        break;
    case ID_PDR:
        index = pdr;
        break;
    }

    return index;
}
int FusionSensor::enable(int32_t handle, int en)
{
    int fd, index = -1;
    int flags = en ? 1 : 0;
    char buf[8] = {0};

    ALOGI("enable, handle:%d, en:%d\n", handle, en);
    strlcpy(&input_sysfs_path[input_sysfs_path_len], "fusionactive", sizeof(input_sysfs_path) - input_sysfs_path_len);
    fd = TEMP_FAILURE_RETRY(open(input_sysfs_path, O_RDWR));
    if (fd < 0) {
        return -1;
    }

    index = HandleToIndex(handle);
    if (index < 0) {
        ALOGE("HandleToIndex err, handle:%d, index:%d\n", handle, index);
        return -1;
    }
    sprintf(buf, "%d,%d", handle, flags);
    if (flags) {
        mEnabled[index] = true;
        mEnabledTime[index] = getTimestamp() + IGNORE_EVENT_TIME;
    } else {
        mEnabled[index] = false;
    }

    TEMP_FAILURE_RETRY(write(fd, buf, sizeof(buf)));
    close(fd);
    return 0;
}

int FusionSensor::setDelay(int32_t handle, int64_t ns)
{
    int fd = -1;
    ALOGI("setDelay: (handle=%d, ns=%" PRId64 ")", handle, ns);
    strlcpy(&input_sysfs_path[input_sysfs_path_len], "fusiondelay", sizeof(input_sysfs_path) - input_sysfs_path_len);
    fd = TEMP_FAILURE_RETRY(open(input_sysfs_path, O_RDWR));
    if (fd < 0) {
        ALOGE("no setDelay control attr\r\n");
        return -1;
    }
    char buf[80] = {0};
    sprintf(buf, "%d,%" PRId64 "", handle, ns);
    TEMP_FAILURE_RETRY(write(fd, buf, strlen(buf)+1));
    close(fd);
    return 0;
}

int FusionSensor::batch(int handle, int flags, int64_t samplingPeriodNs, int64_t maxBatchReportLatencyNs)
{
    int fd = -1;
    char buf[128] = {0};

    ALOGI("batch: handle:%d, flag:%d,samplingPeriodNs:%" PRId64 " maxBatchReportLatencyNs:%" PRId64 "\r\n",
        handle, flags,samplingPeriodNs, maxBatchReportLatencyNs);

    strlcpy(&input_sysfs_path[input_sysfs_path_len], "fusionbatch", sizeof(input_sysfs_path) - input_sysfs_path_len);
    fd = TEMP_FAILURE_RETRY(open(input_sysfs_path, O_RDWR));
    if(fd < 0) {
        ALOGE("no batch control attr\r\n");
        return -1;
    }
    sprintf(buf, "%d,%d,%" PRId64 ",%" PRId64 "", handle, flags, samplingPeriodNs, maxBatchReportLatencyNs);
    TEMP_FAILURE_RETRY(write(fd, buf, sizeof(buf)));
    close(fd);
    return 0;
}

int FusionSensor::flush(int handle)
{
    int fd = -1, index = -1;
    char buf[32] = {0};

    index = HandleToIndex(handle);
    if (index < 0) {
        ALOGE("HandleToIndex err, handle:%d, index:%d\n", handle, index);
        return -1;
    }
    mFlushCnt[index]++;
    ALOGI("flush, handle:%d, mFlushCnt:%d\n", handle, mFlushCnt[index]);
    strlcpy(&input_sysfs_path[input_sysfs_path_len], "fusionflush", sizeof(input_sysfs_path) - input_sysfs_path_len);
    fd = TEMP_FAILURE_RETRY(open(input_sysfs_path, O_RDWR));
    if(fd < 0) {
        ALOGE("no flush control attr\r\n");
        return -1;
    }
    sprintf(buf, "%d", handle);
    TEMP_FAILURE_RETRY(write(fd, buf, sizeof(buf)));
    close(fd);
    return 0;
}

int FusionSensor::readEvents(sensors_event_t* data, int count)
{
    int index = -1;

    if (count < 1)
        return -EINVAL;

    ssize_t n = mSensorReader.fill();
    if (n < 0)
        return n;
    int numEventReceived = 0;
    struct sensor_event const* event;

    while (count && mSensorReader.readEvent(&event)) {
        processEvent(event);
        index = HandleToIndex(event->handle);
        if (index < 0)
            return -EINVAL;
        if (event->flush_action <= FLUSH_ACTION) {
            *data++ = mPendingEvent;
            numEventReceived++;
            count--;
        }
        mSensorReader.next();
    }
    return numEventReceived;
}

void FusionSensor::processEvent(struct sensor_event const *event)
{
    int index = HandleToIndex(event->handle);

    if (index < 0)
        ALOGE("HandleToIndex err, handle:%d, index:%d\n", event->handle, index);
    switch (event->handle) {
    case ID_ORIENTATION:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_ORIENTATION;
            mPendingEvent.type = SENSOR_TYPE_ORIENTATION;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.orientation.x = (float)event->word[0] / mDataDiv[index];
            mPendingEvent.orientation.y = (float)event->word[1] / mDataDiv[index];
            mPendingEvent.orientation.z = (float)event->word[2] / mDataDiv[index];
            mPendingEvent.orientation.status = event->status;
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_ORIENTATION;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mFlushCnt[index]--;
            ALOGI("orientation flush complete, mFlushCnt:%d\n", mFlushCnt[index]);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_GAME_ROTATION_VECTOR:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_GAME_ROTATION_VECTOR;
            mPendingEvent.type = SENSOR_TYPE_GAME_ROTATION_VECTOR;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.data[0] = (float)event->word[0] / mDataDiv[index];
            mPendingEvent.data[1] = (float)event->word[1] / mDataDiv[index];
            mPendingEvent.data[2] = (float)event->word[2] / mDataDiv[index];
            mPendingEvent.data[3] = (float)event->word[3] / mDataDiv[index];
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_GAME_ROTATION_VECTOR;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mFlushCnt[index]--;
            ALOGI("grv flush complete, mFlushCnt:%d\n", mFlushCnt[index]);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_GEOMAGNETIC_ROTATION_VECTOR:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_GEOMAGNETIC_ROTATION_VECTOR;
            mPendingEvent.type = SENSOR_TYPE_GEOMAGNETIC_ROTATION_VECTOR;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.data[0] = (float)event->word[0] / mDataDiv[index];
            mPendingEvent.data[1] = (float)event->word[1] / mDataDiv[index];
            mPendingEvent.data[2] = (float)event->word[2] / mDataDiv[index];
            mPendingEvent.data[3] = (float)event->word[3] / mDataDiv[index];
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_GEOMAGNETIC_ROTATION_VECTOR;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mFlushCnt[index]--;
            ALOGI("gmrv flush complete, mFlushCnt:%d\n", mFlushCnt[index]);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_ROTATION_VECTOR:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_ROTATION_VECTOR;
            mPendingEvent.type = SENSOR_TYPE_ROTATION_VECTOR;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.data[0] = (float)event->word[0] / mDataDiv[index];
            mPendingEvent.data[1] = (float)event->word[1] / mDataDiv[index];
            mPendingEvent.data[2] = (float)event->word[2] / mDataDiv[index];
            mPendingEvent.data[3] = (float)event->word[3] / mDataDiv[index];
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_ROTATION_VECTOR;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mFlushCnt[index]--;
            ALOGI("rv flush complete, mFlushCnt:%d\n", mFlushCnt[index]);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_LINEAR_ACCELERATION:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_LINEAR_ACCELERATION;
            mPendingEvent.type = SENSOR_TYPE_LINEAR_ACCELERATION;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.acceleration.x = (float)event->word[0] / mDataDiv[index];
            mPendingEvent.acceleration.y = (float)event->word[1] / mDataDiv[index];
            mPendingEvent.acceleration.z = (float)event->word[2] / mDataDiv[index];
            mPendingEvent.acceleration.status = event->status;
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_LINEAR_ACCELERATION;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mFlushCnt[index]--;
            ALOGI("la flush complete, mFlushCnt:%d\n", mFlushCnt[index]);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_GRAVITY:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_GRAVITY;
            mPendingEvent.type = SENSOR_TYPE_GRAVITY;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.acceleration.x = (float)event->word[0] / mDataDiv[index];
            mPendingEvent.acceleration.y = (float)event->word[1] / mDataDiv[index];
            mPendingEvent.acceleration.z = (float)event->word[2] / mDataDiv[index];
            mPendingEvent.acceleration.status = event->status;
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_GRAVITY;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mFlushCnt[index]--;
            ALOGI("grav flush complete, mFlushCnt:%d\n", mFlushCnt[index]);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_GYROSCOPE_UNCALIBRATED:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_GYROSCOPE_UNCALIBRATED;
            mPendingEvent.type = SENSOR_TYPE_GYROSCOPE_UNCALIBRATED;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.uncalibrated_gyro.x_uncalib = (float)event->word[0] / mDataDiv[index];
            mPendingEvent.uncalibrated_gyro.y_uncalib = (float)event->word[1] / mDataDiv[index];
            mPendingEvent.uncalibrated_gyro.z_uncalib = (float)event->word[2] / mDataDiv[index];
            mPendingEvent.uncalibrated_gyro.x_bias = (float)event->word[3] / mDataDiv[index];
            mPendingEvent.uncalibrated_gyro.y_bias = (float)event->word[4] / mDataDiv[index];
            mPendingEvent.uncalibrated_gyro.z_bias = (float)event->word[5] / mDataDiv[index];
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_GYROSCOPE_UNCALIBRATED;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mFlushCnt[index]--;
            ALOGI("ungyro flush complete, mFlushCnt:%d\n", mFlushCnt[index]);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_MAGNETIC_UNCALIBRATED:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_MAGNETIC_UNCALIBRATED;
            mPendingEvent.type = SENSOR_TYPE_MAGNETIC_FIELD_UNCALIBRATED;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.uncalibrated_magnetic.x_uncalib = (float)event->word[0] / mDataDiv[index];
            mPendingEvent.uncalibrated_magnetic.y_uncalib = (float)event->word[1] / mDataDiv[index];
            mPendingEvent.uncalibrated_magnetic.z_uncalib = (float)event->word[2] / mDataDiv[index];
            mPendingEvent.uncalibrated_magnetic.x_bias = (float)event->word[3] / mDataDiv[index];
            mPendingEvent.uncalibrated_magnetic.y_bias = (float)event->word[4] / mDataDiv[index];
            mPendingEvent.uncalibrated_magnetic.z_bias = (float)event->word[5] / mDataDiv[index];
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_MAGNETIC_UNCALIBRATED;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mFlushCnt[index]--;
            ALOGI("unmag flush complete, mFlushCnt:%d\n", mFlushCnt[index]);
        } else
            ALOGE("unknow action\n");
        break;
    }
}
#else

#define FLOAT_TO_INTEGER 1000000

#define MAX_SAMPLE_DELAY_NS   0x7FFFFFFFFFFFFFFFULL
#define MAX_REPORT_LETANCY_NS 200000000ULL

#ifndef MAGNETOMETER_MINDELAY
#define MIN_MAG_SAMPLE_DELAY_NS  20000000
#else
#define MIN_MAG_SAMPLE_DELAY_NS  (MAGNETOMETER_MINDELAY * 1000)
#endif

#ifndef ACCELEROMETER_MINDELAY
#define MIN_ACC_SAMPLE_DELAY_NS  10000000
#else
#define MIN_ACC_SAMPLE_DELAY_NS  (ACCELEROMETER_MINDELAY * 1000)
#endif

#ifndef GYROSCOPE_MINDELAY
#define MIN_GYRO_SAMPLE_DELAY_NS  10000000
#else
#define MIN_GYRO_SAMPLE_DELAY_NS  (GYROSCOPE_MINDELAY * 1000)
#endif

static BaseInterface *selectInterface(void) {
#ifdef FUSION_USE_MTK_ALGORITHM
    return MtkInterface::getInstance();
#else
    return VendorInterface::getInstance();
#endif
}

FusionSensor::FusionSensor()
    : mSensorReader(BATCH_SENSOR_MAX_READ_INPUT_NUMEVENTS) {
    int pipeFds[2] = {0};

    mPendingEvent.version = 0;
    mPendingEvent.sensor = 0;
    mPendingEvent.type = 0;
    memset(mPendingEvent.data, 0x00, sizeof(mPendingEvent.data));
    mPendingEvent.flags = 0;
    mPendingEvent.reserved0 = 0;
    mPendingEvent.timestamp = 0;

    mWritePipeFd = -1;
    memset(mSensorInfo, 0, sizeof(mSensorInfo));
    for (int index = orientation; index < max_fusion_support; ++index) {
        mSensorInfo[index].samplingPeriodNs = MAX_SAMPLE_DELAY_NS;
        mSensorInfo[index].batchReportLatencyNs = MAX_REPORT_LETANCY_NS;
        mSensorInfo[index].useAccData = true;
#ifdef FUSION_SUPPORT_9D_ALGORITHM
        mSensorInfo[index].useGyroData = true;
#else
        mSensorInfo[index].useGyroData = false;
#endif
        mSensorInfo[index].useMagData = true;
    }
#ifdef FUSION_SUPPORT_9D_ALGORITHM
    mSensorInfo[grv].useMagData = false;
#else
    mSensorInfo[grv].useMagData = true;
#endif
    mSensorInfo[gmrv].useGyroData = false;
    mSensorInfo[ungyro].useAccData = false;
    mSensorInfo[ungyro].useGyroData = true;
    mSensorInfo[ungyro].useMagData = false;
    mSensorInfo[unmag].useAccData = false;
    mSensorInfo[unmag].useGyroData = false;
    mSensorInfo[unmag].useMagData = true;
    bestSamplingPeriodNs = MAX_SAMPLE_DELAY_NS;
    bestBatchReportLatencyNs = MAX_REPORT_LETANCY_NS;
    gyroEnabledCount = 0;
    accEnabledCount = 0;
    magEnabledCount = 0;

    if (mSensorReader.selectSensorEventFd(NULL) >= 0)
        mWritePipeFd = mSensorReader.getWriteFd();

    mBaseInterface = selectInterface();
    mSensorManager = SensorManager::getInstance();
    mSensorConnection = mSensorManager->createSensorConnection(fusion);
    mSensorCalibration = SensorCalibration::getInstance();
}

FusionSensor::~FusionSensor() {
    mBaseInterface = NULL;
    mSensorManager->removeSensorConnection(mSensorConnection);
    mSensorManager = NULL;
}

int FusionSensor::HandleToIndex(int handle) {
    int index = -1;

    switch (handle) {
    case ID_ORIENTATION:
        index = orientation;
        break;
    case ID_GAME_ROTATION_VECTOR:
        index = grv;
        break;
    case ID_GEOMAGNETIC_ROTATION_VECTOR:
        index = gmrv;
        break;
    case ID_ROTATION_VECTOR:
        index = rv;
        break;
    case ID_LINEAR_ACCELERATION:
        index = la;
        break;
    case ID_GRAVITY:
        index = grav;
        break;
    case ID_GYROSCOPE_UNCALIBRATED:
        index = ungyro;
        break;
    case ID_MAGNETIC_UNCALIBRATED:
        index = unmag;
        break;
    case ID_PDR:
        index = pdr;
        break;
    }

    return index;
}

int FusionSensor::reportFlush(int handle) {
    struct sensor_event event;

    memset(&event, 0, sizeof(struct sensor_event));
    event.handle = handle;
    event.flush_action = FLUSH_ACTION;
    mSensorReader.writeEvent(&event);
    return 0;
}

int FusionSensor::reportData(int handle, struct sensorData *data) {
    struct sensor_event event;

    memset(&event, 0, sizeof(struct sensor_event));
    event.handle = handle;
    event.time_stamp = data->timeStamp;
    event.flush_action = DATA_ACTION;
    event.word[0] = data->data[0] * FLOAT_TO_INTEGER;
    event.word[1] = data->data[1] * FLOAT_TO_INTEGER;
    event.word[2] = data->data[2] * FLOAT_TO_INTEGER;
    event.word[3] = data->data[3] * FLOAT_TO_INTEGER;
    event.word[4] = data->data[4] * FLOAT_TO_INTEGER;
    event.word[5] = data->data[5] * FLOAT_TO_INTEGER;
    event.status = data->status;
    mSensorReader.writeEvent(&event);
    return 0;
}

int FusionSensor::selectBestSampleLatency(void) {
    for (int index = orientation; index < max_fusion_support; ++index) {
        if (mSensorInfo[index].mEnabled) {
            if (bestSamplingPeriodNs > mSensorInfo[index].samplingPeriodNs) {
                bestSamplingPeriodNs = mSensorInfo[index].samplingPeriodNs;
            }
            if (bestBatchReportLatencyNs > mSensorInfo[index].batchReportLatencyNs) {
                bestBatchReportLatencyNs = mSensorInfo[index].batchReportLatencyNs;
            }
        }
    }
    if (bestSamplingPeriodNs < 0)
        bestSamplingPeriodNs = 0;
    if (bestBatchReportLatencyNs < 0)
        bestBatchReportLatencyNs = 0;
    if (bestBatchReportLatencyNs > MAX_REPORT_LETANCY_NS)
        bestBatchReportLatencyNs = MAX_REPORT_LETANCY_NS;

    /* ALOGI("bestSamplingPeriodNs:%" PRId64 ", bestBatchReportLatencyNs:%" PRId64 "\n",
        bestSamplingPeriodNs, bestBatchReportLatencyNs); */
    return 0;
}

int FusionSensor::getUncaliGyroAndReport(sensors_event_t *data) {
    struct sensorData outputData;

    memset(&outputData, 0, sizeof(struct sensorData));
    if (mSensorInfo[ungyro].mEnabled) {
        mSensorCalibration->gyroGetCalibration(&outputData);
        // bias
        outputData.data[3] = outputData.data[0];
        outputData.data[4] = outputData.data[1];
        outputData.data[5] = outputData.data[2];
        // raw data
        outputData.data[0] = data->data[0] + outputData.data[0];
        outputData.data[1] = data->data[1] + outputData.data[1];
        outputData.data[2] = data->data[2] + outputData.data[2];
        outputData.timeStamp = data->timestamp;
        reportData(ID_GYROSCOPE_UNCALIBRATED, &outputData);
    }
    return 0;
}

int FusionSensor::getUncaliMagAndReport(sensors_event_t *data) {
    struct sensorData outputData;

    memset(&outputData, 0, sizeof(struct sensorData));
    if (mSensorInfo[unmag].mEnabled) {
        mSensorCalibration->magGetCalibration(&outputData);
        // bias
        outputData.data[3] = outputData.data[0];
        outputData.data[4] = outputData.data[1];
        outputData.data[5] = outputData.data[2];
        // raw data
        outputData.data[0] = data->data[0] + outputData.data[0];
        outputData.data[1] = data->data[1] + outputData.data[1];
        outputData.data[2] = data->data[2] + outputData.data[2];
        outputData.timeStamp = data->timestamp;
        reportData(ID_MAGNETIC_UNCALIBRATED, &outputData);
    }
    return 0;
}

int FusionSensor::getFusionAndReport() {
    struct sensorData outputData;

    memset(&outputData, 0, sizeof(struct sensorData));
    if (mSensorInfo[orientation].mEnabled) {
        mBaseInterface->getOrientation(&outputData);
        reportData(ID_ORIENTATION, &outputData);
    }
    if (mSensorInfo[grv].mEnabled) {
        mBaseInterface->getGameRotationVector(&outputData);
        reportData(ID_GAME_ROTATION_VECTOR, &outputData);
    }
    if (mSensorInfo[gmrv].mEnabled) {
        mBaseInterface->getGeoMagnetic(&outputData);
        reportData(ID_GEOMAGNETIC_ROTATION_VECTOR, &outputData);
    }
    if (mSensorInfo[rv].mEnabled) {
        mBaseInterface->getRotationVector(&outputData);
        reportData(ID_ROTATION_VECTOR, &outputData);
    }
    if (mSensorInfo[la].mEnabled) {
        mBaseInterface->getLinearaccel(&outputData);
        reportData(ID_LINEAR_ACCELERATION, &outputData);
    }
    if (mSensorInfo[grav].mEnabled) {
        mBaseInterface->getGravity(&outputData);
        reportData(ID_GRAVITY, &outputData);
    }
    return 0;
}

int FusionSensor::enable(int32_t handle, int en) {
    int index = -1, total = 0;
    int64_t samplingPeriodNs = 0;
    ALOGI("enable, handle:%d, en:%d\n", handle, en);

    index = HandleToIndex(handle);
    if (index < 0) {
        ALOGE("HandleToIndex err, handle:%d, index:%d\n", handle, index);
        return -1;
    }

    if (!!en) {
        mSensorInfo[index].mEnabled = true;
        selectBestSampleLatency();
        /* gyro enable */
        if (mSensorInfo[index].useGyroData) {
            if (bestSamplingPeriodNs < MIN_GYRO_SAMPLE_DELAY_NS)
                samplingPeriodNs = MIN_GYRO_SAMPLE_DELAY_NS;
            else
                samplingPeriodNs = bestSamplingPeriodNs;
            mSensorManager->batch(mSensorConnection, ID_GYROSCOPE, samplingPeriodNs, bestBatchReportLatencyNs);
            if (!gyroEnabledCount++) {
                mSensorManager->activate(mSensorConnection, ID_GYROSCOPE, true);
            }
        }
        /* acc enable */
        if (mSensorInfo[index].useAccData) {
            if (bestSamplingPeriodNs < MIN_ACC_SAMPLE_DELAY_NS)
                samplingPeriodNs = MIN_ACC_SAMPLE_DELAY_NS;
            else
                samplingPeriodNs = bestSamplingPeriodNs;
            mSensorManager->batch(mSensorConnection, ID_ACCELEROMETER, samplingPeriodNs, bestBatchReportLatencyNs);
            if (!accEnabledCount++) {
                mSensorManager->activate(mSensorConnection, ID_ACCELEROMETER, true);
            }
        }
        /* mag enable */
        if (mSensorInfo[index].useMagData) {
            if (bestSamplingPeriodNs < MIN_MAG_SAMPLE_DELAY_NS)
                samplingPeriodNs = MIN_MAG_SAMPLE_DELAY_NS;
            else
                samplingPeriodNs = bestSamplingPeriodNs;
            mSensorManager->batch(mSensorConnection, ID_MAGNETIC, samplingPeriodNs, bestBatchReportLatencyNs);
            if (!magEnabledCount++) {
                mSensorManager->activate(mSensorConnection, ID_MAGNETIC, true);
            }
        }
    } else {
        mSensorInfo[index].mEnabled = false;
        mSensorInfo[index].samplingPeriodNs = MAX_SAMPLE_DELAY_NS;
        mSensorInfo[index].batchReportLatencyNs = MAX_REPORT_LETANCY_NS;
        selectBestSampleLatency();
        /* gyro disable */
        if (mSensorInfo[index].useGyroData) {
            if (!--gyroEnabledCount) {
                mSensorManager->activate(mSensorConnection, ID_GYROSCOPE, false);
            } else if (gyroEnabledCount > 0) {
                if (bestSamplingPeriodNs < MIN_GYRO_SAMPLE_DELAY_NS)
                    samplingPeriodNs = MIN_GYRO_SAMPLE_DELAY_NS;
                else
                    samplingPeriodNs = bestSamplingPeriodNs;
                mSensorManager->batch(mSensorConnection, ID_GYROSCOPE, samplingPeriodNs, bestBatchReportLatencyNs);
            } else
                gyroEnabledCount = 0;
        }
        /* acc disable */
        if (mSensorInfo[index].useAccData) {
            if (!--accEnabledCount) {
                mSensorManager->activate(mSensorConnection, ID_ACCELEROMETER, false);
            } else if (accEnabledCount > 0) {
                if (bestSamplingPeriodNs < MIN_ACC_SAMPLE_DELAY_NS)
                    samplingPeriodNs = MIN_ACC_SAMPLE_DELAY_NS;
                else
                    samplingPeriodNs = bestSamplingPeriodNs;
                mSensorManager->batch(mSensorConnection, ID_ACCELEROMETER, samplingPeriodNs, bestBatchReportLatencyNs);
            } else
                accEnabledCount = 0;
        }
        /* mag disable */
        if (mSensorInfo[index].useMagData) {
            if (!--magEnabledCount) {
                mSensorManager->activate(mSensorConnection, ID_MAGNETIC, false);
            } else if (magEnabledCount > 0) {
                if (bestSamplingPeriodNs < MIN_MAG_SAMPLE_DELAY_NS)
                    samplingPeriodNs = MIN_MAG_SAMPLE_DELAY_NS;
                else
                    samplingPeriodNs = bestSamplingPeriodNs;
                mSensorManager->batch(mSensorConnection, ID_MAGNETIC, samplingPeriodNs, bestBatchReportLatencyNs);
            } else
                magEnabledCount = 0;
        }
        /* reset best batch params */
        for (int index = orientation; index < max_fusion_support; ++index) {
            total += mSensorInfo[index].mEnabled;
        }
        if (!total) {
            bestSamplingPeriodNs = MAX_SAMPLE_DELAY_NS;
            bestBatchReportLatencyNs = MAX_REPORT_LETANCY_NS;
        }
    }
    return 0;
}

int FusionSensor::setDelay(int32_t handle, int64_t ns) {
    ALOGD("setDelay: (handle=%d, ns=%" PRId64 ")", handle, ns);
    return 0;
}

int FusionSensor::batch(int handle, int flags,
    int64_t samplingPeriodNs, int64_t maxBatchReportLatencyNs) {
    int index = -1;
    int64_t tmpSamplingPeriodNs;

    ALOGI("batch: handle:%d, flag:%d,samplingPeriodNs:%" PRId64 " maxBatchReportLatencyNs:%" PRId64 "\n",
        handle, flags,samplingPeriodNs, maxBatchReportLatencyNs);

    index = HandleToIndex(handle);
    if (index < 0) {
        ALOGE("HandleToIndex err, handle:%d, index:%d\n", handle, index);
        return -1;
    }

    mSensorInfo[index].samplingPeriodNs = samplingPeriodNs;
    mSensorInfo[index].batchReportLatencyNs = maxBatchReportLatencyNs;
    selectBestSampleLatency();

    /* gyro batch */
    if (mSensorInfo[index].useGyroData) {
        if (bestSamplingPeriodNs < MIN_GYRO_SAMPLE_DELAY_NS)
            tmpSamplingPeriodNs = MIN_GYRO_SAMPLE_DELAY_NS;
        else
            tmpSamplingPeriodNs = bestSamplingPeriodNs;
        if (gyroEnabledCount)
            mSensorManager->batch(mSensorConnection, ID_GYROSCOPE, tmpSamplingPeriodNs, bestBatchReportLatencyNs);
    }
    /* acc batch */
    if (mSensorInfo[index].useAccData) {
        if (bestSamplingPeriodNs < MIN_ACC_SAMPLE_DELAY_NS)
            tmpSamplingPeriodNs = MIN_ACC_SAMPLE_DELAY_NS;
        else
            tmpSamplingPeriodNs = bestSamplingPeriodNs;
        if (accEnabledCount)
            mSensorManager->batch(mSensorConnection, ID_ACCELEROMETER, tmpSamplingPeriodNs, bestBatchReportLatencyNs);
    }
    /* mag batch */
    if (mSensorInfo[index].useMagData) {
        if (bestSamplingPeriodNs < MIN_MAG_SAMPLE_DELAY_NS)
            tmpSamplingPeriodNs = MIN_MAG_SAMPLE_DELAY_NS;
        else
            tmpSamplingPeriodNs = bestSamplingPeriodNs;
        if (magEnabledCount)
            mSensorManager->batch(mSensorConnection, ID_MAGNETIC, tmpSamplingPeriodNs, bestBatchReportLatencyNs);
    }
    return 0;
}

int FusionSensor::flush(int handle) {
    int index = -1;

    index = HandleToIndex(handle);
    if (index < 0) {
        ALOGE("HandleToIndex err, handle:%d, index:%d\n", handle, index);
        return -1;
    }
    mSensorInfo[index].mFlushCnt++;

    reportFlush(handle);
    return 0;
}

int FusionSensor::setEvent(sensors_event_t *data) {
    struct sensorData inputData;

    // ALOGD("handle=%d x=%f, y=%f, z=%f\n", data->sensor, data->data[0], data->data[1], data->data[2]);

    memset(&inputData, 0, sizeof(struct sensorData));

    inputData.timeStamp = data->timestamp;
    inputData.data[0] = data->data[0];
    inputData.data[1] = data->data[1];
    inputData.data[2] = data->data[2];
    if (data->sensor == ID_ACCELEROMETER) {
        inputData.status = data->acceleration.status;
        mBaseInterface->setAccData(&inputData);
#ifndef FUSION_SUPPORT_9D_ALGORITHM
        getFusionAndReport();
#endif
    } else if (data->sensor == ID_GYROSCOPE) {
        inputData.status = data->gyro.status;
        mBaseInterface->setGyroData(&inputData);
        getUncaliGyroAndReport(data);
#ifdef FUSION_SUPPORT_9D_ALGORITHM
        getFusionAndReport();
#endif
    } else if (data->sensor == ID_MAGNETIC) {
        inputData.status = data->magnetic.status;
        mBaseInterface->setMagData(&inputData);
        getUncaliMagAndReport(data);
    }
    return 0;
}

int FusionSensor::readEvents(sensors_event_t* data, int count) {
    int index = -1;

    if (count < 1)
        return -EINVAL;

    ssize_t n = mSensorReader.fill();
    if (n < 0)
        return n;
    int numEventReceived = 0;
    struct sensor_event const* event;

    while (count && mSensorReader.readEvent(&event)) {
        processEvent(event);
        index = HandleToIndex(event->handle);
        if (index < 0)
            return -EINVAL;
        *data++ = mPendingEvent;
        numEventReceived++;
        count--;
        mSensorReader.next();
    }
    return numEventReceived;
}

void FusionSensor::processEvent(struct sensor_event const *event)
{
    int index = HandleToIndex(event->handle);

    if (index < 0)
        ALOGE("HandleToIndex err, handle:%d, index:%d\n", event->handle, index);
    switch (event->handle) {
    case ID_ORIENTATION:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_ORIENTATION;
            mPendingEvent.type = SENSOR_TYPE_ORIENTATION;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.orientation.x = (float)event->word[0] / FLOAT_TO_INTEGER;
            mPendingEvent.orientation.y = (float)event->word[1] / FLOAT_TO_INTEGER;
            mPendingEvent.orientation.z = (float)event->word[2] / FLOAT_TO_INTEGER;
            mPendingEvent.orientation.status = event->status;
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_ORIENTATION;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mSensorInfo[index].mFlushCnt--;
            ALOGD("orientation flush complete, mFlushCnt:%d\n", mSensorInfo[index].mFlushCnt);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_GAME_ROTATION_VECTOR:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_GAME_ROTATION_VECTOR;
            mPendingEvent.type = SENSOR_TYPE_GAME_ROTATION_VECTOR;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.data[0] = (float)event->word[0] / FLOAT_TO_INTEGER;
            mPendingEvent.data[1] = (float)event->word[1] / FLOAT_TO_INTEGER;
            mPendingEvent.data[2] = (float)event->word[2] / FLOAT_TO_INTEGER;
            mPendingEvent.data[3] = (float)event->word[3] / FLOAT_TO_INTEGER;
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_GAME_ROTATION_VECTOR;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mSensorInfo[index].mFlushCnt--;
            ALOGD("grv flush complete, mFlushCnt:%d\n", mSensorInfo[index].mFlushCnt);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_GEOMAGNETIC_ROTATION_VECTOR:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_GEOMAGNETIC_ROTATION_VECTOR;
            mPendingEvent.type = SENSOR_TYPE_GEOMAGNETIC_ROTATION_VECTOR;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.data[0] = (float)event->word[0] / FLOAT_TO_INTEGER;
            mPendingEvent.data[1] = (float)event->word[1] / FLOAT_TO_INTEGER;
            mPendingEvent.data[2] = (float)event->word[2] / FLOAT_TO_INTEGER;
            mPendingEvent.data[3] = (float)event->word[3] / FLOAT_TO_INTEGER;
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_GEOMAGNETIC_ROTATION_VECTOR;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mSensorInfo[index].mFlushCnt--;
            ALOGD("gmrv flush complete, mFlushCnt:%d\n", mSensorInfo[index].mFlushCnt);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_ROTATION_VECTOR:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_ROTATION_VECTOR;
            mPendingEvent.type = SENSOR_TYPE_ROTATION_VECTOR;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.data[0] = (float)event->word[0] / FLOAT_TO_INTEGER;
            mPendingEvent.data[1] = (float)event->word[1] / FLOAT_TO_INTEGER;
            mPendingEvent.data[2] = (float)event->word[2] / FLOAT_TO_INTEGER;
            mPendingEvent.data[3] = (float)event->word[3] / FLOAT_TO_INTEGER;
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_ROTATION_VECTOR;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mSensorInfo[index].mFlushCnt--;
            ALOGD("rv flush complete, mFlushCnt:%d\n", mSensorInfo[index].mFlushCnt);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_LINEAR_ACCELERATION:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_LINEAR_ACCELERATION;
            mPendingEvent.type = SENSOR_TYPE_LINEAR_ACCELERATION;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.acceleration.x = (float)event->word[0] / FLOAT_TO_INTEGER;
            mPendingEvent.acceleration.y = (float)event->word[1] / FLOAT_TO_INTEGER;
            mPendingEvent.acceleration.z = (float)event->word[2] / FLOAT_TO_INTEGER;
            mPendingEvent.acceleration.status = event->status;
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_LINEAR_ACCELERATION;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mSensorInfo[index].mFlushCnt--;
            ALOGD("la flush complete, mFlushCnt:%d\n", mSensorInfo[index].mFlushCnt);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_GRAVITY:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_GRAVITY;
            mPendingEvent.type = SENSOR_TYPE_GRAVITY;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.acceleration.x = (float)event->word[0] / FLOAT_TO_INTEGER;
            mPendingEvent.acceleration.y = (float)event->word[1] / FLOAT_TO_INTEGER;
            mPendingEvent.acceleration.z = (float)event->word[2] / FLOAT_TO_INTEGER;
            mPendingEvent.acceleration.status = event->status;
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_GRAVITY;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mSensorInfo[index].mFlushCnt--;
            ALOGD("grav flush complete, mFlushCnt:%d\n", mSensorInfo[index].mFlushCnt);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_GYROSCOPE_UNCALIBRATED:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_GYROSCOPE_UNCALIBRATED;
            mPendingEvent.type = SENSOR_TYPE_GYROSCOPE_UNCALIBRATED;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.uncalibrated_gyro.x_uncalib = (float)event->word[0] / FLOAT_TO_INTEGER;
            mPendingEvent.uncalibrated_gyro.y_uncalib = (float)event->word[1] / FLOAT_TO_INTEGER;
            mPendingEvent.uncalibrated_gyro.z_uncalib = (float)event->word[2] / FLOAT_TO_INTEGER;
            mPendingEvent.uncalibrated_gyro.x_bias = (float)event->word[3] / FLOAT_TO_INTEGER;
            mPendingEvent.uncalibrated_gyro.y_bias = (float)event->word[4] / FLOAT_TO_INTEGER;
            mPendingEvent.uncalibrated_gyro.z_bias = (float)event->word[5] / FLOAT_TO_INTEGER;
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_GYROSCOPE_UNCALIBRATED;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mSensorInfo[index].mFlushCnt--;
            ALOGD("ungyro flush complete, mFlushCnt:%d\n", mSensorInfo[index].mFlushCnt);
        } else
            ALOGE("unknow action\n");
        break;
    case ID_MAGNETIC_UNCALIBRATED:
        if (event->flush_action == DATA_ACTION) {
            mPendingEvent.version = sizeof(sensors_event_t);
            mPendingEvent.sensor = ID_MAGNETIC_UNCALIBRATED;
            mPendingEvent.type = SENSOR_TYPE_MAGNETIC_FIELD_UNCALIBRATED;
            mPendingEvent.timestamp = event->time_stamp;
            mPendingEvent.uncalibrated_magnetic.x_uncalib = (float)event->word[0] / FLOAT_TO_INTEGER;
            mPendingEvent.uncalibrated_magnetic.y_uncalib = (float)event->word[1] / FLOAT_TO_INTEGER;
            mPendingEvent.uncalibrated_magnetic.z_uncalib = (float)event->word[2] / FLOAT_TO_INTEGER;
            mPendingEvent.uncalibrated_magnetic.x_bias = (float)event->word[3] / FLOAT_TO_INTEGER;
            mPendingEvent.uncalibrated_magnetic.y_bias = (float)event->word[4] / FLOAT_TO_INTEGER;
            mPendingEvent.uncalibrated_magnetic.z_bias = (float)event->word[5] / FLOAT_TO_INTEGER;
        } else if (event->flush_action == FLUSH_ACTION) {
            mPendingEvent.version = META_DATA_VERSION;
            mPendingEvent.sensor = 0;
            mPendingEvent.type = SENSOR_TYPE_META_DATA;
            mPendingEvent.meta_data.what = META_DATA_FLUSH_COMPLETE;
            mPendingEvent.meta_data.sensor = ID_MAGNETIC_UNCALIBRATED;
            // must fill timestamp, if not, readEvents may can not report flush to framework
            mPendingEvent.timestamp = android::elapsedRealtimeNano() + IGNORE_EVENT_TIME;
            mSensorInfo[index].mFlushCnt--;
            ALOGD("unmag flush complete, mFlushCnt:%d\n", mSensorInfo[index].mFlushCnt);
        } else
            ALOGE("unknow action\n");
        break;
    }
}

#endif
