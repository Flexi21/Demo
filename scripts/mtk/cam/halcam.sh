#!/bin/bash

#——————————————————————————————————————————
#————————————Config Part Start—————————————
SENSOR_ID_NUM=`echo $2 | tr -cd [0-9]`
SENSOR_ID_NUM="0x$SENSOR_ID_NUM"
#SENSOR_ID_NUM="0xFFFF"     ##default


SENSOR_RST_HW=("Vol_Low" "Vol_High")
#SENSOR_RST_HW=("Vol_High" "Vol_Low")
SENSOR_PDN_HW=("Vol_Low" "Vol_High")
#SENSOR_PDN_HW=("Vol_High" "Vol_Low")

SENSOR_DOVDD="Vol_1800"  ##IO
SENSOR_DVDD="Vol_1500"   ##AA
#————————————Config Part End———————————————
#——————————————————————————————————————————


IS_SUB="none"
SENSOR_SRC=$1
SENSOR_DST="none"
SENSOR_DST_PRE=$2
SENSOR_SRC_1=`echo $1 |tr '[a-z]' '[A-Z]'`
#SENSOR_DST_1=`echo $2 |tr '[a-z]' '[A-Z]'`
SENSOR_DST_1="none"
SENSOR_SRC_FILE="$1""_mipi_raw"
SENSOR_SRC_FILE_UP=`echo $SENSOR_SRC_FILE |tr '[a-z]' '[A-Z]'`
SENSOR_DST_FILE="none"
SENSOR_DST_FILE_UP="none"
SENSOR_LIST_FILE="sensorlist.cpp"
SENSOR_ID_NAME="none"
SENSOR_ID_SRC_NAME="$SENSOR_SRC_1""_SENSOR_ID"
PLATFORM_INFO="none"
KERNEL_VERSION="none"
SENSOR_KERNEL_C_F="none"
SENSOR_KERNEL_H_F="none"
SENSOR_KERNEL_INC_F="inc/kd_imgsensor.h"
SENSOR_KERNEL_HW_F="none"
SENSOR_DEVICE_HERADR_F="../../../../../../device/mediatek/common/kernel-headers/kd_imgsensor.h"
DATE=$(date +%Y%m%d)


GetPlatformInfo(){
	tmp=`echo $PWD | grep -c 6580`
	if [ "$tmp" == "1" ];then
		PLATFORM_INFO="6580"
		KERNEL_VERSION="kernel-4.9-lc"
		SENSOR_KERNEL_C_F="none"
		SENSOR_KERNEL_H_F="src/mt6580/kd_sensorlist.h"
		SENSOR_KERNEL_HW_F="src/mt6580/camera_hw/hwPowerDown.h"
	fi
	
	tmp=`echo $PWD | grep -c 6739`
	if [ "$tmp" == "1" ];then
		PLATFORM_INFO="6739"
		KERNEL_VERSION="kernel-4.14"
		SENSOR_KERNEL_C_F="src/common/v1/imgsensor_sensor_list.c"
		SENSOR_KERNEL_H_F="src/common/v1/imgsensor_sensor_list.h"
		SENSOR_KERNEL_HW_F="src/mt$PLATFORM_INFO/camera_hw/imgsensor_cfg_table.c"
	fi

	tmp=`echo $PWD | grep -c 6765`
	if [ "$tmp" == "1" ];then
		PLATFORM_INFO="6765"
		KERNEL_VERSION="kernel-4.9"
		SENSOR_KERNEL_C_F="src/common/v1/imgsensor_sensor_list_mt6765.c"
		SENSOR_KERNEL_H_F="src/common/v1/imgsensor_sensor_list.h"
		SENSOR_KERNEL_HW_F="src/mt$PLATFORM_INFO/camera_hw/imgsensor_cfg_table.c"
	fi

	tmp=`echo $PWD | grep -c 6761`
	if [ "$tmp" == "1" ];then
		PLATFORM_INFO="6761"
		KERNEL_VERSION="kernel-4.9"
		SENSOR_KERNEL_C_F="src/common/v1/imgsensor_sensor_list_mt6761.c"
		SENSOR_KERNEL_H_F="src/common/v1/imgsensor_sensor_list.h"
		SENSOR_KERNEL_HW_F="src/mt$PLATFORM_INFO/camera_hw/imgsensor_cfg_table.c"
	fi

}

