/*
 * Copyright (C) 2015 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#if defined(MTK_LCM_DEVICE_TREE_SUPPORT)
#include <linux/string.h>
#include <linux/wait.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/pinctrl/consumer.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/module.h>

#ifdef BUILD_LK
#include <platform/upmu_common.h>
#include <platform/upmu_hw.h>
#include <platform/mt_gpio.h>
#include <platform/mt_i2c.h>
#include <platform/mt_pmic.h>
#include <string.h>
#else
#ifdef CONFIG_MTK_LEGACY
#include <mach/mt_pm_ldo.h>	/* hwPowerOn */
#include <mt-plat/upmu_common.h>
#include <mach/upmu_sw.h>
#include <mach/upmu_hw.h>
#else
#include <mt-plat/upmu_common.h>
#include <mach/upmu_sw.h>
#include <mach/upmu_hw.h>
#endif
#endif
#ifdef CONFIG_MTK_LEGACY
#include <mach/mt_gpio.h>
//#include <cust_gpio_usage.h>
#include <cust_i2c.h>
#else
#include <mt-plat/mt_gpio.h>
#endif

#include "lcm_define.h"
#include "lcm_drv.h"
#include "lcm_gpio.h"


#ifdef CONFIG_MTK_LEGACY
#if defined(GPIO_LCD_BIAS_ENP_PIN)
#define GPIO_65132_EN GPIO_LCD_BIAS_ENP_PIN
#else
#define GPIO_65132_EN 0
#endif
#else
#ifdef CONFIG_PINCTRL
static struct pinctrl *_lcm_gpio;
static struct pinctrl_state *_lcm_gpio_mode_default;
static struct pinctrl_state *_lcm_gpio_mode[MAX_LCM_GPIO_MODE];
static unsigned char _lcm_gpio_mode_list[MAX_LCM_GPIO_MODE][128] = {
	"lcm_mode_00",
	"lcm_mode_01",
	"lcm_mode_02",
	"lcm_mode_03",
	"lcm_mode_04",
	"lcm_mode_05",
	"lcm_mode_06",
	"lcm_mode_07"
};

static unsigned int GPIO_LCD_PWR_EN;
static unsigned int GPIO_LCD_BL_EN;
#endif

/* function definitions */
static int __init _lcm_gpio_init(void);
static void __exit _lcm_gpio_exit(void);
static int _lcm_gpio_probe(struct platform_device *pdev);
static int _lcm_gpio_remove(struct platform_device *pdev);

#ifdef CONFIG_OF
static const struct of_device_id _lcm_gpio_of_ids[] = {
	{.compatible = "mediatek,lcm_mode",},
	{},
};
MODULE_DEVICE_TABLE(of, _lcm_gpio_of_ids);
#endif

static struct platform_driver _lcm_gpio_driver = {
	.driver = {
		.name = LCM_GPIO_DEVICE,
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(_lcm_gpio_of_ids),
	},
	.probe = _lcm_gpio_probe,
	.remove = _lcm_gpio_remove,
};
module_platform_driver(_lcm_gpio_driver);
#endif


#ifdef CONFIG_MTK_LEGACY
#else
/* LCM GPIO probe */
static int _lcm_gpio_probe(struct platform_device *pdev)
{
#ifdef CONFIG_PINCTRL
	int ret;
	unsigned int mode;
	const struct of_device_id *match;
	struct device	*dev = &pdev->dev;

	pr_debug("[LCM][GPIO] enter %s, %d\n", __func__, __LINE__);

	_lcm_gpio = devm_pinctrl_get(dev);
	if (IS_ERR(_lcm_gpio)) {
		ret = PTR_ERR(_lcm_gpio);
		pr_info("[LCM][ERROR] Cannot find _lcm_gpio!\n");
		return ret;
	}
	_lcm_gpio_mode_default = pinctrl_lookup_state(_lcm_gpio, "default");
	if (IS_ERR(_lcm_gpio_mode_default)) {
		ret = PTR_ERR(_lcm_gpio_mode_default);
		pr_info("[LCM][ERROR] Cannot find lcm_mode_default %d!\n",
			ret);
	}
	for (mode = LCM_GPIO_MODE_00; mode < MAX_LCM_GPIO_MODE; mode++) {
		_lcm_gpio_mode[mode] =
			pinctrl_lookup_state(_lcm_gpio,
				_lcm_gpio_mode_list[mode]);
		if (IS_ERR(_lcm_gpio_mode[mode]))
			pr_info("[LCM][ERROR] Cannot find lcm_mode:%d! skip it.\n",
			mode);

	}

	if (dev->of_node) {
		match = of_match_device(of_match_ptr(_lcm_gpio_of_ids), dev);
		if (!match) {
			pr_info("[LCM][ERROR] No device match found\n");
			return -ENODEV;
		}
	}
	GPIO_LCD_PWR_EN =
		of_get_named_gpio(dev->of_node, "lcm_power_gpio", 0);
	GPIO_LCD_BL_EN =
		of_get_named_gpio(dev->of_node, "lcm_bl_gpio", 0);

	ret = gpio_request(GPIO_LCD_PWR_EN, "lcm_power_gpio");
	if (ret < 0)
		pr_info("[LCM][ERROR] Unable to request GPIO_LCD_PWR_EN\n");
	ret = gpio_request(GPIO_LCD_BL_EN, "lcm_bl_gpio");
	if (ret < 0)
		pr_info("[LCM][ERROR] Unable to request GPIO_LCD_BL_EN\n");

	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!\n");
#endif

	return 0;
}


