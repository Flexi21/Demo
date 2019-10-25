1. 在9820e_1h10_oversea.pl打包脚本的 my parem数组中，file_path 中的 index+x 要和传入的ID顺序是一致的。
2. file_path是空的默认打包就是空：又分为以下两种情况
   2.1 file_path是空的，但是该项又没有注释的情况，就需要打包的时候多传一个参数进来匹配，。有几项传几个
   2.2 file_path是空的,直接注释的情况，就不需要考虑那么多，传的参数跟index+n保持一致就行。
my @param = (
   #ID              , file_path          , file_flag, check_flag, omit_flag, addr1     , addr2
   ["FDL"           , ${ARGV[$index+0]}  , 0x0101   , 1,        , 0        , 0x50000000, 0xFFFFFFFF  ],
   ["FDL2"          , ${ARGV[$index+1]}  , 0x0101   , 1,        , 0        , 0x80000000, 0xFFFFFFFF  ],
   ["NV_WLTE"       , ${ARGV[$index+2]}  , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["ProdNV"        , ${ARGV[$index+3]}  , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   #["PhaseCheck"    , ""                 , 0        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   #["EraseUBOOT"    , ""                 , 0        , 1,        , 1        , 0x0       , 0xFFFFFFFF  ],
   ["SPLLoader"     , ${ARGV[$index+4]}  , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["Modem_WLTE"    , ${ARGV[$index+5]}  , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["DSP_WLTE_LTE"  , ${ARGV[$index+6]}  , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["DSP_WLTE_GGE"  , ${ARGV[$index+7]}  , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   #["WARM_WLTE"     , ${ARGV[$index+8]}  , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["DFS"           , ${ARGV[$index+8]}  , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["Modem_WCN"     , ${ARGV[$index+9]} , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["BOOT"          , ${ARGV[$index+10]} , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["Recovery"      , ${ARGV[$index+11]} , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["System"        , ${ARGV[$index+12]} , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["UserData"      , ${ARGV[$index+13]} , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["BootLogo"      , ${ARGV[$index+14]} , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["Fastboot_Logo" , ${ARGV[$index+15]} , 1        , 1,        , 1        , 0x0       , 0xFFFFFFFF  ],
   ["Cache"         , ${ARGV[$index+16]} , 1        , 1,        , 1        , 0x0       , 0xFFFFFFFF  ],
   #["FLASH_WLTE"    , ""                 , 0        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   #["EraseMisc"     , ""                 , 0        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["UBOOTLoader"   , ${ARGV[$index+17]} , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],
   ["SML"           , ${ARGV[$index+18]} , 1        , 1,        , 1        , 0x0       , 0xFFFFFFFF  ],  
   ["Trustos"       , ${ARGV[$index+19]} , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ], 
   ["GPS_GL"        , ${ARGV[$index+20]} , 1        , 1,        , 1        , 0x0       , 0xFFFFFFFF  ],  
   ["GPS_BD"        , ${ARGV[$index+21]} , 1        , 1,        , 0        , 0x0       , 0xFFFFFFFF  ],    
   ["Modem_WLTE_DELTANV", ${ARGV[$index+22]}        , 1        , 1        , 0        , 0x0       , 0xFFFFFFFF  ],        
   #config must be the last one
   [""              , $config            , 2        , 0,        , 0        , 0x0       , 0xFFFFFFFF  ],
);

2.然后param的ID也不是随便取的，要和sp9820e_1h10.xml中的名字保持一致。
