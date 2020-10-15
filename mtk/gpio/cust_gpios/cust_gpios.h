#include <linux/of_irq.h>
#include <linux/module.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include "cust_gpio_config.h"

#define VALUE_ON	1
#define VALUE_OFF	0


#if defined(CGPIO_MISCDEV_SUPPORT) //Leo 20200824
#define CGPIO_IOC_MAGIC                   'c'
#define  CGPIO_IOC_RLED_SET              _IOW(CGPIO_IOC_MAGIC, 1, int)
#define  CGPIO_IOC_RLED_GET              _IOW(CGPIO_IOC_MAGIC, 2, int)
#define  CGPIO_IOC_GLED_SET              _IOW(CGPIO_IOC_MAGIC, 3, int)
#define  CGPIO_IOC_GLED_GET              _IOW(CGPIO_IOC_MAGIC, 4, int)
#define  CGPIO_IOC_BLED_SET              _IOW(CGPIO_IOC_MAGIC, 5, int)
#define  CGPIO_IOC_BLED_GET              _IOW(CGPIO_IOC_MAGIC, 6, int)
#define  CGPIO_IOC_RF24_RSV_SET          _IOW(CGPIO_IOC_MAGIC, 7, int)
#define  CGPIO_IOC_RF24_RSV_GET          _IOW(CGPIO_IOC_MAGIC, 8, int)
#define  CGPIO_IOC_WD_CLK_SET            _IOW(CGPIO_IOC_MAGIC, 9, int)
#define  CGPIO_IOC_WD_CLK_GET            _IOW(CGPIO_IOC_MAGIC, 10, int)
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
#if defined(VL01C_CONFIG) //Leo 20200316
	CUST_GPIO_TRX_EN,	
	CUST_GPIO_ADC_SW,
	CUST_GPIO_RS485_DATA,
	CUST_GPIO_LDO_5V,
#elif defined(P340_CONFIG)
	CUST_GPIO_IRCUT,
	CUST_GPIO_MICSW,
	CUST_GPIO_OLED,
	CUST_GPIO_FM,
	CUST_GPIO_RF24_EN,
	CUST_GPIO_RF24_RST,
	CUST_GPIO_RF24_RSV,
	CUST_GPIO_RF24_LVD,
#elif defined(KU982020_CONFIG)//Leo 20200730
	CUST_GPIO_RF24_EN,
	CUST_GPIO_RF24_RST,
	CUST_GPIO_RF24_RSV,
	CUST_GPIO_RF24_LVD,
#elif defined(Y140_CONFIG)//Leo 20200928
	CUST_GPIO_WTD_CLK,
#endif
	CUST_GPIO_MAX
};

extern int cust_gpio_set_value(enum cust_gpio_type type,int value);
extern int cust_gpio_get_value(enum cust_gpio_type type);
extern struct input_dev *get_cust_gpio_dev(void);
int jm_customer_init(void);
extern struct cust_gpio_attr *cust_get_gpio(enum cust_gpio_type type);
extern int cust_eint_regiter(struct cust_gpio_attr *gpio, irq_handler_t handler, unsigned long flags);

#if defined(Y140_CONFIG) //Leo 20200930
extern int y140_feed_wd_clk(int val);
#endif
