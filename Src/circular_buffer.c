#include "circular_buffer.h"
#include <string.h>

#define CR1_RXNEIE	 (1U<<5); // ... 0001 0000

portType debug_port   =	 0;
portType esp82xx_port =	 1;

/*Buffers for ESP_UART*/
circular_buffer rx_buffer1 = {{INIT_VAL},INIT_VAL,INIT_VAL};
circular_buffer tx_buffer1 = {{INIT_VAL},INIT_VAL,INIT_VAL};

/*Buffers for DEBUG_UART*/
circular_buffer rx_buffer2 = {{INIT_VAL},INIT_VAL,INIT_VAL};
circular_buffer tx_buffer2 = {{INIT_VAL},INIT_VAL,INIT_VAL};

circular_buffer *_rx_buffer1;
circular_buffer *_tx_buffer1;
circular_buffer *_rx_buffer2;
circular_buffer *_tx_buffer2;

void circular_buffer_init(void)
{
	/*Initial buffers*/
	_rx_buffer1 = &rx_buffer1;
	_tx_buffer1 = &tx_buffer1;
	_rx_buffer2 = &rx_buffer2;
	_tx_buffer2 = &tx_buffer2;

	/*Initial UART interrupts*/
	//reference data sheet usart_cr1->rxneIE (Interrupt Enable) check if rx buffer is empty or not
	USART1->CR1 |= CR1_RXNEIE; 		/*esp_uart*/
	USART1->CR1 |= CR1_RXNEIE; 		/*debug_uart*/
}

static void buff_store_char(unsigned char c, circular_buffer * buffer)
{
	 int loc =  (uint32_t)(buffer->head +1)% UART_BUFFER_SIZE;

	/*Check if no overflow will occur*/

	 if(loc != buffer->tail){
		 /*Store character*/
		 buffer->buffer[buffer->head]  = c ;
		 /*Update head*/
		 buffer->head = loc;
	 }
}

/*Find a substring within a string*/
int8_t find_str(char *str2, char *str1)
{
	int l,i,j;

	/*Count substring i.r str2*/
	for(l=0; str2[l] != '\0'; l++){}

	for(i=0, j=0; str1[i] !='\0' && str2[j] != '\0'; i++)
	{
		if(str1[i] == str2[j])
		{
			j++;
		}
		else
		{
			j=0;
		}
	}
		if(j ==l)
		{
			/*Success*/
			return 1;
		}
		else
		{
			return -1;
		}
}

/*clearing the buffer*/
void buffer_clear(portType uart)
{
	if (uart == esp82xx_port)
	{
		/*Set buffer content to '0\'*/
		memset(_rx_buffer1->buffer,'\0',UART_BUFFER_SIZE);
		_rx_buffer1->head = 0;
	}
	if (uart == debug_port)
		{
			/*Set buffer content to '0\'*/
			memset(_rx_buffer2->buffer,'\0',UART_BUFFER_SIZE);
			_rx_buffer2->head = 0;
		}
}

/*Checking what is in the buffer tail*/
int32_t buffer_peek(portType uart)
{
	if(uart == esp82xx_port )
	{
	   if(_rx_buffer1->head  ==  _rx_buffer1->tail)
	   {
		   return -1;
	   }
	   else
	   {
		   return _rx_buffer1->buffer[_rx_buffer1->tail];
	   }
	}

	else if(uart == debug_port )
	{
	   if(_rx_buffer2->head  ==  _rx_buffer2->tail)
	   {
		   return -1;
	   }
	   else
	   {
		   return _rx_buffer2->buffer[_rx_buffer2->tail];
	   }
	}

	else
	{
		 return -1;
	}
}

/*Reading data from the buffer*/
int32_t buffer_read(portType uart)
{
	if(uart == esp82xx_port )
	{
		   if(_rx_buffer1->head  ==  _rx_buffer1->tail)
			   {
				   return -1;
			   }
		   else
		   {
			  unsigned char c =  _rx_buffer1->buffer[_rx_buffer1->tail];
			  _rx_buffer1->tail =  (uint32_t)(_rx_buffer1->tail +1)%UART_BUFFER_SIZE;

			  return c;
		   }
	}

	else if(uart == debug_port )
	{
		   if(_rx_buffer2->head  ==  _rx_buffer2->tail)
			 {
				   return -1;
			 }
		   else
		   {
				  unsigned char c =  _rx_buffer2->buffer[_rx_buffer2->tail];
				  _rx_buffer2->tail =  (uint32_t)(_rx_buffer2->tail +1)%UART_BUFFER_SIZE;
				  return c;

		   }
	}

	else
	{
		 return -1;
	}
}


