#ifndef HAL_UART_H
#define HAL_UART_H

#include "tm4c123gh6pm.h"

/*@brief structure for different UART state*/
typedef enum{

	UART_STATE_RESET			= 0x00, /*UART is not yet initialized*/
	UART_STATE_READY			= 0x01,	/*UART is initialized and ready to use */
	UART_STATE_BUSY				= 0x02, /*UART is busy in an internal process*/
	UART_STATE_BUSY_TX 			= 0x12, /*UART is busy in transmitting data*/
	UART_STATE_BUSY_RX  		= 0x22, /*UART is busy in receiving data*/
	UART_STATE_BUSY_RX_TX 		= 0x32  /*UART is busy in tramsitting and receiving data*/

}uart_state_t;


/***************************************************************************************/
/*                                                                                     */
/*					Register Bit Definitions                                                   */  
/*                                                                                     */
/***************************************************************************************/

/*Bit definitions for UARTD register*/
#define UARTD_REG_OE_FLAG_MASK							(11)
#define UARTD_REG_BE_FLAG_MASK							(10)
#define UARTD_REG_PE_FLAG_MASK	                  		(9)
#define UARTD_REG_FE_FLAG_MASK	                  		(8)

/*Bit definitions for UARTECR register*/
#define UARTECR_REG_OE_FLAG_MASK						(3)
#define UARTECR_REG_BE_FLAG_MASK						(2)
#define UARTECR_REG_PE_FLAG_MASK						(1)
#define UARTECR_REG_FE_FLAG_MASK						(0)	

/*Bit definitions for UARTFR register*/
#define UARTFR_REG_TXFE_FLAG_MASK						(7)
#define UARTFR_REG_RXFF_FLAG_MASK						(6)
#define UARTFR_REG_TXFF_FLAG_MASK						(5)
#define UARTFR_REG_RXFE_FLAG_MASK						(4)
#define UARTFR_REG_BUSY_FLAG_MASK						(3)
#define UARTFR_REG_CTS_FLAG_MASK						(0)
	
/*Bit definitions for UARTLCRH register*/
#define UARTLCRH_REG_SPS_FLAG_MASK						(7)
#define UARTLCRH_REG_WLEN_FLAG_MASK						(5)
#define UARTLCRH_REG_FEN_FLAG_MASK						(4)
#define UARTLCRH_REG_STP2_FLAG_MASK						(3)
#define UARTLCRH_REG_EPS_FLAG_MASK						(2)
#define UARTLCRH_REG_PEN_FLAG_MASK						(1)
#define UARTLCRH_REG_BRK_FLAG_MASK						(0)

/*Bit definitions for UARTCTL register*/
#define UARTCTL_REG_RXE_FLAG_MASK						(9)
#define UARTCTL_REG_TXE_FLAG_MASK						(8)
#define UARTCTL_REG_LBE_FLAG_MASK						(7)
#define UARTCTL_REG_HSE_FLAG_MASK						(5)
#define UARTCTL_REG_EOT_FLAG_MASK						(4)	
#define UARTCTL_REG_UARTEN_FLAG_MASK					(0)

/*Bit definitions for UARTIFLS register*/
#define UARTIFLS_RXIFLSEL_MASK							(3)
#define UARTIFLS_TXIFLSEL_MASK							(0)

/*Bit definitions for UARTIM register*/
#define UARTIM_REG_9BITIM_FLAG_MASK						(12)
#define UARTIM_REG_OEIM_FLAG_MASK						(10)
#define UARTIM_REG_BEIM_FLAG_MASK						(9)
#define UARTIM_REG_PEIM_FLAG_MASK						(8)
#define UARTIM_REG_FEIM_FLAG_MASK						(7)
#define UARTIM_REG_RTIM_FLAG_MASK						(6)
#define UARTIM_REG_TXIM_FLAG_MASK						(5)
#define UARTIM_REG_RXIM_FLAG_MASK						(4)
#define UARTIM_REG_CTSIM_FLAG_MASK						(1)
		
/*Bit definitions for UARTRIS register*/
#define UARTRIS_REG_9BITIM_FLAG_MASK					(12)
#define UARTRIS_REG_OEIM_FLAG_MASK						(10)
#define UARTRIS_REG_BEIM_FLAG_MASK						(9)
#define UARTRIS_REG_PEIM_FLAG_MASK						(8)
#define UARTRIS_REG_FEIM_FLAG_MASK						(7)
#define UARTRIS_REG_RTIM_FLAG_MASK						(6)
#define UARTRIS_REG_TXIM_FLAG_MASK						(5)
#define UARTRIS_REG_RXIM_FLAG_MASK						(4)
#define UARTRIS_REG_CTSIM_FLAG_MASK						(1)

