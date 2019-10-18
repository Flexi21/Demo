/*
 * Copyright (C) 2010 MediaTek, Inc.
 *
 * Author: Terry Chang <terry.chang@mediatek.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "kpd.h"
#ifdef CONFIG_PM_WAKELOCKS
#include <linux/pm_wakeup.h>
#else
#include <linux/wakelock.h>
#endif
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/clk.h>
#include <linux/debugfs.h>

#define KPD_NAME	"mtk-kpd"

int kpd_klog_en;
void __iomem *kp_base;
static unsigned int kp_irqnr;
struct input_dev *kpd_input_dev;
static struct dentry *kpd_droot;
static struct dentry *kpd_dklog;
unsigned long call_status;
static bool kpd_suspend;
static unsigned int kp_irqnr;
static u32 kpd_keymap[KPD_NUM_KEYS];
static u16 kpd_keymap_state[KPD_NUM_MEMS];

struct input_dev *kpd_input_dev;
#ifdef CONFIG_PM_WAKELOCKS
struct wakeup_source kpd_suspend_lock;
#else
struct wake_lock kpd_suspend_lock;
#endif
struct keypad_dts_data kpd_dts_data;

#if defined(HALL_FUNCTION_SUPPORT)     //added by xen for test HALL function 20130819
//#include "cust_eint.h"
//#define KPD_HALL_SWITCH_EINT           CUST_EINT_MHALL_NUM
//#define KPD_HALL_SWITCH_DEBOUNCE       50    //CUST_EINT_MHALL_DEBOUNCE_CN
//#define KPD_HALL_SWITCH_POLARITY       0     //CUST_EINT_MHALL_POLARITY
//#define KPD_HALL_SWITCH_SENSITIVE      CUST_EINT_MHALL_TYPE   //CUST_EINT_MHALL_SENSITIVE
//#define KPD_HALL_SWITCH_POLARITY       CUST_EINT_MHALL_POLARITY
//#define KPD_HALL_SWITCH_SENSITIVE      CUST_EINT_MHALL_SENSITIVE
u32 mhall_irq_number = 0;
struct delayed_work mhall_eint_work;
//static void kpd_halldet_handler(unsigned long data);
//static DECLARE_TASKLET(kpd_halldet_tasklet, kpd_halldet_handler, 0);
static u8 kpd_halldet_state = 1; //!KPD_HALL_SWITCH_POLARITY; //HALL_FAR_AWAY;  //!KPD_PWRKEY_POLARITY;
#endif


/* for keymap handling */
static void kpd_keymap_handler(unsigned long data);
static DECLARE_TASKLET(kpd_keymap_tasklet, kpd_keymap_handler, 0);

static void kpd_memory_setting(void);
static int kpd_pdrv_probe(struct platform_device *pdev);
static int kpd_pdrv_suspend(struct platform_device *pdev, pm_message_t state);
static int kpd_pdrv_resume(struct platform_device *pdev);
static struct platform_driver kpd_pdrv;

static void kpd_memory_setting(void)
{
	kpd_init_keymap(kpd_keymap);
	kpd_init_keymap_state(kpd_keymap_state);
}

static ssize_t kpd_store_call_state(struct device_driver *ddri,
		const char *buf, size_t count)
{
	int ret;

	ret = kstrtoul(buf, 10, &call_status);
	if (ret) {
		kpd_print("kpd call state: Invalid values\n");
		return -EINVAL;
	}

	switch (call_status) {
	case 1:
		kpd_print("kpd call state: Idle state!\n");
		break;
	case 2:
		kpd_print("kpd call state: ringing state!\n");
		break;
	case 3:
		kpd_print("kpd call state: active or hold state!\n");
		break;

	default:
		kpd_print("kpd call state: Invalid values\n");
		break;
	}
	return count;
}

static ssize_t kpd_show_call_state(struct device_driver *ddri, char *buf)
{
	ssize_t res;

	res = snprintf(buf, PAGE_SIZE, "%ld\n", call_status);
	return res;
}

static DRIVER_ATTR(kpd_call_state, 0644, kpd_show_call_state,
		kpd_store_call_state);

#if defined(YKQ_OTG_DVB_T_SUPPORT)||defined(ET732_CONFIG) //xen 20180801
unsigned long dvb_otg_status;

extern void set_gpio_ite_dvb_v33_en(int enable);
extern void set_gpio_bk_ite_ant_pwr_en(int enable);
extern void set_gpio_usb_ite_switch_sel(int sel); 
//extern void set_gpio_usb_ite_switch_oe(int enable); 
extern void set_gpio_bk_ite_ant_switch_sel(int sel);
extern void set_gpio_ite_dvb_otg_en(int enable);


//static 
void dvb_otg_enter(int enable)
{
	if (enable) {
		set_gpio_usb_ite_switch_sel(1); //select ite-dvb path
		set_gpio_bk_ite_ant_switch_sel(1);
		set_gpio_bk_ite_ant_pwr_en(1);
		set_gpio_ite_dvb_v33_en(1);
		set_gpio_ite_dvb_otg_en(1);
	}
	else {
		set_gpio_ite_dvb_otg_en(0);
		set_gpio_ite_dvb_v33_en(0);
		set_gpio_usb_ite_switch_sel(0); //select usb path
		set_gpio_bk_ite_ant_switch_sel(0);
		set_gpio_bk_ite_ant_pwr_en(0);
	}
}

static ssize_t kpd_store_dvb_otg_status(struct device_driver *ddri,
		const char *buf, size_t count)
{
	unsigned int databuf[5];
	printk("kpd_store_dvb_otg_status\n");
	sscanf(buf,"%d",&databuf[0]);
	switch(databuf[0]) 
	{
	   case 1:
		dvb_otg_enter(1);
		dvb_otg_status = 1;
		kpd_print("kpd otg_status: work state!\n");
		break;
	   case 0:	//else if(strncmp("no",buf,2)==0) {
		dvb_otg_enter(0);
		//dvb_otg_status = 0; //removed to otg hisr, by xen 20180806
		kpd_print("kpd otg_status: exit state!\n");
		break;
	   default:
		kpd_print("kpd otg_status: invalid command!\n");
		break;
	}
	return count;
}

