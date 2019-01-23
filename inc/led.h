#ifndef LED_H
#define LED_H

#include "hal_gpio.h"
#include "interrupt.h"

#define PORTF_PIN_0			0
#define PORTF_PIN_1			1
#define PORTF_PIN_2			2
#define PORTF_PIN_3			3
#define PORTF_PIN_4			4

#define LED_RED_PIN					PORTF_PIN_1
#define LED_BLUE_PIN				PORTF_PIN_2
#define LED_GREEN_PIN				PORTF_PIN_3
#define SWITCH_SW1_PIN			PORTF_PIN_4
#define SWITCH_SW2_PIN			PORTF_PIN_0

void led_switch_init(void);
void led_on(GPIOA_Type *GPIOx, int32_t pin_no);
void led_off(GPIOA_Type *GPIOx, int32_t pin_no);

#endif
