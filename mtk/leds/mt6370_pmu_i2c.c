/*
 *  Copyright (C) 2017 MediaTek Inc.
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

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/pm.h>
#include <linux/of_gpio.h>
#include <linux/pm_runtime.h>

#include "inc/mt6370_pmu.h"

static bool dbg_log_en; /* module param to enable/disable debug log */
module_param(dbg_log_en, bool, 0644);

static int mt6370_pmu_read_device(void *i2c, u32 addr, int len, void *dst)
{
	return i2c_smbus_read_i2c_block_data(i2c, addr, len, dst);
}

static int mt6370_pmu_write_device(void *i2c, u32 addr, int len,
				   const void *src)
{
	return i2c_smbus_write_i2c_block_data(i2c, addr, len, src);
}

static struct rt_regmap_fops mt6370_regmap_fops = {
	.read_device = mt6370_pmu_read_device,
	.write_device = mt6370_pmu_write_device,
};

int mt6370_pmu_reg_read(struct mt6370_pmu_chip *chip, u8 addr)
{
#ifdef CONFIG_RT_REGMAP
	struct rt_reg_data rrd = {0};
	int ret = 0;

	mt_dbg(chip->dev, "%s: reg %02x\n", __func__, addr);
	mutex_lock(&chip->io_lock);
	ret = rt_regmap_reg_read(chip->rd, &rrd, addr);
	mutex_unlock(&chip->io_lock);
	return (ret < 0 ? ret : rrd.rt_data.data_u32);
#else
	u8 data = 0;
	int ret = 0;

	mt_dbg(chip->dev, "%s: reg %02x\n", __func__, addr);
	mutex_lock(&chip->io_lock);
	ret = mt6370_pmu_read_device(chip->i2c, addr, 1, &data);
	mutex_unlock(&chip->io_lock);
	return (ret < 0 ? ret : data);
#endif /* #ifdef CONFIG_RT_REGMAP */
}
EXPORT_SYMBOL(mt6370_pmu_reg_read);

int mt6370_pmu_reg_write(struct mt6370_pmu_chip *chip, u8 addr, u8 data)
{
#ifdef CONFIG_RT_REGMAP
	struct rt_reg_data rrd = {0};
	int ret = 0;

	mt_dbg(chip->dev, "%s: reg %02x data %02x\n", __func__,
		addr, data);
	mutex_lock(&chip->io_lock);
	ret = rt_regmap_reg_write(chip->rd, &rrd, addr, data);
	mutex_unlock(&chip->io_lock);
	return ret;
#else
	int ret = 0;

	mt_dbg(chip->dev, "%s: reg %02x data %02x\n", __func__,
		addr, data);
	mutex_lock(&chip->io_lock);
	ret = mt6370_pmu_write_device(chip->i2c, addr, 1, &data);
	mutex_unlock(&chip->io_lock);
	return (ret < 0 ? ret : data);
#endif /* #ifdef CONFIG_RT_REGMAP */
}
EXPORT_SYMBOL(mt6370_pmu_reg_write);

int mt6370_pmu_reg_update_bits(struct mt6370_pmu_chip *chip, u8 addr,
			       u8 mask, u8 data)
{
#ifdef CONFIG_RT_REGMAP
	struct rt_reg_data rrd = {0};
	int ret = 0;

	mt_dbg(chip->dev, "%s: reg %02x data %02x\n", __func__,
		addr, data);
	mt_dbg(chip->dev, "%s: mask %02x\n", __func__, mask);
	mutex_lock(&chip->io_lock);
	ret = rt_regmap_update_bits(chip->rd, &rrd, addr, mask, data);
	mutex_unlock(&chip->io_lock);
	return ret;
#else
	u8 orig = 0;
	int ret = 0;

	mt_dbg(chip->dev, "%s: reg %02x data %02x\n", __func__,
		addr, data);
	mt_dbg(chip->dev, "%s: mask %02x\n", __func__, mask);
	mutex_lock(&chip->io_lock);
	ret = mt6370_pmu_read_device(chip->i2c, addr, 1, &orig);
	if (ret < 0)
		goto out_update_bits;
	orig &= ~mask;
	orig |= (data & mask);
	ret = mt6370_pmu_write_device(chip->i2c, addr, 1, &orig);
out_update_bits:
	mutex_unlock(&chip->io_lock);
	return ret;
#endif /* #ifdef CONFIG_RT_REGMAP */
}
EXPORT_SYMBOL(mt6370_pmu_reg_update_bits);

