#!/bin/bash
BUILDTYPE="none"
BUILD_DEFAULT_EVRIONMENT="yes"

Unzip_prop()
{
        echo "Unzip prop"
        if [ -f proprietories-${TARGET_PRODUCT}-${TARGET_BUILD_VARIANT}.zip ]; then
                unzip proprietories-${TARGET_PRODUCT}-${TARGET_BUILD_VARIANT}.zip;
        else
            echo "proprietories-${TARGET_PRODUCT}-${TARGET_BUILD_VARIANT}.zip no exist!"
            exit 1
        fi
}

CustomerSet()
{
        boarddir=`get_build_var BOARDDIR`
        PROJ_NAME=`echo $boarddir | sed 's/device\/sprd\/sharkle\///'`

        if [ "$PROJ_NAME" = "sp9820e_2h10" ];then
                echo "cp sp9820e_2h10 Entry"
                if [ -e "custom_ka208_nand" ];then 
                        pushd custom_ka208_nand/
                        ./custom.sh
                        popd
                else 
                        exit 1
                fi
            
                if [ -e "custom_bmi160_nand" ];then 
                        pushd custom_bmi160_nand/
                        ./custom.sh
                        popd
                else
                        exit 1
                fi
        elif [ "$PROJ_NAME" = "sp9820e_1h10" ];then
                echo "cp sp9820e_1h10 Entry"       
                if [ -e "custom_ka208_emmc" ];then  
                        pushd custom_ka208_emmc/
                        ./custom.sh
                        popd
                else
                        exit 1            
                fi
            
                if [ -e "custom_bmi160_emmc" ];then
                        pushd custom_bmi160_emmc/
                        ./custom.sh
                        popd
                else
                        exit 1
                fi
        else
            echo "Customerset do nothing"
        fi
}

EnviromentSet()
{
        if [ -e lunch_history ];then
                rm ./lunch_history
        fi
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
BUILDTYPE=`get_build_var TARGET_BUILD_VARIANT`
}

##  bootloader    : fdl2-sign.bin u-boot-sign.bin u-boot_autopoweron-sign.bin
##  chipram       : fdl1-sign.bin u-boot-spl-16k-sign.bin
##  bootimage     : boot.img dt.img kernel ramdisk.img
##  systemimage   : system.img
##  userdataimage : userdata.img
##  vendorimage   : vendorimage.img
RunCommand()
{
        UBUNTU18=`grep -c 18.04.2 /etc/issue`
        if [ $UBUNTU18 -eq "1" ]; then
        export LC_ALL=C
        fi
        kheader
        
        Tnum=`cat /proc/cpuinfo | grep "processor" | wc -l`
        if [ $Tnum -gt "32" ];then
            $Tnum="32"
        fi
        #make -j$Tnum $* 2>&1 | tee build.log
        make -j4 $* 2>&1 | tee build.log
}

