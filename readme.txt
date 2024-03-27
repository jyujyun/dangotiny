dangotiny library 

3shokudango(jyujyun)

2023/10/26

2023/10/28

2024/2/19

Github Page:https://github.com/jyujyun/dangoOLED
HomePage :https://3shokudango.web.fc2.com
Mail:jyujyun@aol.com

[EN]
===============================
This library can control 0.49" 64x32 SSD1306 OLED i2C.
Please note that the buffer consumes 256byte of RAM.


-functions
[!]Bitmap data must be save in PROGMEM.

*x:0~127 y:0~63
*bx:0~15 by:0~7
OLED.OLED_init() - Init SSD1306. Please run first.
OLED.OLED_clear() - Clear library buffer.
[!]This function is not clear SSD1306 screen. If you want to clear the device screen, run the send function after this function.
OLED.OLED_send() - Send the buffer data to 64x32 SSD1306.
OLED.OLED_send2x() - Send the buffer data to 128x64 SSD1306.
OLED.OLED_drawfill(64x32bmp) - Draw 128x64 bitmap to library buffer.
OLED.OLED_draw8(x,y,8x8bmp) - Draw 8x8 bitmap to library buffer.
OLED.OLED_setpixel(x,y,light) - Draw 1x1 dot to library buffer.
OLED.OLED_drawfill(128x64bmp) - Draw 128x64 bitmap.
OLED.OLED_draw8(x,y,8x8bmp) - Draw 8x8 bitmap.
OLED.OLED_setpixel(x,y,light) - Draw 1x1 dot.
light=1:on
light=0:off
OLED.OLED_line(x1,y1,x2,y2) - Draw a line to library buffer.
OLED.OLED_line(x1,y1,x2,y2) - Draw a line.
OLED.OLED_box(x1,y1,x2,y2) - Draw a wire-box.
OLED.OLED_fillbox(x1,y1,x2,y2,color) - Draw a box.
color=0:black
color=1:white
color=2:gray
OLED.OLED_char(bx,by,char) - Draw a char.
OLED.OLED_string(bx,by,String) - Draw a string.
OLED.OLED_num(bx,by,variable) - Draw a number.
OLED.OLED_drawbyte(bx,by,width,height,bitmap) - Draw a bitmap.
-ToDo list


[JP]
===============================
このライブラリはi2Cの64x32ドットのSSD1306 OLEDを制御できます。
RAMを256バイト消費するので注意してください。



-関数リスト
!注意!
ビットマップデータはPROGMEMに保存してください。

bx,byがある関数は座標を1バイト(8ドット)単位で指定する必要があります。
引数にx,yがある関数は座標を1ビット(1ドット)単位で指定できます。
OLED.OLED_init() - SSD1306を初期化する。最初に実行してください。
OLED.OLED_clear() - バッファーのデータを消す。
!注意!この関数はSSD1306の画面を消するわけではありません。消したい場合はこの後にOLED.OLED_send関数を実行してください。
OLED.OLED_send() - ライブラリ内のバッファーをSSD1306に送る。
OLED.OLED_send2x() - 128x64用のデーターをSSD1306に送る。
OLED.OLED_drawfill(128x64bmp) - 128x64のビットマップをバッファーに書き込む。
OLED.OLED_draw8(x,y,8x8bmp) - 8x8のビットマップをx,yの位置に書き込む。
OLED.OLED_setpixel(x,y,light) - x,yの位置に1ドットバッファーに書き込む。
OLED.OLED_drawfill(64x32bmp) - 128x64のビットマップを描く。
OLED.OLED_draw8(x,y,8x8bmp) - 8x8のビットマップをx,yの位置に描く。
OLED.OLED_setpixel(x,y,light) - x,yの位置に1ドット描く。
light=1:オン
light=0:オフ
OLED.OLED_line(x1,y1,x2,y2) - 線をバッファーに書き込む。
OLED.OLED_line(x1,y1,x2,y2) - 線を描く。
OLED.OLED_box(x1,y1,x2,y2) - 四角形を描く。中は塗りつぶされない。
OLED.OLED_fillbox(x1,y1,x2,y2,color) - 四角形を描く。中はcolorの色で塗りつぶされる。
color=0:くろ
color=1:しろ
color=2:しろとくろの市松模様
OLED.OLED_char(bx,by,char) - 1文字描く。
OLED.OLED_string(bx,by,String) - 文字列を描く。
OLED.OLED_num(bx,by,variable) - 数値を描く。
OLED.OLED_drawbyte(bx,by,width,height,bitmap) - ビットマップを書く。
-追加予定の機能
文字列の描写

-更新履歴-
2024/2/19 前のライブラリからの移植完了
2024/3/27 ピン用の定義追加