int mt6370_pmu_reg_block_read(struct mt6370_pmu_chip *chip, u8 addr,
			      int len, u8 *dest)
{
#ifdef CONFIG_RT_REGMAP
	int ret = 0;

	mt_dbg(chip->dev, "%s: reg %02x size %d\n", __func__,
		addr, len);
	mutex_lock(&chip->io_lock);
	ret = rt_regmap_block_read(chip->rd, addr, len, dest);
	mutex_unlock(&chip->io_lock);
	return ret;
#else
	int ret = 0;

	mt_dbg(chip->dev, "%s: reg %02x size %d\n", __func__,
		addr, len);
	mutex_lock(&chip->io_lock);
	ret = mt6370_pmu_read_device(chip->i2c, addr, len, dest);
	mutex_unlock(&chip->io_lock);
	return ret;
#endif /* #ifdef CONFIG_RT_REGMAP */
}
EXPORT_SYMBOL(mt6370_pmu_reg_block_read);

int mt6370_pmu_reg_block_write(struct mt6370_pmu_chip *chip, u8 addr,
			       int len, const u8 *src)
{
#ifdef CONFIG_RT_REGMAP
	int ret = 0;

	mt_dbg(chip->dev, "%s: reg %02x size %d\n", __func__, addr,
		len);
	mutex_lock(&chip->io_lock);
	ret = rt_regmap_block_write(chip->rd, addr, len, src);
	mutex_unlock(&chip->io_lock);
	return ret;
#else
	int ret = 0;

	mt_dbg(chip->dev, "%s: reg %02x size %d\n", __func__, addr,
		len);
	mutex_lock(&chip->io_lock);
	ret = mt6370_pmu_write_device(chip->i2c, addr, len, src);
	mutex_unlock(&chip->io_lock);
	return ret;
#endif /* #ifdef CONFIG_RT_REGMAP */
}
EXPORT_SYMBOL(mt6370_pmu_reg_block_write);

static int mt_parse_dt(struct device *dev,
		       struct mt6370_pmu_platform_data *pdata)
{
	struct device_node *np = dev->of_node;
	int ret = 0;

#if (!defined(CONFIG_MTK_GPIO) || defined(CONFIG_MTK_GPIOLIB_STAND))
	ret = of_get_named_gpio(np, "mt6370,intr_gpio", 0);
	if (ret < 0)
		goto out_parse_dt;
	pdata->intr_gpio = ret;
#else
	ret =  of_property_read_u32(np, "mt6370,intr_gpio_num",
					&pdata->intr_gpio);
	if (ret < 0)
		goto out_parse_dt;
#endif
	return 0;
out_parse_dt:
	return ret;
}

static inline void rt_config_of_node(struct device *dev)
{
	struct device_node *np = NULL;

	np = of_find_node_by_name(NULL, "mt6370_pmu_dts");
	if (np) {
		dev_err(dev, "find mt6370_pmu_dts node\n");
		dev->of_node = np;
	}
}

static inline int mt6370_pmu_chip_id_check(struct i2c_client *i2c)
{
	int ret = 0;

	ret = i2c_smbus_read_byte_data(i2c, MT6370_PMU_REG_DEVINFO);
	if (ret < 0)
		return ret;

	if ((ret & 0xF0) == 0x80 || (ret & 0xF0) == 0xE0 ||
		(ret & 0xF0) == 0xF0)
		return (ret & 0xff);
	return -ENODEV;
}

static int mt6370_pmu_suspend(struct device *dev)
{
	struct mt6370_pmu_chip *chip = dev_get_drvdata(dev);

	mt_dbg(chip->dev, "%s\n", __func__);
	mt6370_pmu_irq_suspend(chip);
	return 0;
}

