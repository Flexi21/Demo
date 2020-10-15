package com.android.server;  
import android.content.Context;  
import android.os.IMiscdrvService;  
import android.util.Log;  
import android.os.RtcTime;

public class MiscdrvService extends IMiscdrvService.Stub {  
	private static final String TAG = "MiscdrvService";  
	private int jniPtr = -1;
	
	MiscdrvService() 
	{
		jniPtr =  miscdrvNativeOpen(); 
		Log.d(TAG,"miscdrv jniPtr="+jniPtr);	   
	}
	
	public void miscdrvDummy() 
	{
		Log.d(TAG,"miscdrvDummy Entry!");	   
		miscdrvNativeDummy();
	}
	
	public void miscdrvLedCtrl(int type, int brightness, int on_ms, int off_ms)
	{
		Log.d(TAG,"miscdrvLedCtrl Entry!");	
		miscdrvNativeJniLedCtrl(type, brightness, on_ms, off_ms);
	}

	public RtcTime miscdrvReadtime()
	{
		RtcTime rtc = miscdrvNativeJniReadtime();	
	
		Log.d(TAG,"miscdrv miscdrvReadtime rtc"+rtc.tm_year+":"+rtc.tm_mon+":"+rtc.tm_mday
									+" "+rtc.tm_wday+" "+rtc.tm_hour+":"+rtc.tm_min+":"+rtc.tm_sec);
	
		return rtc;
	}

	public void miscdrvSettime(int year, int mon, int mday,int wday, int hour, int min, int sec)
	{
		int ret;
		Log.d(TAG,"miscdrvSettime Entry!");	
		ret = miscdrvNativeJniSettime(year, mon, mday, wday, hour, min, sec);
		if (ret < 0)
			Log.e(TAG,"miscdrvSettime failed!");	
	}
	
	public void miscdrvSetWdClk(int val)
	{
		Log.d(TAG,"miscdrvSetWdClk Entry!");	
		miscdrvNativeJniSetWdClk(val);
	}
	
	private native int miscdrvNativeOpen();  
	private native void miscdrvNativeDummy();  
	private native void miscdrvNativeJniLedCtrl(int type, int brightness, int on_ms, int off_ms);
	private native RtcTime miscdrvNativeJniReadtime();
	private native int miscdrvNativeJniSettime(int year, int mon, int mday, int 
                                                   wday, int hour, int min, int sec);
	private native void miscdrvNativeJniSetWdClk(int val);
}; 