static int _lcm_gpio_remove(struct platform_device *pdev)
{
#ifdef CONFIG_PINCTRL
	gpio_free(GPIO_LCD_BL_EN);
	gpio_free(GPIO_LCD_PWR_EN);
#endif

	return 0;
}


/* called when loaded into kernel */
static int __init _lcm_gpio_init(void)
{
	pr_debug("MediaTek LCM GPIO driver init\n");
	if (platform_driver_register(&_lcm_gpio_driver) != 0) {
		pr_info("unable to register LCM GPIO driver.\n");
		return -1;
	}
	return 0;
}


/* should never be called */
static void __exit _lcm_gpio_exit(void)
{
	pr_debug("MediaTek LCM GPIO driver exit\n");
	platform_driver_unregister(&_lcm_gpio_driver);
}
#endif


static enum LCM_STATUS _lcm_gpio_check_data(char type,
	const struct LCM_DATA_T1 *t1)
{
	switch (type) {
	case LCM_GPIO_MODE:
		switch (t1->data) {
		case LCM_GPIO_MODE_00:
		case LCM_GPIO_MODE_01:
		case LCM_GPIO_MODE_02:
		case LCM_GPIO_MODE_03:
		case LCM_GPIO_MODE_04:
		case LCM_GPIO_MODE_05:
		case LCM_GPIO_MODE_06:
		case LCM_GPIO_MODE_07:
			break;

		default:
			pr_info("[LCM][ERROR] %s/%d: %d, %d\n",
				__func__, __LINE__, type, t1->data);
			return LCM_STATUS_ERROR;
		}
		break;

	case LCM_GPIO_DIR:
		switch (t1->data) {
		case LCM_GPIO_DIR_IN:
		case LCM_GPIO_DIR_OUT:
			break;

		default:
			pr_info("[LCM][ERROR] %s/%d: %d, %d\n",
				__func__, __LINE__, type, t1->data);
			return LCM_STATUS_ERROR;
		}
		break;

	case LCM_GPIO_OUT:
		switch (t1->data) {
		case LCM_GPIO_OUT_ZERO:
		case LCM_GPIO_OUT_ONE:
			break;

		default:
			pr_info("[LCM][ERROR] %s/%d: %d, %d\n",
				__func__, __LINE__, type, t1->data);
			return LCM_STATUS_ERROR;
		}
		break;

	default:
		pr_info("[LCM][ERROR] %s/%d: %d\n",
			__func__, __LINE__, type);
		return LCM_STATUS_ERROR;
	}

	return LCM_STATUS_OK;
}


enum LCM_STATUS lcm_gpio_set_data(char type, const struct LCM_DATA_T1 *t1)
{
	/* check parameter is valid */
	if (_lcm_gpio_check_data(type, t1) == LCM_STATUS_OK) {
		switch (type) {
#ifdef CONFIG_MTK_LEGACY
		case LCM_GPIO_MODE:
			mt_set_gpio_mode(GPIO_65132_EN, (unsigned int)t1->data);
			break;

		case LCM_GPIO_DIR:
			mt_set_gpio_dir(GPIO_65132_EN, (unsigned int)t1->data);
			break;

		case LCM_GPIO_OUT:
			mt_set_gpio_out(GPIO_65132_EN, (unsigned int)t1->data);
			break;
#else
#ifdef CONFIG_PINCTRL
		case LCM_GPIO_MODE:
			pr_debug("[LCM][GPIO] %s/%d: set mode: %d\n",
				__func__, __LINE__, (unsigned int)t1->data);
			pinctrl_select_state(_lcm_gpio,
				_lcm_gpio_mode[(unsigned int)t1->data]);
			break;

		case LCM_GPIO_DIR:
			pr_debug("[LCM][GPIO] %s/%d: set dir: %d, %d\n",
				__func__, __LINE__, GPIO_LCD_PWR_EN,
				(unsigned int)t1->data);
			gpio_direction_output(GPIO_LCD_PWR_EN, (int)t1->data);
			break;

		case LCM_GPIO_OUT:
			pr_debug("[LCM][GPIO] %s/%d: set out: %d, %d\n",
				__func__, __LINE__, GPIO_LCD_PWR_EN,
				(unsigned int)t1->data);
			gpio_set_value(GPIO_LCD_PWR_EN, (int)t1->data);
			break;
#else
		case LCM_GPIO_MODE:
		case LCM_GPIO_DIR:
		case LCM_GPIO_OUT:
			break;
#endif
#endif
		default:
			pr_info("[LCM][ERROR] %s/%d: %d\n",
				__func__, __LINE__, type);
			return LCM_STATUS_ERROR;
		}
	} else {
		pr_info("[LCM][ERROR] %s: 0x%x, 0x%x\n",
			__func__, type, t1->data);
		return LCM_STATUS_ERROR;
	}

	return LCM_STATUS_OK;
}


