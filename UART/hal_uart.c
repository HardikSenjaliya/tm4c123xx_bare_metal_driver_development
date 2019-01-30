#include "hal_uart.h"

/**
  * @brief  Enable UART
	* @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_uart_module(UART0_Type *uart){
	uart->CTL |= (1 << UARTCTL_REG_UARTEN_FLAG_MASK);
}

/**
  * @brief  Disable UART
	* @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_uart_module(UART0_Type *uart){
	uart->CTL &= ~(1 << UARTCTL_REG_UARTEN_FLAG_MASK);
}

/**
  * @brief  Enable Tx section of UART
	* @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_uart_Tx(UART0_Type *uart){
	uart->CTL |= (1 << UARTCTL_REG_TXE_FLAG_MASK);
}

/**
  * @brief  Disable Tx section of UART
	* @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_uart_Tx(UART0_Type *uart){
	uart->CTL &= ~(1 << UARTCTL_REG_TXE_FLAG_MASK);
}

/**
  * @brief  Enable Rx section of UART
	* @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_uart_Rx(UART0_Type *uart){
	uart->CTL |= (1 << UARTCTL_REG_RXE_FLAG_MASK);
}


/**
  * @brief  Disable Rx section of UART
	* @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_uart_Rx(UART0_Type *uart){
	uart->CTL &= ~(1 << UARTCTL_REG_RXE_FLAG_MASK);
}


/**
  * @brief  Configure the clock source
	* @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_configure_clock_source(UART0_Type *uart, int8_t source_type){
	
	if(source_type == UART_CLOCK_PIOSC)
		uart->CC |= UART_CLOCK_PIOSC;
	else
		uart->CC |= UART_CLOCK_SYSTEM;
}

/**
  * @brief  configure baudrate for the communication
  * @param  handle: pointer to a uart_handle_t structure
  * @retval None
	* For now the baud rate setting is limited to default system
	* of 16 MHz AND for clock divisor of 16
  */
void hal_uart_configure_baudrate(uart_handle_t *handle){
	
	uint32_t baurdrate = handle->init.baudrate;
	
	/*Calculate integer part of the baud rate divisor*/
	double BRD = (UART_SYS_CLOCK)/(baurdrate * UART_CLOCK_DIV);
	
	/*Separate decimal and fractional part from the BRD*/
	int32_t d_BRD = (int32_t)(BRD);
	int32_t f_BRD = (BRD - d_BRD) * 1000;  /*multiplied by 1000 to get four decimal points precision*/	
	
	/*set the d_BRD and f_BRD values into required register*/
	handle->instance->IBRD = d_BRD;
	handle->instance->FBRD = f_BRD;

}

/**
  * @brief  configure word length for the communication
  * @param  handle: pointer to a uart_handle_t structure
  * @retval None
  */
void hal_uart_configure_world_length(uart_handle_t *handle)
{
	handle->instance->LCRH |= (handle->init.worldlength << UARTLCRH_REG_WLEN_FLAG_MASK);
}

/**
  * @brief  Enables the FIFO for the communication
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_fifo(UART0_Type *uart){
	uart->LCRH |= (1 << UARTLCRH_REG_FEN_FLAG_MASK);
}

/**
  * @brief  Disables the FIFO for the communication
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disble_fifo(UART0_Type *uart){
	uart->LCRH &= ~(1 << UARTLCRH_REG_FEN_FLAG_MASK);
}

/**
  * @brief  Configures  stop bits for the communication
  * @param  handle: pointer to a uart_handle_t structure
  * @retval None
  */
void hal_uart_configure_stopbits(uart_handle_t *handle){
	handle->instance->LCRH |= (handle->init.stopbits << UARTLCRH_REG_STP2_FLAG_MASK);
}

