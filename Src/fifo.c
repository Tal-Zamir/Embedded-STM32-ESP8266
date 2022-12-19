#include "fifo.h"

#define TXFIFOSIZE 1024
#define RXFIFOSIZE 1024
#define TXFAIL	   0
#define TXSUCCESS  1
#define RXFAIL	   0
#define RXSUCCESS  1

tx_dataType static TX_FIFO[TXFIFOSIZE];
rx_dataType static RX_FIFO[RXFIFOSIZE];

//volatile variable tell the compiler the value of the variable might be change during code run by some external source to avoid assiment into this variable
uint32_t volatile tx_put_itr;
uint32_t volatile tx_get_itr;
uint32_t volatile rx_put_itr;
uint32_t volatile rx_get_itr;

/*Initialize Tx FIFO to contain to outgoing data*/
void tx_fifo_init(void)
{
	tx_put_itr = 0;
	tx_get_itr = 0;
}

/*Put data into tx fifo*/
uint8_t tx_fifo_put (tx_dataType data)
{
	/*Check if fifo is full*/
	if((tx_put_itr - tx_get_itr) & ~ (TXFIFOSIZE-1))
	{
		//FIFO is full
		return(TXFAIL);
	}
	//if the fifo is not full then hold data in the fifo array
	TX_FIFO[tx_put_itr & (TXFIFOSIZE -1)] = data; // The current free location at the array
	//Increment itr
	tx_put_itr++;
	return(TXSUCCESS);
}

uint8_t tx_fifo_get(tx_dataType *pdata)
{
	/*Check if FIFO is empty*/
	if(tx_put_itr == tx_get_itr)
	{
		//FIFO is empty
		return(TXFAIL);
	}
	/* if not empty then Get the data*/
	*pdata	=	TX_FIFO[tx_get_itr & (TXFIFOSIZE -1)];
	//Increment the itr
	tx_get_itr++;
	return(TXSUCCESS);
}

uint32_t tx_fifo_size(void)
{
	return (uint32_t)(tx_put_itr - tx_get_itr);
}


#include "fifo.h"

#define RXFIFOSIZE 1024
#define RXFIFOSIZE 1024
#define RXFAIL	   0
#define RXSUCCESS  1
#define RXFAIL	   0
#define RXSUCCESS  1

rx_dataType static RX_FIFO[RXFIFOSIZE];
rx_dataType static RX_FIFO[RXFIFOSIZE];

//volatile variable tell the compilar the value of the variable might be change during code run by some external source to avoid assiment into this variable
uint32_t volatile rx_put_itr;
uint32_t volatile rx_get_itr;
uint32_t volatile rx_put_itr;
uint32_t volatile rx_get_itr;

/*Initialize rx FIFO to contain to outgoing data*/
void rx_fifo_init(void)
{
	rx_put_itr = 0;
	rx_get_itr = 0;
}

/*Put data into rx fifo*/
uint8_t rx_fifo_put (rx_dataType data)
{
	/*Check if fifo is full*/
	if((rx_put_itr - rx_get_itr) & ~ (RXFIFOSIZE-1))
	{
		//FIFO is full
		return(RXFAIL);
	}
	//if the fifo is not full then hold data in the fifo array
	RX_FIFO[rx_put_itr & (RXFIFOSIZE -1)] = data; // The current free location at the array
	//Increment itr
	rx_put_itr++;
	return(RXSUCCESS);
}

uint8_t rx_fifo_get(rx_dataType *pdata)
{
	/*Check if FIFO is empty*/
	if(rx_put_itr == rx_get_itr)
	{
		//FIFO is empty
		return(RXFAIL);
	}
	/* if not empty then Get the data*/
	*pdata	=	RX_FIFO[rx_get_itr & (RXFIFOSIZE -1)];
	//Increment the itr
	rx_get_itr++;
	return(RXSUCCESS);
}

uint32_t rx_fifo_size(void)
{
	return (uint32_t)(rx_put_itr - rx_get_itr);
}