static ssize_t kpd_show_dvb_otg_status(struct device_driver *ddri, char *buf)
{
	ssize_t res;

	res = snprintf(buf, PAGE_SIZE, "%ld\n", dvb_otg_status);
	return res;
}

static DRIVER_ATTR(kpd_dvb_otg_status, 0644, kpd_show_dvb_otg_status,
		kpd_store_dvb_otg_status);
#endif

#if defined(YKQ_DUIJIANG_RX_SUPPORT)||defined(ET732_CONFIG) //xen 20180803
unsigned long dj_rx_status;

extern void set_gpio_bk_3v3_enable(int enable);
extern void set_gpio_mc_kb_sw_enable(int enable);
extern void set_gpio_bk_reset(int enable); 
extern void set_gpio_bk_sq(int enable); 
extern void set_gpio_bk_ptt(int enable); 
extern void set_gpio_bk_ite_ant_switch_sel(int sel);
extern void set_gpio_bk_ite_ant_pwr_en(int enable);

static ssize_t kpd_store_dj_rx_status(struct device_driver *ddri,
		const char *buf, size_t count)
{
	unsigned int databuf[5];

	printk("kpd_store_dj_rx_status\n");
	sscanf(buf,"%d",&databuf[0]);
	switch(databuf[0]) 
	{
		case 0: //power off
			set_gpio_bk_3v3_enable(0);  //3v3 ldo
			set_gpio_mc_kb_sw_enable(0);  //mic to KB path
			set_gpio_bk_reset(0);   //Bk reset
			set_gpio_bk_sq(0);      //BK SQ
			set_gpio_bk_ite_ant_pwr_en(0);//set_gpio_bk_ite_sw_pwr(0); //ant switch Power Enable
			set_gpio_bk_ite_ant_switch_sel(1);   //ant switch to DVB path
			printk("power off databuf[0]=%d", databuf[0]);
			break;
		case 1: //power on
			set_gpio_bk_3v3_enable(1); //3v3 ldo
			mdelay(10);
			set_gpio_mc_kb_sw_enable(1);  //mic to KB path
			set_gpio_bk_sq(1);            //Bk SQ
			set_gpio_bk_ite_ant_pwr_en(1);//set_gpio_bk_ite_sw_pwr(1);
			set_gpio_bk_reset(1);          //Bk reset
			set_gpio_bk_ite_ant_switch_sel(0);//set_gpio_bpi_bus2(0); //ant switch to DJ RX path
			printk("power on databuf[0]=%d", databuf[0]);
			break;
		case 3: //reset
			set_gpio_bk_reset(1);
			mdelay(10);
			set_gpio_bk_reset(0);
			mdelay(10);
			set_gpio_bk_reset(1);
			printk("bk reset databuf[0]=%d", databuf[0]);
			break;
		default:
			printk("not supported databuf[0]= %d", databuf[0]);
			break;
		
	}
	return count;
}

static ssize_t kpd_show_dj_rx_status(struct device_driver *ddri, char *buf)
{
	ssize_t res;

	res = snprintf(buf, PAGE_SIZE, "%ld\n", dj_rx_status);
	return res;
}

static DRIVER_ATTR(kpd_dj_rx_status, 0644, kpd_show_dj_rx_status,
		kpd_store_dj_rx_status);
#endif

static struct driver_attribute *kpd_attr_list[] = {
	&driver_attr_kpd_call_state,
#if defined(YKQ_OTG_DVB_T_SUPPORT)||defined(ET732_CONFIG) //xen 20180801
	&driver_attr_kpd_dvb_otg_status,
#endif
#if defined(YKQ_DUIJIANG_RX_SUPPORT)||defined(ET732_CONFIG) //xen 20180803
	&driver_attr_kpd_dj_rx_status,
#endif
};

static int kpd_create_attr(struct device_driver *driver)
{
	int idx, err = 0;
	int num = ARRAY_SIZE(kpd_attr_list);

	if (driver == NULL)
		return -EINVAL;

	for (idx = 0; idx < num; idx++) {
		err = driver_create_file(driver, kpd_attr_list[idx]);
		if (err) {
			kpd_info("driver_create_file (%s) = %d\n",
				kpd_attr_list[idx]->attr.name, err);
			break;
		}
	}
	return err;
}

static int kpd_delete_attr(struct device_driver *driver)
{
	int idx, err = 0;
	int num = ARRAY_SIZE(kpd_attr_list);

	if (!driver)
		return -EINVAL;

	for (idx = 0; idx < num; idx++)
		driver_remove_file(driver, kpd_attr_list[idx]);

	return err;
}

#if defined(HALL_FUNCTION_SUPPORT)          //added by xen for test HALL function 20130819
//extern void lcm_backlight_close(void);     //test by xen
//extern void lcm_backlight_open(void); 
//extern int old_level;
//static void kpd_halldet_handler(unsigned long data)
static irqreturn_t kpd_halldet_eint_handler(int irq, void *desc);
static void kpd_halldet_handler(struct work_struct *work)
{
	bool pressed;
	//u8 old_state = kpd_halldet_state;

        printk("\nxxx==kpd_halldet_handler hall_state=%d\n", kpd_halldet_state);
	kpd_halldet_state = 1 - kpd_halldet_state;
	pressed = (kpd_halldet_state == 0); //!!KPD_HALL_SWITCH_POLARITY);
	if (kpd_show_hw_keycode) {
		printk(KPD_SAY "(%s) HW keycode = using EINT\n",
		       pressed ? "pressed" : "released");
	}

	if (pressed)  //kpd_halldet_state==HALL_CLOSE_TO)
	{
	   input_report_key(kpd_input_dev, KEY_HALL_CLOSE, 1);
	   input_sync(kpd_input_dev);
	   input_report_key(kpd_input_dev, KEY_HALL_CLOSE, 0);
	   input_sync(kpd_input_dev);

	   printk("\nxxxHALL_CLOSE_TO===\n");
	   irq_set_irq_type(mhall_irq_number, IRQ_TYPE_LEVEL_HIGH);

	}
	else
	{
	   input_report_key(kpd_input_dev, KEY_HALL_FARAWAY, 1);
	   input_sync(kpd_input_dev);
	   input_report_key(kpd_input_dev, KEY_HALL_FARAWAY, 0);
	   input_sync(kpd_input_dev);

	   printk("\nxxxHALL_FAR_AWAY===\n");
	   irq_set_irq_type(mhall_irq_number, IRQ_TYPE_LEVEL_LOW);

	}

	/* for detecting the return to old_state */
	//mt_eint_set_polarity(KPD_HALL_SWITCH_EINT, old_state);
	//mt_eint_unmask(KPD_HALL_SWITCH_EINT);
	//mt_eint_set_polarity(KPD_HALL_SWITCH_EINT, old_state);
	//mt_eint_unmask(KPD_HALL_SWITCH_EINT);
	//request_irq(mhall_irq_number, kpd_halldet_eint_handler, IRQF_TRIGGER_HIGH, "mhall-eint", NULL)
	enable_irq(mhall_irq_number);
}