static int mt6370_pmu_resume(struct device *dev)
{
	struct mt6370_pmu_chip *chip = dev_get_drvdata(dev);

	mt_dbg(dev, "%s\n", __func__);
	mt6370_pmu_irq_resume(chip);
	return 0;
}

static SIMPLE_DEV_PM_OPS(mt6370_pmu_pm_ops, mt6370_pmu_suspend,
	mt6370_pmu_resume);

#if defined(YK921_CONFIG)||defined(ET918_CONFIG)
#include <linux/delay.h>
struct i2c_client *mt6370_i2c_client = NULL;
#define FLED_CS1              0x02 // #define MT6370_FLED_CS_MASK0	0x02
#define FLED_CS2              0x01 // #define MT6370_FLED_CS_MASK1	0x01
#define FLED_CS1_2            FLED_CS1|FLED_CS2
#define FLED_400MA_CURRENT    0x1E
#define FLED_300MA_CURRENT    0x16

#if defined(SET_FLED_400MA)
#define FLED_SET_CURRENT      FLED_400MA_CURRENT
#else
#define FLED_SET_CURRENT      FLED_300MA_CURRENT //FLED_400MA_CURRENT
#endif
int mt6370_set_fled_enable(char enable,unsigned char leds)
{
	int ret = 0;
	u8 data = 0;

        leds &= FLED_CS1_2; //zwl 20181119
	pr_debug("mt6370_set_fled_enable enable=%d fleds=%d,\n",enable, leds);
	if (enable) {
	   /* read data */
	   //FLED1 current:
           if(leds|FLED_CS1){
	          ret = i2c_smbus_read_i2c_block_data(mt6370_i2c_client,MT6370_PMU_REG_FLED1TORCTRL, 1, &data);
	          if (ret < 0) {
		       printk("%s Line261: read i2c block fail\n", __func__);
		       return ret; //goto out;
	          }
	          udelay(40);
	   	  data |= FLED_SET_CURRENT;
	          ret = i2c_smbus_write_i2c_block_data(mt6370_i2c_client, MT6370_PMU_REG_FLED1TORCTRL, 1, &data);
	          if (ret < 0) {
		       printk("%s: Line271: write i2c block fail\n", __func__);
		       return ret; //goto out;
	          }
           }

	   //FLED2 current:
           if(leds|FLED_CS2){
	   	  ret = i2c_smbus_read_i2c_block_data(mt6370_i2c_client,MT6370_PMU_REG_FLED2TORCTRL, 1, &data);
	   	  if (ret < 0) {
		  printk("%s Line261: read i2c block fail\n", __func__);
		  return ret; //goto out;
	          }
	          udelay(40);
	          data |= FLED_SET_CURRENT;
	          ret = i2c_smbus_write_i2c_block_data(mt6370_i2c_client, MT6370_PMU_REG_FLED2TORCTRL, 1, &data);
	          if (ret < 0) {
		       printk("%s: Line271: write i2c block fail\n", __func__);
		       return ret; //goto out;
	          }
           }

	   //FLED1/2 Enable:
	   ret = i2c_smbus_read_i2c_block_data(mt6370_i2c_client,MT6370_PMU_REG_FLEDEN, 1, &data);
	   if (ret < 0) {
		printk("%s Line293: read i2c block fail\n", __func__);
		return ret; //goto out;
	   }
	   udelay(40);
           //data = 0xB;
	   data |= (0x08|leds);//zwl 20181119
	   ret = i2c_smbus_write_i2c_block_data(mt6370_i2c_client, MT6370_PMU_REG_FLEDEN, 1, &data);
	   if (ret < 0) {
		printk("%s: Line300: write i2c block fail\n", __func__);
		return ret; //goto out;
	   }
	   udelay(40);
	}
	else {
	   //FLED1/2 Enable:
	   ret = i2c_smbus_read_i2c_block_data(mt6370_i2c_client,MT6370_PMU_REG_FLEDEN, 1, &data);
	   if (ret < 0) {
		printk("%s Line309: read i2c block fail\n", __func__);
		return ret; //goto out;
	   }

	   udelay(40);
	   //data &= 0xF4;
           data &= ~(leds);           //zwl 20181119
           #if !defined(ET918_CONFIG) //when cs1/cs2 one for flash one for other
           if(!(data && FLED_CS1_2)){
               data &= ~(0x08);     
           }
           #endif
	   ret = i2c_smbus_write_i2c_block_data(mt6370_i2c_client, MT6370_PMU_REG_FLEDEN, 1, &data);
	   if (ret < 0) {
		printk("%s: Line316: write i2c block fail\n", __func__);
		return ret; //goto out;
	   }
	   udelay(40);
	}

	return ret;
}
#endif

