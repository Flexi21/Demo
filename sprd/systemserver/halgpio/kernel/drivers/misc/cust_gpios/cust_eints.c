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
#include <linux/irq.h>
#include <linux/interrupt.h>

#include "cust_gpios.h"

struct cust_eint_s {
	struct cust_gpio_attr *gpio;
	irq_handler_t		cust_handler;
	unsigned long flags;
};

int cust_eint_regiter(struct cust_gpio_attr *gpio, irq_handler_t cust_handler, unsigned long flags)
{
	int ret;

	ret = gpio_direction_input(gpio->pin);
	if (ret < 0) {
		pr_err("cust: func%s gpio_direction_input IRQ failed\n", __func__);
		return -EINVAL;
	}

	gpio->eint_num = gpio_to_irq(gpio->pin);
	if (gpio->eint_num < 0) {
		pr_err("cust: func:%s error, irq_num:%d !\n",__func__,gpio->eint_num);
		return -EINVAL;
	}
	
	ret = request_irq(gpio->eint_num, cust_handler, flags|IRQF_NO_SUSPEND, gpio->name, NULL);
	if (ret) {
		pr_err("cust: func:%s request irq error,ret :%d!\n",__func__, ret);
		return -EINVAL;
	}

	pr_info("cust: func:%s register End!\n",__func__);
	return 0;
}  