//static void kpd_halldet_eint_handler(void)
static irqreturn_t kpd_halldet_eint_handler(int irq, void *desc)
{
        //printk("\nxxx==kpd_halldet_eint_handler===\n");
	disable_irq_nosync(mhall_irq_number);
	//tasklet_schedule(&kpd_halldet_tasklet);
	schedule_delayed_work(&mhall_eint_work, 0);
	return IRQ_HANDLED;
}
#endif

#if defined (ALSPS_GESTURE)  // wanghe 2014-01-08
void kpd_alsps_gesture_handler(int key_code)
{
	   input_report_key(kpd_input_dev, key_code, 1);
	   input_sync(kpd_input_dev);
	   input_report_key(kpd_input_dev, key_code, 0);
	   input_sync(kpd_input_dev);
}
#endif

#if defined (TOUCHPANEL_GESTURE)  // xjl 2014-01-16
void kpd_touchpanel_gesture_handler(int key_code)
{
	//for vibrate soon
	//upmu_set_rg_vibr_en(1); //xjl 20140526
	//mdelay(50);
	//upmu_set_rg_vibr_en(0);

	input_report_key(kpd_input_dev, key_code, 1);
	input_sync(kpd_input_dev);
	input_report_key(kpd_input_dev, key_code, 0);
	input_sync(kpd_input_dev);
}
#endif
#if defined(_SUB2_CAM_SHELTER_DESIGN2_)||defined(_MAIN2_CAM_SHELTER_DESIGN2_) //xen 20170211
void kpd_detect_shelter_near_handler(void)
{
	input_report_key(kpd_input_dev, KEY_CAM_SHELTER_NEAR, 1);
	input_sync(kpd_input_dev);
	input_report_key(kpd_input_dev, KEY_CAM_SHELTER_NEAR, 0);
	input_sync(kpd_input_dev);
        
}

void kpd_detect_shelter_far_handler(void)
{
	input_report_key(kpd_input_dev, KEY_CAM_SHELTER_FAR, 1);
	input_sync(kpd_input_dev);
	input_report_key(kpd_input_dev, KEY_CAM_SHELTER_FAR, 0);
	input_sync(kpd_input_dev);
}
#endif

#if 1//defined(FINGERPRINT_SUPPORT) //xen 20170427
#include <linux/proc_fs.h>
#define PROC_FINGERPRINT_INFO "driver/fingerprint_info"
#define fingerprint_info_size 128
char mtk_fingerprint_name[fingerprint_info_size] = {0};
static int subsys_fingerprint_info_read(struct seq_file *m, void *v)
{
   //PK_ERR("subsys_tp_info_read %s\n",mtk_tp_name);
#if defined(FINGERPRINT_SUPPORT) //xen 20170427
   seq_printf(m, "%s\n",mtk_fingerprint_name);
#else
   seq_printf(m, "%s\n","no support");
#endif
   return 0;
};

static int proc_fingerprint_info_open(struct inode *inode, struct file *file)
{
    return single_open(file, subsys_fingerprint_info_read, NULL);
};

static  struct file_operations fingerprint_proc_fops1 = {
    .owner = THIS_MODULE,
    .open  = proc_fingerprint_info_open,
    .read  = seq_read,
};
#if defined(FINGERPRINT_SUPPORT) //xen 20170427
void fingerprint_set_name(char* name)
{
    snprintf(mtk_fingerprint_name,sizeof(mtk_fingerprint_name),"%s",name);
}
#endif

#endif

/*********************************************************************/
#ifdef CONFIG_KPD_PWRKEY_USE_PMIC
void kpd_pwrkey_pmic_handler(unsigned long pressed)
{
	kpd_print("Power Key generate, pressed=%ld\n", pressed);
	if (!kpd_input_dev) {
		kpd_print("KPD input device not ready\n");
		return;
	}
	kpd_pmic_pwrkey_hal(pressed);
}
#endif

void kpd_pmic_rstkey_handler(unsigned long pressed)
{
	kpd_print("PMIC reset Key generate, pressed=%ld\n", pressed);
	if (!kpd_input_dev) {
		kpd_print("KPD input device not ready\n");
		return;
	}
	kpd_pmic_rstkey_hal(pressed);
}

