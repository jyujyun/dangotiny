/*
dangotinyライブラリ

3shokudang(jyujyun)
2023/10/25

参考にしたもの:
mgo-tec電子工作 https://www.mgo-tec.com/
SSD1306xledライブラリ https://bitbucket.org/tinusaur/ssd1306xled
Adafruit OLED ライブラリ https://github.com/adafruit/Adafruit_SSD1306

使用した素材:
ひらがなフォント https://littlelimit.net/misaki.htm
ありがとうございます。 Thank you!
*/

#include <Wire.h>
//#include <avr/pgmspace.h>

#include "dangotiny.h"
#include "font.h"
#include "nums.h"
dangotiny::dangotiny(void){}

void dangotiny::OLED_init(void)
{

	OLED_clear();
	syoki();
	
	OLED_send();

	
}
void dangotiny::OLED_clear(void)
{
	for (int i = 0;i < 256;i++)
	{
		OLED_buff[i] = 0x00;
	}
}
void dangotiny::OLED_drawfill(const uint8_t  bmp[])
{
	uint16_t j = 0;
	for (int i = 0;i < 256;i++)
	{
		OLED_buff[i] = pgm_read_byte(&bmp[j++]);
	}
}
void dangotiny::OLED_fill(char dat)
{
	for (int i = 0;i < 256;i++)
	{
		OLED_buff[i] = dat;
	}
}
//バイト
void dangotiny::OLED_draw8(char dx,char dy,const uint8_t  bmp[])
{

		char j = 0;
		char hy = (dy / 8);
		char tmp_buff = 0x00;
		for (int i = 0;i < 8;i++)
		{
			if (dx + i >= 0 && dx + i < 63)
			{
				tmp_buff = OLED_buff[(dx + (hy * 64)) + i];
				OLED_buff[(dx + (hy * 64)) + i] = ((tmp_buff & (0xFF >> (8 - (dy % 8)))) + ((pgm_read_byte(&bmp[j])) << dy % 8));
			}
			j++;
		}
		j = 0;
		for (int i = 0;i < 8;i++)
		{
			if (dx + i >= 0 && dx + i < 63)
			{
				tmp_buff = OLED_buff[(dx + ((hy + 1) * 64)) + i];
				OLED_buff[(dx + ((hy + 1) * 64)) + i] = ((tmp_buff & (0xFF << ((dy % 8)))) + ((pgm_read_byte(&bmp[j])) >> (8 - (dy % 8))));
			}
			j++;
		}

}
//ニブル バグる!
void dangotiny::OLED_draw4(char dx,char dy,const uint8_t  bmp[])
{
	char j = 0;
	char hy = (dy / 8);
	char tmp_buff = 0x00;

	for(char i=0;i<4;i++)
	{
		tmp_buff = OLED_buff[dx + (hy * 64)+i];
		tmp_buff &= ~(0x11110000 >> (4 - (dy % 8)));
		tmp_buff |= ((pgm_read_byte(&bmp[j]) << 4) >> (4 - (dy % 8)));
		OLED_buff[dx + (hy * 64)+i] = tmp_buff;
		j++;
	}
	j = 0;
	hy += 1;
	if (dy % 8 > 4)
	{
		for(char i=0;i<4;i++)
		{
			tmp_buff = OLED_buff[dx + (hy * 64)+i];
			tmp_buff &= ~(0x11110000 >> ( (dy % 8)));
			tmp_buff |= ((pgm_read_byte(&bmp[j]) << 4) >> ((dy % 8)));
			OLED_buff[dx + (hy * 64)+i] = tmp_buff;
			j++;
		}
	}

}
void dangotiny::OLED_pixel(char dx, char dy, char po)
{
	if (dx < 0 || dx > 63 || dy < 0 || dy > 31)
	{

	}
	else
	{
		char tmp_buff = 0x00;
		char y1 = dy / 8;
		if (po == 0)
		{
			tmp_buff = OLED_buff[(dx + (y1 * 64))] & ~(0b00000001 << (dy % 8));
		}
		if (po == 1)
		{
			tmp_buff = OLED_buff[(dx + (y1 * 64))] | (0b00000001 << (dy % 8));
		}
		OLED_buff[(dx + (y1 * 64))] = tmp_buff;

	}
}
void dangotiny::OLED_line(char x1, char y1, char x2, char y2) 
{
  char dx = abs(x2-x1), sx = x1<x2 ? 1 : -1;
  char dy = abs(y2-y1), sy = y1<y2 ? 1 : -1;
  char err = (dx>dy ? dx : -dy)/2, e2;
  for(;;){
     OLED_pixel(x1,y1,1);
     if (x1==x2 && y1==y2) break;
     e2 = err;
     if (e2 >-dx) { err -= dy; x1 += sx; }
     if (e2 < dy) { err += dx;y1 += sy; }
  }
}
void dangotiny::OLED_drawbyte(int dx, char dy, int dw, char dh, const uint8_t  bmp[])
{
	dx *= 8;
	dw *= 8;
	int k = 0;
	for (int j = dy; j < (dh + dy ); j++)
	{
		for (int i = dx; i < (dw + dx); i++)
		{
			OLED_buff[(j * 64) + i] = pgm_read_byte(&bmp[k]);
			k+=1;
		}
	}


}
void dangotiny::OLED_box(char x1, char y1, char x2, char y2)
{
	for (char i = x1; i <= x2; i++)
	{
		OLED.OLED_pixel(i, y1,1);
		OLED.OLED_pixel(i, y2, 1);
	}
	for (char i = y1; i <= y2; i++)
	{
		OLED.OLED_pixel(x1, i, 1);
		OLED.OLED_pixel(x2, i, 1);
	}
}
void dangotiny::OLED_fillbox(int x1, char y1, int x2, char y2,char color)
{
	//color
	//0 black
	//1 white
	//2 gray
	if (color == 0)
	{
		for (int i = x1;i <= x2;i++)
		{
			for (char j = y1;j <= y2;j++)
			{
				if (i == x1 || i == x2 || j == y1 || j == y2)
				{
					OLED.OLED_pixel(i, j, 1);
				}
				else
				{
					OLED.OLED_pixel(i, j, 0);
				}

			}
		}
	}
	else if (color == 1)
	{
		for (int i = x1;i <= x2;i++)
		{
			for (char j = y1;j <= y2;j++)
			{

				OLED.OLED_pixel(i, j, 1);
			}
		}
	}
	else if (color == 2)
	{
		for (int i = x1;i <= x2;i++)
		{
			for (char j = y1;j <= y2;j++)
			{
				if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
				{
					OLED.OLED_pixel(i, j, 1);
				}
				else
				{
					OLED.OLED_pixel(i, j, 0);
				}
			}
		}
	}

}

