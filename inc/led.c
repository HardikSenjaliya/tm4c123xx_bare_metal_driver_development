#include "led.h"
#include "tm4c123gh6pm.h"


/*Sample application to test the GPIO driver code*/

GPIOA_Type *GPIOx = (GPIOA_Type*)GPIO_PORT_F;


/*function to turn led on*/
void led_on(GPIOA_Type *GPIOx, int32_t pin_no){
	hal_gpio_write_to_pin(GPIOx, pin_no, 1);
}

/*function to turn led off*/
void led_off(GPIOA_Type *GPIOx, int32_t pin_no){
	hal_gpio_write_to_pin(GPIOx, pin_no, 0);
}

/*GPIO port f IRQ handler*/
void GPIOF_Handler(void){
	hal_gpio_clear_interrupt(GPIOx, SWITCH_SW2_PIN);
	led_off(GPIOx, LED_RED_PIN);
}


/*function to initialize led and switch pin of port f*/
void led_switch_init(){
	
	
	gpio_pin_config_t led_pin_config, switch_pin_config;
	
	
	/*Enable clock for PottF*/
	SYSCTL_Type *sysctl = (SYSCTL_Type*)SYSCTL_BASE;
	sysctl->RCGCGPIO |= (1 << port_f);
	
	/*unlock PortF*/
	GPIOx->LOCK = 0x4C4F434B;
	
	/*Allow changes to PF0 and PF1*/
	GPIOx->CR = 0x03;
	
	/*Configure led pin*/
	led_pin_config.pin = LED_RED_PIN;
	led_pin_config.mode = GPIO_PIN_OUTPUT_MODE;
	led_pin_config.digital = GPIO_PIN_DIGITAL_ENABLE;
	hal_gpio_init(GPIOx, &led_pin_config);
	
	/*Configure switch pin*/
	switch_pin_config.pin = SWITCH_SW2_PIN;
	switch_pin_config.mode = GPIO_PIN_INPUT_MODE;
	switch_pin_config.digital = GPIO_PIN_DIGITAL_ENABLE;
	hal_gpio_init(GPIOx, &switch_pin_config);

	/*Configure falling edge interrupt on Switch 2*/
	hal_gpio_configure_register(GPIOx, SWITCH_SW2_PIN, GPIO_PIN_PULL_UP);
	hal_gpio_configure_interrupt_type(GPIOx, SWITCH_SW2_PIN, EDGE_TRIGGRED_INTERRUPT);
	hal_gpio_configure_edge_interrupt(GPIOx, SWITCH_SW2_PIN, INT_FALLING_EDGE);
	hal_gpio_enable_interrupt(GPIOx, SWITCH_SW2_PIN, GPIOF_IRQn);


	/*Enable global interrupt*/
	IntMasterEnable();
}


int main(void){
	
	//int32_t status = 0;
	led_switch_init();
	
	while(1){
			led_on(GPIOx, LED_RED_PIN);
	}
	
	return 0;
}