static void kpd_keymap_handler(unsigned long data)
{
	u16 i, j;
	int32_t pressed;
	u16 new_state[KPD_NUM_MEMS], change, mask;
	u16 hw_keycode, linux_keycode;
	void *dest;

	kpd_get_keymap_state(new_state);
#ifdef CONFIG_PM_WAKELOCKS
	__pm_wakeup_event(&kpd_suspend_lock, 500*8);//songjian 20190910 *8 for screen off press key is wakeup for long press key ,no need auto send key up event
#else
	wake_lock_timeout(&kpd_suspend_lock, HZ / 2);
#endif
	for (i = 0; i < KPD_NUM_MEMS; i++) {
		change = new_state[i] ^ kpd_keymap_state[i];
		if (change == 0U)
			continue;

		for (j = 0; j < 16U; j++) {
			mask = (u16) 1 << j;
			if ((change & mask) == 0U)
				continue;

			hw_keycode = (i << 4) + j;

			if (hw_keycode >= KPD_NUM_KEYS)
				continue;

			/* bit is 1: not pressed, 0: pressed */
			pressed = ((new_state[i] & mask) == 0U) ? 1 : 0;
			kpd_print("(%s) HW keycode = %d\n",
				(pressed == 1) ? "pressed" : "released",
					hw_keycode);

			linux_keycode = kpd_keymap[hw_keycode];
			if (linux_keycode == 0U)
				continue;
			input_report_key(kpd_input_dev, linux_keycode, pressed);
			input_sync(kpd_input_dev);
			kpd_print("report Linux keycode = %d\n", linux_keycode);
		}
	}

	dest = memcpy(kpd_keymap_state, new_state, sizeof(new_state));
	enable_irq(kp_irqnr);
}

static irqreturn_t kpd_irq_handler(int irq, void *dev_id)
{
	/* use _nosync to avoid deadlock */
	disable_irq_nosync(kp_irqnr);
	tasklet_schedule(&kpd_keymap_tasklet);
	return IRQ_HANDLED;
}

static int kpd_open(struct input_dev *dev)
{
	/* void __user *uarg = (void __user *)arg; */
	return 0;
}

void kpd_get_dts_info(struct device_node *node)
{
	int32_t ret;

	of_property_read_u32(node, "mediatek,kpd-key-debounce",
		&kpd_dts_data.kpd_key_debounce);
	of_property_read_u32(node, "mediatek,kpd-sw-pwrkey",
		&kpd_dts_data.kpd_sw_pwrkey);
	of_property_read_u32(node, "mediatek,kpd-hw-pwrkey",
		&kpd_dts_data.kpd_hw_pwrkey);
	of_property_read_u32(node, "mediatek,kpd-sw-rstkey",
		&kpd_dts_data.kpd_sw_rstkey);
	of_property_read_u32(node, "mediatek,kpd-hw-rstkey",
		&kpd_dts_data.kpd_hw_rstkey);
	of_property_read_u32(node, "mediatek,kpd-use-extend-type",
		&kpd_dts_data.kpd_use_extend_type);
	of_property_read_u32(node, "mediatek,kpd-hw-dl-key1",
		&kpd_dts_data.kpd_hw_dl_key1);
	of_property_read_u32(node, "mediatek,kpd-hw-dl-key2",
		&kpd_dts_data.kpd_hw_dl_key2);
	of_property_read_u32(node, "mediatek,kpd-hw-dl-key3",
		&kpd_dts_data.kpd_hw_dl_key3);
	of_property_read_u32(node, "mediatek,kpd-hw-recovery-key",
		&kpd_dts_data.kpd_hw_recovery_key);
	of_property_read_u32(node, "mediatek,kpd-hw-factory-key",
		&kpd_dts_data.kpd_hw_factory_key);
	of_property_read_u32(node, "mediatek,kpd-hw-map-num",
		&kpd_dts_data.kpd_hw_map_num);
	ret = of_property_read_u32_array(node, "mediatek,kpd-hw-init-map",
		kpd_dts_data.kpd_hw_init_map,
			kpd_dts_data.kpd_hw_map_num);

	if (ret) {
		kpd_print("kpd-hw-init-map was not defined in dts.\n");
		memset(kpd_dts_data.kpd_hw_init_map, 0,
			sizeof(kpd_dts_data.kpd_hw_init_map));
	}

	kpd_print("deb= %d, sw-pwr= %d, hw-pwr= %d, hw-rst= %d, sw-rst= %d\n",
		  kpd_dts_data.kpd_key_debounce, kpd_dts_data.kpd_sw_pwrkey,
			kpd_dts_data.kpd_hw_pwrkey, kpd_dts_data.kpd_hw_rstkey,
				kpd_dts_data.kpd_sw_rstkey);
}

static int32_t kpd_gpio_init(struct device *dev)
{
	struct pinctrl *keypad_pinctrl;
	struct pinctrl_state *kpd_default;
	int32_t ret;

	if (dev == NULL) {
		kpd_print("kpd device is NULL!\n");
		ret = -1;
	} else {
		keypad_pinctrl = devm_pinctrl_get(dev);
		if (IS_ERR(keypad_pinctrl)) {
			ret = -1;
			kpd_print("Cannot find keypad_pinctrl!\n");
		} else {
			kpd_default = pinctrl_lookup_state(keypad_pinctrl,
				"default");
			if (IS_ERR(kpd_default)) {
				ret = -1;
				kpd_print("Cannot find ecall_state!\n");
			} else
				ret = pinctrl_select_state(keypad_pinctrl,
					kpd_default);
		}
	}
	return ret;
}

static int mt_kpd_debugfs(void)
{
#ifdef CONFIG_MTK_ENG_BUILD
	kpd_klog_en = 1;
#else
	kpd_klog_en = 0;
#endif
	kpd_droot = debugfs_create_dir("keypad", NULL);
	if (IS_ERR_OR_NULL(kpd_droot))
		return PTR_ERR(kpd_droot);

	kpd_dklog = debugfs_create_u32("debug", 0600, kpd_droot, &kpd_klog_en);

	return 0;
}

#if defined(ET732_CONFIG) //for ET732 DVB&DuiJiang Function 20180808
#include <linux/fs.h>
#include <linux/cdev.h>

#define DUIJIANG_DEV_NAME  "duijiang"
static dev_t duijiang_devno;
static int duijiang_major;
static struct cdev *duijiang_cdev;
static struct class *duijiang_class;
static DEFINE_MUTEX(duijiang_mutex);

extern void set_gpio_usb_ite_switch_oe(int enable); 

