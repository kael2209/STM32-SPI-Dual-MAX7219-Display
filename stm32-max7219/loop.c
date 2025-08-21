#include "loop.h"
#include "max7219.h"
#include "spi.h"
#include "systick_time.h"

void max7219_loop(void)
{
	spi_writereg8(2,MAX7219_REG_INTENSITY,0x0F);
	max7219A_start(100);
	max7219A_clear();

	max7219B_apper_underscore_start();
	max7219B_clear();
	delay(800);
	
	max7219A_display('L');
	max7219B_display_number_dot("AAAAAAAA");
	delay(300);
	max7219B_clear();
	delay(300);
	
	max7219A_display('P');
	max7219B_display_number_dot("AAAAAAAA");
	delay(300);
	max7219B_clear();
	delay(300);
			
	max7219A_display('T');
	max7219B_display_number_dot("AA22.09.AA");
	delay(1000);

	max7219A_scrollText("ILOVEYOU! ",100);
	max7219A_clear();
	delay(700);
	
	for (volatile int i=0;i<7;i++)
	{
		max7219A_waveEffect(50);
	}
	max7219A_clear();
	delay(800);
	
	max7219A_blinkHeart(10,150);
	max7219A_clear();
	delay(800);
	
	for (volatile int i=0;i<5;i++)
	{
		max7219A_waterDropEffect(50);
	}
	max7219A_clear();
	delay(800);
	
	max7219B_apper_underscore_end();
	max7219B_clear();
	max7219A_end(150);
	max7219A_clear();
	
	delay(2500);
}