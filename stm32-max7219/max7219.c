#include "spi.h"
#include "max7219.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include "systick_time.h"

void max7219A_init(void)
{
	spi_start(1);
	spi_writereg8(1,MAX7219_REG_DECODE_MODE,MAX7219_DECODE_NONE);
	spi_writereg8(1,MAX7219_REG_INTENSITY,0x0F);
	spi_writereg8(1,MAX7219_REG_SCAN_LIMIT,0x07);
	spi_writereg8(1,MAX7219_REG_SHUTDOWN,MAX7219_SHUTDOWN_ON);
	spi_writereg8(1,MAX7219_REG_DISPLAY_TEST,0);
}
void max7219A_display(char letter)
{
	for (char i=0;i<8;i++)
	{
		spi_writereg8(1, i+1,ASCII[letter-32][i]); 
	}
}
void max7219A_displayFrame(uint8_t frame[8])
{
    for (uint8_t i = 0; i < 8; i++)
    {
        spi_writereg8(1, i + 1, frame[i]);
    }
}
void max7219A_clear(void)														
{
		uint8_t blank[8]={0};
    for (uint8_t i = 0; i < 8; i++)
    {
        spi_writereg8(1, i + 1, blank[i]);
    }
}

void max7219A_scrollText(const char *text, uint32_t delay_ms)		// Cuon chu
{
    uint8_t buffer[8] = {0};

    for (uint16_t t = 0; text[t] != '\0'; t++)
    {
        uint8_t index = text[t] - 32;
        for (uint8_t shift = 0; shift < 8; shift++)
        {
            for (uint8_t row = 0; row < 8; row++)
            {
                buffer[row] <<= 1;
                if (ASCII[index][row] & (0x80 >> shift))
                {
                    buffer[row] |= 0x01;
                }
            }

            max7219A_displayFrame(buffer);
            delay(delay_ms);
        }
        
        for (uint8_t space = 0; space < 2; space++)
        {
            for (uint8_t row = 0; row < 8; row++)
            {
                buffer[row] <<= 1;
            }
            max7219A_displayFrame(buffer);
            delay(delay_ms);
        }
    }
}

void max7219A_displayHeart()																// Hien thi trai tim
{
    for (uint8_t i = 0; i < 8; i++)
    {
        spi_writereg8(1, i + 1, heart[i]);
    }
}
void max7219A_displayHeartHalf()																// Hien thi trai tim
{
    for (uint8_t i = 0; i < 8; i++)
    {
        spi_writereg8(1, i + 1, heart_half[i]);
    }
}
void max7219A_blinkHeart(uint8_t times, uint32_t delay_ms)			// Nhap nhay trai time, so lan, khoang delay
{
    for (uint8_t t = 0; t < times; t++)
    {
        max7219A_displayHeart();    // B?t
				delay(delay_ms);

				max7219A_displayHeartHalf();
        delay(delay_ms);
    }
}
void max7219A_start(uint16_t delay_ms)
{
	for (char j=0;j<8;j++)
	{
		for (char i=0;i<8;i++)
		{
			spi_writereg8(1, i+1,heart_start[j][i]); 
		}
		delay(delay_ms);
	}
}
void max7219A_end(uint16_t delay_ms)
{
	for (char j=0;j<8;j++)
	{
		for (char i=0;i<8;i++)
		{
			spi_writereg8(1, i+1,heart_start[7-j][i]); 
		}
		delay(delay_ms);
	}
}

void max7219A_waveEffect(uint32_t delay_ms)			// Hieu ung song
{
    uint8_t wave[8];
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // Di chuy?n sóng (trái sang ph?i)
            wave[j] = (1 << ((i + j) % 8));
        }
        
        max7219A_displayFrame(wave);  // Hi?n th? sóng
        delay(delay_ms);  // Ð?i gi?a m?i bu?c
    }
}

