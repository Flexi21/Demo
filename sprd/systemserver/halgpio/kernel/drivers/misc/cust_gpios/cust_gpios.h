#include <linux/of_irq.h>
#include <linux/module.h>
#include <linux/irq.h>
#include <linux/interrupt.h>


#define CUST_GPIO_HAL_SUPPORT
#define VALUE_ON	1
#define VALUE_OFF	0
#if defined(CUST_GPIO_HAL_SUPPORT) //Leo 20200601
#define CUST_GPIO_MAGIC		'c'
#define HAL_GPIO_READ		_IOWR(CUST_GPIO_MAGIC, 0, int)
#define HAL_GPIO_WRITE		_IOW(CUST_GPIO_MAGIC, 1, int)
#endif


struct cust_gpio_attr {
	const char *name;
	int pin;
	bool exist;
	unsigned int eint_num;
};

enum cust_gpio_type {
	CUST_GPIO_RLED = 0,
	CUST_GPIO_GLED,
	CUST_GPIO_BLED,
	CUST_GPIO_IRCUT,
	CUST_GPIO_MICSW,
	CUST_GPIO_OLED,
	CUST_GPIO_FM,
	CUST_GPIO_RF24_EN,
	CUST_GPIO_RF24_RST,
	CUST_GPIO_RF24_RSV,
	CUST_GPIO_RF24_LVD,
	CUST_GPIO_MAX
};

extern int cust_gpio_set_value(enum cust_gpio_type type,int value);
extern int cust_gpio_get_value(enum cust_gpio_type type);
extern struct input_dev *get_cust_gpio_dev(void);
int jm_customer_init(void);
extern struct cust_gpio_attr *cust_get_gpio(enum cust_gpio_type type);
extern int cust_eint_regiter(struct cust_gpio_attr *gpio, irq_handler_t handler, unsigned long flags);
