#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/ioport.h>
#include <linux/errno.h>
#include <linux/spi/spi.h>
#include <linux/workqueue.h>
#include <linux/dma-mapping.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/irqreturn.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/spinlock.h>
#include <linux/sched.h>
//#include <linux/wakelock.h>
#include <linux/kthread.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/spi/spidev.h>
#include <linux/semaphore.h>
#include <linux/poll.h>
#include <linux/fcntl.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/slab.h>
//#include <linux/rtpm_prio.h>
#include <linux/wait.h>
#include <linux/signal.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <DpDataType.h>
#ifndef CONFIG_SPI_MT65XX
#include "mt_spi.h"
#endif
#include "spi_kernel.h"
#ifdef CONFIG_OF
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#endif
#include "ddp_info.h"



#ifdef CONFIG_SPI_MT65XX
u32 gf_spi_speed = 1*1000000;
#endif
static struct of_device_id silead_of_match[] = {
	{ .compatible = "mediatek,spi_lcm",},
	{}
};


static const struct dev_pm_ops lcm_pm = {
    .suspend = lcm_suspend,
    .resume = lcm_resume
};
static struct spi_driver lcm_driver = {
	.driver = {
		.name	= LCM_SPI_NAME,
		.bus	= &spi_bus_type,
		.owner	= THIS_MODULE,
#ifdef CONFIG_PM
       	 .pm = &lcm_pm,
#endif
		.of_match_table = silead_of_match,
	},
#ifndef CONFIG_SPI_MT65XX
	.suspend = lcm_suspend,
	.resume  = lcm_resume,
#endif

	.probe	 = lcm_probe,
};

#ifndef CONFIG_SPI_MT65XX
static struct spi_board_info spi_board_info[] __initdata = {
	[0] = {
		.modalias= LCM_SPI_NAME,
		.bus_num = 2,
		.chip_select=0,
		.mode = SPI_MODE_0,
		.max_speed_hz = LCM_SPI_CLOCK_SPEED,
	},
};
#endif