void max7219A_waterDropEffect(uint32_t delay_ms)
{
    uint8_t drop[8] = {0};
    
    for (int i = 0; i < 8; i++)
    {
        drop[i] = 0xFF;  // Hi?n th? gi?t nu?c
        max7219A_displayFrame(drop);  // Hi?n th? hi?u ?ng mua
        delay(delay_ms);  // Ð?i gi?a m?i bu?c
        drop[i] = 0;  // Làm gi?t nu?c bi?n m?t
    }
}
void max7219A_intensity(uint8_t state, uint16_t delay_ms)
{
	if (state==1)
	{
		spi_writereg8(2, 0x0A, 0);
		for (int i=2;i<15;i++)
		{
			spi_writereg8(2, 0x0A, i);
			delay(delay_ms);
		}
	}
	else if (state==0)
	{
		spi_writereg8(2, 0x0A,0x0F);
		for (int i=15;i>0;i--)
		{
			spi_writereg8(2, 0x0A, i);
			delay(delay_ms);
		}
	}
}
void max7219A_confess(void)
{
	max7219A_start(100);
		max7219A_clear();
		delay(500);
		
		max7219A_display('K');
		delay(500);
		max7219A_display('A');
		delay(500);
		max7219A_display('E');
		delay(500);
		max7219A_display('L');
		delay(500);
		
		max7219A_scrollText("I LOVE YOU SO MUCH ",80);
		max7219A_clear();
		delay(200);
		
		for (volatile int i=0;i<10;i++)
		{
			max7219A_waveEffect(50);
		}
		max7219A_clear();
		delay(200);
		
		max7219A_blinkHeart(2,300);
		max7219A_clear();
		delay(200);
		
		for (volatile int i=0;i<10;i++)
		{
			max7219A_waterDropEffect(50);
		}
		max7219A_clear();
		delay(200);
		
		max7219A_end(200);
		max7219A_clear();
		delay(2000);
}











void max7219B_init(void)
{
	spi_start(2);
	spi_writereg8(2,MAX7219_REG_DECODE_MODE,MAX7219_DECODE_ALL);
	spi_writereg8(2,MAX7219_REG_INTENSITY,0x0F);
	spi_writereg8(2,MAX7219_REG_SCAN_LIMIT,0x07);
	spi_writereg8(2,MAX7219_REG_SHUTDOWN,MAX7219_SHUTDOWN_ON);
	spi_writereg8(2,MAX7219_REG_DISPLAY_TEST,0);
}
void max7219B_pos_num(uint8_t pos, uint8_t number)
{
	spi_writereg8(2,pos+1,number);
}
void rotate_right_special(char str[]) 
{
    int len = strlen(str);
    if (len == 0) return;

    int move_len = 1; // m?c d?nh d?ch 1 ký t?

    // N?u ký t? cu?i cùng là '.' thì ph?i kèm theo s? tru?c dó
    if (len > 1 && str[len - 1] == '.') {
        move_len = 2;
    }

    char temp[3]; // luu t?m nhóm c?n di chuy?n
    temp[move_len] = '\0'; // k?t thúc chu?i t?m

    if (move_len == 1) {
        temp[0] = str[len - 1];
    } else { // move_len == 2
        temp[0] = str[len - 2];
        temp[1] = str[len - 1];
    }

    // D?ch toàn b? chu?i sang ph?i move_len v? trí
    for (int i = len - 1; i >= move_len; i--) {
        str[i] = str[i - move_len];
    }

    // Ð?t temp vào d?u chu?i
    for (int i = 0; i < move_len; i++) {
        str[i] = temp[i];
    }
}
void max7219B_display_number_dot(char str[])	
{
	int i=0,j=0;
	while(str[i])
	{
		char number = str[i];
		if (str[i] == 'A')
		{
			spi_writereg8(2,8-j,10);
			i++;
			j++;
		}
		else if (str[i]!= '.')
		{
			spi_writereg8(2,8-j,(int)(str[i]));
			i++;
			j++;
		}
		else
		{
			spi_writereg8(2,8-j+1,((int)(str[i-1]))|(1<<7));	 
			i++;
		}
	}
	//rotate_right_special(str);
}
void max7219B_clear(void)
{
	for (char i=0;i<8;i++)
	{
		max7219B_pos_num(i,0xF);
	}
}
void max7219B_array_display(uint8_t* data)
{
	for (char i=0;i<8;i++)
	{
		max7219B_pos_num(7-i,*data++);
	}
	
}
void max7219B_array_display_undersocre()
{
	uint8_t score[]={10,10,10,10,10,10,10,10};
	for (char i=0;i<8;i++)
	{
		max7219B_pos_num(7-i,score[i]);
	}
	
}
void max7219B_intensity(uint8_t state, uint16_t delay_ms)
{
	if (state==1)
	{
		spi_writereg8(2, 0x0A, 0);
		for (int i=2;i<15;i++)
		{
			spi_writereg8(2, 0x0A, i);
			delay(delay_ms);
		}
	}
	else if (state==0)
	{
		spi_writereg8(2, 0x0A,0x0F);
		for (int i=15;i>0;i--)
		{
			spi_writereg8(2, 0x0A, i);
			delay(delay_ms);
		}
	}
}
void max7219B_apper_underscore_start()
{
	for (int j=0;j<5;j++)
	{
		for (int i=0;i<8;i++)
		{
			spi_writereg8(2, 0x01+i, score_array_start[j][i]);
		}
		delay(200);
	}
}
void max7219B_apper_underscore_end()
{
	for (int j=0;j<5;j++)
	{
		for (int i=0;i<8;i++)
		{
			spi_writereg8(2, 0x01+i, score_array_end[j][i]);
		}
		delay(200);
	}
}


