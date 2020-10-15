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
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

#include "cust_gpios.h"

#define TAG                  "[CUST][GPIO] "
#define FUNC_ENTRY           pr_info(TAG"%s entry!\n",__func__);
#define FUNC_EXIT            pr_info(TAG"%s exit!\n",__func__);
#define CUST_GPIO_DEVICE     "cust_gpio"

struct cust_gpio_attr cust_gpios[CUST_GPIO_MAX] = {
       [CUST_GPIO_RLED]       =  {"gpio_rled_ctl"},
       [CUST_GPIO_GLED]       =  {"gpio_gled_ctl"},
       [CUST_GPIO_BLED]       =  {"gpio_bled_ctl"},
#if defined(VL01C_CONFIG) //Leo 20200316
       [CUST_GPIO_TRX_EN]     =  {"gpio_trx_en"},
       [CUST_GPIO_ADC_SW]     =  {"gpio_adc_sw"},
       [CUST_GPIO_RS485_DATA] =  {"gpio_rs485_data"},
       [CUST_GPIO_LDO_5V]     =  {"gpio_ldo_5v"},
#elif defined(P340_CONFIG)
       [CUST_GPIO_IRCUT]      =  {"gpio_ircut_ctl"},
       [CUST_GPIO_MICSW]      =  {"gpio_micsw_ctl"},
       [CUST_GPIO_OLED]       =  {"gpio_oled_rst"},
       [CUST_GPIO_FM]         =  {"gpio_fm_ant"},
       [CUST_GPIO_RF24_EN]    =  {"gpio_rf24_en"},
       [CUST_GPIO_RF24_RST]   =  {"gpio_rf24_rst"},
       [CUST_GPIO_RF24_RSV]   =  {"gpio_rf24_rsv"},
       [CUST_GPIO_RF24_LVD]   =  {"gpio_rf24_lvd"},
#elif defined(KU982020_CONFIG) //Leo 20200730
       [CUST_GPIO_RF24_EN]    =  {"gpio_rf24_en"},
       [CUST_GPIO_RF24_RST]   =  {"gpio_rf24_rst"},
       [CUST_GPIO_RF24_RSV]   =  {"gpio_rf24_rsv"},
       [CUST_GPIO_RF24_LVD]   =  {"gpio_rf24_lvd"},
#elif defined(Y140_CONFIG) //Leo 20200928
       [CUST_GPIO_WTD_CLK]    =  {"gpio_wtd_clk"},
#endif
};

struct cust_gpio_attr *cust_get_gpio(enum cust_gpio_type type)
{
	return 	&cust_gpios[type];	
}
EXPORT_SYMBOL(cust_get_gpio);

static int cust_gpio_init(struct platform_device *pdev, 
                 struct cust_gpio_attr gpios[], int size)
{
	int ret = 0, i = 0;
	for(i = 0; i < size; i++) {      
		gpios[i].exist = 1; //init exist
		gpios[i].eint_num = 0; 
		if (gpios[i].name != NULL) {
			gpios[i].pin = of_get_named_gpio(pdev->dev.of_node, gpios[i].name, 0);
			if (gpios[i].pin < 0) {
				gpios[i].exist = 0;
				pr_info("[CUST][GPIO] %s = %d\n",gpios[i].name,gpios[i].pin);
			}
		} else {
			gpios[i].exist = 0; 
			pr_err("[CUST][GPIO]*** error :pin idx:%d no apply the name!\n",gpios[i].pin);
		}

		if (gpios[i].exist) {
			ret = gpio_request(gpios[i].pin, gpios[i].name);
			if (ret < 0) {
				gpios[i].exist = 0;
				pr_info("[CUST][GPIO] %s gpio_request failed!\n",gpios[i].name);
			}
		}
		pr_info("[CUST][GPIO] func:%s name:%s pin:%d \n",__func__,
											gpios[i].name,gpios[i].pin);
	}

	return ret;
}

int cust_gpio_set_value(enum cust_gpio_type type,int value)
{
	if (type >= CUST_GPIO_MAX) {
		pr_err("[CUST][GPIO] func:%s fatel err type:%d no exist!\n",__func__,type);
        return -ENODEV;
	}	
	pr_info("[CUST][GPIO] set pin:%s pin:%d !\n", 
				cust_gpios[type].name, cust_gpios[type].pin);

	if (cust_gpios[type].exist) {
		gpio_set_value(cust_gpios[type].pin, !!value);
		return 0;
	} else {
		pr_debug("[CUST][GPIO] pin %s no found in dts!\n",cust_gpios[type].name);
        return -ENODEV;
    }
}   
EXPORT_SYMBOL(cust_gpio_set_value);