#define DVB_3V3_EN _IOW('k', 0x30, unsigned long)         // EINT10 - W3
#define BK_3V3_EN  _IOW('k', 0x31, unsigned long)         // GPIO_EXT3 - G24
#define BK_RESET   _IOW('k', 0x32, unsigned long)              // GPIO_EXT7 - H24
#define BK_ITE_SW_PWR_EN _IOW('k', 0x33, unsigned long)        // EINT9 - W4
#define ANT_SW1_DUMMY    _IOW('k', 0x34, unsigned long)  // EINT9 - W4 // antenna switch1 (DUMMY IOCTL SINCE IT IS ALREADY CONTROLLED BY BK_ITE_SW_PWR_EN)
#define BPI_BUS2  _IOW('k', 0x35, unsigned long)            // BPI_BUS2 - AF3 // antenna switch2
#define DPDT_OE   _IOW('k', 0x36, unsigned long)               // GPIO_EXT0 - G23 // USB SWITCH OUTPUT ENABLE
#define DPDT_S    _IOW('k', 0x37, unsigned long)                // GPIO_EXT1 - F25 // USB SWITCH BETWEEN ITE?¡¥USB or ADB?¡¥USB
#define MIC_KB_SW_EN _IOW('k', 0x38, unsigned long)     //GPIO_EXT9-Y23//codec receive audio1=>switch between BUILT-IN MIC or BEKEN AUDIO OUT (AF_OUT)
#define BK_SQ   _IOW('k', 0x39, unsigned long)               // GPIO_EXT4 - F26
#define VBUS_CUT_OFF_EN _IOW('k', 0x40, unsigned long)       // not needed, but still use has DUMMY IOCTL TO STAY COMPATIBLE TO BOTH LINUX DRIVERS
#define DVB_OTG    _IOW('k', 0x41, unsigned long) //ITE_OTG
#define BK_PTT     _IOW('k', 0x42, unsigned long)

static long duijiang_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int tmp = (int)arg;

	printk("duijiang_unlocked_ioctl cmd=%x,arg=%d!\n", cmd,tmp);
#if 1  //just for test 20180821
	mutex_lock(&duijiang_mutex);

	switch (cmd) {
	case DVB_3V3_EN:
		set_gpio_ite_dvb_v33_en(tmp);
		break;
	case BK_3V3_EN:
		set_gpio_bk_3v3_enable(tmp);//1);
		break;
	case BK_RESET:
		if(tmp==1) {
			set_gpio_bk_reset(1);
			mdelay(10);
			set_gpio_bk_reset(0);
			mdelay(10);
			set_gpio_bk_reset(1);
		}else {
			set_gpio_bk_reset(0);
		}
		break;
	case BK_ITE_SW_PWR_EN:
		set_gpio_bk_ite_ant_pwr_en(tmp);//1);
		break;
	case ANT_SW1_DUMMY:  //dummy function,no use
		break;
	case BPI_BUS2:
		set_gpio_bk_ite_ant_switch_sel(tmp);//1); //DVB path
		break;
	case DPDT_OE:
		set_gpio_usb_ite_switch_oe(tmp);//0); 
		break;
	case DPDT_S:
		set_gpio_usb_ite_switch_sel(tmp);//1); 
		break;
	case MIC_KB_SW_EN:
		set_gpio_mc_kb_sw_enable(tmp);//1);
		break;
	case BK_SQ:  
		set_gpio_bk_sq(tmp);//1); 
		break;
	case BK_PTT:  
		set_gpio_bk_ptt(tmp);//1); 
		break;
	case VBUS_CUT_OFF_EN: //no need
		break;
	case DVB_OTG:
		set_gpio_ite_dvb_otg_en(tmp);
		if(tmp==1) {
		  dvb_otg_status = 1;  //dvb otg flag set 1 here, by xen 20180809
		}
		else {
		  //dvb_otg_status = 0;  //dvb otg flag set 1 here, by xen 20180809	
		}
		break;
	default:
		break;
	}

	mutex_unlock(&duijiang_mutex);
#endif
	return 0;
}

#ifdef CONFIG_COMPAT
static long compat_duijiang_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk("compat_duijiang_unlocked_ioctl!\n");

	if (!filp->f_op || !filp->f_op->unlocked_ioctl) {
		pr_err("compat_ion_ioctl file has no f_op or no f_op->unlocked_ioctl.\n");
		return -ENOTTY;
	}

	switch (cmd) {
	case DVB_3V3_EN:
	case BK_3V3_EN:
	case BK_RESET:
	case BK_ITE_SW_PWR_EN:
	case ANT_SW1_DUMMY:  //dummy function,no use
	case BPI_BUS2:
	case DPDT_OE:
	case DPDT_S:
	case MIC_KB_SW_EN:
	case BK_SQ:  
	case BK_PTT:  
	case VBUS_CUT_OFF_EN: //no need
	case DVB_OTG:
		return filp->f_op->unlocked_ioctl(filp, cmd,
			(unsigned long)compat_ptr(arg));

	default:
		pr_err("compat_ion_ioctl : No such command!! 0x%x\n", cmd);
		return -ENOIOCTLCMD;
	}
}
#endif

static int duijiang_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int duijiang_release(struct inode *inode, struct file *file)
{
	return 0;
}

static const struct file_operations duijiang_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = duijiang_unlocked_ioctl,
	.open = duijiang_open,
	.release = duijiang_release,
#if IS_ENABLED(CONFIG_COMPAT)
	.compat_ioctl = compat_duijiang_unlocked_ioctl,
#endif
};

#endif

#if defined(ET_KEYS_EINT_SUPPORT)/*zwl add start 20181120*/
#define ET_KEY_CUST0               0
#define ET_KEY_CUST1               1
#define ET_KEY_CUST2               2
#define ET_KEY_CUST3               3

struct et_eint {
        char *irq_name;           
        char *compatible;
	u32  irq_level;
        void (*et_cust_handler)(struct work_struct *work);
        struct delayed_work eint_work;
	u32  irq_num;
        bool key_status;
        int  type;
	u32  key;
};
 
static u32 *pet_cust_key = NULL; 
static struct et_eint *pet_eint_cust = NULL;

