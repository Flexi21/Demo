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

#include "cust_gpios.h"

#define CUST_GPIO_DEVICE	"cust_gpio"

struct cust_gpio_attr cust_gpios[CUST_GPIO_MAX] = {
       [CUST_GPIO_RLED]       =  {"gpio_rled_ctl"},
       [CUST_GPIO_GLED]       =  {"gpio_gled_ctl"},
       [CUST_GPIO_BLED]       =  {"gpio_bled_ctl"},
       [CUST_GPIO_IRCUT]      =  {"gpio_ircut_ctl"},
       [CUST_GPIO_MICSW]      =  {"gpio_micsw_ctl"},
       [CUST_GPIO_OLED]       =  {"gpio_oled_rst"},
       [CUST_GPIO_FM]         =  {"gpio_fm_ant"},
       [CUST_GPIO_RF24_EN]    =  {"gpio_rf24_en"},
       [CUST_GPIO_RF24_RST]   =  {"gpio_rf24_rst"},
       [CUST_GPIO_RF24_RSV]   =  {"gpio_rf24_rsv"},
       [CUST_GPIO_RF24_LVD]   =  {"gpio_rf24_lvd"},
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

#if defined(CUST_GPIO_HAL_SUPPORT) //Leo 20200601
static int halgpio_open(struct inode *inode, struct file *file)
{
	pr_info("[CUST][GPIO] :%s Entry!",__func__);

	return 0;
}

static long hal_gpio_ioctl(struct file *file , unsigned int cmd , unsigned long arg)
{
	//int ret = 0;
	//int temp;
	//int param[2] = {0};

	pr_info("[CUST][GPIO] :%s cmd:0x%x Entry!",__func__,cmd);

	switch (cmd) {
	case HAL_GPIO_READ:
		pr_info("[CUST][GPIO] %s hal gpio read\n",__func__);
		//ret = copy_from_user(param, (void __user *)arg, sizeof(param)/sizeof(unsigned int));
		//if (ret < 0)
			//pr_err("[CUST][GPIO] %s hal gpio read get param failed\n",__func__);
		//hal_get_gpio();
		//copy_to_user((void __user *)arg, );
	break;
	case HAL_GPIO_WRITE:
		pr_info("[CUST][GPIO] %s hal gpio write!\n",__func__);
	break;
	
	default:
		pr_err("[CUST][GPIO] %s cmd no found!\n",__func__);
	break;
	}

	return 0;
}

struct file_operations hal_gpio_fops = {
	.owner    = THIS_MODULE,
	.open     = halgpio_open,
	.unlocked_ioctl = hal_gpio_ioctl,
};

static struct miscdevice halgpio_miscdev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "halgpio",
	.fops = &hal_gpio_fops,
};
#endif

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
	
	#if defined(CUST_GPIO_HAL_SUPPORT) //Leo 20200601
	ret = misc_register(&halgpio_miscdev);
	if (ret)
		pr_err("[CUST][GPIO] halgpio_miscdev register failed!\n");
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