UpdateVar()
{
	IS_SUB=`echo $SENSOR_DST_PRE | grep sub -c`
	if [ "$IS_SUB" == "1" ];then	
		SENSOR_DST=`echo $SENSOR_DST_PRE | cut -d "_" -f 1`
		SENSOR_DST_1=`echo $SENSOR_DST |tr '[a-z]' '[A-Z]'`
		SENSOR_DST_FILE=$SENSOR_DST"_mipi_raw_sub"
		SENSOR_ID_NAME="$SENSOR_DST_1""_SENSOR_ID_SUB"
	else    
		SENSOR_DST=$SENSOR_DST_PRE
		SENSOR_DST_1=`echo $SENSOR_DST |tr '[a-z]' '[A-Za]'`
		SENSOR_DST_FILE=$SENSOR_DST"_mipi_raw"
		SENSOR_ID_NAME="$SENSOR_DST_1""_SENSOR_ID"
	fi   

	GetPlatformInfo
	
	SENSOR_DST_FILE_UP=`echo $SENSOR_DST_FILE |tr '[a-z]' '[A-Z]'`
	
	echo "IS_SUB             : $IS_SUB"
	echo "SENSOR_DST         : $SENSOR_DST"
	echo "SENSOR_DST_1       : $SENSOR_DST_1"
	echo "SENSOR_DST_FILE    : $SENSOR_DST_FILE"
	echo "SENSOR_DST_FILE_UP : $SENSOR_DST_FILE_UP"
	echo "SENSOR_ID_NAME     : $SENSOR_ID_NAME"
	echo "SENSOR_ID_SRC_NAME : $SENSOR_ID_SRC_NAME"
	echo "PLATFORM_INFO      : $PLATFORM_INFO"
	echo "KERNEL_VERSION     : $KERNEL_VERSION"
	echo "SENSOR_KERNEL_C_F  : $SENSOR_KERNEL_C_F"
	echo "SENSOR_KERNEL_H_F  : $SENSOR_KERNEL_H_F"	
	echo "SENSOR_KERNEL_INC_F: $SENSOR_KERNEL_INC_F"
	echo "SENSOR_KERNEL_HW_F : $SENSOR_KERNEL_HW_F"
	echo "SENSOR_ID_NUM      : $SENSOR_ID_NUM"
}

RenameFile()
{
	##rename file 
	find . -type f | rename "s/$SENSOR_SRC/$SENSOR_DST/"      
	find . -type f | rename "s/$SENSOR_SRC_1/$SENSOR_DST_1/" 
	if [ "$IS_SUB" == "1" ];then
		find . -type f | rename "s/raw/raw_sub/"
		find . -type f | rename "s/RAW/RAW_SUB/"
	fi
}

ModifyContext()
{
	##modify context
	find . -type f | xargs sed -i "s/$SENSOR_SRC/$SENSOR_DST/g"
	find . -type f | xargs sed -i "s/$SENSOR_SRC_1/$SENSOR_DST_1/g"
	if [ "$IS_SUB" == "1" ];then
		find . -type f | xargs sed -i "s/mipiraw/mipiraw_sub/g"
		find . -type f | xargs sed -i "s/MIPIRAW/MIPIRAW_SUB/g"
		find . -type f | xargs sed -i "s/mipi_raw/mipi_raw_sub/g"
		find . -type f | xargs sed -i "s/MIPI_RAW/MIPI_RAW_SUB/g"
		find . -type f | xargs sed -i "s/_SENSOR_ID/_SENSOR_ID_SUB/g"
	fi
}

