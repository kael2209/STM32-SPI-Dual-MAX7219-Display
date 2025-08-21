#include "stm32f10x.h"      
#include "max7219.h"
#include "systick_time.h"
#include "spi.h"
#include "loop.h"

/*
	SPI1: Led matrix
		PA4:	CS
		PA5:	CLK
		PA6:	
		PA7:	DIN	
		
	SPI2: 	Led 7 segment
		PB12:	CS
		PB13:	CLK
		PB14:	
		PB15:	DIN	
*/


