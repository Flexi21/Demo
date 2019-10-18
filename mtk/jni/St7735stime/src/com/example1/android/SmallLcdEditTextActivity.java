package com.example1.android;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.Array;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Enumeration;
import java.util.List;






import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.location.GpsStatus;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.media.ExifInterface;
import android.media.MediaRecorder;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.BatteryManager;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.StatFs;
import android.os.storage.StorageManager;
import android.text.Editable;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.PopupWindow;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;
import android.text.TextWatcher;


public class SmallLcdEditTextActivity extends Activity implements OnClickListener {

	private Button mbtn1;


	
	private Toast mToast;
	private EditText mEditText;
	private TextView m_TextView;
	private String mInputTest;

	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.smalllcd_main);
		initlayout();
	


	}


	private void initlayout() {
		m_TextView = (TextView) findViewById(R.id.TextView01);
		mEditText = (EditText) findViewById(R.id.EditText01);
		mbtn1 = (Button) findViewById(R.id.btn1);


		m_TextView.setText("输入文本框的内容是：");
		mbtn1.setText("确认");
		
		mbtn1.setOnClickListener(this);


		mEditText.addTextChangedListener(new TextWatcher() {
			 
            @Override
            public void onTextChanged(CharSequence s, int start, int before,
                    int count) {
            }
 
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count,
                    int after) {
            }
 
            @Override
            public void afterTextChanged(Editable s) {
 

                mInputTest = s.toString();
            	
                //延迟800ms，如果不再输入字符，则执行该线程的run方法
              //  handler.postDelayed(delayRun, 800);
 
 
            }
        });
		
	}
	

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch (v.getId()) {
		case R.id.btn1:
			mToast = Toast.makeText(this, mInputTest, Toast.LENGTH_SHORT);
			Log.i("zhoubin111","mInputTest="+mInputTest);
			  try {
				  com.example.android.St7735s.lcdShowChinese(mInputTest.getBytes("gb2312"));
             } catch (UnsupportedEncodingException e) {
                  e.printStackTrace();
             }
			break;



			
		
		default:
			break;
		}
	}
	
	

	

}