CameraHalHanddler()
{
	pushd imgsensor/
	echo "check imgsensor dst file is exist!!"
	if [ -e $SENSOR_DST_FILE ];then
	   echo -e "\e[31m error: dst file:[$PWD/$SENSOR_DST_FILE] exist, please check and delete it!! \e[0m"
	   exit 1
	fi

	echo "copy imgsensor file !!!"
	if [ -e $SENSOR_SRC_FILE ];then 
		cp -r $SENSOR_SRC_FILE $SENSOR_DST_FILE
	else
		echo -e "\e[31m error: src file:[$PWD/$SENSOR_DST_NAME] no found, please check!! \e[0m"
		exit 1
	fi
	
	pushd $SENSOR_DST_FILE
	echo "change imgsensor file name"
	RenameFile
	echo "modify imgsensor file context"
	ModifyContext
	popd
	popd
	
	###imgsensor_metadata file
	pushd imgsensor_metadata/
	if [ -e $SENSOR_DST_FILE ];then
		echo -e "\e[31m error: dst file:[$PWD/$SENSOR_DST_FILE] exist, please check and delete it!! \e[0m"
		pushd ../imgsensor/
		echo "rm -rf $PWD/$SENSOR_DST_FILE"
		rm -rf $SENSOR_DST_FILE
		popd
		if [ "$IS_GIT_SUPPORT" == "yes" ];then
			git status .
		fi
		exit 1
	fi

	echo "copy imgsensor_metadata file !!!"
        if [ -e $SENSOR_SRC_FILE ];then
                 cp -r $SENSOR_SRC_FILE $SENSOR_DST_FILE
        else
                 echo -e "\e[31m error: src file:[$PWD/$SENSOR_SRC_FILE] no found! \e[0m"
                 exit 1 
        fi
		
	pushd $SENSOR_DST_FILE
	echo "change imgsensor_metadata file name"
	RenameFile
	echo "modify imgsensor_metadata file context"
	ModifyContext	
	popd
	popd
	
	echo -e "\e[32m hal cp successful!! \e[0m"
}

ContextChangeHal(){
	echo "ContextChange Entry!!!"
	pushd imgsensor_src/
	##get the src_name line, if exit sub src, we use sub cam line
	line=`grep -n $SENSOR_SRC_1 $SENSOR_LIST_FILE | tail -1 |cut -d ":" -f 1`
	echo "line:$line"
	sed -i "`expr $line + 1` a\\#if defined($SENSOR_DST_FILE_UP) //Leo $DATE" $SENSOR_LIST_FILE
	sed -i "`expr $line + 2` a\\	RAW_INFO($SENSOR_ID_NAME, SENSOR_DRVNAME_$SENSOR_DST_1\_MIPI_RAW, NULL)," $SENSOR_LIST_FILE
	sed -i "`expr $line + 3` a\\#endif" $SENSOR_LIST_FILE
	popd
}