int spilcm_parse_dts(struct spi_data *spi_data)
{
	struct device_node *node = NULL;
	struct platform_device *pdev = NULL;

	node = of_find_compatible_node(NULL, NULL, "mediatek,spilcm");
	if (IS_ERR(node)) {
		SPI_DBG("spilcm node is null\n");
		return PTR_ERR(node);
	}
	
	pdev = of_find_device_by_node(node);
	if (IS_ERR(pdev)) {
		SPI_DBG("platform device is null\n");
		return PTR_ERR(pdev);
	}

	spi_data->pinctrl = devm_pinctrl_get(&pdev->dev);
	if (IS_ERR(spi_data->pinctrl)) {
		SPI_DBG("devm_pinctrl_get error\n");
		return  PTR_ERR(spi_data->pinctrl);
	}

	/* cs¡¢clk¡¢miso¡¢mosi¡¢int¡¢rst */

	
	spi_data->spilcm_spi2_mi_as_spi2_mi = pinctrl_lookup_state(spi_data->pinctrl, "spilcm_spi2_mi_as_spi2_mi");
	if (IS_ERR(spi_data->spilcm_spi2_mi_as_spi2_mi)) {
		SPI_DBG("Cannot find spilcm_spi2_mi_as_spi2_mi\n");
		return PTR_ERR(spi_data->spilcm_spi2_mi_as_spi2_mi);
	}

	spi_data->spilcm_spi2_mi_as_gpio_high = pinctrl_lookup_state(spi_data->pinctrl, "spilcm_spi2_mi_as_gpio_high");
	if (IS_ERR(spi_data->spilcm_spi2_mi_as_gpio_high)) {
		SPI_DBG("Cannot find spilcm_spi2_mi_as_gpio_high\n");
		return PTR_ERR(spi_data->spilcm_spi2_mi_as_gpio_high);
	}

	spi_data->spilcm_spi2_mi_as_gpio_low = pinctrl_lookup_state(spi_data->pinctrl, "spilcm_spi2_mi_as_gpio_low");
	if (IS_ERR(spi_data->spilcm_spi2_mi_as_gpio_low)) {
		SPI_DBG("Cannot find spilcm_spi2_mi_as_gpio_low\n");
		return PTR_ERR(spi_data->spilcm_spi2_mi_as_gpio_low);
	}


	spi_data->spilcm_spi2_mo_as_spi2_mo = pinctrl_lookup_state(spi_data->pinctrl, "spilcm_spi2_mo_as_spi2_mo");
	if (IS_ERR(spi_data->spilcm_spi2_mo_as_spi2_mo)) {
		SPI_DBG("Cannot find spilcm_spi2_mo_as_spi2_mo\n");
		return PTR_ERR(spi_data->spilcm_spi2_mo_as_spi2_mo);
	}

	spi_data->spilcm_spi2_mo_as_gpio_high = pinctrl_lookup_state(spi_data->pinctrl, "spilcm_spi2_mo_as_gpio_high");
	if (IS_ERR(spi_data->spilcm_spi2_mo_as_gpio_high)) {
		SPI_DBG("Cannot find spilcm_spi2_mo_as_gpio_high\n");
		return PTR_ERR(spi_data->spilcm_spi2_mo_as_gpio_high);
	}

	spi_data->spilcm_spi2_mo_as_gpio_low = pinctrl_lookup_state(spi_data->pinctrl, "spilcm_spi2_mo_as_gpio_low");
	if (IS_ERR(spi_data->spilcm_spi2_mo_as_gpio_low)) {
		SPI_DBG("Cannot find spilcm_spi2_mo_as_gpio_low\n");
		return PTR_ERR(spi_data->spilcm_spi2_mo_as_gpio_low);
	}


	spi_data->spilcm_spi2_clk_as_spi2_clk = pinctrl_lookup_state(spi_data->pinctrl, "spilcm_spi2_clk_as_spi2_clk");
	if (IS_ERR(spi_data->spilcm_spi2_clk_as_spi2_clk)) {
		SPI_DBG("Cannot find spilcm_spi2_clk_as_spi2_clk\n");
		return PTR_ERR(spi_data->spilcm_spi2_clk_as_spi2_clk);
	}

	spi_data->spilcm_spi2_clk_as_gpio_high = pinctrl_lookup_state(spi_data->pinctrl, "spilcm_spi2_clk_as_gpio_high");
	if (IS_ERR(spi_data->spilcm_spi2_clk_as_gpio_high)) {
		SPI_DBG("Cannot find spilcm_spi2_clk_as_gpio_high\n");
		return PTR_ERR(spi_data->spilcm_spi2_clk_as_gpio_high);
	}

	spi_data->spilcm_spi2_clk_as_gpio_low = pinctrl_lookup_state(spi_data->pinctrl, "spilcm_spi2_clk_as_gpio_low");
	if (IS_ERR(spi_data->spilcm_spi2_clk_as_gpio_low)) {
		SPI_DBG("Cannot find spilcm_spi2_clk_as_gpio_low\n");
		return PTR_ERR(spi_data->spilcm_spi2_clk_as_gpio_low);
      }

	spi_data->spilcm_spi2_cs_as_spi2_cs = pinctrl_lookup_state(spi_data->pinctrl, "spilcm_spi2_cs_as_spi2_cs");
	if (IS_ERR(spi_data->spilcm_spi2_cs_as_spi2_cs)) {
		SPI_DBG("Cannot find spilcm_spi2_cs_as_spi2_cs\n");
		return PTR_ERR(spi_data->spilcm_spi2_cs_as_spi2_cs);
	}

	spi_data->spilcm_spi2_cs_as_gpio_high = pinctrl_lookup_state(spi_data->pinctrl, "spilcm_spi2_cs_as_gpio_high");
	if (IS_ERR(spi_data->spilcm_spi2_cs_as_gpio_high)) {
		SPI_DBG("Cannot find spilcm_spi2_cs_as_gpio_high\n");
		return PTR_ERR(spi_data->spilcm_spi2_cs_as_gpio_high);
	}

	spi_data->spilcm_spi2_cs_as_gpio_low = pinctrl_lookup_state(spi_data->pinctrl, "spilcm_spi2_cs_as_gpio_low");
	if (IS_ERR(spi_data->spilcm_spi2_cs_as_gpio_low)) {
		SPI_DBG("Cannot find spilcm_spi2_cs_as_gpio_low\n");
		return PTR_ERR(spi_data->spilcm_spi2_cs_as_gpio_low);
	}

		
	

	
	SPI_DBG("get pinctrl success\n");
	return 0;
}
// Configure IO to make it work in SPI mode

