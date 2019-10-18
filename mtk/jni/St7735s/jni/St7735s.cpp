#include <jni.h>
#include <stdio.h>
#include<sys/poll.h> 
#include<sys/select.h> 
#include<sys/ioctl.h>
#include<sys/types.h>
#include <utils/Log.h>
#include<fcntl.h>
#include <stdlib.h>
#include <string.h>

#define  _LCD_IOCTL           'l'
#define  uLCD_None            _IOW(_LCD_IOCTL, 0, int)
#define  uLCD_Setzoon         _IOW(_LCD_IOCTL, 1, int)
#define  uLCD_ClearArea       _IOW(_LCD_IOCTL, 2, int)
#define  uLCD_ShowChar        _IOW(_LCD_IOCTL, 3, int)
#define  uLCD_ShowString      _IOW(_LCD_IOCTL, 4, int)
#define  uLCD_ShowNum         _IOW(_LCD_IOCTL, 5, int)
#define  ULCD_WriteRoll       _IOW(_LCD_IOCTL, 6, int)
#define  uLCD_ShowPic         _IOW(_LCD_IOCTL, 7, int)
#define  uLCD_ShowRgb         _IOW(_LCD_IOCTL, 8, int)
#define  uLCD_ShowRoll        _IOW(_LCD_IOCTL, 9, int)
#define  uLCD_SetPos          _IOW(_LCD_IOCTL, 10, int)
#define  uLCD_StopRoll        _IOW(_LCD_IOCTL, 11, int)
#define  uLCD_RstLcd          _IOW(_LCD_IOCTL, 12, int)
#define  uLCD_ClearRoll       _IOW(_LCD_IOCTL, 13, int)
#define  uLCD_ShowChinese     _IOW(_LCD_IOCTL, 14, int)
#define  uLCD_StopChinese     _IOW(_LCD_IOCTL, 15, int)
#define  uLCD_ShowIcon        _IOW(_LCD_IOCTL, 16, int)
#define  uLCD_ShowTime        _IOW(_LCD_IOCTL, 17, int)
#define  uLCD_SetTime         _IOW(_LCD_IOCTL, 18, int)

#define  ICON_BT               1
#define  ICON_GPS              2
#define  ICON_WIFI0            3
#define  ICON_WIFI1            4
#define  ICON_WIFI2            5
#define  ICON_SIGNAL0          6
#define  ICON_SIGNAL1          7
#define  ICON_SIGNAL2          8
#define  ICON_SIGNAL3          9
#define  ICON_SIGNAL4          10
#define  ICON_2G               11
#define  ICON_3G               12
#define  ICON_4G               13

static int atmp[30*20];
static int aicon[2];
static int atime[2];

static int LCD_write(int cmd, int *parray)
{
      int fd = 0, ret = 0;
    
      ALOGE("et_lcd func:LCD_write\n");
      fd = open("/proc/et_lcd/et_lcd_node",O_RDONLY); 
      if(fd < 0){
           ALOGE("*** et_lcd open /proc/et_lcd/et_lcd_node error!\n");
      }

      ret = ioctl(fd, cmd, parray);

      if(ret < 0){
	   ALOGE("*** et_lcd  ERROR ioctl fail \n");
	   close(fd);
      }
      close(fd);
      return ret;
}
static void   
LCD_ShowChinese(JNIEnv *env, jobject thiz, jbyteArray jchinese) {
      int i = 0;
      char* data = (char*)env->GetByteArrayElements(jchinese, 0);
      jsize tmpsize = env->GetArrayLength(jchinese); 

      ALOGE("et_lcd data size %d\n",tmpsize);
      memset(atmp,0x00,sizeof(atmp));
      for(i=0; i<tmpsize; i++)
      {
          atmp[i] = (int) (*(data+i));
          ALOGE("et_lcd data size %d addr%d\n",atmp[i],&atmp[0]);
      }   

      LCD_write(uLCD_ShowChinese,atmp);
}

static void   
LCD_StopChinese(JNIEnv *env, jobject thiz, jbyteArray jchinese) {
      ALOGE("et_lcd LCD_StopChinese Entry\n");

      LCD_write(uLCD_StopChinese,NULL);
}

static void   
LCD_ShowIcon(JNIEnv *env, jobject thiz, jint icon ,jint show,jint value) {
      aicon[0] = icon;
      aicon[1] = show;
      ALOGE("et_lcd LCD_ShowIcon Entry\n");
      LCD_write(uLCD_ShowIcon,aicon);
}

static void   
LCD_ShowTime(JNIEnv *env, jobject thiz) {
      ALOGE("et_lcd LCD_ShowTime Entry\n");
      LCD_write(uLCD_ShowTime,NULL);
}

static void 
LCD_SetTime(JNIEnv *env, jobject thiz,jint hour,jint minute) {
      ALOGE("et_lcd LCD_ShowTime Entry\n");
      atime[0] = hour;
      atime[1] = minute;
      LCD_write(uLCD_SetTime,atime);
}

static JNINativeMethod methods[] = {
    {"lcdShowChinese"    , "([B)V", (void*)LCD_ShowChinese},
    {"lcdShowTime"       , "()V", (void*)LCD_ShowTime},
    {"lcdSetTime"    , "(II)V", (void*)LCD_SetTime},
//    {"lcdStopChinese"    , "()V", (void*)LCD_StopChinese},
//    {"lcdShowIcon"    , "(II)V", (void*)LCD_ShowIcon},
};

//if use st7735s.jar,don`t modified the class path
static const char *className = "com/example/android/St7735s";  
//static const char *className = "com/lolaage/policesystem/manager/screen/SmallScreen"; 

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    jint result = -1;
    JNIEnv* env = NULL;
    jclass clazz;

    if (vm->GetEnv(reinterpret_cast<void**> (&env), JNI_VERSION_1_4) != JNI_OK) { 
        goto bail;
    }

    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_ERR;
    }

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        return JNI_FALSE;
    }
    
    result = JNI_VERSION_1_4;
    
bail:
    return result;
}