ContextKernelPower()
{
	tmp=`grep -c $SENSOR_DST_FILE_UP $SENSOR_KERNEL_HW_F`
	if [ "$tmp" != "0" ];then 
		echo -e "\e[31m ContextKernelPower: $SENSOR_DST_FILE_UP is exist,do nothing!! \e[0m"
	else
		if [ "$PLATFORM_INFO" == "6580" ];then
			line=`grep -n $SENSOR_SRC_FILE_UP $SENSOR_KERNEL_HW_F | head -1 | cut -d ":" -f 1`
			echo "SENSOR_KERNEL_HW_F:$line"
			sed -i "`expr $line - 1` a\\#if defined($SENSOR_DST_FILE_UP) //Leo $DATE"     $SENSOR_KERNEL_HW_F
			sed -i "$line a\\	{" 									                      $SENSOR_KERNEL_HW_F
			sed -i "`expr $line + 1` a\\ 		SENSOR_DRVNAME_$SENSOR_DST_1\_MIPI_RAW,"  $SENSOR_KERNEL_HW_F
			sed -i "`expr $line + 2` a\\		{"							              $SENSOR_KERNEL_HW_F	
			sed -i "`expr $line + 3` a\\			{PDN,	${SENSOR_PDN_HW[0],	0},"      $SENSOR_KERNEL_HW_F	
			sed -i "`expr $line + 4` a\\			{RST,	${SENSOR_RST_HW[0]},	0},"  $SENSOR_KERNEL_HW_F
			sed -i "`expr $line + 5` a\\			{DOVDD,	$SENSOR_DOVDD,	0},"          $SENSOR_KERNEL_HW_F		
			sed -i "`expr $line + 6` a\\			{AVDD,	Vol_2800,	5},"              $SENSOR_KERNEL_HW_F	
			sed -i "`expr $line + 7` a\\			{DVDD,	$SENSOR_DVDD,	5},"          $SENSOR_KERNEL_HW_F		
			sed -i "`expr $line + 8` a\\			{PDN,	${SENSOR_PDN_HW[1]},	1},"  $SENSOR_KERNEL_HW_F	
			sed -i "`expr $line + 9` a\\			{RST,	${SENSOR_RST_HW[1]},	1},"  $SENSOR_KERNEL_HW_F		
			sed -i "`expr $line + 10` a\\			{VDD_None,	0,	0}"                   $SENSOR_KERNEL_HW_F	
			sed -i "`expr $line + 11` a\\		},"                                       $SENSOR_KERNEL_HW_F	
			sed -i "`expr $line + 12` a\\	},"                                           $SENSOR_KERNEL_HW_F		
			sed -i "`expr $line + 13` a\\#endif"                                          $SENSOR_KERNEL_HW_F	
		else
			line=`grep -n $SENSOR_SRC_FILE_UP $SENSOR_KERNEL_HW_F | head -1 | cut -d ":" -f 1`
			echo "SENSOR_KERNEL_HW_F:$line"
			sed -i "`expr $line - 1` a\\#if defined($SENSOR_DST_FILE_UP) //Leo $DATE"         $SENSOR_KERNEL_HW_F
			sed -i "$line a\\	{" 									                          $SENSOR_KERNEL_HW_F
			sed -i "`expr $line + 1` a\\		SENSOR_DRVNAME_$SENSOR_DST_1\_MIPI_RAW,"      $SENSOR_KERNEL_HW_F
			sed -i "`expr $line + 2` a\\		{"							                  $SENSOR_KERNEL_HW_F		
			sed -i "`expr $line + 3` a\\			{SensorMCLK, Vol_High, 0},"               $SENSOR_KERNEL_HW_F		
			sed -i "`expr $line + 4` a\\			{PDN, ${SENSOR_PDN_HW[0], 0},"            $SENSOR_KERNEL_HW_F	
			sed -i "`expr $line + 5` a\\			{RST, ${SENSOR_RST_HW[0]}, 0},"           $SENSOR_KERNEL_HW_F		
			sed -i "`expr $line + 6` a\\			{DOVDD, $SENSOR_DOVDD, 1},"               $SENSOR_KERNEL_HW_F		
			sed -i "`expr $line + 7` a\\			{AVDD, Vol_2800, 1},"                     $SENSOR_KERNEL_HW_F		
			sed -i "`expr $line + 8` a\\			{DVDD, $SENSOR_DVDD, 5},"                 $SENSOR_KERNEL_HW_F	
			sed -i "`expr $line + 9` a\\			{AFVDD, Vol_2800, 1},"                    $SENSOR_KERNEL_HW_F		
			sed -i "`expr $line + 10` a\\			{PDN, ${SENSOR_PDN_HW[1]}, 1},"           $SENSOR_KERNEL_HW_F	
			sed -i "`expr $line + 11` a\\			{RST, ${SENSOR_RST_HW[1]}, 2}"            $SENSOR_KERNEL_HW_F	
			sed -i "`expr $line + 12` a\\		},"                                           $SENSOR_KERNEL_HW_F	
			sed -i "`expr $line + 13` a\\	},"                                               $SENSOR_KERNEL_HW_F		
			sed -i "`expr $line + 14` a\\#endif"                                              $SENSOR_KERNEL_HW_F	
		fi
	fi
}