#ifdef __AVR__
void dangotiny::OLED_char(char dx, char dy,uint16_t ch,char color = 0) {
	
	dx *= 8;
	if (ch < 300)
	{
		ch -= 32;
		for (char i = 0; i < 6; i++)
		{
			if (color == 0)
			{
				OLED_buff[(dy * 64) + dx + i] = pgm_read_byte(&font8[ch * 6 + i]);
			}
			else
			{
				OLED_buff[(dy * 64) + dx + i] = ~(pgm_read_byte(&font8[ch * 6 + i]));
			}
			OLED_buff[(dy * 64) + dx + 6] = 0xFF * color;
			OLED_buff[(dy * 64) + dx + 7] = 0xFF * color;
		}
	}

}
void dangotiny::OLED_string(char dx, char dy,char* str,char color = 0) 
{
	while (*str) {
		OLED_char(dx++,dy,*str++,color);
	}
}
void dangotiny::OLED_num(char dx,char dy,int num,char color = 0)
{
	char pp = 0;
	if (((num / 10000) % 10) > 0)
	{
		pp = 1;
		OLED_char_num(dx++,dy,((num / 10000) % 10),color);
	}
	if (((num / 1000) % 10) > 0 || pp == 1)
	{
		pp = 1;
		OLED_char_num(dx++,dy,((num / 1000) % 10),color);
	}
	if (((num / 100) % 10) > 0 || pp == 1)
	{
		pp = 1;
		OLED_char_num(dx++,dy,((num / 100) % 10),color);
	}
	if (((num / 10) % 10) > 0 || pp == 1)
	{
		pp = 1;
		OLED_char_num(dx++,dy,((num / 10) % 10),color);
	}
	OLED_char_num(dx++,dy,((num / 1) % 10),color);
}
void dangotiny::OLED_char_num(char dx, char dy,char ch,char color = 0)
{
	dx *= 8;
	for (char i = 0; i < 6; i++)
	{
		if (color == 0)
		{
			OLED_buff[(dy * 64) + dx + i] = pgm_read_byte(&font8_number[ch * 6 + i]);
		}
		else
		{
			OLED_buff[(dy * 64) + dx + i] = ~(pgm_read_byte(&font8_number[ch * 6 + i]));
		}
		OLED_buff[(dy * 64) + dx + 6] = 0xFF * color;
		OLED_buff[(dy * 64) + dx + 7] = 0xFF * color;
	}
}
#endif
void dangotiny::OLED_char4(char dx, char dy, char ch) {
  for (char i = 0; i < 4; i++) {
    OLED.OLED_buff[64 * dy + dx * 4 + i] = pgm_read_byte(&font4[ch][i]);
  }
}
void dangotiny::OLED_string4(char dx, char dy, char* str)
{
	while (*str) {
		OLED_char4(dx++,dy,*str++);
	}
}
void dangotiny::OLED_num4(char dx,char dy,int num)
{
	char pp = 0;
	if (((num / 10000) % 10) > 0)
	{
		pp = 1;
		OLED_char4(dx++,dy,((num / 10000) % 10)+48);
	}
	if (((num / 1000) % 10) > 0 || pp == 1)
	{
		pp = 1;
		OLED_char4(dx++,dy,((num / 1000) % 10)+48);
	}
	if (((num / 100) % 10) > 0 || pp == 1)
	{
		pp = 1;
		OLED_char4(dx++,dy,((num / 100) % 10)+48);
	}
	if (((num / 10) % 10) > 0 || pp == 1)
	{
		pp = 1;
		OLED_char4(dx++,dy,((num / 10) % 10)+48);
	}
	OLED_char4(dx++,dy,((num / 1) % 10)+48);
}