#if defined(ET918_CONFIG)//zwl 20190419
#include <mt-plat/mtk_boot_common.h>
#include "inc/mt6370_pmu_rgbled.h"

#define DELAY_ON1     250
#define DELAY_ON      500
#define DELAY_OFF     1000

struct wakeup_source mt6370_rgb_suspend_lock;  //wake-lock for sleep control
static struct work_struct  mt6370_rgb_work;
static struct timer_list   mt6370_rgb_timer;
static struct workqueue_struct *mt6370_rgb_workqueue;
extern signed int battery_get_uisoc(void);
extern int mtk_chr_is_charger_exist(unsigned char *exist);

static int mt6370_i2c_update_bits(u8 addr,u8 mask, u8 data)
{
	u8 orig = 0;
	int ret = 0;

	printk("%s: reg %02x data %02x\n", __func__,
		addr, data);
	printk("%s: mask %02x\n", __func__, mask);
	ret = mt6370_pmu_read_device(mt6370_i2c_client, addr, 1, &orig);
	if (ret < 0) {
                printk("Func:%s i2c read error!\n",__func__);
		goto out_update_bits;
        }
	orig &= ~mask;
	orig |= (data ? mask : 0);
	printk("Func:%s register: %02x !\n",__func__,orig);
	ret = mt6370_pmu_write_device(mt6370_i2c_client, addr, 1, &orig);
	if (ret < 0)
	    printk("Func:%s i2c write error!\n",__func__);

out_update_bits:
        return ret;
}

#define ET_RED_LED             MT6370_PMU_LED1
#define ET_GREEN_LED           MT6370_PMU_LED2
#define ET_YELLOW_LED          MT6370_PMU_LED3
#define ISINK4_SFSTR_EN_MASK   0x01
#define ISINK3_SFSTR_EN_MASK   (ISINK4_SFSTR_EN_MASK << 1)
#define ISINK2_SFSTR_EN_MASK   (ISINK4_SFSTR_EN_MASK << 2)
#define ISINK1_SFSTR_EN_MASK   (ISINK4_SFSTR_EN_MASK << 3)
#define ISINK4_CHRIND_EN_MASK  (ISINK4_SFSTR_EN_MASK << 4)
#define ISINK3_DIM_EN_MASK     (ISINK4_SFSTR_EN_MASK << 5)
#define ISINK2_DIM_EN_MASK     (ISINK4_SFSTR_EN_MASK << 6)
#define ISINK1_DIM_EN_MASK     (ISINK4_SFSTR_EN_MASK << 7)
#define ISINK_DIM_CURRENT      0x02 //8ma [2:0](0-24) level += 4ma