int cust_gpio_get_value(enum cust_gpio_type type)
{
	if (type >= CUST_GPIO_MAX) {
		pr_err("[CUST][GPIO] func:%s fatel err type:%d no exist!\n",__func__,type);
		return -ENODEV;
	}

	if (cust_gpios[type].exist) {
		pr_info("[CUST][GPIO] pin:%s val:%d \n",cust_gpios[type].name
									,gpio_get_value(cust_gpios[type].pin));
		return  gpio_get_value(cust_gpios[type].pin);
	} else {
		pr_err("[CUST][GPIO] pin %s no found in dts!\n",cust_gpios[type].name);
		return -ENODEV;
	}
}   
EXPORT_SYMBOL(cust_gpio_get_value);

int cust_gpio_set_output(enum cust_gpio_type type,int value)
{
	if (type >= CUST_GPIO_MAX) {
		pr_err("[CUST][GPIO] func:%s fatel err type:%d no exist!\n",__func__,type);
		return -ENODEV;
	}
	pr_info("[CUST][GPIO] set pin:%s pin:%d !\n",
			cust_gpios[type].name,cust_gpios[type].pin);

	if (cust_gpios[type].exist) {
		gpio_direction_output(cust_gpios[type].pin, !!value);
		return 0;
	} else {
		pr_err("[CUST][GPIO] pin %s no found in dts!\n",cust_gpios[type].name);
		return -ENODEV;
	}
}
EXPORT_SYMBOL(cust_gpio_set_output);

int cust_gpio_set_input(enum cust_gpio_type type)
{
	if (type >= CUST_GPIO_MAX) {
		pr_err("[CUST][GPIO] func:%s fatel err type:%d no exist!\n",__func__,type);
		return -ENODEV;
	}
	pr_info("[CUST][GPIO] set pin:%s pin:%d !\n",
			cust_gpios[type].name,cust_gpios[type].pin);

	if (cust_gpios[type].exist) {
		gpio_direction_input(cust_gpios[type].pin);
		return 0;
	} else {
		pr_err("[CUST][GPIO] pin %s no found in dts!\n",cust_gpios[type].name);
		return -ENODEV;
	}
}
EXPORT_SYMBOL(cust_gpio_set_input);

#if defined(CGPIO_MISCDEV_SUPPORT) //Leo 20200824
static int cgpio_open(struct inode *inode, struct file *filp)
{
	FUNC_ENTRY
	
	return 0;
}

static int cgpio_close(struct inode *inode, struct file *filp)
{
	FUNC_ENTRY
	
	return 0;
}

static ssize_t cgpio_read(struct file *file,
			char __user *buf, size_t count, loff_t *ppos)
{
	FUNC_ENTRY
	
	return count;
}

static ssize_t cgpio_write(struct file *file, 
			const char __user *buf, size_t count, loff_t *ppos)
{
	#if defined(KU982020_CONFIG) //Leo 20200825
	#if 1
	int s_value = 1;
	FUNC_ENTRY

	if (1 == sscanf(buf,"%d",&s_value)) {
		pr_info(TAG"s_value:%d\n",s_value);
		cust_gpio_set_output(CUST_GPIO_RF24_RSV, !!s_value);
	}	
	#else
	int s_value = 1;
	FUNC_ENTRY

	copy_from_user(&s_value, buf, sizeof(s_value));
	pr_info(TAG"s_value:%d\n",s_value);
	cust_gpio_set_output(CUST_GPIO_RF24_RSV, !!s_value);
	#endif
	#endif
	
	return count;
}

static long
cgpio_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{

	int status = 0;
	int s_value = -1;
	int g_value = -1;
	void __user *argp = (void __user *)arg;

	FUNC_ENTRY
	
	switch (cmd) {
	#if defined(KU982020_CONFIG) //Leo 20200824
	case CGPIO_IOC_RF24_RSV_SET:
		
		pr_info(TAG"CGPIO_IOC_RF24_RSV_SET entry!\n");
		copy_from_user(&s_value, argp, sizeof(s_value));
		pr_info(TAG"s_value:%d \n",s_value);
		status = cust_gpio_set_output(CUST_GPIO_RF24_RSV, s_value);
		if (status < 0)
			pr_err(TAG"%s CGPIO_IOC_RF24_RSV_SET failed!\n",__func__); 
		break;
	case CGPIO_IOC_RF24_RSV_GET:
		pr_info(TAG"CGPIO_IOC_RF24_RSV_GET entry!\n");
		g_value = cust_gpio_get_value(CUST_GPIO_RF24_RSV);
		if (g_value < 0) {
			pr_err(TAG"%s CGPIO_IOC_RF24_RSV_GET failed!\n",__func__); 
		} else {
			if (copy_to_user(argp, &g_value, sizeof(g_value))){
				pr_err(TAG "copy_to_user failed\n");
				status = -EFAULT;
			}
		}
		pr_info(TAG"g_value:%d \n",g_value);
		break;
	#endif
	#if defined(Y140_CONFIG) //Leo 20200824
	case CGPIO_IOC_WD_CLK_SET:
		pr_info(TAG"CGPIO_IOC_WD_CLK_SET entry!\n");
		copy_from_user(&s_value, argp, sizeof(s_value));
		pr_info(TAG"s_value:%d \n",s_value);
		status = y140_feed_wd_clk(s_value);
		if (status < 0)
			pr_err(TAG"%s CGPIO_IOC_WD_CLK_SET failed!\n",__func__); 
		break;
	case CGPIO_IOC_WD_CLK_GET:
		pr_info(TAG"CGPIO_IOC_WD_CLK_GET entry!\n");
		g_value = cust_gpio_get_value(CUST_GPIO_WTD_CLK);
		if (g_value < 0) {
			pr_err(TAG"%s CGPIO_IOC_WD_CLK_GET failed!\n",__func__); 
		} else {
			if (copy_to_user(argp, &g_value, sizeof(g_value))){
				pr_err(TAG "copy_to_user failed\n");
				status = -EFAULT;
			}
		}
		pr_info(TAG"g_value:%d \n",g_value);
		break;
	#endif
	default:
		pr_err(TAG"%s %d cmd no found\n",__func__, (unsigned int)argp); 
		status = -EINVAL;
		break;
	}

	pr_info(TAG"s_value:%d, g_value:%d",s_value, g_value);
	
	return status;
}

