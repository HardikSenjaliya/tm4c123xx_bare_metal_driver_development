#include "uart_application.h"


SYSCTL_Type *sysctl = (SYSCTL_Type*)(SYSCTL_BASE);
GPIOA_Type *gpioD = (GPIOA_Type*)(GPIO_PORT_D);

uart_handle_t uart2_handle;

/**
  * @brief  Configures the GPIO Port D for UART operation
	* PD6 = UART Rx pin
	* PD7 = UART Tx pin
  * @param  void
  * @retval None
  */

void uart_gpio_init(){
	
	/*Enable clock gating for port D*/
	sysctl->RCGCGPIO |= (1 << port_d);
	
	/*Unlock the PORT D*/
	gpioD->LOCK = 0x4C4F434B;
	
	/*Enables changes on PD6 and PD7*/
	hal_gpio_enable_changes_on_pin(gpioD, UART_TX_PIN);
	hal_gpio_enable_changes_on_pin(gpioD, UART_RX_PIN);
	
	/*Set alternate function for the pin PD6 and PD7*/
	hal_gpio_set_alt_function(gpioD, UART_TX_PIN);
	hal_gpio_set_alt_function(gpioD, UART_RX_PIN);
	
	/*Set UART Tx pin as output mode*/
	hal_gpio_set_pin_mode(gpioD, UART_TX_PIN, GPIO_PIN_OUTPUT_MODE);
	
	/*Set UART Rx pin as input mode*/
	hal_gpio_set_pin_mode(gpioD, UART_RX_PIN, GPIO_PIN_INPUT_MODE);

	/*Configure current level for both pin to 2 mA*/
	hal_gpio_configure_drive_strength(gpioD, UART_TX_PIN, GPIO_PIN_DS_2MA);
	hal_gpio_configure_drive_strength(gpioD, UART_RX_PIN, GPIO_PIN_DS_2MA);
	
	/*configure both pins digital functionality*/
	hal_gpio_configure_digital_functionality(gpioD, UART_RX_PIN, GPIO_PIN_DIGITAL_ENABLE);
	hal_gpio_configure_digital_functionality(gpioD, UART_TX_PIN, GPIO_PIN_DIGITAL_ENABLE);
	
	/*Configure PMC field in GPIOCTL register to for alternate functionality*/
	hal_gpio_configure_mux_control(gpioD, UART_TX_PIN, 1);
	hal_gpio_configure_mux_control(gpioD, UART_RX_PIN, 1);

}

/**
  * @brief  Initializes UART functionalities
  * @param  None
  * @retval None
  */

void uart_init(){
	
	/*Configure GPIO pins for UART2*/
	uart_gpio_init();
	
	uart2_handle.instance = UART2;
	
	/*Enable clock for UART2*/
	sysctl->RCGCUART |= (1 << RCGCUART_CLOCK_GATING_UART2);
	
	uart2_handle.init.baudrate = UART_BAUDRATE_11500;				/*Configure barudrate of 115200*/
	uart2_handle.init.fifo_mode = UART_FIFO_ENABLED;        /*fifo mode enabled*/
	uart2_handle.init.parity = UART_NO_PARITY;							/*NO parity checking*/
	uart2_handle.init.stopbits = UART_ONE_STOPBIT;					/*One stopbit*/
	uart2_handle.init.worldlength = UART_WORDLENGTH_8BIT;		/*Data in a frame is 8 bits*/
	
	/*Disable the UART2 module before configuring it*/
	hal_uart_disable_uart_module(uart2_handle.instance);
	
	/*Initialize UART2*/
	hal_uart_configure_baudrate(&uart2_handle);
	hal_uart_enable_fifo(uart2_handle.instance);
	hal_uart_disable_parity(uart2_handle.instance);
	hal_uart_configure_stopbits(&uart2_handle);
	hal_uart_configure_world_length(&uart2_handle);
	
	/*Select clock source for the UART*/
	hal_uart_configure_clock_source(uart2_handle.instance, UART_CLOCK_SYSTEM);
	
	/*Enable Tx and Rx section of the UART module*/
	hal_uart_enable_uart_Tx(uart2_handle.instance);
	hal_uart_enable_uart_Rx(uart2_handle.instance);
	
	/*Enable transmission and reception for the UART2*/
	hal_uart_enable_uart_module(uart2_handle.instance);
	
	/*Set the status as ready*/
	uart2_handle.rx_state = UART_STATE_READY;
	uart2_handle.tx_state = UART_STATE_READY;
	
}


int main(void){

	/*Initialize UART functionality*/
	uart_init();

	return 0;
}