static void set_pin_mode(int mode)
{
	int ret = -1;
   FUNC_ENTRY();
   

	if(mode==SPI_PIN_MODE)
	{

		ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_cs_as_spi2_cs);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_cs,error,ret = %d\n",ret);
		}


		ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_clk_as_spi2_clk);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_clk,error,ret = %d\n",ret);
		}

	      ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_mo_as_spi2_mo);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_mo,error,ret = %d\n",ret);
		}
	}
	else
	{	
	

		ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_cs_as_gpio_low);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_cs_as_gpio_low,error,ret = %d\n",ret);
		}


		ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_clk_as_gpio_low);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_clk_as_gpio,error,ret = %d\n",ret);
		}

	      ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_mo_as_gpio_low);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_mo_as_gpio,error,ret = %d\n",ret);
		}
	}
	
	
		ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_mi_as_gpio_low);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_mi_as_gpio,error,ret = %d\n",ret);
		}
	
  FUNC_EXIT();
}


// Select SPI work mode
static int set_spi_mode(int mode)
{

#ifndef CONFIG_SPI_MT65XX
	struct mt_chip_conf* spi_par;
	FUNC_ENTRY();
	spi_par = &spi_conf;
	if (!spi_par)
	{
		return -1;
	}
	if (SPI_DMA_MODE == mode)
	{
		if (spi_par-> com_mod != DMA_TRANSFER)
		{
			spi_par-> com_mod = DMA_TRANSFER;
		}

		packet_size=SPI_DMA_BATYE_PER_TIMES;
	}
	else
	{
		if (spi_par-> com_mod != FIFO_TRANSFER)
		{
			spi_par-> com_mod = FIFO_TRANSFER;
		}

		packet_size=SPI_FIFO_BATYE_PER_TIMES;
	}

	spi_setup(g_lcm->spi);
	FUNC_EXIT();
	return 0;
#else
    FUNC_ENTRY();
	
	if (SPI_DMA_MODE == mode)
	{
 		gf_spi_speed=26*1000000; //24*1000000; //16*1000000; //10*1000000;
		packet_size= SPI_DMA_BATYE_PER_TIMES;
	}
	else
	{	
 		gf_spi_speed=4*1000000; //1*1000000;
		packet_size=SPI_FIFO_BATYE_PER_TIMES;
	}


	FUNC_EXIT();
	return 0;

#endif	
}

// SPI GPIO mode


static void lcm_gpio_send(u8 data)
{
    unsigned int i;
    int ret = -1;


	ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_clk_as_gpio_low);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_clk_as_gpio,error,ret = %d\n",ret);
		}
	for (i = 0; i <8; i++)
	{
		if (data & (0x80)) {
		
		ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_mo_as_gpio_high);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_mo_as_gpio,error,ret = %d\n",ret);
		}
		} else {
			
		ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_mo_as_gpio_low);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_mo_as_gpio,error,ret = %d\n",ret);
		}
		}
	
		ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_clk_as_gpio_low);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_clk_as_gpio,error,ret = %d\n",ret);
		}
		ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_clk_as_gpio_high);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_clk_as_gpio,error,ret = %d\n",ret);
		}
		data <<= 1;
	}
}




// SPI DMA AND FIFO mode
static int lcm_spi_send(u8 *tx,size_t spilen)
{
    int ret=0;
	struct spi_message m;
    struct spi_transfer t = {
		.cs_change = 0,
		.delay_usecs = 0,
		.speed_hz =gf_spi_speed,
		.tx_buf = tx,
		.len = spilen,
		.tx_dma = 1,
		.rx_dma = 1,
		.bits_per_word = 0,
	};
	
	FUNC_ENTRY();

    spi_message_init(&m);
    spi_message_add_tail(&t, &m);
    ret= spi_sync(g_lcm->spi,&m);
	
	SPI_DBG("status= %d,len=%d\n",ret,spilen);
	
    FUNC_EXIT();
	
    return ret;   
}

