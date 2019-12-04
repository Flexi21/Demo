#!/bin/bash
##################################################################
##  Author: Leo                                    
##  Data  : 20191203
##  Sw_ver: Version 1.0
##  Func  : delete a board for customer sprd platform(Andorid 4.4) 
##  Param :  
##         $1 : the src board name               
##         $2 : the dst board name           
##  Usage : ./delete_projects.sh sp9820e_1h10_demo     
##################################################################

if [ "$1" = "" ];then
echo "Param 1 is empty,please check!"
exit 1
fi

SRC=$1
Up_SRC=`echo $SRC | tr -t [a-z] [A-Z]`
_arch="arm"
SRC="$1"         ##sp9820e_1h10
Platform=`echo $SRC | cut -d '_' -f 1`
Board1=`echo $SRC | cut -d '_' -f 2`
Dst_custmer=`echo $SRC | cut -d '_' -f 3`
End_custmer=`echo $DST | cut -d '_' -f 4`
Board2="native"
Big_ver="mocor5"

dts_dst=$Platform"-"$Board1"_"$Dst_custmer"-"$Board2
Diff_config_src=$1"_"$Big_ver"_diff_config"
Device_Base="device/sprd/sharkle"
device_src="$Device_Base/$SRC"
kernel_src1="kernel/arch/$_arch/boot/dts/$dts_dst.dts"
kernel_src2="kernel/sprd-diffconfig/sharkle/arm/$Diff_config_src"
kernel_src3="kernel/arch/arm/boot/dts/Makefile"
uboot_src1="u-boot15/board/spreadtrum/$SRC"
uboot_src2="u-boot15/include/configs/$SRC.h"
U_config_dst=$SRC"_defconfig"
uboot_src3="u-boot15/configs/$U_config_dst"
uboot_src4="u-boot15/board/spreadtrum/Kconfig"
uboot_src5="u-boot15/arch/$_arch/dts/Makefile"
uboot_src10="u-boot15/arch/$_arch/dts/$SRC.dts"
chipram_src1="chipram/include/configs/$SRC.h"
chipram_src2="chipram/board.def"
C_config_src="$SRC""_config : preconfig"
pzip_src1="proprietories-"$SRC"_oversea-user.zip"
pzip_src2="proprietories-"$SRC"_oversea-userdebug.zip"

Rmfile()
{
    rm -rf  $device_src
    rm -rf  $kernel_src1
    rm -rf  $kernel_src2
    rm -rf  $uboot_src1
    rm -rf  $uboot_src2
    rm -rf  $uboot_src3
    rm -rf  $uboot_src10
    rm -rf  $chipram_src1
    rm -rf  $pzip_src1
    rm -rf  $pzip_src2  
}

CutContext()
{
    line=`grep -rn "$dts_dst.dtb" $kernel_src3 | cut -d ":" -f 1`
    if [[ $line = "" ]];then
        exit 1
    fi
    echo $line
    sed -i "$line d" $kernel_src3

    line=`grep -rn "$SRC.dtb" $uboot_src5 | cut -d ":" -f 1`
    if [[ $line = "" ]];then
        exit 1
    fi    
    echo $line
    sed -i "$line d" $uboot_src5

    line=`grep -rn "$SRC" $uboot_src4 | cut -d ":" -f 1`
    if [[ $line = "" ]];then
        exit 1
    fi
    echo $line
    sed -i "$line d" $uboot_src4

    line=`grep -rn "$Up_SRC" $uboot_src4 | cut -d ":" -f 1`
    if [[ $line = "" ]];then
        exit 1
    fi
    line1=`expr $line + 5` 
    echo "$line $line1"
    sed -i "$line,$line1 d" $uboot_src4

    line=`grep -rn "$C_config_src" $chipram_src2 | cut -d ":" -f 1`
    if [[ $line = "" ]];then
        exit 1
    fi
    line1=`expr $line + 2` 
    echo "$line $line1"
    sed -i "$line,$line1 d" $chipram_src2

}

if [[ $# -ne "1" ]] || [[ $Dst_custmer = "" ]] || [[ $End_custmer != "" ]];then
    echo "Params error!"
    echo "usage:"
    echo "      ./delete_projects.sh sp9820e_1h10_demo"
    exit 1
fi

if [ ! -d $device_src ];then
    echo "the input projest not exist!"
    exit 1
fi

Rmfile
CutContext
