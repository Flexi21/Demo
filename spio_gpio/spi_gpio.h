#ifndef __SPI_GPIO_H__
#define __SPI_GPIO_H__

#ifdef BUILD_LK
#define GPIO_SPI_DATA_PIN 		(17|0x80000000)
#define GPIO_SPI_RS_PIN 		(19|0x80000000)
#define GPIO_SPI_CS_PIN                 (20|0x80000000)
#define GPIO_SPI_SCK_PIN                (18|0x80000000)

#define SET_GPIO_MODE(num,mode)								(mt_set_gpio_mode((num),(mode)))
#define SET_GPIO_DIR(num,dir)								(mt_set_gpio_dir((num),(dir)))
#define SET_GPIO_OUT(num,level)								(mt_set_gpio_out((num), (level)))
#define SET_GPIO_PULL_ENABLE(num,enable)					        (mt_set_gpio_pull_enable((num),(enable)))
#define GET_GPIO_VALUE(num)								(mt_get_gpio_in(num))


#if defined(SPI_THREE_CONFIG)
#define SET_SEND_TYPE(level) 				{                                                   \
                                                            SET_GPIO_OUT(GPIO_SPI_DATA_PIN,(level));        \
                                                            SET_GPIO_OUT(GPIO_SPI_SCK_PIN,GPIO_OUT_ZERO);   \
                                                            SET_GPIO_OUT(GPIO_SPI_SCK_PIN,GPIO_OUT_ONE);    \
                                                        }
#else
#define SET_SEND_TYPE(level)				{SET_GPIO_OUT(GPIO_SPI_RS_PIN,(level));} 
#endif	

typedef enum
{
	WRITE_CMD=0,
	WRITE_DATA=1,
	READ_DATA=2
}SPI_OP_MODE;

static char init_flag=0;

#else /*#ifdef BUILD_LK*/
/**************************************BELOW IS KERNER PART***************************************************/
#define GPIO_OUT_ZERO             0
#define GPIO_OUT_ONE              1
#define GPIO_DIR_IN               0
#define GPIO_DIR_OUT              1
struct spi_gpio_attr {
	const char *name;
	int pin;
        char exist;
};

typedef enum
{
	WRITE_CMD=0,
	WRITE_DATA=1,
	READ_DATA=2
}SPI_OP_MODE;

enum spi_gpio_type {
        GPIO_SPI_SCK_PIN = 0,
        GPIO_SPI_CS_PIN,          
        GPIO_SPI_DATA_PIN,
#ifndef SPI_THREE_CONFIG
        GPIO_SPI_RS_PIN,
#endif
        GPIO_SPI_MAX_PIN
};

struct spi_gpio_attr gpio_spi_arrys[GPIO_SPI_MAX_PIN] = {
       [GPIO_SPI_SCK_PIN]       =  {"gpio_spi_ck"},
       [GPIO_SPI_CS_PIN]        =  {"gpio_spi_cs"},
       [GPIO_SPI_DATA_PIN]      =  {"gpio_spi_mosi"},
       #ifndef SPI_THREE_CONFIG
       [GPIO_SPI_RS_PIN]        =  {"gpio_spi_miso"},
       #endif
};

int get_spi_gpio_value(enum spi_gpio_type type);
int set_spi_gpio_value(enum spi_gpio_type type,int value);
int set_spi_gpio_dir(enum spi_gpio_type type,int value);
static char init_flag=0;
#endif
#endif

