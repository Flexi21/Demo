#!/bin/bash

EnviromentSet()
{
	source mbldenv.sh
	source build/envsetup.sh
}

ProjectSelect()
{
if [ -f "./myProjectNum" ];then
	myProjectNum=$(head -1 ./myProjectNum)
	#rm ./myProjectNum
	lunch $myProjectNum
else
	echo "./myProjectNum not found"
	lunch
fi
}

CustReqSelect()
{

   parameter=`get_build_var TARGET_PRODUCT`
   prj_folder_name=${parameter##*full_}
   prj_folder_name=${prj_folder_name%%-eng}
   prj_folder_name=${prj_folder_name%%-user*}

if [[ $1 = "" ]];then 
rm -rf out/target/product/$prj_folder_name/obj/BOOTLOADER_OBJ/build-$prj_folder_name/dev/lcm
rm -rf out/target/product/$prj_folder_name/obj/BOOTLOADER_OBJ/build-$prj_folder_name/dev/logo
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/input/touchscreen
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/lcm
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/imgsensor
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/camera
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/lens
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/keypad
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/alsps

rm -rf out/target/product/$prj_folder_name/obj/PRELOADER_OBJ
rm -rf out/target/product/$prj_folder_name/obj/PTGEN

###modem related
rm -rf out/target/product/$prj_folder_name/obj/ETC/mdm_layout_desc_1_*
rm -rf out/target/product/$prj_folder_name/vendor/etc/mddb/mdm_layout_desc_1_*

rm -rf out/target/product/$prj_folder_name/obj/ETC/em_filter_1_*
rm -rf out/target/product/$prj_folder_name/vendor/firmware/em_filter_1_*

rm -rf out/target/product/$prj_folder_name/obj/ETC/DbgInfo_*
rm -rf out/target/product/$prj_folder_name/vendor/etc/mddb/DbgInfo_*

rm -rf out/target/product/$prj_folder_name/obj/ETC/catcher_filter_1_*
rm -rf out/target/product/$prj_folder_name/vendor/firmware/catcher_filter_1_*

rm -rf out/target/product/$prj_folder_name/obj/ETC/md1dsp*
rm -rf out/target/product/$prj_folder_name/md1dsp*

rm -rf out/target/product/$prj_folder_name/obj/ETC/md1rom*
rm -rf out/target/product/$prj_folder_name/md1rom*

rm -rf out/target/product/$prj_folder_name/obj/ETC/MDDB*
rm -rf out/target/product/$prj_folder_name/vendor/etc/mddb/MDDB*
fi

if [[ $1 = "pl" ]];then
rm -rf out/target/product/$prj_folder_name/obj/PRELOADER_OBJ
fi

if [[ $1 = "lk" ]];then
rm -rf out/target/product/$prj_folder_name/obj/BOOTLOADER_OBJ/build-$prj_folder_name/dev/lcm
rm -rf out/target/product/$prj_folder_name/obj/BOOTLOADER_OBJ/build-$prj_folder_name/dev/logo
elif [[ $2 = "lk" ]];then
rm -rf out/target/product/$prj_folder_name/obj/BOOTLOADER_OBJ/build-$prj_folder_name/dev/lcm
rm -rf out/target/product/$prj_folder_name/obj/BOOTLOADER_OBJ/build-$prj_folder_name/dev/logo
fi

if [[ $1 = "kernel" ]];then
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/input/touchscreen
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/lcm
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/imgsensor
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/camera
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/lens
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/keypad
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/alsps
elif [[ $2 = "kernel" ]];then
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/input/touchscreen
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/lcm
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/imgsensor
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/camera
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/lens
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/keypad
rm -rf out/target/product/$prj_folder_name/obj/KERNEL_OBJ/drivers/misc/mediatek/alsps
fi

rm -rf out/target/product/$prj_folder_name/system/build.prop
rm -rf out/target/product/$prj_folder_name/obj/ETC/system_build_prop_intermediates/build.prop
}

RunCommand()
{
        UBUNTU18=`grep -c 18.04.2 /etc/issue`
        if [ $UBUNTU18 -eq "1" ]; then
        export LC_ALL=C
        fi
        
        Tnum=`cat /proc/cpuinfo | grep "processor" | wc -l`
        if [ $Tnum -gt "32" ];then
            $Tnum="32"
        fi
        make -j$Tnum $* 2>&1 | tee build.log
}

PackSoftware()
{
   current_path=$PWD

   parameter=`get_build_var TARGET_PRODUCT`
   prj_folder_name=${parameter##*full_}
   prj_folder_name=${prj_folder_name%%-eng}
   prj_folder_name=${prj_folder_name%%-user*}

   BASE_NAME=$current_path
   PROJ_NAME=$prj_folder_name
   DATE_TIME=$(date +%y%m%d_%H%M)
   DIR_FOLDER="jm_"$PROJ_NAME"_"$DATE_TIME

   cust_file="device/mediateksample/$prj_folder_name/ProjectConfig.mk"

   MTK_PLATFORM_SUPPORT=`grep -w "^MTK_PLATFORM" "$cust_file" |tail -1|cut -d "=" -f 2 |tr -d " "`
   echo "MTK_PLATFORM_SUPPORT:$MTK_PLATFORM_SUPPORT"

   mkdir $DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/preloader_$PROJ_NAME.bin $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/logo.bin $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/lk.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/spmfw.img $BASE_NAME/$DIR_FOLDER
if [ -f $BASE_NAME/out/target/product/$PROJ_NAME/scp.img ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/scp.img $BASE_NAME/$DIR_FOLDER
fi
   cp $BASE_NAME/out/target/product/$PROJ_NAME/sspm.img $BASE_NAME/$DIR_FOLDER

if [ -f $BASE_NAME/out/target/product/$PROJ_NAME/system/etc/mddb/MDDB.META.ODB_MT6765*_1_*_n.XML.GZ ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/system/etc/mddb/MDDB.META.ODB_MT6765*_1_*_n.XML.GZ $BASE_NAME/$DIR_FOLDER
fi
if [ -f $BASE_NAME/out/target/product/$PROJ_NAME/system/etc/mddb/MDDB.META_MT6765*_1_*_n.EDB ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/system/etc/mddb/MDDB.META_MT6765*_1_*_n.EDB $BASE_NAME/$DIR_FOLDER
fi
if [ -f $BASE_NAME/out/target/product/$PROJ_NAME/system/etc/mddb/MDDB_InfoCustomAppSrcP_MT6765*_1_*_n.EDB ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/system/etc/mddb/MDDB_InfoCustomAppSrcP_MT6765*_1_*_n.EDB $BASE_NAME/$DIR_FOLDER
fi

if [ -f $BASE_NAME/out/target/product/$PROJ_NAME/vendor/etc/mddb/MDDB.META.ODB_MT6765*_1_*_n.XML.GZ ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/vendor/etc/mddb/MDDB.META.ODB_MT6765*_1_*_n.XML.GZ $BASE_NAME/$DIR_FOLDER
fi
if [ -f $BASE_NAME/out/target/product/$PROJ_NAME/vendor/etc/mddb/MDDB.META_MT6765*_1_*_n.EDB ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/vendor/etc/mddb/MDDB.META_MT6765*_1_*_n.EDB $BASE_NAME/$DIR_FOLDER
fi
if [ -f $BASE_NAME/out/target/product/$PROJ_NAME/vendor/etc/mddb/MDDB_InfoCustomAppSrcP_MT6765*_1_*_n.EDB ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/vendor/etc/mddb/MDDB_InfoCustomAppSrcP_MT6765*_1_*_n.EDB $BASE_NAME/$DIR_FOLDER
fi

if [ "$MTK_PLATFORM_SUPPORT" == "MT6765" ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/obj/CGEN/APDB_MT6765_S01_alps-mp-o1.*_W??.?? $BASE_NAME/$DIR_FOLDER
fi

##******************** MT6761 package start ***********************************************************************
if [ -f $BASE_NAME/out/target/product/$PROJ_NAME/system/etc/mddb/MDDB.META.ODB_MT6761*_1_*_n.XML.GZ ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/system/etc/mddb/MDDB.META.ODB_MT6761*_1_*_n.XML.GZ $BASE_NAME/$DIR_FOLDER
fi
if [ -f $BASE_NAME/out/target/product/$PROJ_NAME/system/etc/mddb/MDDB.META_MT6761*_1_*_n.EDB ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/system/etc/mddb/MDDB.META_MT6761*_1_*_n.EDB $BASE_NAME/$DIR_FOLDER
fi
if [ -f $BASE_NAME/out/target/product/$PROJ_NAME/system/etc/mddb/MDDB_InfoCustomAppSrcP_MT6761*_1_*_n.EDB ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/system/etc/mddb/MDDB_InfoCustomAppSrcP_MT6761*_1_*_n.EDB $BASE_NAME/$DIR_FOLDER
fi

if [ -f $BASE_NAME/out/target/product/$PROJ_NAME/vendor/etc/mddb/MDDB.META.ODB_MT6761*_1_*_n.XML.GZ ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/vendor/etc/mddb/MDDB.META.ODB_MT6761*_1_*_n.XML.GZ $BASE_NAME/$DIR_FOLDER
fi
if [ -f $BASE_NAME/out/target/product/$PROJ_NAME/vendor/etc/mddb/MDDB.META_MT6761*_1_*_n.EDB ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/vendor/etc/mddb/MDDB.META_MT6761*_1_*_n.EDB $BASE_NAME/$DIR_FOLDER
fi
if [ -f $BASE_NAME/out/target/product/$PROJ_NAME/vendor/etc/mddb/MDDB_InfoCustomAppSrcP_MT6761*_1_*_n.EDB ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/vendor/etc/mddb/MDDB_InfoCustomAppSrcP_MT6761*_1_*_n.EDB $BASE_NAME/$DIR_FOLDER
fi

if [ "$MTK_PLATFORM_SUPPORT" == "MT6761" ];then
   cp $BASE_NAME/out/target/product/$PROJ_NAME/obj/CGEN/APDB_MT6761_S01_alps-mp-o1.*_W??.?? $BASE_NAME/$DIR_FOLDER
fi
##******************** MT6761 package end ***************************************************************************

   cp $BASE_NAME/out/target/product/$PROJ_NAME/vendor/data/misc/ProjectConfig.mk $BASE_NAME/$DIR_FOLDER
   cp -r $BASE_NAME/out/target/product/$PROJ_NAME/system/build.prop $BASE_NAME/$DIR_FOLDER

   cp $BASE_NAME/out/target/product/$PROJ_NAME/MT67*_Android_scatter.txt $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/boot.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/recovery.img $BASE_NAME/$DIR_FOLDER
##   cp $BASE_NAME/out/target/product/$PROJ_NAME/secro.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/system.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/userdata.img $BASE_NAME/$DIR_FOLDER
##   cp $BASE_NAME/out/target/product/$PROJ_NAME/trustzone.bin $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/cache.img $BASE_NAME/$DIR_FOLDER

   if [ "$MTK_PLATFORM_SUPPORT" == "MT6761" ];then
       cp $BASE_NAME/out/target/product/$PROJ_NAME/odmdtbo.img $BASE_NAME/$DIR_FOLDER/dtbo.img
   else
       cp $BASE_NAME/out/target/product/$PROJ_NAME/odmdtbo.img $BASE_NAME/$DIR_FOLDER/
   fi
   cp $BASE_NAME/out/target/product/$PROJ_NAME/vendor.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/tee.img $BASE_NAME/$DIR_FOLDER

   cp $BASE_NAME/out/target/product/$PROJ_NAME/md1arm7.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/md1dsp.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/md1img.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/md3img.img $BASE_NAME/$DIR_FOLDER

   cp $BASE_NAME/out/target/product/$PROJ_NAME/obj/KERNEL_OBJ/vmlinux $BASE_NAME/$DIR_FOLDER

   echo "copy done!!!!!!!!!"
}

if [[ $1 = "bootimage" ]];then  
EnviromentSet
ProjectSelect
RunCommand $*
elif [[ $1 = "pac" ]];then
EnviromentSet
ProjectSelect
#CustReqSelect $*
#RunCommand $*
elif [[ $1 = "only" ]];then
EnviromentSet
ProjectSelect
#CustReqSelect $*
RunCommand $*
else
EnviromentSet
ProjectSelect
CustReqSelect $*
RunCommand $*
fi

#######################################################################
temp=`grep -c "#### build completed successfully" build.log`
if [ "$temp" == "1" ];then
if [[ $1 = "" ]] || [[ $1 = "pac" ]] || [[ $1 = "only" ]];then
echo "begin pack software..."
PackSoftware
fi
fi

./prebuilts/sdk/tools/jack-admin kill-server
