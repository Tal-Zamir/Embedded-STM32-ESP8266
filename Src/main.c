#include <stdio.h>
#include "stm32f4xx.h"
#include "esp82xx_driver.h"
#include "fifo.h"
#include "circular_buffer.h"

int result;

int main()
{
	char main_str[] = "Homework";
	char str_to_find[] = "Homet";

	result = find_str(str_to_find, main_str);
	while(1)
	{

	}

}