static irqreturn_t kpd_et_eint_handler(int irq, void *desc)
{
        int cust_num = *(int *)desc;
        //printk("zwl %d",cust_num);
	disable_irq_nosync((*(pet_eint_cust + cust_num)).irq_num);
	schedule_delayed_work(&(*(pet_eint_cust + cust_num)).eint_work, 0);
	return IRQ_HANDLED;
}

static void et_key_report(int cust_num)
{
	bool pressed;

	(*(pet_eint_cust + cust_num)).key_status = 1 - (*(pet_eint_cust + cust_num)).key_status;
	pressed = ((*(pet_eint_cust + cust_num)).key_status == 0); 
	pr_debug(KPD_SAY "(%s) HW keycode = using EINT\n",
		            pressed ? "pressed" : "released");

       if (pressed){ 
	       input_report_key(kpd_input_dev, (*(pet_eint_cust + cust_num)).key, 1);
	       input_sync(kpd_input_dev);
	       irq_set_irq_type((*(pet_eint_cust + cust_num)).irq_num, IRQ_TYPE_LEVEL_HIGH);
       }
       else{
	       input_report_key(kpd_input_dev, (*(pet_eint_cust + cust_num)).key, 0);
	       input_sync(kpd_input_dev);
	       irq_set_irq_type((*(pet_eint_cust + cust_num)).irq_num, IRQ_TYPE_LEVEL_LOW);
	}
}

/*TODO------------------------custom part start-------------------------*/
#define ET_HANDLER(num)               et_handler_cust##num

#define ET_KEY_HANDLER(num)                                \
static void et_handler_cust##num(struct work_struct *work) \
{                                                          \
        et_key_report(num);                                \
        enable_irq(pet_eint_cust[num].irq_num);            \
}

/*TODO*/
#if defined(ET918_CONFIG)
#define ET_KEY_CUST_MAX            4
#else
#define ET_KEY_CUST_MAX            1
#endif

u32 et_cust_key[ET_KEY_CUST_MAX] = {
/*TODO*/
#if defined(ET918_CONFIG)
        KEY_CAMERA, 
        KEY_F1,
        KEY_F2,
        KEY_F3,
#else
        KEY_F1,
#endif
};    

#if ET_KEY_CUST_MAX > 0 
        ET_KEY_HANDLER(0);
#endif

#if ET_KEY_CUST_MAX > 1
        ET_KEY_HANDLER(1);
#endif

#if ET_KEY_CUST_MAX > 2
        ET_KEY_HANDLER(2);
#endif

#if ET_KEY_CUST_MAX > 3
        ET_KEY_HANDLER(3);
#endif

static struct et_eint et_eint_cust[ET_KEY_CUST_MAX] = {
        #if ET_KEY_CUST_MAX > 0
        [ET_KEY_CUST0]  =  {"key_cust0", "mediatek, key_cust0-eint", IRQF_TRIGGER_LOW, ET_HANDLER(0)},
        #endif
        #if ET_KEY_CUST_MAX > 1
        [ET_KEY_CUST1]  =  {"key_cust1", "mediatek, key_cust1-eint", IRQF_TRIGGER_LOW, ET_HANDLER(1)},
        #endif
        #if ET_KEY_CUST_MAX > 2
        [ET_KEY_CUST2]  =  {"key_cust2", "mediatek, key_cust2-eint", IRQF_TRIGGER_LOW, ET_HANDLER(2)},
        #endif
        #if ET_KEY_CUST_MAX > 3
        [ET_KEY_CUST3]  =  {"key_cust3", "mediatek, key_cust3-eint", IRQF_TRIGGER_LOW, ET_HANDLER(3)}
        #endif
};
/*TODO------------------------custom part end-------------------------*/

static void et_init_private_data(int cust_num)
{
        (*(pet_eint_cust + cust_num)).type = cust_num;

        (*(pet_eint_cust + cust_num)).key_status = 1;

        (*(pet_eint_cust + cust_num)).irq_num = 0;

        (*(pet_eint_cust + cust_num)).key = *(pet_cust_key + cust_num);
}

int et_eint_init(struct et_eint cust[], int size)
{
	struct device_node *et_node = NULL;
	u32 ints[2] = { 0, 0 }, i = 0;
        static unsigned long init_flg = 0;
        pet_eint_cust = et_eint_cust;
        pet_cust_key = et_cust_key;
 
        for(i = 0; i < size; i++)
        {
             et_init_private_data(i);
            
             __set_bit(cust[i].key, kpd_input_dev->keybit);

             INIT_DELAYED_WORK(&cust[i].eint_work, cust[i].et_cust_handler);

             et_node = of_find_compatible_node(NULL, NULL, cust[i].compatible);
	     if (et_node) {
		    of_property_read_u32_array(et_node, "debounce", ints,ARRAY_SIZE(ints));

		    gpio_set_debounce(ints[0], ints[1]);
		    pr_debug("kpd: ints[0] = %d, ints[1] = %d!!\n", ints[0], ints[1]);

		    cust[i].irq_num = irq_of_parse_and_map(et_node, 0);
		    pr_debug("%s = %d\n",cust[i].irq_name,cust[i].irq_num);

		    if (!cust[i].irq_num) {
		         pr_debug("kpd: %s irq_of_parse_and_map fail!!\n",cust[i].compatible);
		         return -EINVAL;
	 	    }

		    if (request_irq(cust[i].irq_num, kpd_et_eint_handler, cust[i].irq_level, cust[i].irq_name, &cust[i].type)) {
			 pr_debug("kpd:%s IRQ LINE NOT AVAILABLE!!\n",cust[i].irq_name);
		         return -EINVAL;
	            }
		    enable_irq(cust[i].irq_num);
	    }
	    else{
		    pr_debug("kpd:%s null irq node!!\n",cust[i].irq_name);
                    set_bit(i, &init_flg);
                    pr_debug("kpd: cust_key_init_flg 0x:%lx",~(init_flg));
                    //continue;
		    return -EINVAL;
	    }
        }
        pr_debug("kpd: cust_key_init_flg 0x:%lx",~(init_flg));
        return 0;
}
#endif /*end of #if defined(ET_KEYS_CUST_SUPPORT)*/
/*zwl add end 20181120*/


