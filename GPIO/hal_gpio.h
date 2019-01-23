#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>

/*GPIO port address*/

#define GPIO_PORT_A				GPIOA_BASE
#define GPIO_PORT_B				GPIOB_BASE
#define GPIO_PORT_C				GPIOC_BASE
#define GPIO_PORT_D				GPIOD_BASE
#define GPIO_PORT_E				GPIOE_BASE
#define GPIO_PORT_F				GPIOF_BASE
#define GPIO_PORT_AHB_A		GPIOA_AHB_BASE
#define GPIO_PORT_AHB_B		GPIOB_AHB_BASE
#define GPIO_PORT_AHB_C		GPIOC_AHB_BASE
#define GPIO_PORT_AHB_D		GPIOD_AHB_BASE
#define GPIO_PORT_AHB_E		GPIOE_AHB_BASE
#define GPIO_PORT_AHB_F		GPIOF_AHB_BASE


/*GPIO pin mode*/
#define GPIO_PIN_INPUT_MODE				0x00
#define GPIO_PIN_OUTPUT_MODE			0x01


/*Enable alternate functionality of the pin*/
#define	GPIO_PIN_ALT_MODE					0x01


/*GPIO pin drive strength*/
#define GPIO_PIN_DS_2MA						0x02
#define GPIO_PIN_DS_4MA						0x04
#define GPIO_PIN_DS_8MA						0x08

/*GPIO pin register mode*/
#define	GPIO_PIN_PULL_UP					0x01
#define GPIO_PIN_PULL_DOWN				0x02
#define GPIO_PIN_OPEN_DRAIN				0x03

/*GPIO pin digital functionality*/
#define GPIO_PIN_DIGITAL_ENABLE				0x01


#define EDGE_TRIGGRED_INTERRUPT				0x00
#define LEVEL_TRIGGRED_INTERRUPT			0x01


/*Macros to enable clock for GPIO port*/
#define GPIO_PORTA_CLOCK_ENABLE()			(RCGCGPIO	|= (1 << 0))
#define GPIO_PORTB_CLOCK_ENABLE()			(RCGCGPIO	|= (1 << 1))
#define GPIO_PORTC_CLOCK_ENABLE()			(RCGCGPIO	|= (1 << 2))
#define GPIO_PORTD_CLOCK_ENABLE()			(RCGCGPIO	|= (1 << 3))
#define GPIO_PORTE_CLOCK_ENABLE()			(RCGCGPIO	|= (1 << 4))
#define GPIO_PORTF_CLOCK_ENABLE()			(RCGCGPIO	|= (1 << 5))

/*enum for gpio port numbers*/
typedef enum{
	
	port_a,
	port_b,
	port_c,
	port_d,
	port_e,
	port_f
	
}gpio_port_number;



/*enum for gpio edge interrupt*/
typedef enum{
	
	INT_RISING_EDGE,
	INT_FALLING_EDGE,
	INT_RISING_FALLING_EDGE
}gpio_edge_interrupt;


/*enum for gpio level interrupt*/
typedef enum{

	INT_LOW_LEVEL,
	INT_HIGH_LEVEL
}gpio_level_interrupt;


/*Data structure for GPIO pin initialization*/
typedef struct{

	uint32_t	pin;														/*specifies gpio pin to be configured*/
	uint32_t	mode;														/*specifies gpio pin mode ie input or output or alternate*/
	uint32_t 	drive_strength;									/*specifies gpio pin drive strength 2mA or 4mA or 8mA*/
	uint32_t 	digital;												/*specifies gpio pin as digital pin*/
	uint32_t  register_config;								/*specifies external pull up or pull down or open drain configuration*/
	bool int_type;														/*1 = level sensitive, 0 = edge sensitive*/
	gpio_edge_interrupt edge_selection;				/*select type of edge triggered interrupt*/
	gpio_level_interrupt	level_selection;    /*select type of level trigerred interrupt*/
	IRQn_Type irq_no;													/*NVIC number of the interrupt*/
	
}gpio_pin_config_t;


/***********************************************/
/*             Various APIs for GPIO           */
/***********************************************/




/**
	* @brief  Initializes the gpio pin 
	* @param  *GPIOx : GPIO Port Base address
	* @param  *gpio_pin_config :Pointer to the pin conf structure sent by application 
	* @retval None
	*/
