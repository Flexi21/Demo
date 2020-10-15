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
#include <linux/input.h>   
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/delay.h>

#include "cust_gpios.h"

#if defined(CUST_GPIO_KPD_SUPPORT)//Leo 20191229
struct input_dev *cust_gpio_kpd_dev;
#endif

extern int cust_gpio_set_output(enum cust_gpio_type type,int value);
extern int cust_gpio_set_input(enum cust_gpio_type type);
extern int cust_gpio_set_value(enum cust_gpio_type type,int value);
extern int cust_gpio_get_value(enum cust_gpio_type type);

#if defined(JM_RF24_SUPPORT)&&defined(CUST_GPIO_KPD_SUPPORT)//Leo 20191229
#define JM_RF24_RSV_KEY			KEY_F7
struct cust_gpio_attr *jm_rf24_gpio;
static struct delayed_work jm_rf24_work;

static void jm_rf24_rsv_work_callback(struct work_struct *work)
{	
	static int flag = 1;
	pr_info("jm: func:%s %s Entry!\n",__func__, flag ? "down": "up");

	if (!!flag) {
		input_report_key(cust_gpio_kpd_dev, JM_RF24_RSV_KEY, 0);
		input_sync(cust_gpio_kpd_dev);
		irq_set_irq_type(jm_rf24_gpio->eint_num, IRQF_TRIGGER_LOW);
	} else {
		input_report_key(cust_gpio_kpd_dev, JM_RF24_RSV_KEY, 1);
		input_sync(cust_gpio_kpd_dev);
		irq_set_irq_type(jm_rf24_gpio->eint_num, IRQF_TRIGGER_HIGH);
	}

	flag = !flag;

	enable_irq(jm_rf24_gpio->eint_num);
}

static irqreturn_t jm_rf24_rsv_irq_callback(int irq, void *dev_id)               
{
	disable_irq_nosync(irq);
	schedule_delayed_work(&jm_rf24_work, msecs_to_jiffies(0));

	return IRQ_HANDLED;
} 

static int jm_rf24_init(void)
{
	jm_rf24_gpio = cust_get_gpio(CUST_GPIO_RF24_RSV);
	INIT_DELAYED_WORK(&jm_rf24_work, jm_rf24_rsv_work_callback);
	cust_eint_regiter(jm_rf24_gpio, jm_rf24_rsv_irq_callback, IRQF_TRIGGER_LOW);

	return 0;
}
#endif

#if defined(JM_FM_ANT_SUPPORT) //leo 20191225
int jm_fm_ant_en(int en)
{
	return cust_gpio_set_output(CUST_GPIO_FM, !!en);
}
EXPORT_SYMBOL(jm_fm_ant_en);
#endif

#if defined(P340_CONFIG) //Leo 20200424
static void jm_rf24_rst_init(void)
{
	cust_gpio_set_output(CUST_GPIO_RF24_RST, VALUE_OFF);
	mdelay(20);
	cust_gpio_set_output(CUST_GPIO_RF24_RST, VALUE_ON);
}

static void jm_p340_cust_init(void)
{
	jm_rf24_rst_init();
}
#endif

#if defined(KU982020_CONFIG) //Leo 20200730
static void ku982020_rf24_init(void)
{
	cust_gpio_set_output(CUST_GPIO_RF24_EN, VALUE_ON);
	cust_gpio_set_output(CUST_GPIO_RF24_RST, VALUE_OFF);
	mdelay(20);
	cust_gpio_set_output(CUST_GPIO_RF24_RST, VALUE_ON);
	
	//added by Leo for single board int, sleep high, activity low
	cust_gpio_set_output(CUST_GPIO_RF24_RSV, VALUE_ON);
}

static void ku982020_cust_init(void)
{
	ku982020_rf24_init();
}
#endif

#if defined(Y140_CONFIG) //Leo 20200930
static void jm_y140_cust_init(void)
{
	pr_info("%s %d Entry!\n",__func__,__LINE__);
	cust_gpio_set_output(CUST_GPIO_WTD_CLK, VALUE_OFF);
}

int y140_feed_wd_clk(int val)
{
	int ret;
	pr_info("%s %d Entry!\n",__func__,__LINE__);

	if (val)
		ret = cust_gpio_set_output(CUST_GPIO_WTD_CLK, VALUE_ON);
	else 
		ret = cust_gpio_set_output(CUST_GPIO_WTD_CLK, VALUE_OFF);

	return ret;
}
#endif

#if defined(CUST_GPIO_KPD_SUPPORT)//Leo 20191229
static void cust_gpio_kpd_dev_register(void)
{               
	int ret;          
                   
	cust_gpio_kpd_dev = input_allocate_device();	
	if (!cust_gpio_kpd_dev)  	 	 	
		return; 

	cust_gpio_kpd_dev->name = "cust_gpio_kp";              
	set_bit(EV_KEY, cust_gpio_kpd_dev->evbit);	 
	
	#if defined(JM_RF24_SUPPORT) //Leo 20191229			
	set_bit(JM_RF24_RSV_KEY, cust_gpio_kpd_dev->keybit);	
	#endif 

	set_bit(KEY_F1, cust_gpio_kpd_dev->keybit);	//FOR DEFAULT

	ret = input_register_device(cust_gpio_kpd_dev);  	 
	if (ret) {
		pr_err("cust: func:%s input_register_device err!\n",__func__);   	 	 	    
        input_free_device(cust_gpio_kpd_dev);  	               
	}
}

struct input_dev *get_cust_gpio_dev(void)
{
	return cust_gpio_kpd_dev;
}
#endif

int jm_customer_init(void)
{
	pr_info("jm: func:%s Entry!\n",__func__);

	#if defined(CUST_GPIO_KPD_SUPPORT) 
	cust_gpio_kpd_dev_register();
	#endif	

	#if defined(JM_RF24_SUPPORT) //Leo 20191229
	jm_rf24_init();
	#endif
	
	#if defined(P340_CONFIG) //Leo 20200424
	jm_p340_cust_init();
	#endif

	#if defined(KU982020_CONFIG) //Leo 20200730
	ku982020_cust_init();
	#endif
	
	#if defined(Y140_CONFIG) //Leo 20200930
	jm_y140_cust_init();
	#endif

	return 0;
}