#ifdef CONFIG_COMPAT
static long
cgpio_compat_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	FUNC_ENTRY
	
	return 0;
}
#endif

static const struct file_operations cgpio_fops = {
	.owner     = THIS_MODULE,
	.open      = cgpio_open,
	.read      = cgpio_read,
	.write     = cgpio_write,
	.release   = cgpio_close,
	.unlocked_ioctl = cgpio_ioctl,
	#ifdef CONFIG_COMPAT
	.compat_ioctl   = cgpio_compat_ioctl,
	#endif
};

struct miscdevice cgpio_device = {
	.name = "cgpio_device",
	.fops = &cgpio_fops,
	.minor = MISC_DYNAMIC_MINOR,
};
#endif

//debug part
static ssize_t cust_get_value_show(struct device* cd,
                      struct device_attribute *attr, char* buf)
{
	int i = 0, len = 0;

	len += snprintf(buf+len, PAGE_SIZE-len, "\r\n"); 
	for (i = 0; i < CUST_GPIO_MAX; i++) {
	if (cust_gpios[i].exist) {
		len += snprintf(buf+len, PAGE_SIZE-len, "name:%s index:%d value:%d\n",
				cust_gpios[i].name, i, gpio_get_value(cust_gpios[i].pin));
		}
	}	

	return len;
}

static ssize_t cust_set_value_store(struct device* cd,
                   struct device_attribute *attr,const char* buf, size_t len)
{
	unsigned int databuf[2];
	if (2 == sscanf(buf,"%d %d",&databuf[0], &databuf[1])) {
		if (cust_gpios[databuf[0]].exist) {
			pr_info("pin_index:%d value:%d", cust_gpios[databuf[0]].pin, databuf[1]);			
			gpio_direction_output(cust_gpios[databuf[0]].pin, databuf[1]);
		}
	}
	return len;
}

static DEVICE_ATTR(custgpio, 0664, cust_get_value_show, cust_set_value_store);

static struct attribute *custgpio_attrs[] = {
	&dev_attr_custgpio.attr,
	NULL,
};

static struct attribute_group custgpio_group = {
	.attrs = custgpio_attrs
};


#ifdef CONFIG_OF
static const struct of_device_id _cust_gpio_of_ids[] = {
	{.compatible = "gpio_cust",},
	{},
};
MODULE_DEVICE_TABLE(of, _cust_gpio_of_ids);
#endif

static int _cust_gpio_probe(struct platform_device *pdev)
{
	int ret;
	cust_gpio_init(pdev, cust_gpios, CUST_GPIO_MAX);
	ret = sysfs_create_group(&pdev->dev.kobj, &custgpio_group);
	if (ret < 0) {
		pr_err("[CUST][GPIO] unable to create custgpio attribute file\n");
		return ret;
	}

	#if defined(CGPIO_MISCDEV_SUPPORT) //Leo 20200824
	ret = misc_register(&cgpio_device);
	if (ret < 0) {
		pr_err(TAG"misc_register failed\n");
		return ret;
	}
	#endif

	jm_customer_init();

	return 0;
}

static int _cust_gpio_remove(struct platform_device *pdev)
{
	return 0;
}

static struct platform_driver _cust_gpio_driver = {
	.driver = {
		.name = CUST_GPIO_DEVICE,
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(_cust_gpio_of_ids),
	},
	.probe = _cust_gpio_probe,
	.remove = _cust_gpio_remove,
};
module_platform_driver(_cust_gpio_driver);

static int __init _cust_gpio_init(void)
{
	pr_info("CUST GPIO driver init\n");
	if (platform_driver_register(&_cust_gpio_driver) != 0) {
		pr_err("unable to register CUST GPIO driver.\n");
		return -1;
	}
	return 0;
}

/* should never be called */
static void __exit _cust_gpio_exit(void)
{
	pr_info("CUST GPIO driver exit\n");
	platform_driver_unregister(&_cust_gpio_driver);
}

module_init(_cust_gpio_init);
module_exit(_cust_gpio_exit);
