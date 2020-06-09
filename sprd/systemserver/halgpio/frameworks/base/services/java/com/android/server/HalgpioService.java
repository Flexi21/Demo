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

package com.android.server;

import android.app.AppOpsManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.database.ContentObserver;
import android.hardware.input.InputManager;
import android.os.BatteryStats;
import android.os.Handler;
import android.os.PowerManager;
import android.os.Process;
import android.os.RemoteException;
import android.os.IBinder;
import android.os.Binder;
import android.os.IHalgpioService;
import android.os.ServiceManager;
import android.os.SystemClock;
import android.os.UserHandle;
import android.os.Vibrator;
import android.os.WorkSource;
import android.provider.Settings;
import android.provider.Settings.SettingNotFoundException;
import android.util.Slog;
import android.view.InputDevice;

import com.android.internal.app.IAppOpsService;
import com.android.internal.app.IBatteryStats;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.ListIterator;

public class HalgpioService extends IHalgpioService.Stub {
	private static final String TAG = "halGpio";
	private int ptr;
		
	HalgpioService() {
		ptr = halGpioOpen();
		Slog.e(TAG, "con func entry!"+ptr);
	}
		
	public void setHalgpioVal(int num, int val) 
	{
		Slog.e(TAG, "setHalgpioVal");
		halGpioGetValue(12);
	}
	
	public void getHalgpioVal(int num)
	{
		Slog.e(TAG, "getHalgpioVal");
	}
	
	public void setHalgpioDir(int num, int val)
	{
		Slog.e(TAG, "setHalgpioDir");
	}
	
	public void getHalgpioDir(int num)
	{
		Slog.e(TAG, "getHalgpioDir");
	}
	
	private static native int halGpioOpen();
	private static native int halGpioGetValue(int num);
	private static native int halGpioSetValue(int num, int val);
	private static native int halGpioGetDir(int num);
	private static native int halGpioSetDir(int num, int dir);

}
