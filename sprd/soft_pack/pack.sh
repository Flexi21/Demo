#!/bin/bash




test(){

   #["FLASH_WLTE"    , ""                 , 0        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   #["EraseMisc"     , ""                 , 0        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["GPS_GL"        , ${ARGV[$index+20]} , 1        , 1,        , 1        , 0x0       , 0xFFFFFFFF  ],  
   ["GPS_BD"        , ${ARGV[$index+21]} , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],    
   ["Modem_WLTE_DELTANV", ${ARGV[$index+22]}        , 1        , 1        , 0        , 0x0       , 0xFFFFFFFF  ],        
   #config must be the last one
   [""              , $config            , 2        , 0,        , 0        , 0x0       , 0xFFFFFFFF  ],




/usr/bin/perl $BASE_NAME/sp9820e_1h10_oversea.pl $IMG_DIR/${PAC_NAME}.pac $PAC_PROJ $PAC_VER $PAC_CONFILE 
$IMG_DIR/fdl1-sign.bin                #0
$IMG_DIR/fdl2-sign.bin                #1
${MODEM_NVITEM}                       #2
$IMG_DIR/prodnv.img                   #3
$IMG_DIR/u-boot-spl-16k-sign.bin      #4
${MODEM_MODEM_W_DAT}                  #5
${L_LDSP}                             #6
${L_GDSP}                             #7
${PM_SYS}                             #8
${Modem_WCN}                          #9
$IMG_DIR/boot.img                     #10
$IMG_DIR/recovery.img                 #11
$IMG_DIR/system.img                   #12
$IMG_DIR/userdata.img                 #13 
$AP_BASE/sprd_boot.bmp                #14
$AP_BASE/sprd_fastboot.bmp            #15
$IMG_DIR/cache.img                    #16
$IMG_DIR/u-boot-sign.bin              #17
$IMG_DIR/sml-sign.bin                 #18
$IMG_DIR/tos-sign.bin                 #19
$IMG_DIR/gnssbdmodem.bin              #20
$IMG_DIR/gnssmodem.bin                #21
${MODEM_DELTAANV}                     #22
}



Pack()
{

   current_path=$PWD
   PAC_NAME="test"

   prj_folder_name="sp9820e_1h10"

   BASE_NAME=$current_path
   PROJ_NAME=$prj_folder_name
   DATE_TIME=$(date +%y%m%d_%H%M)

   #mkdir $DIR_FOLDER
   DIR_FOLDER="sp9820e_1h10_userdebug_191025_1607"

   PAC_PROJ="sp9820e_1h10"
   PAC_VER="MocorDroid6.0_trunk_SharkL"

   IMG_DIR=$BASE_NAME/$DIR_FOLDER
   MODEM_NVITEM="`ls $IMG_DIR/*nvitem.bin`"
   MODEM_MODEM_W_DAT="`ls $IMG_DIR/*modem.dat`"
   LDSP="`ls  $IMG_DIR/SharkLE_LTEA_DSP_evs_off.bin`"
   L_GDSP="`ls $IMG_DIR/*DM_DSP.bin `"
   MODEM_DELTAANV="`ls $IMG_DIR/*deltanv.bin`"
   PM_SYS="`ls $IMG_DIR/sharkle_cm4.bin`"
   MODEM_WCN="`ls $IMG_DIR/PM_sharkle_cm4.bin`"
   PAC_CONFILE="${IMG_DIR}/sp9820e_1h10.xml"


/usr/bin/perl $BASE_NAME/9820e_1h10_oversea.pl $IMG_DIR/${PAC_NAME}.pac $PAC_PROJ $PAC_VER $PAC_CONFILE $IMG_DIR/fdl1-sign.bin $IMG_DIR/fdl2-sign.bin ${MODEM_NVITEM} $IMG_DIR/prodnv.img $IMG_DIR/u-boot-spl-16k-sign.bin ${MODEM_MODEM_W_DAT} ${LDSP} ${L_GDSP} $PM_SYS ${MODEM_WCN} $IMG_DIR/boot.img $IMG_DIR/recovery.img $IMG_DIR/system.img $IMG_DIR/userdata.img $IMG_DIR/sprd_boot.bmp $IMG_DIR/sprd_fastboot.bmp $IMG_DIR/cache.img $IMG_DIR/u-boot-sign.bin $IMG_DIR/sml-sign.bin $IMG_DIR/tos-sign.bin $IMG_DIR/gnssbdmodem.bin $IMG_DIR/gnssmodem.bin ${MODEM_DELTAANV} 
}

Pack
