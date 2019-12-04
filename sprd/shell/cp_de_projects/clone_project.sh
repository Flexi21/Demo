#!/bin/bash
###############################################################
##  Author: Leo                                    
##  Data  : 20191203
##  Sw_ver: Version 1.0
##  Func  : clone a board for sprd platform(Andorid 4.4) 
##  Param :  
##         $1 : the src board name               
##         $2 : the dst board name                  
##  Usage : ./clone_projects.sh sp9820e_1h10 sp9820e_1h10_demo
###############################################################

tab="	"
space8="        "
_arch="arm"
SRC="$1"         ##eg:sp9820e_1h10
DST="$2"         ##eg:sp9820e_1h10_jw11
Up_SRC=`echo $SRC | tr -t [a-z] [A-Z]`
Up_DST=`echo $DST | tr -t [a-z] [A-Z]`
Platform=`echo $SRC | cut -d '_' -f 1`
Board1=`echo $SRC | cut -d '_' -f 2`
Up_Board1=`echo $Board1 | tr -t [a-z] [A-Z]`
Board2="native"
Big_ver="mocor5"
Dst_custmer=`echo $DST | cut -d '_' -f 3`
Up_Dst_custmer=`echo $Dst_custmer | tr -t [a-z] [A-Z]`
End_custmer=`echo $DST | cut -d '_' -f 4`
Diff_config_src=$SRC"_"$Big_ver"_diff_config"
Diff_config_dst=$DST"_"$Big_ver"_diff_config"
Device_Base="device/sprd/sharkle"
device_src="$Device_Base/$SRC"
device_dst="$Device_Base/$DST"
U_config_src=$SRC"_defconfig"
U_config_dst=$DST"_defconfig"
C_config_src="$SRC""_config : preconfig"
C_config_dst="$DST""_config : preconfig"

dts_src=$Platform"-"$Board1"-"$Board2
udts_src=$Platform"_"$Board1
kernel_src1="kernel/arch/$_arch/boot/dts/$dts_src.dts"
kernel_src2="kernel/sprd-diffconfig/sharkle/arm/$Diff_config_src"
kernel_src3="kernel/arch/arm/boot/dts/Makefile"
uboot_src1="u-boot15/board/spreadtrum/$SRC"
uboot_src2="u-boot15/include/configs/$SRC.h"   ##sp9820e_1h10.h
uboot_src3="u-boot15/configs/$U_config_src"  ##sp9820e_1h10_defconfig
uboot_src4="u-boot15/board/spreadtrum/Kconfig"
uboot_src5="u-boot15/arch/arm/dts/Makefile"
uboot_src10="u-boot15/arch/arm/dts/$SRC.dts"
chipram_src1="chipram/include/configs/$SRC.h"
chipram_src2="chipram/board.def"
#chipram_src3=""
pzip_src1="proprietories-"$SRC"_oversea-user.zip"
pzip_src2="proprietories-"$SRC"_oversea-userdebug.zip"

dts_dst=$Platform"-"$Board1"_"$Dst_custmer"-"$Board2
udts_dst=$Platform"_"$Board1"_"$Dst_custmer
kernel_dst1="kernel/arch/$_arch/boot/dts/$dts_dst.dts"
kernel_dst2="kernel/sprd-diffconfig/sharkle/arm/$Diff_config_dst"
uboot_dst1="u-boot15/board/spreadtrum/$DST"
uboot_dst2="u-boot15/include/configs/$DST.h"
uboot_dst3="u-boot15/configs/$U_config_dst"
uboot_dst4="source \"board/spreadtrum/$DST/Kconfig\""
uboot_dst5="config TARGET_$Up_DST"
uboot_dst6="##Leo#bool \"Spreadtrum sharkle\""
uboot_dst7="##Leo#select CPU_V7"
uboot_dst8="##Leo#help"
uboot_dst9="####Leo#This is the Spreadtrum sharkle Board"
uboot_dst10="u-boot15/arch/arm/dts/$DST.dts"
chipram_dst1="chipram/include/configs/$DST.h"
chipram_dst2='####Leo#@$(MKCONFIG) $@ arm armv8 '"$DST spreadtrum sharkle"
pzip_dst1="proprietories-"$DST"_oversea-user.zip"
pzip_dst2="proprietories-"$DST"_oversea-userdebug.zip"


CopyFiles()
{
    cp -ar $device_src        $device_dst  
    cp     $kernel_src1       $kernel_dst1
    cp     $kernel_src2       $kernel_dst2   
    cp -ar $uboot_src1        $uboot_dst1     
    cp     $uboot_src2        $uboot_dst2
    cp     $uboot_src3        $uboot_dst3
    cp     $uboot_src10       $uboot_dst10
    cp     $chipram_src1      $chipram_dst1
#    cp     $pzip_src1         $pzip_dst1
#    cp     $pzip_src2         $pzip_dst2    
}