void dangotiny::OLED_send()
{


	uint8_t i, j, k;
	int l = 0;
	for(i = 4; i < 8; i++)
	{
		Wire.beginTransmission(OLED_ADD);
		Wire.write(0x80);
		Wire.write(0xB0 | i);
		//Wire.write(0x00);

/*
		Wire.write(0x21);
		Wire.write(0);
		Wire.write(63);		
		
		Wire.write(0x22);
		Wire.write(0);
		Wire.write(3);
*/

		Wire.endTransmission();
	
		for(j = 0; j < 8; j++)
		{
		Wire.beginTransmission(OLED_ADD);
			Wire.write(0x5F);
			for(k = 0; k < 8; k++)
			{
				Wire.write(OLED_buff[l++]);
			}
		Wire.endTransmission();
		}
	}
}
void dangotiny::OLED_send2x(void)
{


	uint8_t i, j, k;
	int l = 0;
	char tmpb = 0x00;

	char tmpx = 0;
	char tmpy = 0;

	char tmpc = 0x00;
	for(i = 0; i < 8; i++)
	{
		Wire.beginTransmission(OLED_ADD);
		Wire.write(0x80);
			Wire.write(0xB0 | i);
		Wire.write(0x00);
			Wire.write(0x21);
			Wire.write(0);
			Wire.write(127);
		Wire.endTransmission();
			if (i < 2)
		{
			l = 0;
		}
		else if (i < 4)
		{
			l = 1 * 64;
		}
		else if (i < 6)
		{
			l = 2 * 64;
		}
		else if (i < 8)
		{
			l = 3 * 64;
		}
		for(j = 0; j < 16; j++)
		{
		Wire.beginTransmission(OLED_ADD);
			Wire.write(0b01000000);
			tmpx = 0;
			for(k = 0; k < 8; k++)
			{
				tmpc = 0x00;
				tmpc = OLED_buff[l];
				tmpb = 0x00;
				if (i % 2 == 0)
				{
					tmpc &= 0b00001111;

					for (char m=0;m<4;m++)
					{
						tmpb |= (tmpc & ((0b00000001) << m)) << (m);
						
						tmpb |= (tmpc & ((0b00000001) << m)) << (m + 1);
						//tmpb |= (tmpc << m*2);
						//tmpb |= (tmpc << (m*2 + 1));
					}
				}
				else
				{
					tmpc &= 0b11110000;
					tmpc = tmpc >> 4;
					for (char m=0;m<4;m++)
					{
						tmpb |= (tmpc & ((0b00000001) << m)) << (m);
						
						tmpb |= (tmpc & ((0b00000001) << m)) << (m + 1);
					}
				}
				tmpx += 1;
				Wire.write(tmpb);
				if (tmpx % 2 == 0)
				{
					l++;
				}
			}
			Wire.endTransmission();
		}

	}
}
void dangotiny::syoki(void)

{

	#ifdef __AVR__
		Wire.begin();
	#elif defined(ESP8266) || defined(ESP32)
		Wire.begin(16,17);
	#elif defined(ARDUINO_RASPBERRY_PI_PICO)
		Wire.begin();
	#else
		Wire.begin();
	#endif
	Wire.setClock(400000);
	
	delay(100);
		
	Wire.beginTransmission(OLED_ADD);
	Wire.write(0x80);
	Wire.write(0xAE);
    Wire.write(0x00);
	Wire.write(0xA8);
	Wire.write(0b00111111);
    Wire.write(0x00);
	Wire.write(0xD3);
	Wire.write(0x00);
    Wire.write(0x80);
	Wire.write(0x40);
    Wire.write(0x80);
	Wire.write(0xA1);
    Wire.write(0x80);
	Wire.write(0xC8);
    Wire.write(0x00);
	Wire.write(0xDA);
	Wire.write(0b00010010);
    Wire.write(0x00);
	Wire.write(0x81);
	Wire.write(255);
    Wire.write(0x80);
	Wire.write(0xA4);
    Wire.write(0x00);
	Wire.write(0xA6);
    Wire.write(0x00);
	Wire.write(0xD5);
	Wire.write(0x80);
    Wire.write(0x00);
	Wire.write(0x20);
	Wire.write(0x10);
  	Wire.endTransmission();

  	Wire.beginTransmission(OLED_ADD);
    Wire.write(0x00);
	Wire.write(0x22);
	Wire.write(0);
	Wire.write(3); 
    Wire.write(0x00);
	Wire.write(0x21);
	Wire.write(32);
	Wire.write(95);
    Wire.write(0x00);
	Wire.write(0x8D);
	Wire.write(0x14);
    Wire.write(0x80);
	Wire.write(0xAF);
	Wire.endTransmission();
}

dangotiny OLED;
// ----------------------------------------------------------------------------
