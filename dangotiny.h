/*
dangotinyライブラリ

3shokudang(jyujyun)
2023/12/9

参考にしたもの:
mgo-tec電子工作 https://www.mgo-tec.com/
SSD1306xledライブラリ https://bitbucket.org/tinusaur/ssd1306xled
Adafruit OLED ライブラリ https://github.com/adafruit/Adafruit_SSD1306

ありがとうございます。 Thank you!

*/


#include <Arduino.h>



#ifndef DANGOTINY_H
#define DANGOTINY_H

#ifdef __AVR__

#define PIN_LEFT 9
#define PIN_UP 10
#define PIN_RIGHT 7
#define PIN_DOWN 8
#define PIN_A 5

#elif defined(ARDUINO_RASPBERRY_PI_PICO)

#define PIN_LEFT 9
#define PIN_UP 10
#define PIN_RIGHT 7
#define PIN_DOWN 8
#define PIN_A 6

#else

#define PIN_LEFT 9
#define PIN_UP 10
#define PIN_RIGHT 7
#define PIN_DOWN 8
#define PIN_A 5

#endif

class dangotiny
{
	public:
		dangotiny(void);
		char OLED_ADD = 0x3C;
		char OLED_buff [256];

		void OLED_init(void);
		void OLED_fill(char dat);
		void OLED_clear(void);
		void OLED_drawfill(const uint8_t  bmp[]);
		void OLED_draw8(char dx,char dy,const uint8_t  bmp[]);
		void OLED_draw4(char dx,char dy,const uint8_t  bmp[]);
		void OLED_send(void);
		void OLED_send2x(void);
		void OLED_pixel(char dx, char dy, char po);
		void OLED_line(char x1, char y1, char x2, char y2);
		#ifdef __AVR__
		void OLED_num(char dx,char dy,int num,char color);
		void OLED_char_num(char dx, char dy,char ch,char color);
		void OLED_char(char dx, char dy,uint16_t ch,char color);
		void OLED_string(char dx, char dy,char* str,char color); 

		#endif
		void OLED_num4(char dx,char dy,int num);
		void OLED_char4(char dx, char dy,char ch);
		void OLED_string4(char dx, char dy,char* str); 
		void OLED_box(char x1, char y1, char x2, char y2);
		void OLED_fillbox(int x1, char y1, int x2, char y2,char color);
		void OLED_drawbyte(int dx, char dy, int dw, char dh, const uint8_t  bmp[]);
		//void tess(void);
		void syoki(void);
};
/*
class dangotiny_board
{
	public:
		dangotiny_board(void);
		char LEFT = 0;
		char RIGHT = 0;
		char UP = 0;
		char DOWN = 0;

		char LEFT = 0;
};
extern dangotiny_board button;
*/
extern dangotiny OLED;
#endif