void hal_gpio_init(GPIOA_Type *GPIOx, gpio_pin_config_t *gpio_pin_config);

/**
	* @brief  Read a value from a  given pin number 
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @retval uint8_t: Value read 
	*/
uint8_t hal_gpio_read_pin(GPIOA_Type *GPIOx, uint16_t pin_no);


/**
	* @brief  Read a value from a  given port
	* @param  *GPIOx : GPIO Port Base address
	* @retval uint8_t: Value read 
	*/
uint8_t hal_gpio_read_port(GPIOA_Type *GPIOx);

/**
	* @brief  Write a value to given pin number 
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @param  value   : value to be written 
	* @retval None
	*/
void hal_gpio_write_to_pin(GPIOA_Type *GPIOx, uint16_t pin_no, uint8_t value);


/**
	* @brief  Write a value to a  given port
	* @param  *GPIOx : GPIO Port Base address
	* @param  value  : uint8_t: Value to be written 
	*	@retval None
	*/
void hal_gpio_write_port(GPIOA_Type *GPIOx, uint8_t value);

/**
	* @brief  Set the pin mode for the given pin 
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @param  pin_mode : mode of the pin input or output 
	* @retval None
	*/
void hal_gpio_set_pin_mode(GPIOA_Type *GPIOx, uint16_t pin_no, uint8_t pin_mode);

/**
	* @brief  Set the alternate functionality for the given pin  
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @retval None
	*/
void hal_gpio_set_alt_function(GPIOA_Type *GPIOx, uint16_t pin_no);

/**
	* @brief  Configure the edge triggered interrupt for a given pin number   
	* @param  pin_no : GPIO pin number 
	* @param  edge_sel   :  Triggering edge slection value of type "gpio_edge_interrupt"
	* @retval None
	*/	
void hal_gpio_configure_edge_interrupt(GPIOA_Type *GPIOx, uint16_t pin_no, gpio_edge_interrupt edge_sel);

/**
	* @brief  Configure external register configuration for a given pin
	* @param  pin_no : GPIO pin number 
	* @param  register_config : pull up or pull down or open drain configuration
	* @retval None
	*/	
void hal_gpio_configure_register(GPIOA_Type *GPIOx, uint16_t pin_no, uint16_t register_config);

/**
	* @brief  Configure drive strength for a given pin number
	* @param  pin_no : GPIO pin number 
	* @param  drive_strength   :  drive strength value
	* @retval None
	*/	
void hal_gpio_configure_drive_strength(GPIOA_Type *GPIOx, uint16_t pin_no, uint16_t drive_strength);

/**
	* @brief  enable digital functionality for a given pin number
	* @param  pin_no : GPIO pin number 
	* @param  enable : 1 to enable 
	* @retval None
	*/	
void hal_gpio_configure_digital_functionality(GPIOA_Type *GPIOx, uint16_t pin_no, bool enable);

/**
	* @brief  Configure the type of interrupt for a given pin number   
	* @param  pin_no : GPIO pin number 
	* @param  interrupt_type   :  edge triggered or level triggered
	* @retval None
	*/
void hal_gpio_configure_interrupt_type(GPIOA_Type *GPIOx, uint16_t pin_no, bool interrupt_type);


/**
	* @brief  Configure the level interrupt for a given pin number   
	* @param  pin_no : GPIO pin number 
	* @param  edge_sel   :  level slection value of type "gpio_level_interrupt"
	* @retval None
	*/
void hal_gpio_configure_level_interrupt(GPIOA_Type *GPIOx, uint16_t pin_no, gpio_level_interrupt level_sel);


/**
	* @brief  Enable the interrupt for a give pin number and irq number  
	* @param  pin_no : GPIO pin number 
	* @param  irq_no   :  irq_number to be enabled in NVIC 
	* @retval None
	*/
void hal_gpio_enable_interrupt(GPIOA_Type *GPIOx, uint16_t pin_no, IRQn_Type irq_no);

/**
	* @brief  Clear the sticky interrupt pending bit if set 
	* @param  pin_no : GPIO pin number 
	* @retval None
	*/
void 	hal_gpio_clear_interrupt(GPIOA_Type *GPIOx, uint16_t pin_no);

#endif
