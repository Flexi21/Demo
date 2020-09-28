package com.android.server;  
import android.content.Context;  
import android.os.IMiscdrvService;  
import android.util.Log;  


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

	private native int miscdrvNativeOpen();  
	private native void miscdrvNativeDummy();  
}; 