ContextChangeKernel(){
	pushd ../../../../../../$KERNEL_VERSION/drivers/misc/mediatek/imgsensor/
	## inc
	tmp=`grep -c $SENSOR_ID_NAME $SENSOR_KERNEL_INC_F`
	if [ "$tmp" != "0" ];then 
		echo -e "\e[31m ContextChangeKernel: $SENSOR_ID_NAME  is exist,do nothing!! \e[0m"
	else
		line=`grep -n $SENSOR_ID_SRC_NAME $SENSOR_KERNEL_INC_F | head -1 | cut -d ":" -f 1`
		echo "SENSOR_KERNEL_INC_F $line"  
		##  #define OV8825_SENSOR_ID                        0x8825
		sed -i "$line a\\#define $SENSOR_ID_NAME                        $SENSOR_ID_NUM //Leo $DATE" $SENSOR_KERNEL_INC_F
		line=`grep -n "SENSOR_DRVNAME_$SENSOR_SRC_1\_MIPI_RAW" $SENSOR_KERNEL_INC_F | tail -1 | cut -d ":" -f 1`
		echo "SENSOR_KERNEL_INC_F $line"  
		##  #define SENSOR_DRVNAME_OV8825_MIPI_RAW          "ov8825_mipi_raw"
		sed -i "$line a\\#define SENSOR_DRVNAME_$SENSOR_DST_FILE_UP          \"$SENSOR_DST_FILE\" //Leo $DATE" $SENSOR_KERNEL_INC_F
	fi
	
	
	## src 
	## UINT32 GC8034MIPI_RAW_SensorInit(struct SENSOR_FUNCTION_STRUCT **pfFunc);
	if [ "$PLATFORM_INFO" == "6580" ];then
		h_tmp=`grep -c "UINT32 $SENSOR_DST_1" $SENSOR_KERNEL_H_F`

		if [ "$h_tmp" != "0" ];then 
			echo -e "\e[31m ContextChangeKernel: "$SENSOR_DST_FILE_UP"_SensorInit is exist,do nothing!! \e[0m"
		else
			## kd_sensorlist.h
			## UINT32 GC8034MIPI_RAW_SensorInit(struct SENSOR_FUNCTION_STRUCT **pfFunc);
			line=`grep -n "UINT32 $SENSOR_SRC_1" $SENSOR_KERNEL_H_F | head -1 | cut -d ":" -f 1`
			echo "SENSOR_KERNEL_H_F $line"
			sed -i "$line a\\UINT32 "$SENSOR_DST_FILE_UP"_SensorInit(struct SENSOR_FUNCTION_STRUCT **pfFunc); //Leo $DATE"  $SENSOR_KERNEL_H_F

			## kd_sensorlist.h
			## #if defined(GC8034_MIPI_RAW)
			##    {GC8034_SENSOR_ID, SENSOR_DRVNAME_GC8034_MIPI_RAW,GC8034MIPI_RAW_SensorInit},
			## #endif
			line=`grep -n $SENSOR_ID_SRC_NAME $SENSOR_KERNEL_H_F | tail -1 |cut -d ":" -f 1`
			echo "SENSOR_KERNEL_H_F:$line"
			sed -i "`expr $line + 1` a\\#if defined($SENSOR_DST_FILE_UP) //Leo $DATE" $SENSOR_KERNEL_H_F
			sed -i "`expr $line + 2` a\\	{$SENSOR_ID_NAME, SENSOR_DRVNAME_$SENSOR_DST_1\_MIPI_RAW, $SENSOR_DST_FILE_UP\_SensorInit}," $SENSOR_KERNEL_H_F
			sed -i "`expr $line + 3` a\\#endif" $SENSOR_KERNEL_H_F
		fi	
	#elif [ "$PLATFORM_INFO" == "6739" ];then
	else ## mt6739 mt6762 mt6761
		e_line=`grep -n joyatel $SENSOR_KERNEL_H_F | tail -1 | cut -d ":" -f 1`	
		echo "xxxxx"
		c_line=`grep -n "UINT32 $SENSOR_DST_1" $SENSOR_KERNEL_H_F | head -1 | cut -d ":" -f 1`
		echo "PLATFORM_INFO:6739 e_line:$e_line c_line:$c_line"
		
		if  [[ $c_line == "" ]] || [[ $c_line -gt $e_line ]];then
			## imgsensor_sensor_list.h
			## UINT32 GC8034MIPI_RAW_SensorInit(struct SENSOR_FUNCTION_STRUCT **pfFunc);
			line=`grep -n "UINT32 $SENSOR_SRC_1" $SENSOR_KERNEL_H_F | head -1 | cut -d ":" -f 1`
			echo "SENSOR_KERNEL_H_F $line"
			sed -i "$line a\\UINT32 "$SENSOR_DST_FILE_UP"_SensorInit(struct SENSOR_FUNCTION_STRUCT **pfFunc); //Leo $DATE" $SENSOR_KERNEL_H_F
			
			## imgsensor_sensor_list.c
			## #if defined(GC8034_MIPI_RAW)
			##    {GC8034_SENSOR_ID, SENSOR_DRVNAME_GC8034_MIPI_RAW,GC8034MIPI_RAW_SensorInit},
			## #endif
			line=`grep -n $SENSOR_ID_SRC_NAME $SENSOR_KERNEL_C_F | head -1 |cut -d ":" -f 1`
			echo "SENSOR_KERNEL_C_F:$line"
			sed -i "`expr $line + 1` a\\#if defined($SENSOR_DST_FILE_UP) //Leo $DATE" $SENSOR_KERNEL_C_F
			sed -i "`expr $line + 2` a\\	{$SENSOR_ID_NAME, SENSOR_DRVNAME_$SENSOR_DST_1\_MIPI_RAW, $SENSOR_DST_FILE_UP\_SensorInit}," $SENSOR_KERNEL_C_F
			sed -i "`expr $line + 3` a\\#endif" $SENSOR_KERNEL_C_F
		else
			echo "ContextChangeKernel: "$SENSOR_DST_FILE_UP"_SensorInit is exist,do nothing"
		fi	
	fi
	
	ContextKernelPower
		
	popd
}