static void SET_SEND_TYPE(u8 level) //zxs 20180203
{

    int ret = -1;


#if defined(SPI_THREE_CONFIG)//zlh add 20180825
	   if(level != 0){
			ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_mo_as_gpio_high);
			if(ret < 0){
			SPI_DBG("pinctrl_select_state,spi_mo_as_gpio,error,ret = %d\n",ret);
			}				
		}else{
			ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_mo_as_gpio_low);
			if(ret < 0){
			SPI_DBG("pinctrl_select_state,spi_mo_as_gpio,error,ret = %d\n",ret);
			}
		}
		
	  	ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_clk_as_gpio_low);
		if(ret < 0){
			SPI_DBG("pinctrl_select_state,spi_clk_as_gpio,error,ret = %d\n",ret);
		}
		ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_clk_as_gpio_high);
		if(ret < 0){
			SPI_DBG("pinctrl_select_state,spi_clk_as_gpio,error,ret = %d\n",ret);
		}
#else
	if(level != 0){
		ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_mi_as_gpio_high);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_mi_as_gpio,error,ret = %d\n",ret);
		}
				
	}else{
		ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_mi_as_gpio_low);
		if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_mi_as_gpio,error,ret = %d\n",ret);
		}
	}
#endif
	
	

}
void print_framebuf(size_t len, unsigned char *src_addr);
void lcm_spi_interface(unsigned char *sbuf, size_t spilen, unsigned char mode)
{
	int i;
	size_t times = 0;
	size_t left = 0;
       int ret = -1;
	FUNC_ENTRY();	
	switch(mode)
	{
		case WRITE_CMD:
			SPI_DBG("WRITE_CMD\n");			
			if(g_lcm->mode_flag!=GPIO_PIN_MODE)
			{
				set_pin_mode(GPIO_PIN_MODE);
				g_lcm->mode_flag=GPIO_PIN_MODE;
			}
			ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_cs_as_gpio_low);
			if(ret < 0){
			SPI_DBG("pinctrl_select_state,spi_cs_as_gpio_low,error,ret = %d\n",ret);
			}

			for(i=0;i<spilen;i++)
			{
				SET_SEND_TYPE(GPIO_OUT_ZERO);
				lcm_gpio_send(sbuf[i]);
				SPI_DBG("cmd<0x%x>\n",sbuf[i]);
			}
			ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_cs_as_gpio_high);
			if(ret < 0){
			SPI_DBG("pinctrl_select_state,spi_cs_as_gpio_low,error,ret = %d\n",ret);
			}
			break;
		case WRITE_DATA:
			SPI_DBG("WRITE_DATA\n");
			if(spilen<32)
			{
				if(g_lcm->mode_flag!=GPIO_PIN_MODE)
				{
					SPI_DBG("GPIO MODE\n");
					set_pin_mode(GPIO_PIN_MODE);
					g_lcm->mode_flag=GPIO_PIN_MODE;
				}
				ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_cs_as_gpio_low);
				if(ret < 0){
				SPI_DBG("pinctrl_select_state,spi_cs_as_gpio_low,error,ret = %d\n",ret);
				}
				for(i=0;i<spilen;i++)
				{
					SET_SEND_TYPE(GPIO_OUT_ONE);
					lcm_gpio_send(sbuf[i]);
					SPI_DBG("data<0x%x>\n",sbuf[i]);
				}
				ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_cs_as_gpio_high);
				if(ret < 0){
				SPI_DBG("pinctrl_select_state,spi_cs_as_gpio_low,error,ret = %d\n",ret);
				}
			}
			else 
			{
				if(g_lcm->mode_flag!=SPI_PIN_MODE)
				{
					SPI_DBG("SPI MODE\n");
					set_pin_mode(SPI_PIN_MODE);
					g_lcm->mode_flag=SPI_PIN_MODE;
				}
				
				if(spilen<1024)
				{
					SPI_DBG("FIFO MODE\n");
					set_spi_mode(SPI_FIFO_MODE);
				}
				else
				{
					SPI_DBG("DMA MODE\n");
					set_spi_mode(SPI_DMA_MODE);
				}	
				 				
				SET_SEND_TYPE(GPIO_OUT_ONE);
				
				SPI_DBG("packet_size=%d\n",packet_size);
				
				times=spilen/packet_size;
				
				for(i=0; i<times; i++)
				{
					lcm_spi_send(&sbuf[i*packet_size], packet_size);
				}

				if(spilen % packet_size != 0)
				{
					left = spilen - times*packet_size;
					lcm_spi_send(&sbuf[times*packet_size], left);
				} 
			}
			break;
		default:
			SPI_DBG("DELAY_TIME!\n"); 
			mdelay(spilen);
			break;	
	}
	FUNC_EXIT();
}

