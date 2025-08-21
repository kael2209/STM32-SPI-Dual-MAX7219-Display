#include "main.h"

int main(void)
{
	systick_init();
	max7219A_init();
	max7219B_init();
	
	max7219A_clear();
	max7219B_clear();
	delay(500);
	
	while(1)
	{
//		max7219_loop();
		max7219B_display_number_dot("AA22.09.AA");
		max7219A_displayHeart();
	}
}