#ifdef CONFIG_MTK_LEGACY
#else
module_init(_lcm_gpio_init);
module_exit(_lcm_gpio_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MediaTek LCM GPIO driver");
MODULE_AUTHOR("Joey Pan<joey.pan@mediatek.com>");
#endif

#else  //added by xen for LCD_ID control 20171106
#ifndef BUILD_LK
#include <linux/string.h>
#include <linux/wait.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/pinctrl/consumer.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/module.h>

#ifdef CONFIG_MTK_LEGACY
#include <mach/mt_pm_ldo.h>	/* hwPowerOn */
#include <mt-plat/upmu_common.h>
#include <mach/upmu_sw.h>
#include <mach/upmu_hw.h>
#else
#include <mt-plat/upmu_common.h>
#include <mach/upmu_sw.h>
#include <mach/upmu_hw.h>
#endif

#ifdef CONFIG_MTK_LEGACY
#include <mach/mt_gpio.h>
//#include <cust_gpio_usage.h>
#include <cust_i2c.h>
#else
//#include <mt-plat/mtk_gpio.h> //xjl 20180531
#endif

#include "lcm_define.h"
#include "lcm_drv.h"
#include "lcm_gpio.h"

#define LCM_GPIO_DEVICE	"lcd_id_gpio"
static int lcm_id_high = 0xFF;
static int gpio_lcd_id;
int gpio_mic_gnd;
int gpio_usb_sw;
int gpio_wifi_en;
int gpio_charge_en;
#if defined(YK921_CONFIG)
int gpio_cam_cut_en; //xen 20180708

//dual battery:
int gpio_no_id;
int gpio_vbat_en;
int gpio_bat_chg_en;
int gpio_sel_bat;

//led control: //xen 20180714
int gpio_red_alarm_en;
int gpio_blue_alarm_en;
int gpio_ray_led_en;

//flashlight control: //xen 20180723
int gpio_flashlight_strobe;
int gpio_flashlight_enable;

#endif

#if defined(LCM_ENABLE_ICN6211)
static int gpio_rgb_rst;
#endif

int get_lcd_id_state(void)
{
	int input_value = 0;
	int ret = 0;

	if(0xFF != lcm_id_high) 
	{
	    return lcm_id_high;
	}

	ret = gpio_request(gpio_lcd_id, "lcd_id");
	if (ret<0){
	   pr_debug("lcd-id gpio_request failed!\n");
	   return -ENODEV;
	}

	ret = gpio_direction_input(gpio_lcd_id);
	if (ret<0){
	   pr_debug("lcd-id gpio_direction_input failed!\n");
	   return -ENODEV;
	}

	input_value = gpio_get_value(gpio_lcd_id);
	gpio_free(gpio_lcd_id);

	lcm_id_high = input_value;  //save lcd_id state

        return input_value;
}

void set_gpio_mic_gnd(int enable)
{
	int input_value = 0;

	gpio_set_value(gpio_mic_gnd, enable);
	input_value = gpio_get_value(gpio_mic_gnd);
	pr_debug("get gpio_mic_gnd = %d\n", input_value);
}

void set_gpio_usb_sw(int enable)
{
	int input_value = 0;

	gpio_set_value(gpio_usb_sw, enable);
	input_value = gpio_get_value(gpio_usb_sw);
	pr_debug("get gpio_usb_sw = %d\n", input_value);
}

void set_gpio_wifi_en(int enable)
{
	int input_value = 0;

	gpio_set_value(gpio_wifi_en, enable);
	input_value = gpio_get_value(gpio_wifi_en);
	pr_debug("get gpio_wifi_en = %d\n", input_value);
}

void set_gpio_charge_en(int enable)
{
	int input_value = 0;

	gpio_set_value(gpio_charge_en, enable);
	input_value = gpio_get_value(gpio_charge_en);
	pr_debug("get gpio_charge_en = %d\n", input_value);
}

EXPORT_SYMBOL(set_gpio_mic_gnd);
EXPORT_SYMBOL(set_gpio_usb_sw);
EXPORT_SYMBOL(set_gpio_wifi_en);
EXPORT_SYMBOL(set_gpio_charge_en);

#if defined(LCM_ENABLE_ICN6211) //zwl 20180806
void set_gpio_rgb_rst(int enable)
{
	int input_value = 0;
	gpio_set_value(gpio_rgb_rst, enable);
	input_value = gpio_get_value(gpio_rgb_rst);
	pr_debug("get gpio_rgb_rst = %d\n", input_value);
}
#endif

#if defined(YK921_CONFIG) //dual battery
void set_gpio_no_id(int enable)
{
	int input_value = 0;

	gpio_set_value(gpio_no_id, enable);
	input_value = gpio_get_value(gpio_no_id);
	pr_debug("get gpio_no_id = %d\n", input_value);
}

void set_gpio_vbat_en(int enable)
{
	int input_value = 0;

	gpio_set_value(gpio_vbat_en, enable);
	input_value = gpio_get_value(gpio_vbat_en);
	pr_debug("get gpio_vbat_en = %d\n", input_value);
}

void set_gpio_bat_chg_en(int enable)
{
	int input_value = 0;

	gpio_set_value(gpio_bat_chg_en, enable);
	input_value = gpio_get_value(gpio_bat_chg_en);
	pr_debug("get gpio_bat_chg_en = %d\n", input_value);
}

void set_gpio_sel_bat(int enable)
{
	int input_value = 0;

	gpio_set_value(gpio_sel_bat, enable);
	input_value = gpio_get_value(gpio_sel_bat);
	pr_debug("get gpio_sel_bat = %d\n", input_value);
}
EXPORT_SYMBOL(set_gpio_no_id);
EXPORT_SYMBOL(set_gpio_vbat_en);
EXPORT_SYMBOL(set_gpio_bat_chg_en);
EXPORT_SYMBOL(set_gpio_sel_bat);
#endif

#if defined(YK921_CONFIG)
void set_gpio_cam_cut_en(int enable)
{
	//int input_value = 0;

	gpio_set_value(gpio_cam_cut_en, enable);
	//input_value = gpio_get_value(gpio_cam_cut_en);
	pr_debug("set gpio_cam_cut_en = %d\n", enable);
}

EXPORT_SYMBOL(set_gpio_cam_cut_en); //xen 20180708

//led controller: //xen 20180714
void set_gpio_red_alarm_en(int enable)
{
	gpio_set_value(gpio_red_alarm_en, enable);
	pr_debug("set gpio_red_alarm_en = %d\n", enable);
}
void set_gpio_blue_alarm_en(int enable)
{
	gpio_set_value(gpio_blue_alarm_en, enable);
	pr_debug("set gpio_blue_alarm_en = %d\n", enable);
}
void set_gpio_ray_led_en(int enable)
{
	gpio_set_value(gpio_ray_led_en, enable);
	pr_debug("set gpio_ray_led_en = %d\n", enable);
}
EXPORT_SYMBOL(set_gpio_red_alarm_en);
EXPORT_SYMBOL(set_gpio_blue_alarm_en);
EXPORT_SYMBOL(set_gpio_ray_led_en);

//flashlight control: //xen 20180723
void set_gpio_flashlight_strobe(int enable)
{
	gpio_set_value(gpio_flashlight_strobe, enable);
	pr_debug("set gpio_flashlight_strobe = %d\n", enable);
}
void set_gpio_flashlight_enable(int enable)
{
	gpio_set_value(gpio_flashlight_enable, enable);
	pr_debug("set gpio_flashlight_enable = %d\n", enable);
}

EXPORT_SYMBOL(set_gpio_flashlight_strobe);
EXPORT_SYMBOL(set_gpio_flashlight_enable);

#endif

#if defined(ET732_CONFIG) //xen 20180801
int gpio_ite_dvb_v33_en;
int gpio_bk_ite_ant_pwr_en;
int gpio_usb_ite_switch_sel;
int gpio_usb_ite_switch_oe;
int gpio_bk_ite_ant_switch_sel;
int gpio_ite_dvb_otg_en;

//Broadcast RX:
int gpio_bk_3v3_en;
int gpio_mc_kb_sw_en;
int gpio_bk_reset;
int gpio_bk_sq;
int gpio_bk_ptt;
//int gpio_bk_ite_sw_pwr;
//int gpio_bpi_bus2;
void set_gpio_ite_dvb_v33_en(int enable)
{
	gpio_set_value(gpio_ite_dvb_v33_en, enable);
	pr_debug("set gpio_ite_dvb_v33_en = %d\n", enable);
}
void set_gpio_bk_ite_ant_pwr_en(int enable)
{
	gpio_set_value(gpio_bk_ite_ant_pwr_en, enable);
	pr_debug("set gpio_bk_ite_ant_pwr_en = %d\n", enable);
}
void set_gpio_usb_ite_switch_sel(int sel)  //1--ite path, 0--usb path
{
	gpio_set_value(gpio_usb_ite_switch_sel, sel);
	pr_debug("set gpio_usb_ite_switch_sel = %d\n", sel);
}
void set_gpio_usb_ite_switch_oe(int enable) //alway set low level
{
	gpio_set_value(gpio_usb_ite_switch_oe, enable);
	pr_debug("set gpio_usb_ite_switch_oe = %d\n", enable);
}
void set_gpio_bk_ite_ant_switch_sel(int sel)
{
	gpio_set_value(gpio_bk_ite_ant_switch_sel, sel);
	pr_debug("set gpio_bk_ite_ant_switch_sel = %d\n", sel);
}
void set_gpio_ite_dvb_otg_en(int enable)
{
	gpio_set_value(gpio_ite_dvb_otg_en, enable);
	pr_debug("set gpio_ite_dvb_otg_en = %d\n", enable);
}

void set_gpio_bk_3v3_enable(int enable)
{
	//int input_value = 0;

	gpio_set_value(gpio_bk_3v3_en, enable);
	//input_value = gpio_get_value(gpio_bk_3v3_en);
	pr_debug("set gpio_bk_3v3_en = %d\n", enable);
}

void set_gpio_mc_kb_sw_enable(int enable)
{
	//int input_value = 0;

	gpio_set_value(gpio_mc_kb_sw_en, enable);
	//input_value = gpio_get_value(gpio_mc_kb_sw_en);
	pr_debug("set gpio_mc_kb_sw_en = %d\n", enable);
}

void set_gpio_bk_reset(int enable)
{
	//int input_value = 0;

	gpio_set_value(gpio_bk_reset, enable);
	//input_value = gpio_get_value(gpio_bk_reset);
	pr_debug("set gpio_bk_reset = %d\n", enable);
}
void set_gpio_bk_sq(int enable)
{
	//int input_value = 0;

	gpio_set_value(gpio_bk_sq, enable);
	//input_value = gpio_get_value(gpio_bk_sq);
	pr_debug("set gpio_bk_sq = %d\n", enable);
}
void set_gpio_bk_ptt(int enable)
{
	//int input_value = 0;

	gpio_set_value(gpio_bk_ptt, enable);
	//input_value = gpio_get_value(gpio_bk_pt);
	pr_debug("set gpio_bk_ptt = %d\n", enable);
}

EXPORT_SYMBOL(set_gpio_ite_dvb_v33_en);
EXPORT_SYMBOL(set_gpio_bk_ite_ant_pwr_en);
EXPORT_SYMBOL(set_gpio_usb_ite_switch_sel);
EXPORT_SYMBOL(set_gpio_usb_ite_switch_oe);
EXPORT_SYMBOL(set_gpio_bk_ite_ant_switch_sel);
EXPORT_SYMBOL(set_gpio_ite_dvb_otg_en);

EXPORT_SYMBOL(set_gpio_bk_3v3_enable);
EXPORT_SYMBOL(set_gpio_mc_kb_sw_enable);
EXPORT_SYMBOL(set_gpio_bk_reset);
EXPORT_SYMBOL(set_gpio_bk_sq);
EXPORT_SYMBOL(set_gpio_bk_ptt);

#endif

#if defined(ET918_CONFIG)/*zwl 20181009*/
/*add the new gpio name here and dts,then add the enum gpio on lcm_gpio.h*/
struct et_cust_gpio_attr et_cust_gpios[ET_GPIO_MAX] = {
       [ET_GPIO_RLED]       =  {"gpio_rled_ctl"},
       [ET_GPIO_GLED]       =  {"gpio_gled_ctl"},
       [ET_GPIO_BLED]       =  {"gpio_bled_ctl"},
       [ET_GPIO_IRCUT]      =  {"gpio_ircut_ctl"},
       [ET_GPIO_SMIC]       =  {"gpio_smic_ctl"},
};

static int et_cust_gpio_init(struct platform_device *pdev, 
                 struct et_cust_gpio_attr gpios[], int size)
{
        int ret = 0, i = 0;
        for(i = 0; i < size; i++){      
                gpios[i].exist = 1; //init exist
                if(gpios[i].name != NULL){
                       gpios[i].pin = of_get_named_gpio(pdev->dev.of_node, gpios[i].name, 0);
                       if(gpios[i].pin < 0){
                                gpios[i].exist = 0;
                                pr_debug("[LCM][GPIO] %s = %d\n",gpios[i].name,gpios[i].pin);
                       }
                }
                else{
                        gpios[i].exist = 0; 
                        pr_debug("[LCM][GPIO]*** error :pin idx:%d no apply the name!\n",gpios[i].pin);
                }

                if(gpios[i].exist){
                        ret = gpio_request(gpios[i].pin, gpios[i].name);
	                if (ret < 0){
                                gpios[i].exist = 0;
	                        pr_debug("[LCM][GPIO] %s gpio_request failed!\n",gpios[i].name);
	                }
                }
                pr_debug("[LCM][GPIO] func:%s name:%s pin:%d \n",__func__,
                                               et_cust_gpios[i].name,et_cust_gpios[i].pin);
        }

        return ret;
}

int et_gpio_set_value(enum et_cust_gpio_type type,int value)
{
       if(type >= ET_GPIO_MAX)
       {
               pr_err("[LCM][GPIO] func:%s fatel err type:%d no exist!\n",__func__,type);
               return -ENODEV;
       }

       pr_debug("[LCM][GPIO] set pin:%s pin:%d !\n",et_cust_gpios[type].name,et_cust_gpios[type].pin);
       value = !!value;
       if(et_cust_gpios[type].exist){
               gpio_set_value(et_cust_gpios[type].pin, value);
               return 0;
       }
       else{
               pr_debug("[LCM][GPIO] pin %s no found in dts!\n",et_cust_gpios[type].name);
               return -ENODEV;
       }
}   

int et_gpio_get_value(enum et_cust_gpio_type type)
{
       if(type >= ET_GPIO_MAX)
       {
               pr_err("[LCM][GPIO] func:%s fatel err type:%d no exist!\n",__func__,type);
               return -ENODEV;
       }

       if(et_cust_gpios[type].exist){
               pr_debug("[LCM][GPIO] pin:%s val:%d \n",et_cust_gpios[type].name
                                                 ,gpio_get_value(et_cust_gpios[type].pin));
               return  gpio_get_value(et_cust_gpios[type].pin);
       }
       else{
               pr_debug("[LCM][GPIO] pin %s no found in dts!\n",et_cust_gpios[type].name);
               return -ENODEV;
       }

}   

int et_gpio_set_dir(enum et_cust_gpio_type type,int value)
{
       if(type >= ET_GPIO_MAX)
       {
               pr_err("[LCM][GPIO] func:%s fatel err type:%d no exist!\n",__func__,type);
               return -ENODEV;
       }

       pr_debug("[LCM][GPIO] set pin:%s pin:%d !\n",et_cust_gpios[type].name,et_cust_gpios[type].pin);
       value = !!value;
       if(et_cust_gpios[type].exist){
               gpio_direction_output(et_cust_gpios[type].pin, value);
               return 0;
       }
       else{
               pr_debug("[LCM][GPIO] pin %s no found in dts!\n",et_cust_gpios[type].name);
               return -ENODEV;
       }
}

//debug part
static ssize_t et_get_value_show(struct device* cd,
                      struct device_attribute *attr, char* buf)
{
        int i = 0, len = 0;

	len += snprintf(buf+len, PAGE_SIZE-len, "\r\n");
        for(i = 0; i < ET_GPIO_MAX; i++)
        {
            if(et_cust_gpios[i].exist){
	        len += snprintf(buf+len, PAGE_SIZE-len, "name:%s index:%d value:%d\n",
                               et_cust_gpios[i].name, i, gpio_get_value(et_cust_gpios[i].pin));
            }
        }

	return len;
}

static ssize_t et_set_value_store(struct device* cd,
                   struct device_attribute *attr,const char* buf, size_t len)
{
	unsigned int databuf[2];
	if(2 == sscanf(buf,"%d %d",&databuf[0], &databuf[1]))
        {
            if(et_cust_gpios[databuf[0]].exist){
                gpio_set_value(et_cust_gpios[databuf[0]].pin, databuf[1]);
            }
	}
	return len;
}

static DEVICE_ATTR(etgpio, 0664, et_get_value_show, et_set_value_store);

static struct attribute *etgpio_attrs[] = {
	&dev_attr_etgpio.attr,
	NULL,
};

static struct attribute_group etgpio_group = {
	.attrs = etgpio_attrs
};
#endif

static int _lcm_gpio_probe(struct platform_device *pdev)
{
	int ret = 0;

	pr_debug("[LCM][GPIO] enter %s, %d\n", __func__, __LINE__);

	gpio_lcd_id = of_get_named_gpio(pdev->dev.of_node, "gpio_lcd_id", 0);
	gpio_mic_gnd = of_get_named_gpio(pdev->dev.of_node, "gpio_mic_gnd", 0);
	gpio_usb_sw = of_get_named_gpio(pdev->dev.of_node, "gpio_usb_sw", 0);
	gpio_wifi_en = of_get_named_gpio(pdev->dev.of_node, "gpio_wifi_en", 0);
	gpio_charge_en = of_get_named_gpio(pdev->dev.of_node, "gpio_charge_en", 0);

	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_lcd_id=%d\n", gpio_lcd_id);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_mic_gnd=%d\n", gpio_mic_gnd);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_usb_sw=%d\n", gpio_usb_sw);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_wifi_en=%d\n", gpio_wifi_en);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_charge_en=%d\n", gpio_charge_en);