void print_framebuf(size_t len, unsigned char *src_addr)
{
    size_t i;
    unsigned char *data;
	size_t data_len;

	data=src_addr;
	data_len=len;
	
    for(i = 0; i < len; i++)
    {                
       printk("0x%x,",data[i]); 	
 		if(i%100==0)
       		printk("}\n{");
    }
	return;
} 


#define ENDIAN_SWITCH2(x)      (((((x) >> 8) & 0xFF) <<  0) |((((x) >>  0) & 0xFF) << 8))
static int lcm_get_frambuffer(void)
{

	int i;
	unsigned int ret=0;

	FUNC_ENTRY();

	if(ret != primary_display_capture_framebuffer_ovl((unsigned long)For_Capture_p,UFMT_RGB565)){//UFMT_RGB565)){ //eRGB565 eRGB565	

		return -1;
	}
	memcpy(For_BackupBuffer_p, For_Capture_p, ONE_FB_SIZE); 
	for(i=0;i<ONE_FB_SIZE/2;i++)
		For_Capture_p[i]=ENDIAN_SWITCH2(For_BackupBuffer_p[i]);

	lcm_spi_interface((unsigned char *)For_Capture_p,ONE_FB_SIZE_FORMAT,WRITE_DATA);
	memset(For_Capture_p,0x00,ONE_FB_SIZE);
	memset(For_BackupBuffer_p,0x00,ONE_FB_SIZE);

	FUNC_EXIT();

	return 0;
}

// Interrupt handler function
void lcm_spiCap_trigger(void)
{
	FUNC_ENTRY();
	 
	SPI_DBG("trigger_spiCap_enable_flag=%d!\n",atomic_read(&trigger_spiCap_enable_flag)); 
	
	if (atomic_read(&trigger_spiCap_enable_flag))
	{   	
		atomic_set(&trigger_spiCap_thread_flag,1);
		wake_up_interruptible(&trigger_spiCap_thread_wq); 		
	}
	else
	{
		atomic_set(&trigger_spiCap_thread_flag,0);
	}
	FUNC_EXIT();
}


//Thread processing function

static int Lcm_trigger_spiCap_thread(void *unused)
{

	struct sched_param param = { .sched_priority = 94};//RTPM_PRIO_SCRN_UPDATE };
	sched_setscheduler(current, SCHED_FIFO, &param);
	FUNC_ENTRY();
	
	do
	{
		SPI_DBG("Lcm_trigger_spiCap_thread waitting! \n");
		wait_event_interruptible(trigger_spiCap_thread_wq, atomic_read(&trigger_spiCap_thread_flag));
		atomic_set(&trigger_spiCap_thread_flag,0);
		atomic_set(&trigger_spiCap_enable_flag,0);
		if (!primary_display_is_sleepd())
		{
			SPI_DBG("Lcm_trigger_spiCap_thread working! \n");
			lcm_get_frambuffer(); 
		}
		atomic_set(&trigger_spiCap_enable_flag,1);

	}while(!kthread_should_stop());
	
	FUNC_EXIT();
	return 0;
}


static int lcm_suspend(struct device *pdev)
{
      int ret = -1;
	FUNC_ENTRY();
	printk("spi lcm_suspend\n");
	atomic_set(&trigger_spiCap_enable_flag, 0);
	set_pin_mode(GPIO_PIN_MODE);

	ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_cs_as_gpio_high);
	if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_cs_as_gpio_low,error,ret = %d\n",ret);
	}
	FUNC_EXIT();
	return 0;
}