static int mt6370_i2c_rgb_on(int leds, int status)
{
        unsigned char en_mask = 0, ret = 0;
        u8 orig = 0, reg_mask = 0x07, reg_addr = 0;

        printk("Func:%s Entry!\n",__func__);

	switch (leds) {
	case MT6370_PMU_LED1:
		reg_addr = MT6370_PMU_REG_RGB1ISINK;
		en_mask |= ISINK1_DIM_EN_MASK;
		break;
	case MT6370_PMU_LED2:
		reg_addr = MT6370_PMU_REG_RGB2ISINK;
		en_mask |= ISINK2_DIM_EN_MASK;
		break;
	case MT6370_PMU_LED3://yellow
		reg_addr = MT6370_PMU_REG_RGB3ISINK;
		en_mask |= ISINK3_DIM_EN_MASK;
		break;
	default:
	       printk("Func:%s param error!\n",__func__);
        }
	 ret = mt6370_pmu_read_device(mt6370_i2c_client, reg_addr, 1, &orig);
	 if (ret < 0) {
                printk("Func:%s i2c read error!\n",__func__);
		goto out_rgb_on;
         }

         orig &= ~reg_mask;
         orig |= (status ? ISINK_DIM_CURRENT : 0x00);
	 ret = mt6370_pmu_write_device(mt6370_i2c_client, reg_addr, 1, &orig);

         mt6370_i2c_update_bits(MT6370_PMU_REG_RGBEN, en_mask, !!status);
         if (ret < 0)
	    printk("Func:%s i2c write error!\n",__func__);

out_rgb_on:
         return 0;
}

static void et_rgb_blink(int leds, int delay_on, int delay_off)
{
        static int status = 0;
        int div = 0;
        if (status) {
                if (delay_on == DELAY_ON1){
                        div = 4;
                } else {
                        div = 2;
                }
        } else {
                div = 1;
        }

        if (delay_off == 0)
            status = 1;

        mt6370_i2c_rgb_on(leds, !!status);
        status = !status;
        mod_timer(&mt6370_rgb_timer, jiffies + HZ/div);
}

static void et_reg_on(int leds, int status)
{
        mt6370_i2c_rgb_on(leds, !!status);
}

static void set_rgb_status(signed int uisoc)
{
        unsigned char chr_exist = 0;

        if (uisoc > 100){
                uisoc = 100;
        } else if (uisoc < 0) {
                uisoc = 0;
        }

        mtk_chr_is_charger_exist(&chr_exist);
        if (chr_exist){
               if (uisoc == 100) {
                     et_reg_on(ET_RED_LED,0);
                     et_rgb_blink(ET_GREEN_LED, DELAY_ON, 0);
               } else if (uisoc >= 90) {
                     et_reg_on(ET_RED_LED,0);
                     et_rgb_blink(ET_GREEN_LED, DELAY_ON, DELAY_OFF);
               } else if (uisoc >= 15) {
                     et_reg_on(ET_GREEN_LED,0);
                     et_rgb_blink(ET_RED_LED, DELAY_ON, DELAY_OFF);
               } else {
                     et_reg_on(ET_GREEN_LED,0);
                     et_rgb_blink(ET_RED_LED, DELAY_ON1, DELAY_OFF);
               }
         } else {
                 mod_timer(&mt6370_rgb_timer, jiffies + 2*HZ);
         }
}

static void mt6370_rgb_work_func(struct work_struct *work)
{
        set_rgb_status(battery_get_uisoc());
}

static void mt6370_rgb_timer_func(unsigned long data)
{
        queue_work(mt6370_rgb_workqueue, &mt6370_rgb_work);
}

static void mt6370_rgb_power_off_charger(void)
{
        if (get_boot_mode() == KERNEL_POWER_OFF_CHARGING_BOOT || \
                  get_boot_mode() == LOW_POWER_OFF_CHARGING_BOOT) {
             unsigned char chr_exist = 0;

            INIT_WORK(&mt6370_rgb_work, mt6370_rgb_work_func);
            mt6370_rgb_workqueue = create_singlethread_workqueue("mt6370_rgb");
            if (!mt6370_rgb_workqueue)
                    printk("***error,Func:%s Can`t create workqueue!\n",__func__);

            setup_timer(&mt6370_rgb_timer, mt6370_rgb_timer_func, (unsigned long)0);
            add_timer(&mt6370_rgb_timer);
            mtk_chr_is_charger_exist(&chr_exist);
            mod_timer(&mt6370_rgb_timer, jiffies + 10*HZ);

            wakeup_source_init(&mt6370_rgb_suspend_lock, "mt6370_rgb_wakelock");
            __pm_stay_awake(&mt6370_rgb_suspend_lock);
        }

}
#endif