PackSoftware()
{

   #USE_SW_VER="yes"
   BASE_NAME=$PWD
   boarddir=`get_build_var BOARDDIR`
   PROJ_NAME=`echo $boarddir | sed 's/device\/sprd\/sharkle\///'`
   PAC_VER="MOCOR5_sfphone"   
   DATE_TIME=$(date +%y%m%d_%H%M)
 
   SW_VER_S=`cat out/target/product/$PROJ_NAME/system/build.prop |grep ro.build.display.id`
   SW_VER=${SW_VER_S##*ro.build.display.id=}
   echo "sw_version:$SW_VER"

   #BUILDTYPE=`get_build_var TARGET_BUILD_VARIANT`
   if [[ $USE_SW_VER == "yes" ]];then ##eg:KA8501_S270_V1.0_190809_6223C [BOARD NAME]_[PROJECT NAME]_[BIG VERSION].[SMALL VERSUON]_[DATA]_[OTHERS]
        DIR_FOLDER=${SW_VER%%_20*}"_"$DATE_TIME
   else
        DIR_FOLDER=$PROJ_NAME"_"$BUILDTYPE"_"$DATE_TIME   
   fi
   mkdir $DIR_FOLDER
   
   if [ "$PROJ_NAME" = "sp9820e_2h10" ];then
        #USE_P2K="yes"
        USE_P4K="yes"
   else
        USE_P2K="no"   
        USE_P4K="no"        
   fi     
   
   ##---------------------------------- copy part start ---------------------------------------------------###
        if [ "$USE_P2K" = "yes" ];then
                echo "pac: USE_P2K"
                cp $BASE_NAME/out/target/product/$PROJ_NAME/prodnv_b128k_p2k.img $BASE_NAME/$DIR_FOLDER/     
                cp $BASE_NAME/out/target/product/$PROJ_NAME/cache_b128k_p2k.img $BASE_NAME/$DIR_FOLDER/
                cp $BASE_NAME/out/target/product/$PROJ_NAME/system_b128k_p2k.img $BASE_NAME/$DIR_FOLDER/
                cp $BASE_NAME/out/target/product/$PROJ_NAME/userdata_b128k_p2k.img $BASE_NAME/$DIR_FOLDER/                 
        elif [ "$USE_P4K" = "yes" ];then
                echo "pac: USE_P4K"        
                cp $BASE_NAME/out/target/product/$PROJ_NAME/cache_b256k_p4k.img $BASE_NAME/$DIR_FOLDER/
                cp $BASE_NAME/out/target/product/$PROJ_NAME/prodnv_b256k_p4k.img $BASE_NAME/$DIR_FOLDER/
                cp $BASE_NAME/out/target/product/$PROJ_NAME/system_b256k_p4k.img $BASE_NAME/$DIR_FOLDER/
                cp $BASE_NAME/out/target/product/$PROJ_NAME/userdata_b256k_p4k.img $BASE_NAME/$DIR_FOLDER/                                     
        else
                echo "pac: default"        
                cp $BASE_NAME/out/target/product/$PROJ_NAME/cache.img $BASE_NAME/$DIR_FOLDER
                cp $BASE_NAME/out/target/product/$PROJ_NAME/prodnv.img $BASE_NAME/$DIR_FOLDER      
                cp $BASE_NAME/out/target/product/$PROJ_NAME/system.img $BASE_NAME/$DIR_FOLDER          
                cp $BASE_NAME/out/target/product/$PROJ_NAME/userdata.img $BASE_NAME/$DIR_FOLDER                            
        fi

        cp $BASE_NAME/out/target/product/$PROJ_NAME/fdl1-sign.bin $BASE_NAME/$DIR_FOLDER
        cp $BASE_NAME/out/target/product/$PROJ_NAME/fdl2-sign.bin $BASE_NAME/$DIR_FOLDER
        cp $BASE_NAME/out/target/product/$PROJ_NAME/boot.img $BASE_NAME/$DIR_FOLDER                    
        #cp $BASE_NAME/out/target/product/$PROJ_NAME/persist.img $BASE_NAME/$DIR_FOLDER
        cp $BASE_NAME/out/target/product/$PROJ_NAME/recovery.img $BASE_NAME/$DIR_FOLDER
        cp $BASE_NAME/out/target/product/$PROJ_NAME/sml-sign.bin $BASE_NAME/$DIR_FOLDER
        #cp $BASE_NAME/out/target/product/$PROJ_NAME/sysinfo.img $BASE_NAME/$DIR_FOLDER
        cp $BASE_NAME/out/target/product/$PROJ_NAME/tos-sign.bin $BASE_NAME/$DIR_FOLDER
        cp $BASE_NAME/out/target/product/$PROJ_NAME/u-boot-sign.bin $BASE_NAME/$DIR_FOLDER
        cp $BASE_NAME/out/target/product/$PROJ_NAME/u-boot-spl-16k-sign.bin $BASE_NAME/$DIR_FOLDER
        ##pac needed this xml file:
        cp $BASE_NAME/out/target/product/$PROJ_NAME/$PROJ_NAME.xml $BASE_NAME/$DIR_FOLDER   
   
        ##mode bin file
        cp $BASE_NAME/Other_images/* $BASE_NAME/$DIR_FOLDER
   
        ##vmlinux copy:
        cp $BASE_NAME/out/target/product/$PROJ_NAME/obj/KERNEL/vmlinux $BASE_NAME/$DIR_FOLDER
        echo "copy done!!!!!!!!!"
        ##---------------------------------- copy part end ---------------------------------------------------###   

   echo "Begin pac software!!!!!!!!!"

   IMG_DIR=$BASE_NAME/$DIR_FOLDER
   PRODNV_IMG=`ls $IMG_DIR/prodnv*.img`
   CACHE_IMG=`ls $IMG_DIR/cache*.img`
   SYSTEM_IMG=`ls $IMG_DIR/system*.img`
   USERDATA_IMG=`ls $IMG_DIR/userdata*.img`      
   
   MODEM_NVITEM="`ls $IMG_DIR/*nvitem.bin`"
   MODEM_MODEM_W_DAT="`ls $IMG_DIR/*modem.dat`"
   LDSP="`ls  $IMG_DIR/SharkLE_LTEA_DSP_evs_off.bin`"
   L_GDSP="`ls $IMG_DIR/*DM_DSP.bin `"
   MODEM_DELTAANV="`ls $IMG_DIR/*deltanv.bin`"
   PM_SYS="`ls $IMG_DIR/sharkle_cm4.bin`"
   MODEM_WCN="`ls $IMG_DIR/PM_sharkle_cm4.bin`"
   PAC_CONFILE="${IMG_DIR}/$PROJ_NAME.xml"


   /usr/bin/perl $BASE_NAME/9820e_1h10_oversea.pl $IMG_DIR/$DIR_FOLDER.pac $PROJ_NAME $PAC_VER $PAC_CONFILE $IMG_DIR/fdl1-sign.bin $IMG_DIR/fdl2-sign.bin ${MODEM_NVITEM} $PRODNV_IMG $IMG_DIR/u-boot-spl-16k-sign.bin ${MODEM_MODEM_W_DAT} ${LDSP} ${L_GDSP} $PM_SYS ${MODEM_WCN} $IMG_DIR/boot.img $IMG_DIR/recovery.img $SYSTEM_IMG $USERDATA_IMG $IMG_DIR/sprd_boot.bmp $IMG_DIR/sprd_fastboot.bmp $CACHE_IMG $IMG_DIR/u-boot-sign.bin $IMG_DIR/sml-sign.bin $IMG_DIR/tos-sign.bin $IMG_DIR/gnssbdmodem.bin $IMG_DIR/gnssmodem.bin ${MODEM_DELTAANV} 

   echo "End pac software by zwl !!!!!!!!!"
}

Kernelmaro(){
TARBOARD=`get_build_var TARGET_BOARD`
boarddir=`get_build_var BOARDDIR`
def_file="device/sprd/sharkle/common/ProjectConfig.mk"
cust_file="$boarddir/ProjectConfig_def.mk"
current_path=$PWD

echo "boarddir:     $boarddir"
echo "def_file:     $def_file"
echo "cust_file:    $cust_file"
echo "current_path: $current_path"
echo "dst_path:     include $current_path/$cust_file"
echo "TARBOARD $TARBOARD"

if [ -f $cust_file ];then
echo "use ProjectConfig_def.mk"
echo "include $current_path/$cust_file" > $def_file
else
echo "unuse ProjectConfig_def.mk"
echo " " > $def_file
fi
}

EnviromentSet
ProjectSelect
Unzip_prop
CustomerSet
##Kernelmaro
RunCommand $*

temp=`grep -c "#### make completed successfully" build.log`	
if [ $temp == "1" ];then  
PackSoftware
echo -e "\033[1;32m #### make completed successfully!!! \033[0m"
else
echo -e "\033[1;31m #### build completed failed!!! \033[0m"
fi