static int lcm_resume(struct device *pdev)
{
      int ret = -1;
	FUNC_ENTRY();
	printk("spi lcm_resume\n");
	atomic_set(&trigger_spiCap_enable_flag, 1);
	set_pin_mode(GPIO_PIN_MODE);
	ret=pinctrl_select_state(g_lcm->pinctrl, g_lcm->spilcm_spi2_cs_as_gpio_low);
	if(ret < 0){
		SPI_DBG("pinctrl_select_state,spi_cs_as_gpio_low,error,ret = %d\n",ret);
	}
	FUNC_EXIT();
	return 0;

}

static int lcm_probe(struct spi_device *spi)
{
	struct spi_data *spi_data = NULL;	
	int status = -ENODEV;
	
	FUNC_ENTRY();
	//printk("spi_lcm_probe begin\n");
	spi_data = kzalloc(sizeof(struct spi_data),GFP_KERNEL);
	if (!spi_data)
	{
		return -ENOMEM;
	}
	

	For_Capture_p = (unsigned short*)kmalloc((ONE_FB_SIZE+64), GFP_KERNEL | GFP_DMA);
	if (!For_Capture_p)
	{
		return -ENOMEM;
	}
	For_BackupBuffer_p = (unsigned short*)kmalloc((ONE_FB_SIZE+64), GFP_KERNEL | GFP_DMA);
	if (!For_BackupBuffer_p)
	{
		return -ENOMEM;
	}

	For_Capture_p = (unsigned short*)ALIGN_TO((unsigned long)For_Capture_p,64); 
	For_BackupBuffer_p = (unsigned short*)ALIGN_TO((unsigned long)For_BackupBuffer_p,64);//åœ°å?€64 align//MTK_FB_ALIGNMENT

	//init head
	INIT_LIST_HEAD(&spi_data->device_entry);
	spin_lock_init(&spi_data->spi_lock);

	//init lock
	mutex_init(&spi_data->buf_lock);
	
	sema_init(&spi_data->lcm_sem, 1);
	
	mutex_lock(&device_list_lock);

	spi_data->mode_flag=-1;

	status = IS_ERR(spi_data->device)? PTR_ERR(spi_data->device):0;
	if (status !=0)
	{
		return status;
	}
	spi_set_drvdata(spi,spi_data); 

	if(spilcm_parse_dts(spi_data) != 0){ //zxs 20180203
		SPI_DBG("Failed to parse dts\n");
		//printk("Failed to parse spi_lcm dts\n");
		return -ENODEV;
	}

	g_lcm = spi_data;
	//spi init
	set_pin_mode(SPI_PIN_MODE);
	
	spi_data->spi = spi;
	spi_data->spi->bits_per_word = 8;
	spi_data->spi->mode = SPI_MODE_0;
#ifndef CONFIG_SPI_MT65XX
	spi_data->spi->controller_data = (void*)&spi_conf;
	spi_setup(spi_data->spi);
#endif
	
	lcm_device = spi_data->device;
	
	//Thread operation
#if defined(LCM_ENABLE_ICN6211)
        if (0)
        {
#endif
	    lcm_thread = kthread_run(Lcm_trigger_spiCap_thread,"Spi lcm thread","spithread");
#if defined(LCM_ENABLE_ICN6211)
        }
#endif

	mutex_unlock(&device_list_lock);
	FUNC_EXIT();
	return status;
}


static int  lcm_spi_init(void)
{
	int ret=0;
	
	FUNC_ENTRY();
#ifndef CONFIG_SPI_MT65XX	
	ret=spi_register_board_info(spi_board_info,ARRAY_SIZE(spi_board_info));
#endif
	ret=spi_register_driver(&lcm_driver);

	FUNC_EXIT();
	return ret; 
}


static void  lcm_spi_exit(void)
{
	FUNC_ENTRY();
	
	spi_unregister_driver(&lcm_driver);
	device_destroy(g_lcm->class,g_lcm->devno);
	if (g_lcm->class)
	{
		class_destroy(g_lcm->class);
	}
	unregister_chrdev_region (g_lcm->devno,1);
	list_del(&g_lcm->device_entry);
	
	FUNC_EXIT();
}

module_init(lcm_spi_init);
module_exit(lcm_spi_exit);

MODULE_DESCRIPTION("MT6739 SPI Controller Driver");
MODULE_AUTHOR("CTY");
MODULE_LICENSE("GPL");
MODULE_ALIAS("lcm_spi");