static int kpd_pdrv_probe(struct platform_device *pdev)
{
	struct clk *kpd_clk = NULL;
	u32 i;
	int32_t err = 0;
#if defined(HALL_FUNCTION_SUPPORT) //added by xen 20160413
	struct device_node *hall_node = NULL;
	u32 ints[2] = { 0, 0 };
#endif

#if defined(ET732_CONFIG)
	struct device *duijiang_dev = NULL;
#endif

	if (!pdev->dev.of_node) {
		kpd_notice("no kpd dev node\n");
		return -ENODEV;
	}

	kpd_clk = devm_clk_get(&pdev->dev, "kpd-clk");
	if (!IS_ERR(kpd_clk)) {
		err = clk_prepare_enable(kpd_clk);
		if (err)
			kpd_notice("get kpd-clk fail: %d\n", err);
	} else {
		kpd_notice("kpd-clk is default set by ccf.\n");
	}

	kp_base = of_iomap(pdev->dev.of_node, 0);
	if (!kp_base) {
		kpd_notice("KP iomap failed\n");
		return -ENODEV;
	};

	kp_irqnr = irq_of_parse_and_map(pdev->dev.of_node, 0);
	if (!kp_irqnr) {
		kpd_notice("KP get irqnr failed\n");
		return -ENODEV;
	}
	kpd_info("kp base: 0x%p, addr:0x%p,  kp irq: %d\n",
			kp_base, &kp_base, kp_irqnr);
	err = kpd_gpio_init(&pdev->dev);
	if (err != 0)
		kpd_print("gpio init failed\n");

	kpd_get_dts_info(pdev->dev.of_node);

	kpd_memory_setting();

	kpd_input_dev = devm_input_allocate_device(&pdev->dev);
	if (!kpd_input_dev) {
		kpd_notice("input allocate device fail.\n");
		return -ENOMEM;
	}

	kpd_input_dev->name = KPD_NAME;
	kpd_input_dev->id.bustype = BUS_HOST;
	kpd_input_dev->id.vendor = 0x2454;
	kpd_input_dev->id.product = 0x6500;
	kpd_input_dev->id.version = 0x0010;
	kpd_input_dev->open = kpd_open;
	kpd_input_dev->dev.parent = &pdev->dev;

	__set_bit(EV_KEY, kpd_input_dev->evbit);
#if defined(CONFIG_KPD_PWRKEY_USE_PMIC)
	__set_bit(kpd_dts_data.kpd_sw_pwrkey, kpd_input_dev->keybit);
	kpd_keymap[8] = 0;
#endif
	if (!kpd_dts_data.kpd_use_extend_type) {
		for (i = 17; i < KPD_NUM_KEYS; i += 9)
			kpd_keymap[i] = 0;
	}
	for (i = 0; i < KPD_NUM_KEYS; i++) {
		if (kpd_keymap[i] != 0)
			__set_bit(kpd_keymap[i], kpd_input_dev->keybit);
	}

#if defined(HALL_FUNCTION_SUPPORT)          //added by xen for test HALL function 20130819
        __set_bit(KEY_HALL_CLOSE, kpd_input_dev->keybit);
        __set_bit(KEY_HALL_FARAWAY, kpd_input_dev->keybit);
#endif

#if defined (ALSPS_GESTURE)  // wanghe 2014-01-08
	__set_bit(KEY_GESTURE_UP, kpd_input_dev->keybit);
	__set_bit(KEY_GESTURE_DOWN, kpd_input_dev->keybit);
#endif

#if defined (TOUCHPANEL_GESTURE)  // xjl 2014-01-16
	__set_bit(KEY_TPGESTURE_UP, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_DOWN, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_LEFT, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_RIGHT, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_DOUBLE, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_C, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_E, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_M, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_O, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_S, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_V, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_W, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_Z, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_ARROWUP, kpd_input_dev->keybit);
	__set_bit(KEY_TPGESTURE_ARROWRIGHT, kpd_input_dev->keybit);	
#endif


#if defined(_SUB2_CAM_SHELTER_DESIGN2_)||defined(_MAIN2_CAM_SHELTER_DESIGN2_) //xen 20170211
	//__set_bit(KEY_CAMERA, kpd_input_dev->keybit);
	__set_bit(KEY_CAM_SHELTER_NEAR, kpd_input_dev->keybit);
	__set_bit(KEY_CAM_SHELTER_FAR, kpd_input_dev->keybit);
#endif

//#if defined(FINGERPRINT_SUPPORT) //xen 20170427
       memset(mtk_fingerprint_name,0,fingerprint_info_size);
       proc_create(PROC_FINGERPRINT_INFO, 0, NULL, &fingerprint_proc_fops1);
#if defined(FINGERPRINT_SUPPORT)
       snprintf(mtk_fingerprint_name,sizeof(mtk_fingerprint_name),"%s","No Detected");
#endif
//#endif

	if (kpd_dts_data.kpd_sw_rstkey)
		__set_bit(kpd_dts_data.kpd_sw_rstkey, kpd_input_dev->keybit);
#ifdef KPD_KEY_MAP
	__set_bit(KPD_KEY_MAP, kpd_input_dev->keybit);
#endif
#ifdef CONFIG_MTK_MRDUMP_KEY
	__set_bit(KEY_RESTART, kpd_input_dev->keybit);
#endif

	err = input_register_device(kpd_input_dev);
	if (err) {
		kpd_notice("register input device failed (%d)\n", err);
		return err;
	}
#ifdef CONFIG_PM_WAKELOCKS
	wakeup_source_init(&kpd_suspend_lock, "kpd wakelock");
#else
	wake_lock_init(&kpd_suspend_lock, WAKE_LOCK_SUSPEND, "kpd wakelock");
#endif
	/* register IRQ and EINT */
	kpd_set_debounce(kpd_dts_data.kpd_key_debounce);
	err = request_irq(kp_irqnr, kpd_irq_handler, IRQF_TRIGGER_NONE,
			KPD_NAME, NULL);
	if (err) {
		kpd_notice("register IRQ failed (%d)\n", err);
		input_unregister_device(kpd_input_dev);
		return err;
	}
#ifdef CONFIG_MTK_MRDUMP_KEY
	mt_eint_register();
#endif

#if defined(HALL_FUNCTION_SUPPORT)     //added by xen for test HALL function 20130819
        //mt_set_gpio_mode(GPIO_MHALL_EINT_PIN, GPIO_MHALL_EINT_PIN_M_EINT);
        //mt_set_gpio_dir(GPIO_MHALL_EINT_PIN, GPIO_DIR_IN);
        //mt_set_gpio_pull_enable(GPIO_MHALL_EINT_PIN, GPIO_PULL_DISABLE); //To disable GPIO PULL.
        //mt_eint_set_sens(KPD_HALL_SWITCH_EINT, KPD_HALL_SWITCH_SENSITIVE);
        //mt_eint_set_hw_debounce(KPD_HALL_SWITCH_EINT, KPD_HALL_SWITCH_DEBOUNCE);
        //mt65xx_eint_registration(KPD_HALL_SWITCH_EINT, true,KPD_HALL_SWITCH_POLARITY, kpd_halldet_eint_handler, false);
        //mt_eint_registration(KPD_HALL_SWITCH_EINT, CUST_EINT_MHALL_TYPE, kpd_halldet_eint_handler, 0); 
        //mt_eint_unmask(KPD_HALL_SWITCH_EINT);  
        INIT_DELAYED_WORK(&mhall_eint_work, kpd_halldet_handler);

        hall_node = of_find_compatible_node(NULL, NULL, "mediatek, mhall-eint");
	if (hall_node) {
		of_property_read_u32_array(hall_node, "debounce", ints,
					   ARRAY_SIZE(ints));
		//gpio_request(ints[0], "hallfunc");
		gpio_set_debounce(ints[0], ints[1]);
		kpd_print("ints[0] = %d, ints[1] = %d!!\n", ints[0], ints[1]);
                //pinctrl_select_state(pinctrl, pins_cfg);
		mhall_irq_number = irq_of_parse_and_map(hall_node, 0);
		kpd_print("mhall_irq_number = %d\n", mhall_irq_number);
		if (!mhall_irq_number) {
			kpd_print("mhall irq_of_parse_and_map fail!!\n");
			return -EINVAL;
		}
		if (request_irq(mhall_irq_number, kpd_halldet_eint_handler, IRQF_TRIGGER_LOW, "mhall-eint", NULL)) {
			kpd_print("IRQ LINE NOT AVAILABLE!!\n");
			return -EINVAL;
		}
		enable_irq(mhall_irq_number);
	}
	else
	{
		kpd_print("mhall null irq node!!\n");
		return -EINVAL;
	}
#endif

#if defined(ET732_CONFIG) //
	err = alloc_chrdev_region(&duijiang_devno, 0, 1, DUIJIANG_DEV_NAME);
	if (err)
		printk("[KPD]Error: Can't Get Major number for duijiang\n");

	duijiang_cdev = cdev_alloc();
	duijiang_cdev->owner = THIS_MODULE;
	duijiang_cdev->ops = &duijiang_fops;
	err = cdev_add(duijiang_cdev, duijiang_devno, 1);
	if (err)
		printk("duijiang Error: cdev_add\n");

	duijiang_major = MAJOR(duijiang_devno);
	duijiang_class = class_create(THIS_MODULE, DUIJIANG_DEV_NAME);
	duijiang_dev = (struct device *)device_create(duijiang_class,
						 NULL, duijiang_devno, NULL,
						 DUIJIANG_DEV_NAME);
	printk("[mtk_kpd_probe] dvb-duijiang device prepare : done !!\n");
#endif

#ifdef ET_KEYS_EINT_SUPPORT /*zwl 20181122*/
        et_eint_init(et_eint_cust, ET_KEY_CUST_MAX);
#endif

#ifdef CONFIG_MTK_PMIC_NEW_ARCH
	long_press_reboot_function_setting();
#endif
	err = kpd_create_attr(&kpd_pdrv.driver);
	if (err) {
		kpd_notice("create attr file fail\n");
		kpd_delete_attr(&kpd_pdrv.driver);
		return err;
	}
	/* Add kpd debug node */
	mt_kpd_debugfs();

	kpd_info("kpd_probe OK.\n");

	return err;
}