#if defined(LCM_ENABLE_ICN6211)
	gpio_rgb_rst = of_get_named_gpio(pdev->dev.of_node, "gpio_rgb_rst", 0);
#endif

#if defined(YK921_CONFIG)
	gpio_cam_cut_en = of_get_named_gpio(pdev->dev.of_node, "gpio_cam_cut_en", 0); //xen 20180708
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_cam_cut_en=%d\n", gpio_cam_cut_en);

//led controller
	gpio_red_alarm_en = of_get_named_gpio(pdev->dev.of_node, "gpio_red_alarm_en", 0);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_red_alarm_en=%d\n", gpio_red_alarm_en);
	gpio_blue_alarm_en = of_get_named_gpio(pdev->dev.of_node, "gpio_blue_alarm_en", 0);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_blue_alarm_en=%d\n", gpio_blue_alarm_en);
	gpio_ray_led_en = of_get_named_gpio(pdev->dev.of_node, "gpio_ray_led_en", 0);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_ray_led_en=%d\n", gpio_ray_led_en);

//flashlight control: //xen 20180723
	gpio_flashlight_strobe = of_get_named_gpio(pdev->dev.of_node, "gpio_flashlight_strobe", 0);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_flashlight_strobe=%d\n", gpio_flashlight_strobe);
	gpio_flashlight_enable = of_get_named_gpio(pdev->dev.of_node, "gpio_flashlight_enable", 0);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_flashlight_enable=%d\n", gpio_flashlight_enable);