/**
  * @brief  Enables the Parity checking for the communication
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_parity(UART0_Type *uart){
	uart->LCRH |= (1 << UARTLCRH_REG_PEN_FLAG_MASK);
}

/**
  * @brief  Disables the Parity checking for the communication
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_parity(UART0_Type *uart){
	uart->LCRH &= ~(1 << UARTLCRH_REG_PEN_FLAG_MASK);
}

/**
  * @brief  Enables the Even Parity checking for the communication
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_even_parity(UART0_Type *uart){
	uart->LCRH |= (1 << UARTLCRH_REG_EPS_FLAG_MASK);
}

/**
  * @brief  Enables the Odd Parity checking for the communication
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_odd_parity(UART0_Type *uart){
	uart->LCRH &= ~(1 << UARTLCRH_REG_EPS_FLAG_MASK);
}


/**
  * @brief  Enables the 9bit mode interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_9bitMode_interrupt(UART0_Type *uart){
	uart->IM |= (1 << UARTIM_REG_9BITIM_FLAG_MASK);
}

/**
  * @brief  Disables the 9bit mode interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_9bitMode_interrupt(UART0_Type *uart){
	uart->IM &= ~(1 << UARTIM_REG_9BITIM_FLAG_MASK);
}

/**
  * @brief  Enables the overrun error interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_overrun_error_interrupt(UART0_Type *uart){
	uart->IM |= (1 << UARTIM_REG_OEIM_FLAG_MASK);
}
/**
  * @brief  Disables the overrun error interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_overrun_error_interrupt(UART0_Type *uart){
	uart->IM &= ~(1 << UARTIM_REG_OEIM_FLAG_MASK);
}
/**
  * @brief  Enables the break error interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_break_error_interrupt(UART0_Type *uart){
	uart->IM |= (1 << UARTIM_REG_BEIM_FLAG_MASK);
}

/**
  * @brief  Disables the break error interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_break_error_interrupt(UART0_Type *uart){
	uart->IM &= ~(1 << UARTIM_REG_BEIM_FLAG_MASK);
}

/**
  * @brief  Enables the parity error interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_parity_error_interrupt(UART0_Type *uart){
	uart->IM |= (1 << UARTIM_REG_PEIM_FLAG_MASK);
}

/**
  * @brief  Disables the parity error interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_parity_error_interrupt(UART0_Type *uart){
	uart->IM &= ~(1 << UARTIM_REG_PEIM_FLAG_MASK);
}
/**
  * @brief  Enables the framing error interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_framing_error_interrupt(UART0_Type *uart){
	uart->IM |= (1 << UARTIM_REG_FEIM_FLAG_MASK);
}

/**
  * @brief  Disables the framing error interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_framing_error_interrupt(UART0_Type *uart){
	uart->IM &= ~(1 << UARTIM_REG_FEIM_FLAG_MASK);
}
/**
  * @brief  Enables the receive time out interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_receive_timeout_interrupt(UART0_Type *uart){
	uart->IM |= (1 << UARTIM_REG_RTIM_FLAG_MASK);
}

/**
  * @brief  Disables the receive time out interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_receive_timeout_interrupt(UART0_Type *uart){
	uart->IM &= ~(1 << UARTIM_REG_RTIM_FLAG_MASK);
}
/**
  * @brief  Enables the Transmisstion interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_tx_interrupt(UART0_Type *uart){
	uart->IM |= (1 << UARTIM_REG_TXIM_FLAG_MASK);
}

/**
  * @brief  Disables the Transmisstion interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_tx_interrupt(UART0_Type *uart){
	uart->IM &= ~(1 << UARTIM_REG_TXIM_FLAG_MASK);
}

/**
  * @brief  Enables the Receiver interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_rx_interrupt(UART0_Type *uart){
	uart->IM |= (1 << UARTIM_REG_RXIM_FLAG_MASK);
}
/**
  * @brief  Disables the Receiver interrupt
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_rx_interrupt(UART0_Type *uart){
	uart->IM &= ~(1 << UARTIM_REG_RXIM_FLAG_MASK);
}

/**
  * @brief  Enables the Receiver using DMA
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_rx_dma(UART0_Type *uart){
	uart->DMACTL |= (1 << UARTDMACTL_REG_RXDMAE_FLAG_MASK);
}

/**
  * @brief  Disables the Receiver using DMA
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_rx_dma(UART0_Type *uart){
	uart->DMACTL &= ~(1 << UARTDMACTL_REG_RXDMAE_FLAG_MASK);
}
/**
  * @brief  Enables the transmission using DMA
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_enable_tx_dma(UART0_Type *uart){
	uart->DMACTL |= (1 << UARTDMACTL_REG_TXDMAE_FLAG_MASK);
}

/**
  * @brief  Disables the transmission using DMA
  * @param  uart: pointer to UART base address
  * @retval None
  */
void hal_uart_disable_tx_dma(UART0_Type *uart){
	uart->DMACTL &= ~(1 << UARTDMACTL_REG_TXDMAE_FLAG_MASK);
}