FileRename(){

    pushd $device_dst
    file_list=`find . -name "*$SRC*" |sed -e "s/\.\///"`
    for _temp in ${file_list[@]};do
        new_file=`echo $_temp | sed -e "s/$Board1/&_$Dst_custmer/" |sed -e "s/\.\///"`
        mv $_temp $new_file
    done 
    popd

    pushd $uboot_dst1
    file_list=`find . -name "*$SRC*" | sed -e "s/\.\///"`
    for _temp in ${file_list[@]};do
        new_file=`echo $_temp | sed -e "s/$Board1/&_$Dst_custmer/" |sed -e "s/\.\///"`
        mv $_temp $new_file
    done 
    popd 

    mkdir __temp
    pushd __temp/
    cp       ../$pzip_src1    .
    unzip -o $pzip_src1
    rm  $pzip_src1
    file_list=`find . -name "*$SRC*" | sed -e "s/\.\///"`
    for _temp in ${file_list[@]};do
        new_file=`echo $_temp | sed -e "s/$Board1/&_$Dst_custmer/" |sed -e "s/\.\///"`
        mv $_temp $new_file
    done     
    zip $pzip_dst1 -r out
    chmod 777 $pzip_dst1
    rm -rf out/
    mv $pzip_dst1 ../

    cp       ../$pzip_src2    .
    unzip -o $pzip_src2
    rm  $pzip_src2
    file_list=`find . -name "*$SRC*" | sed -e "s/\.\///"`
    for _temp in ${file_list[@]};do
        new_file=`echo $_temp | sed -e "s/$Board1/&_$Dst_custmer/" |sed -e "s/\.\///"`
        mv $_temp $new_file
    done     
    zip $pzip_dst2 -r out
    chmod 777 $pzip_dst2    
    rm -rf out/
    mv $pzip_dst2 ../  
    popd
    rm -rf __temp/
}

ContextChange()
{
    file_list=`grep -r "$Board1"  "$device_dst" | cut -d ":" -f 1 | uniq | sort` 
    sed -i "s/$Board1/&\_$Dst_custmer/g" ${file_list[@]}
    echo "device part end"

    line=`grep -rn "$dts_src.dtb" $kernel_src3 | cut -d ":" -f 1`
    sed -i "/$dts_src.dtb/a \ \ \ \ \ \ \ \ $dts_dst.dtb\ \\\ " $kernel_src3
    sed -i 's/[ \t]*$//g' $kernel_src3 
    sed -i "s/$Board1/&\_$Dst_custmer/g" $kernel_dst1
    sed -i "s/$Board1/&\_$Dst_custmer/g" $kernel_dst2  
    echo "kernel part end"        

    file_list=`grep -r "$Board1"  "$uboot_dst1" | cut -d ":" -f 1 | uniq | sort` 
    sed -i "s/$Board1/&\_$Dst_custmer/g" ${file_list[@]}
    file_list=`grep -r "$Up_Board1"  "$uboot_dst1" | cut -d ":" -f 1 | uniq | sort`    
    sed -i "s/$Up_Board1/&\_$Up_Dst_custmer/g" ${file_list[@]}    
    sed -i "s/$Up_Board1/&\_$Up_Dst_custmer/g" $uboot_dst3
    
    line=`grep -rn "$SRC" $uboot_src4 | cut -d ":" -f 1`
    sed -i "/$SRC/a $uboot_dst4\ " $uboot_src4   

    line=`grep -rn "$Up_SRC" $uboot_src4 | cut -d ":" -f 1`
    #echo "$line"
    sed -i "$line i$uboot_dst5" $uboot_src4       
    sed -i "$line a$uboot_dst6" $uboot_src4
    sed -i "`expr $line + 1` a$uboot_dst7" $uboot_src4   
    sed -i "`expr $line + 2` a$uboot_dst8" $uboot_src4 
    sed -i "`expr $line + 3` a$uboot_dst9" $uboot_src4       
    sed -i "`expr $line + 4` a##Leo#" $uboot_src4       
    sed -i "s/####Leo#/\	\ \ /g" $uboot_src4
    sed -i "s/##Leo#/\	/g" $uboot_src4      
      
    line=`grep -rn "$udts_src.dtb" $uboot_src5 | cut -d ":" -f 1`
    #echo "$line"
    sed -i "/$udts_src.dtb/a \ \ \ \ \ \ \ \ $udts_dst.dtb\ \\\ " $uboot_src5   
    sed -i 's/[ \t]*$//g' $uboot_src5 
    sed -i "s/$Board1/&\_$Dst_custmer/g" $uboot_dst10

    echo "uboot part end" 

    line=`grep -rn "$C_config_src" $chipram_src2 | cut -d ":" -f 1`
    #echo "$line"
    sed -i "$line i$C_config_dst" $chipram_src2     
    sed -i "$line a$chipram_dst2" $chipram_src2
    sed -i "`expr $line + 1` a####Leo#" $chipram_src2   
    sed -i "s/####Leo#/\	/g" $chipram_src2          
    
    echo "chipram part end"                    
}

if [[ $# -ne "2" ]] || [[ $2 = "" ]] || [[ $Dst_custmer = "" ]] || [[ $End_custmer != "" ]];then
    echo "Params error!"
    echo "usage:"
    echo "      ./clone_projects.sh sp9820e_1h10 sp9820e_1h10_demo"
    exit 1
fi

if [ -d $device_dst ];then
    echo "the dst projest already exist!"
    exit 1
fi

CopyFiles
FileRename
ContextChange
