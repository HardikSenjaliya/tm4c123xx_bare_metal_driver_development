#ifndef UART_APPLICATION_H
#define UART_APPLICATION_H


#include "hal_uart.h"
#include "hal_gpio.h"


#define GPIO_PORTD_PD6						(6)
#define GPIO_PORTD_PD7						(7)


#define RCGCUART_CLOCK_GATING_UART7			(7)
#define RCGCUART_CLOCK_GATING_UART6			(6)
#define RCGCUART_CLOCK_GATING_UART5			(5)
#define RCGCUART_CLOCK_GATING_UART4			(4)
#define RCGCUART_CLOCK_GATING_UART3			(3)
#define RCGCUART_CLOCK_GATING_UART2			(2)
#define RCGCUART_CLOCK_GATING_UART1			(1)
#define RCGCUART_CLOCK_GATING_UART0			(0)

	
#define UART_TX_PIN							(GPIO_PORTD_PD7)
#define UART_RX_PIN							(GPIO_PORTD_PD6)


/*Function to initialize GPIO for UART functionality*/
void uart_gpio_init(void);

/*Function to UART functionality*/
void uart_init(void);


#endif