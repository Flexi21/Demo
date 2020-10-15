#!/bin/bash

if [ $1 = "cpp" ];then
	if [ $2 != "" ];then
		if [ $3 != "" ];then
			hidl-gen -o $2 -Lc++-impl -randroid.hardware:hardware/interfaces -randroid.hidl:system/libhidl/transport android.hardware.$3@1.0
		else
				echo "hidl module info error!"
				exit 1;
		fi
	else
		echo "path info error!"
		exit 1;
	fi
elif [ $1 = "bp" ];then 
	if [ $2 != "" ];then
		if [ $3 != "" ];then
			hidl-gen -o $2 -Landroidbp-impl -randroid.hardware:hardware/interfaces -randroid.hidl:system/libhidl/transport android.hardware.$3@1.0
		else
				echo "hidl module info error!"
				exit 1;
		fi
	else
		echo "path info error!"
		exit 1;
	fi
fi
