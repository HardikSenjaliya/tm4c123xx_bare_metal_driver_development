#include "stdint.h"
#include "hal_gpio.h"

		

/**
	* @brief  Initializes the gpio pin 
	* @param  *GPIOx : GPIO Port Base address
	* @param  *gpio_pin_config :Pointer to the pin conf structure sent by application 
	* @retval None
	*/
void hal_gpio_init(GPIOA_Type *GPIOx, gpio_pin_config_t *gpio_pin_config){
		
	hal_gpio_set_pin_mode(GPIOx, gpio_pin_config->pin, gpio_pin_config->mode);
	
	hal_gpio_configure_digital_functionality(GPIOx, gpio_pin_config->pin, gpio_pin_config->digital);
	
}


/**
	* @brief  Read a value from a  given pin number 
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @retval uint8_t: Value read 
	*/
uint8_t hal_gpio_read_pin(GPIOA_Type *GPIOx, uint16_t pin_no){
	
	return ((GPIOx->DATA >> pin_no) & 0x00000001);
}

/**
	* @brief  Write a value to given pin number 
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @param  value   : value to be written 
	* @retval None
	*/
void hal_gpio_write_to_pin(GPIOA_Type *GPIOx, uint16_t pin_no, uint8_t value){
	if(value){
		GPIOx->DATA |= (1 << pin_no);
	}
	else{
		GPIOx->DATA &= ~(1 << pin_no);
	}
}

/**
	* @brief  Read a value from a  given port
	* @param  *GPIOx : GPIO Port Base address
	* @retval uint8_t: Value read 
	*/
uint8_t hal_gpio_read_port(GPIOA_Type *GPIOx){
	
	return (GPIOx->DATA);
}

/**
	* @brief  Write a value to a  given port
	* @param  *GPIOx : GPIO Port Base address
	* @param  value  : uint8_t: Value to be written 
	*	@retval None
	*/
void hal_gpio_write_port(GPIOA_Type *GPIOx, uint8_t value){
	
	GPIOx->DATA = value;
	
	
}

/**
	* @brief  Set the pin mode for the given pin 
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @param  pin_mode : mode of the pin input or output 
	* @retval None
	*/
void hal_gpio_set_pin_mode(GPIOA_Type *GPIOx, uint16_t pin_no, uint8_t pin_mode){
	if(pin_mode)
		GPIOx->DIR |= (pin_mode << pin_no);
	else
		GPIOx->DIR &= ~(pin_mode << pin_no);
}


/**
	* @brief  Set the alternate functionality for the given pin  
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @retval None
	*/
void hal_gpio_set_alt_function(GPIOA_Type *GPIOx, uint16_t pin_no){
	
	GPIOx->AFSEL |= (1 << pin_no);
}

/**
	* @brief  Configure drive strength for a given pin number
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @param  drive_strength   :  drive strength value
	* @retval None
	*/	
void hal_gpio_configure_drive_strength(GPIOA_Type *GPIOx, uint16_t pin_no, uint16_t drive_strength){

	if(drive_strength == GPIO_PIN_DS_2MA){
		GPIOx->DR2R |= (1 << pin_no);
	}
	else if(drive_strength == GPIO_PIN_DS_4MA){
		GPIOx->DR4R |= (1 << pin_no);
	}
	else{
		GPIOx->DR4R |= (1 << pin_no);
	}
}

/**
	* @brief  Configure external register configuration for a given pin
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @param  register_config : pull up or pull down or open drain configuration
	* @retval None
	*/	
void hal_gpio_configure_register(GPIOA_Type *GPIOx, uint16_t pin_no, uint16_t register_config){
	
	if(register_config == GPIO_PIN_PULL_UP){
		GPIOx->PUR |= (1 << pin_no);
	}
	else if(register_config == GPIO_PIN_PULL_DOWN){
		GPIOx->PDR |= (1 << pin_no);
	}
	else{
		GPIOx->ODR |= (1 << pin_no);
	}
}

/**
	* @brief  enable digital functionality for a given pin number
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @param  enable : 1 to enable 
	* @retval None
	*/	
void hal_gpio_configure_digital_functionality(GPIOA_Type *GPIOx, uint16_t pin_no, bool enable){
	
	GPIOx->DEN |= (1 << pin_no);
}

/**
	* @brief  Configure the type of interrupt for a given pin number
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @param  interrupt_type   :  edge triggered or level triggered
	* @retval None
	*/
void hal_gpio_configure_interrupt_type(GPIOA_Type *GPIOx, uint16_t pin_no, bool interrupt_type){
	
		GPIOx->IS |= (interrupt_type << pin_no);
}


/**
	* @brief  Configure the edge triggered interrupt for a given pin number
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @param  edge_sel   :  Triggering edge slection value of type "gpio_edge_interrupt"
	* @retval None
	*/	
void hal_gpio_configure_edge_interrupt(GPIOA_Type *GPIOx, uint16_t pin_no, gpio_edge_interrupt edge_sel){
	
	if(edge_sel == INT_RISING_FALLING_EDGE){
			GPIOx->IBE |= (1 << pin_no);
	}
	else if(edge_sel == INT_FALLING_EDGE){
			GPIOx->IEV &= ~(1 << pin_no);
	}else{
			GPIOx->IEV |= (1 << pin_no);
	}
}

/**
	* @brief  Configure the level interrupt for a given pin number '
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @param  edge_sel   :  level slection value of type "gpio_level_interrupt"
	* @retval None
	*/
void hal_gpio_configure_level_interrupt(GPIOA_Type *GPIOx, uint16_t pin_no, gpio_level_interrupt level_sel){
	
	if(level_sel == INT_HIGH_LEVEL){
		GPIOx->IEV |= (1 << pin_no);
	}
	else{
		GPIOx->IEV &= ~(1 << pin_no);
	}
}


/**
	* @brief  Enable the interrupt for a give pin number and irq number  
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @param  irq_no :  irq_number to be enabled in NVIC 
	* @retval None
	*/
void hal_gpio_enable_interrupt(GPIOA_Type *GPIOx, uint16_t pin_no, IRQn_Type irq_no){
		
	/*First clear the interrupt flag before enabling it*/
	GPIOx->ICR |= (1 << pin_no);
	
	/*Mask given pin to send the generated interrupt to NVIC*/
	GPIOx->IM |= (1 << pin_no);
	
	/*Enable the interrupt in NVIC*/
	NVIC_EnableIRQ(irq_no);
}

/**
	* @brief  Clear the sticky interrupt pending bit if set 
	* @param  *GPIOx : GPIO Port Base address
	* @param  pin_no : GPIO pin number 
	* @retval None
	*/
void 	hal_gpio_clear_interrupt(GPIOA_Type *GPIOx, uint16_t pin_no){
	GPIOx->ICR |= (1 << pin_no);
}