//zlh add for dual battery 
	gpio_no_id = of_get_named_gpio(pdev->dev.of_node, "gpio_no_id", 0);
	gpio_vbat_en = of_get_named_gpio(pdev->dev.of_node, "gpio_vbat_en", 0);
	gpio_bat_chg_en = of_get_named_gpio(pdev->dev.of_node, "gpio_bat_chg_en", 0);
	gpio_sel_bat = of_get_named_gpio(pdev->dev.of_node, "gpio_sel_bat", 0);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_no_id=%d\n", gpio_no_id);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_vbat_en=%d\n", gpio_vbat_en);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_bat_chg_en=%d\n", gpio_bat_chg_en);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_sel_bat=%d\n", gpio_sel_bat);
#endif

//gpio_mic_gnd
	ret = gpio_request(gpio_mic_gnd, "gpio_mic_gnd");
	if (ret<0){
	   pr_debug("gpio_mic_gnd gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_mic_gnd, 0);
	gpio_set_value(gpio_mic_gnd, 0);

//gpio_usb_sw
	ret = gpio_request(gpio_usb_sw, "gpio_usb_sw");
	if (ret<0){
	   pr_debug("gpio_usb_sw gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_usb_sw, 0);
	gpio_set_value(gpio_usb_sw, 0);

//gpio_wifi_en
	ret = gpio_request(gpio_wifi_en, "gpio_wifi_en");
	if (ret<0){
	   pr_debug("gpio_wifi_en gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_wifi_en, 1);
	gpio_set_value(gpio_wifi_en, 1);

//gpio_charge_en
	ret = gpio_request(gpio_charge_en, "gpio_charge_en");
	if (ret<0){
	   pr_debug("gpio_charge_en gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_charge_en, 0);
	gpio_set_value(gpio_charge_en, 0);
#if defined(LCM_ENABLE_ICN6211)
        //gpio_rgb_rst
	ret = gpio_request(gpio_rgb_rst, "gpio_rgb_rst");
	if (ret < 0){
	   pr_debug("gpio_rgb_rst gpio_request failed!\n");
	   return -ENODEV;
	}
#endif 
    
#if defined(YK921_CONFIG) //xen 20180708
	ret = gpio_request(gpio_cam_cut_en, "gpio_cam_cut_en");
	if (ret<0){
	   pr_debug("gpio_cam_cut_en gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_cam_cut_en, 0);
	gpio_set_value(gpio_cam_cut_en, 0);
	
//dual battery:
//gpio_no_id
	ret = gpio_request(gpio_no_id, "gpio_no_id");
	if (ret<0){
	   pr_debug("gpio_no_id gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_no_id, 0);
	gpio_set_value(gpio_no_id, 0);

//gpio_vbat_en
	ret = gpio_request(gpio_vbat_en, "gpio_vbat_en");
	if (ret<0){
	   pr_debug("gpio_vbat_en gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_vbat_en, 1);
	gpio_set_value(gpio_vbat_en, 1);
	
//gpio_bat_chg_en
	ret = gpio_request(gpio_bat_chg_en, "gpio_bat_chg_en");
	if (ret<0){
	   pr_debug("gpio_bat_chg_en gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_bat_chg_en, 0);
	gpio_set_value(gpio_bat_chg_en, 0);
	
//gpio_sel_bat
	ret = gpio_request(gpio_sel_bat, "gpio_sel_bat");
	if (ret<0){
	   pr_debug("gpio_sel_bat gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_sel_bat, 0);
	gpio_set_value(gpio_sel_bat, 0);	
#endif

#if defined(ET732_CONFIG) //xen 20180801
	gpio_ite_dvb_v33_en = of_get_named_gpio(pdev->dev.of_node, "gpio_ite_dvb_v33_en", 0);
	gpio_bk_ite_ant_pwr_en = of_get_named_gpio(pdev->dev.of_node, "gpio_bk_ite_ant_pwr_en", 0);
	gpio_usb_ite_switch_sel = of_get_named_gpio(pdev->dev.of_node, "gpio_usb_ite_switch_sel", 0);
	gpio_usb_ite_switch_oe = of_get_named_gpio(pdev->dev.of_node, "gpio_usb_ite_switch_oe", 0);
	gpio_bk_ite_ant_switch_sel = of_get_named_gpio(pdev->dev.of_node, "gpio_bk_ite_ant_switch_sel", 0);
	gpio_ite_dvb_otg_en = of_get_named_gpio(pdev->dev.of_node, "gpio_ite_dvb_otg_en", 0);

	ret = gpio_request(gpio_ite_dvb_v33_en, "gpio_ite_dvb_v33_en");
	if (ret<0){
	   pr_debug("gpio_ite_dvb_v33_en gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_ite_dvb_v33_en, 0);
	gpio_set_value(gpio_ite_dvb_v33_en, 0);

	ret = gpio_request(gpio_bk_ite_ant_pwr_en, "gpio_bk_ite_ant_pwr_en");
	if (ret<0){
	   pr_debug("gpio_bk_ite_ant_pwr_en gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_bk_ite_ant_pwr_en, 0);
	gpio_set_value(gpio_bk_ite_ant_pwr_en, 0);

	ret = gpio_request(gpio_usb_ite_switch_sel, "gpio_usb_ite_switch_sel");
	if (ret<0){
	   pr_debug("gpio_usb_ite_switch_sel gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_usb_ite_switch_sel, 0);
	gpio_set_value(gpio_usb_ite_switch_sel, 0);

	ret = gpio_request(gpio_usb_ite_switch_oe, "gpio_usb_ite_switch_oe");
	if (ret<0){
	   pr_debug("gpio_usb_ite_switch_oe gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_usb_ite_switch_oe, 0);
	gpio_set_value(gpio_usb_ite_switch_oe, 0);

	ret = gpio_request(gpio_bk_ite_ant_switch_sel, "gpio_bk_ite_ant_switch_sel");
	if (ret<0){
	   pr_debug("gpio_bk_ite_ant_switch_sel gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_bk_ite_ant_switch_sel, 0);
	gpio_set_value(gpio_bk_ite_ant_switch_sel, 0);

	ret = gpio_request(gpio_ite_dvb_otg_en, "gpio_ite_dvb_otg_en");
	if (ret<0){
	   pr_debug("gpio_ite_dvb_otg_en gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_ite_dvb_otg_en, 0);
	gpio_set_value(gpio_ite_dvb_otg_en, 0); 
	
//Broadcast RX:
	gpio_bk_3v3_en = of_get_named_gpio(pdev->dev.of_node, "gpio_bk_3v3_en", 0);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_bk_3v3_en=%d\n", gpio_bk_3v3_en);
	gpio_mc_kb_sw_en = of_get_named_gpio(pdev->dev.of_node, "gpio_mc_kb_sw_en", 0);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_mc_kb_sw_en=%d\n", gpio_mc_kb_sw_en);
	gpio_bk_reset = of_get_named_gpio(pdev->dev.of_node, "gpio_bk_reset", 0);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_bk_reset=%d\n", gpio_bk_reset);	
	gpio_bk_sq = of_get_named_gpio(pdev->dev.of_node, "gpio_bk_sq", 0);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_bk_sq=%d\n", gpio_bk_sq);	
	gpio_bk_ptt = of_get_named_gpio(pdev->dev.of_node, "gpio_bk_ptt", 0);
	pr_debug("[LCM][GPIO] _lcm_gpio_get_info end!gpio_bk_ptt=%d\n", gpio_bk_ptt);
	
	ret = gpio_request(gpio_bk_3v3_en, "gpio_bk_3v3_en");
	if (ret<0){
	   pr_debug("gpio_bk_3v3_en gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_bk_3v3_en, 0);
	gpio_set_value(gpio_bk_3v3_en, 0);	
	
	ret = gpio_request(gpio_mc_kb_sw_en, "gpio_mc_kb_sw_en");
	if (ret<0){
	   pr_debug("gpio_mc_kb_sw_en gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_mc_kb_sw_en, 0);
	gpio_set_value(gpio_mc_kb_sw_en, 0);
	
	ret = gpio_request(gpio_bk_reset, "gpio_bk_reset");
	if (ret<0){
	   pr_debug("gpio_bk_reset gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_bk_reset, 0);
	gpio_set_value(gpio_bk_reset, 0);
	
	ret = gpio_request(gpio_bk_sq, "gpio_bk_sq");
	if (ret<0){
	   pr_debug("gpio_bk_sq gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_bk_sq, 0);
	gpio_set_value(gpio_bk_sq, 0);	
	
	ret = gpio_request(gpio_bk_ptt, "gpio_bk_ptt");
	if (ret<0){
	   pr_debug("gpio_bk_ptt gpio_request failed!\n");
	   return -ENODEV;
	}
	gpio_direction_output(gpio_bk_ptt, 0);
	gpio_set_value(gpio_bk_ptt, 0);	
#endif

#if defined(ET918_CONFIG) /*zwl 20181109*/
	  et_cust_gpio_init(pdev, et_cust_gpios, ET_GPIO_MAX);//sizeof(et_cust_gpios[ET_GPIO_NUM])/sizeof(et_cust_gpios[0])
	ret = sysfs_create_group(&pdev->dev.kobj, &etgpio_group);
        if(ret < 0){
                printk("[LCM][GPIO] unable to create etgpio attribute file\n");
		return ret;
        }
#endif
	return 0;
}

static int _lcm_gpio_remove(struct platform_device *pdev)
{

	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id _lcm_gpio_of_ids[] = {
	{.compatible = "mediatek,lcd_id_gpio",},
	{},
};
MODULE_DEVICE_TABLE(of, _lcm_gpio_of_ids);
#endif

static struct platform_driver _lcm_gpio_driver = {
	.driver = {
		.name = LCM_GPIO_DEVICE,
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(_lcm_gpio_of_ids),
	},
	.probe = _lcm_gpio_probe,
	.remove = _lcm_gpio_remove,
};
module_platform_driver(_lcm_gpio_driver);

static int __init _lcm_gpio_init(void)
{
	pr_debug("MediaTek LCM GPIO driver init\n");
	if (platform_driver_register(&_lcm_gpio_driver) != 0) {
		pr_err("unable to register LCM GPIO driver.\n");
		return -1;
	}
	return 0;
}


/* should never be called */
static void __exit _lcm_gpio_exit(void)
{
	pr_debug("MediaTek LCM GPIO driver exit\n");
	platform_driver_unregister(&_lcm_gpio_driver);
}

module_init(_lcm_gpio_init);
module_exit(_lcm_gpio_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MediaTek LCM GPIO driver");
MODULE_AUTHOR("Joey Pan<joey.pan@mediatek.com>");

#else  //#ifndef BUILD_LK
#include "lcm_drv.h"
#include <platform/mt_gpio.h>
//#include "cust_gpio_usage.h"

#define GPIO_LCM_ID_PIN    (9|0x80000000)  //for yk736

static int lcm_id_high = 0xFF;
int get_lcd_id_state(void)
{
    unsigned char lcd_id = 0;
    //Solve Coverity scan warning : check return value
    unsigned int ret = 0;
    //only recognise once
    if(0xFF != lcm_id_high) 
    {
        return lcm_id_high;
    }
    //Solve Coverity scan warning : check return value
    ret = mt_set_gpio_mode(GPIO_LCM_ID_PIN, GPIO_MODE_GPIO);

    ret = mt_set_gpio_dir(GPIO_LCM_ID_PIN, GPIO_DIR_IN);
   
    lcd_id = mt_get_gpio_in(GPIO_LCM_ID_PIN);

    //if (lcd_id == 1)
    //{
    //	ret = mt_set_gpio_pull_select(GPIO_LCM_ID_PIN, GPIO_PULL_UP); 
    //}
    //else if (lcd_id == 0)
    //{
    //	ret = mt_set_gpio_pull_select(GPIO_LCM_ID_PIN, GPIO_PULL_DOWN);
    //}
    //else
    //{
    //	ret = mt_set_gpio_pull_select(GPIO_LCM_ID_PIN, GPIO_PULL_DISABLE);
    //}

    lcm_id_high = lcd_id;
    return lcd_id;
}
#endif

#endif
