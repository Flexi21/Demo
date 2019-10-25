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
	lunch $myProjectNum
else
	echo "./myProjectNum not found"
	lunch
fi
}

RunCommand()
{
        UBUNTU18=`grep -c 18.04.2 /etc/issue`
        if [ $UBUNTU18 -eq "1" ]; then
        export LC_ALL=C
        fi

	make -j16 $* 2>&1 | tee build.log
}

PackSoftware()
{

   BASE_NAME=$PWD
   PROJ_NAME="sp9820e_1h10"
   PAC_VER="MocorDroid6.0_trunk_SharkL"   
   DATE_TIME=$(date +%y%m%d_%H%M)

   BUILDTYPE=`get_build_var TARGET_BUILD_VARIANT`
   DIR_FOLDER=$PROJ_NAME"_"$BUILDTYPE"_"$DATE_TIME
   mkdir $DIR_FOLDER
   
   cp $BASE_NAME/out/target/product/$PROJ_NAME/fdl1-sign.bin $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/fdl2-sign.bin $BASE_NAME/$DIR_FOLDER

   cp $BASE_NAME/out/target/product/$PROJ_NAME/boot.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/cache.img $BASE_NAME/$DIR_FOLDER
   #cp $BASE_NAME/out/target/product/$PROJ_NAME/persist.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/prodnv.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/recovery.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/system.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/userdata.img $BASE_NAME/$DIR_FOLDER

   cp $BASE_NAME/out/target/product/$PROJ_NAME/sml-sign.bin $BASE_NAME/$DIR_FOLDER
   #cp $BASE_NAME/out/target/product/$PROJ_NAME/sysinfo.img $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/tos-sign.bin $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/u-boot-sign.bin $BASE_NAME/$DIR_FOLDER
   cp $BASE_NAME/out/target/product/$PROJ_NAME/u-boot-spl-16k-sign.bin $BASE_NAME/$DIR_FOLDER
   ##pac needed this xml file:
   cp $BASE_NAME/out/target/product/$PROJ_NAME/sp9820e_1h10.xml $BASE_NAME/$DIR_FOLDER

   ##mode bin file
   cp $BASE_NAME/other_images/* $BASE_NAME/$DIR_FOLDER

   ##vmlinux copy:
   cp $BASE_NAME/out/target/product/$PROJ_NAME/obj/KERNEL/vmlinux $BASE_NAME/$DIR_FOLDER
   echo "copy done!!!!!!!!!"

   echo "Begin pac software!!!!!!!!!"

   IMG_DIR=$BASE_NAME/$DIR_FOLDER
   MODEM_NVITEM="`ls $IMG_DIR/*nvitem.bin`"
   MODEM_MODEM_W_DAT="`ls $IMG_DIR/*modem.dat`"
   LDSP="`ls  $IMG_DIR/SharkLE_LTEA_DSP_evs_off.bin`"
   L_GDSP="`ls $IMG_DIR/*DM_DSP.bin `"
   MODEM_DELTAANV="`ls $IMG_DIR/*deltanv.bin`"
   PM_SYS="`ls $IMG_DIR/sharkle_cm4.bin`"
   MODEM_WCN="`ls $IMG_DIR/PM_sharkle_cm4.bin`"
   PAC_CONFILE="${IMG_DIR}/sp9820e_1h10.xml"


   /usr/bin/perl $BASE_NAME/9820e_1h10_oversea.pl $IMG_DIR/$DIR_FOLDER.pac $PROJ_NAME $PAC_VER $PAC_CONFILE $IMG_DIR/fdl1-sign.bin $IMG_DIR/fdl2-sign.bin ${MODEM_NVITEM} $IMG_DIR/prodnv.img $IMG_DIR/u-boot-spl-16k-sign.bin ${MODEM_MODEM_W_DAT} ${LDSP} ${L_GDSP} $PM_SYS ${MODEM_WCN} $IMG_DIR/boot.img $IMG_DIR/recovery.img $IMG_DIR/system.img $IMG_DIR/userdata.img $IMG_DIR/sprd_boot.bmp $IMG_DIR/sprd_fastboot.bmp $IMG_DIR/cache.img $IMG_DIR/u-boot-sign.bin $IMG_DIR/sml-sign.bin $IMG_DIR/tos-sign.bin $IMG_DIR/gnssbdmodem.bin $IMG_DIR/gnssmodem.bin ${MODEM_DELTAANV} 

   echo "End pac software by zwl !!!!!!!!!"
}

EnviromentSet
ProjectSelect
RunCommand
PackSoftware
