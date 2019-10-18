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

package com.example1.android;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.os.Bundle;
import android.widget.Button;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Toast;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.BroadcastReceiver;
import android.content.Context;
import java.io.UnsupportedEncodingException;

public class St7735stime extends Activity {

/*
    static {
        System.loadLibrary("St7735stime");
    }

    public static native void lcdSetTime(int hour,int minute);
*/
    //public static native void lcdStopChinese();
    //public static native void lcdShowIcon(int icon,int show);
    String str1 = "1多行显示测试测试2多行显示测试测试3多行显示测试测试4多行显示测试测试5多行显示测试测试6多行显示测试测试7多行显示测试测试8多行显示测试测试9多行显示测试测试0多行显示测试测试a多行显示测试测试b多行显示测试测试c多行显示测试测试d多行显示测试测试e多行显示测试测试f多行显示测试测试g多行显示测试测试h多行显示测试测试i多行显示测试测试j多行显示测试测试k多行显示测试测试l多行显示测试测试m多行显示测试测试n多行显示测试测试o多行显示测试测试p多行显示测试测试q多行显示测试测试r多行显示测试测试s多行显示测试测试t";
    String str2 = "一行显示测试!";
    String str3 = "两行显示测试!两行显示测试!";

    private Button button1;
    private Button button2;
    private Button button3;
    private Button button4;
    private Button button5;
    private Button button6;
    private Button button7;



    @Override
    public void onCreate(Bundle savedInstanceState) {
           super.onCreate(savedInstanceState);

           setContentView(R.layout.main);

           button1 = (Button)findViewById(R.id.button01);
           button2 = (Button)findViewById(R.id.button02);
           button3 = (Button)findViewById(R.id.button03);
           button4 = (Button)findViewById(R.id.button04);
           button5 = (Button)findViewById(R.id.button05);
           button6 = (Button)findViewById(R.id.button06);
           button7 = (Button)findViewById(R.id.button07);
           button1.setOnClickListener(listener);
           button2.setOnClickListener(listener);
           button3.setOnClickListener(listener);
           button4.setOnClickListener(listener);
           button5.setOnClickListener(listener);
           button6.setOnClickListener(listener);
           button7.setOnClickListener(listener);
           //button2.setVisibility(View.GONE);
           //button3.setVisibility(View.GONE);
           button4.setVisibility(View.GONE);
           button5.setVisibility(View.GONE);
           button6.setVisibility(View.GONE);
           button7.setVisibility(View.GONE);
           IntentFilter filter=new IntentFilter();
           filter.addAction(Intent.ACTION_TIME_TICK);
           registerReceiver(mReceiver,filter);

    };

    public void setTime() {
           Calendar calendar = Calendar.getInstance();
           int year = calendar.get(Calendar.YEAR);
           int month = calendar.get(Calendar.MONTH)+1;
           int day = calendar.get(Calendar.DAY_OF_MONTH);
           int hour = calendar.get(Calendar.HOUR_OF_DAY);
           int minute = calendar.get(Calendar.MINUTE);
           int second = calendar.get(Calendar.SECOND);
           Log.d("et_lcd",year+"."+month+"."+day+"."+hour+":"+minute+":"+second);
    };

    private final BroadcastReceiver mReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (action.equals(Intent.ACTION_TIME_TICK)) {
                setTime();
                Toast.makeText(getApplicationContext(), "time update", Toast.LENGTH_SHORT).show();
            }
        }
    };

    public View.OnClickListener listener = new View.OnClickListener() {

       @Override
       public void onClick(View v) {
           if (v.getId() == R.id.button01) {
                        //  Toast.makeText(getApplicationContext(), "一行显示测试!", Toast.LENGTH_SHORT).show();
                      //    try {
                      //          com.example.android.St7735s.lcdShowChinese(str2.getBytes("gb2312"));
                    //      } catch (UnsupportedEncodingException e) {
                    //            e.printStackTrace();
                        //  }
						  Intent AnimationIntent=new Intent(St7735stime.this,SmallLcdEditTextActivity.class);
			
							startActivity(AnimationIntent);
                       }
                    else if (v.getId() == R.id.button02) {
                        Toast.makeText(getApplicationContext(), "两行显示测试!", Toast.LENGTH_SHORT).show();
                          try {
                                com.example.android.St7735s.lcdShowChinese(str3.getBytes("gb2312"));
                          } catch (UnsupportedEncodingException e) {
                                e.printStackTrace();
                          }
                    }
                    else if (v.getId() == R.id.button03) {
                        Toast.makeText(getApplicationContext(), "三行显示测试!", Toast.LENGTH_SHORT).show();
                          try {
                                com.example.android.St7735s.lcdShowChinese(str1.getBytes("gb2312"));
                          } catch (UnsupportedEncodingException e) {
                                e.printStackTrace();
                          }
                   }
                    else if (v.getId() == R.id.button04) {
                        Toast.makeText(getApplicationContext(), "lcdSetPos and lcdShowchar", Toast.LENGTH_SHORT).show();
                         //lcdStopChinese();
                    }
                    else if (v.getId() == R.id.button05) {
                        Toast.makeText(getApplicationContext(), "lcdSetPos and lcdShowchar", Toast.LENGTH_SHORT).show();
                       // lcdShowIcon(1,0);
                   }
                    else if (v.getId() == R.id.button06) {
                        Toast.makeText(getApplicationContext(), "清除第一行的前半部分", Toast.LENGTH_SHORT).show();
                        //lcdShowChinese(str.getBytes("gb2312"));
                    }
                    else if (v.getId() == R.id.button07) {
                        Toast.makeText(getApplicationContext(), "lcdStopRoll", Toast.LENGTH_SHORT).show();
                        //lcdShowChinese(str.getBytes("gb2312"));
                    }else {
                        Toast.makeText(getApplicationContext(), "no match!", Toast.LENGTH_SHORT).show();
                        //lcdShowChinese(str.getBytes("gb2312"));
                    }
                }
            };
}