ContextDevHeader()
{

	tmp=`grep -c $SENSOR_ID_NAME $SENSOR_DEVICE_HERADR_F`
	if [ "$tmp" != "0" ];then 
		echo -e "\e[31m ContextDevHeader: $SENSOR_ID_NAME  is exist,do nothing!! \e[0m"
	else
		line=`grep -n $SENSOR_ID_SRC_NAME $SENSOR_DEVICE_HERADR_F | head -1 | cut -d ":" -f 1`
		echo "SENSOR_DEVICE_HERADR_F $line"  
		##  #define OV8825_SENSOR_ID                        0x8825
		sed -i "$line a\\#define $SENSOR_ID_NAME $SENSOR_ID_NUM //Leo $DATE" $SENSOR_DEVICE_HERADR_F
		line=`grep -n "SENSOR_DRVNAME_$SENSOR_SRC_1\_MIPI_RAW" $SENSOR_DEVICE_HERADR_F | tail -1 | cut -d ":" -f 1`
		echo "SENSOR_DEVICE_HERADR_F $line"  
		##  #define SENSOR_DRVNAME_OV8825_MIPI_RAW          "ov8825_mipi_raw"
		sed -i "$line a\\#define SENSOR_DRVNAME_$SENSOR_DST_FILE_UP \"$SENSOR_DST_FILE\" //Leo $DATE" $SENSOR_DEVICE_HERADR_F
	fi
}

if [ "$#" != "2" ];then
	echo -e "Invaild Input Params!"
	echo "usage:"
	echo -e "\e[32m for main cam \e[0m"
	echo "      $0 gc8034 ov8825"
	echo -e "\e[32m for sub cam \e[0m"
	echo "      $0 gc8034 ov8825_sub"
	exit 1 
fi




echo "SNESOR_SRC  :$SENSOR_SRC   SENSOR_DST  :$SENSOR_DST"
echo "SENSOR_SRC_1:$SENSOR_SRC_1 SENSOR_DST_1:$SENSOR_DST_1" 
echo "SENSOR_SRC_FILE:$SENSOR_SRC_FILE SENSOR_DST_FILE:$SENSOR_DST_FILE"

UpdateVar
ContextChangeHal
CameraHalHanddler
ContextChangeKernel
ContextDevHeader

#grep -rni "$SENSOR_DST" imgsensor/$SENSOR_DST_FILE
#grep -rni "$SENSOR_DST" imgsensor_metadata/$SENSOR_DST_FILE

if [ "IS_GIT_SUPPORT" == "yes" ];then
	git status .
fi