static int kpd_pdrv_suspend(struct platform_device *pdev, pm_message_t state)
{
	kpd_suspend = true;
#ifdef MTK_KP_WAKESOURCE
	if (call_status == 2) {
		kpd_print("kpd_early_suspend wake up source enable!! (%d)\n",
				kpd_suspend);
	} else {
		kpd_wakeup_src_setting(0);
		kpd_print("kpd_early_suspend wake up source disable!! (%d)\n",
				kpd_suspend);
	}
#endif
	kpd_print("suspend!! (%d)\n", kpd_suspend);
	return 0;
}

static int kpd_pdrv_resume(struct platform_device *pdev)
{
	kpd_suspend = false;
#ifdef MTK_KP_WAKESOURCE
	if (call_status == 2) {
		kpd_print("kpd_early_suspend wake up source enable!! (%d)\n",
				kpd_suspend);
	} else {
		kpd_print("kpd_early_suspend wake up source resume!! (%d)\n",
				kpd_suspend);
		kpd_wakeup_src_setting(1);
	}
#endif
	kpd_print("resume!! (%d)\n", kpd_suspend);
	return 0;
}

static const struct of_device_id kpd_of_match[] = {
	{.compatible = "mediatek,kp"},
	{},
};

static struct platform_driver kpd_pdrv = {
	.probe = kpd_pdrv_probe,
	.suspend = kpd_pdrv_suspend,
	.resume = kpd_pdrv_resume,
	.driver = {
		   .name = KPD_NAME,
		   .owner = THIS_MODULE,
		   .of_match_table = kpd_of_match,
		   },
};

module_platform_driver(kpd_pdrv);

MODULE_AUTHOR("Mediatek Corporation");
MODULE_DESCRIPTION("MTK Keypad (KPD) Driver");
MODULE_LICENSE("GPL");