static int mt6370_pmu_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct mt6370_pmu_chip *chip;
	struct mt6370_pmu_platform_data *pdata = dev_get_platdata(&i2c->dev);
	bool use_dt = i2c->dev.of_node;
	uint8_t chip_id = 0;
	int ret = 0;

	ret = mt6370_pmu_chip_id_check(i2c);
	if (ret < 0)
		return ret;
	chip_id = ret;
	if (use_dt) {
		rt_config_of_node(&i2c->dev);
		pdata = devm_kzalloc(&i2c->dev, sizeof(*pdata), GFP_KERNEL);
		if (!pdata)
			return -ENOMEM;
		ret = mt_parse_dt(&i2c->dev, pdata);
		if (ret < 0) {
			dev_err(&i2c->dev, "error parse platform data\n");
			devm_kfree(&i2c->dev, pdata);
			return ret;
		}
		i2c->dev.platform_data = pdata;
	} else {
		if (!pdata)
			return -EINVAL;
	}
	chip = devm_kzalloc(&i2c->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;
	chip->i2c = i2c;
	chip->dev = &i2c->dev;
	chip->chip_rev = chip_id & 0x0f;
	chip->chip_vid = chip_id & 0xf0;
	mutex_init(&chip->io_lock);
	i2c_set_clientdata(i2c, chip);

	pm_runtime_set_active(&i2c->dev);
	ret = mt6370_pmu_regmap_register(chip, &mt6370_regmap_fops);
	if (ret < 0)
		goto out_regmap;
	ret = mt6370_pmu_irq_register(chip);
	if (ret < 0)
		goto out_irq;
	ret = mt6370_pmu_subdevs_register(chip);
	if (ret < 0)
		goto out_subdevs;
	pm_runtime_enable(&i2c->dev);

#if defined(YK921_CONFIG)||defined(ET918_CONFIG) //xen 20180726
	mt6370_i2c_client = i2c;
#endif

#if defined(ET918_CONFIG)//zwl 20190419
        mt6370_rgb_power_off_charger();
#endif

	dev_info(&i2c->dev, "%s successfully\n", __func__);
	return 0;
out_subdevs:
	mt6370_pmu_irq_unregister(chip);
out_irq:
	mt6370_pmu_regmap_unregister(chip);
out_regmap:
	pm_runtime_set_suspended(&i2c->dev);
	devm_kfree(&i2c->dev, chip);
	if (use_dt)
		devm_kfree(&i2c->dev, pdata);
	return ret;
}

static int mt6370_pmu_remove(struct i2c_client *i2c)
{
	struct mt6370_pmu_chip *chip = i2c_get_clientdata(i2c);

	pm_runtime_disable(&i2c->dev);
	mt6370_pmu_subdevs_unregister(chip);
	mt6370_pmu_irq_unregister(chip);
	mt6370_pmu_regmap_unregister(chip);
	pm_runtime_set_suspended(&i2c->dev);
	dev_info(chip->dev, "%s successfully\n", __func__);
	return 0;
}

static const struct i2c_device_id mt6370_pmu_id_table[] = {
	{"mt6370_pmu", 0},
	{}
};
MODULE_DEVICE_TABLE(i2c, mt6370_pmu_id_table);

static const struct of_device_id mt6370_pmu_ofid_table[] = {
	{.compatible = "mediatek,mt6370_pmu",},
	{.compatible = "mediatek,subpmic_pmu",},
	{},
};
MODULE_DEVICE_TABLE(of, mt6370_pmu_ofid_table);

static struct i2c_driver mt6370_pmu = {
	.driver = {
		.name = "mt6370_pmu",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(mt6370_pmu_ofid_table),
		.pm = &mt6370_pmu_pm_ops,
	},
	.probe = mt6370_pmu_probe,
	.remove = mt6370_pmu_remove,
	.id_table = mt6370_pmu_id_table,
};

module_i2c_driver(mt6370_pmu);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MediaTek MT6370 PMU");
MODULE_VERSION("1.0.2_G");