/*Bit definitions for UARTICR register*/
#define UARTICR_REG_9BITIM_FLAG_MASK					(12)
#define UARTICR_REG_OEIM_FLAG_MASK						(10)
#define UARTICR_REG_BEIM_FLAG_MASK						(9)
#define UARTICR_REG_PEIM_FLAG_MASK						(8)
#define UARTICR_REG_FEIM_FLAG_MASK						(7)
#define UARTICR_REG_RTIM_FLAG_MASK						(6)
#define UARTICR_REG_TXIM_FLAG_MASK						(5)
#define UARTICR_REG_RXIM_FLAG_MASK						(4)
#define UARTICR_REG_CTSIM_FLAG_MASK						(1)


/*Bit definitions for UARTDMACTL, register*/
#define UARTDMACTL_REG_DMAERR_FLAG_MASK					(2)
#define UARTDMACTL_REG_TXDMAE_FLAG_MASK					(1)
#define UARTDMACTL_REG_RXDMAE_FLAG_MASK					(0)

/*UART baudrates*/
#define UART_BAUDRATE_4800								(uint32_t)(4800)
#define UART_BAUDRATE_9600								(uint32_t)(9600)
#define UART_BAUDRATE_11500								(uint32_t)(115200)



/*****************************************************************************/
/*                                                                           */
/*                        Data Structures for initializing UART              */
/*                                                                           */
/*****************************************************************************/

/*UART init structure definition*/
typedef struct{

<<<<<<< HEAD
	uint32_t 		baudrate;			/*specifies baudrate of the uart communication*/
	uint32_t 		worldlength;		/*specifies number of bits per frame*/
	uint32_t		stopbits;			/*specifies stop bits */
	uint32_t 		parity;				/*specifies parity*/
	uint32_t 		mode;				/*specifies mode of communication Transmission or Reception*/
=======
	uint32_t 		baudrate;								/*specifies baudrate of the uart communication */
	uint32_t 		worldlength;							/*specifies number of bits per frame*/
	uint32_t		stopbits;								/*specifies stop bits */
	uint32_t 		parity;									/*specifies parity*/
	uint32_t 		mode;									/*specifies mode of communication Transmission or Reception*/
>>>>>>> 7a73fceda3586f67fe9bde5f37c7ba1a3baf24f8
	
}uart_init_t;


/*UART handle structure*/
typedef struct{
	
	UART0_Type		*instance;			 		/*UART register base address*/
	uart_init_t		init;						/*UART communication initilization parameters*/
	uint8_t 		*pTxBuffer;					/*pointer to transmit buffer*/
	uint8_t			*pRxBuffer;					/*pointer to received buffer*/
	uint16_t 		txBufferSize;				/*transfer buffer size*/
	uint16_t		rxBufferSize;				/*received buffer size*/
	uart_state_t	rx_state;					/*uart communication current state*/
	uart_state_t	tx_state;					/*uart communication current state*/

}uart_handle_t;


/******************************************************************************/
/*                                                                            */
/*                       APIs to use UART                                     */
/*                                                                            */
/******************************************************************************/


/**
	* @brief  Initialized UART peripheral   
	* @param  *handle : pointer to the handle structure  
	* @retval None
	*/	
void hal_uart_init(uart_handle_t *handle);

/**
	* @brief  handles transmission of the data
	* @param  *uart_handle : pointer to the handle structure 
  * @param  *buffer : pointer to the TX buffer 
  * @param  len : length of the data
	* @retval None
	*/
void hal_uart_tx(uart_handle_t *handle, uint8_t *buffer, uint32_t len);

/**
	* @brief  handles reception of the data
	* @param  *uart_handle : pointer to the handle structure 
  * @param  *buffer : pointer to the RX buffer 
  * @param  len : length of the data
	* @retval None
	*/
void hal_uart_rx(uart_handle_t *handle, uint8_t *buffer, uint32_t len);

/**
  * @brief  handles various UART interrupt request.
  * @param  huart: pointer to a uart_handle_t structure
  * @retval None
  */
void hal_uart_handle_interrupt(uart_handle_t *handle);


#endif
