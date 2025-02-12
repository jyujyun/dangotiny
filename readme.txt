Dangotinyマニュアル
===============================
このライブラリはi2Cの64x32ドットのSSD1306 OLEDを制御できます。
RAMは256バイトぐらい必要です。

-関数リスト
!注意!
ビットマップデータはPROGMEMに保存してください。

引数がbx,byの関数は座標を1バイト(8ドット)単位で指定する必要があります。
引数がx,yの関数は座標を1ビット(1ドット)単位で指定できます。

-制御系
OLED.OLED_init() - SSD1306を初期化する。最初に実行してください。
OLED.OLED_send() - 画面を更新する。
OLED.OLED_send2x() - 2倍に拡大したデータで更新する。よくみる128x64ドットで表示できるが、遅い。
OLED.OLED_clear() - バッファーのデータをクリアする。
OLED.OLED_flip() - バッファーのデータを反転させる。

-ビットマップ描画
OLED.OLED_drawfill(bmp) - 128x64の画像を描く。
OLED.OLED_draw8(x,y,bmp) - 8x8のビットマップを描く。
OLED.OLED_drawbyte(bx,by,width,height,bitmap) - ビットマップを書く。

-図形描画
OLED.OLED_setpixel(x,y,light) - 1ドット置く。
OLED.OLED_line(x1,y1,x2,y2) - 線を描く。
OLED.OLED_box(x1,y1,x2,y2) - 四角形を描く。中は塗りつぶされない。
OLED.OLED_fillbox(x1,y1,x2,y2,color) - 四角形を描く。中はcolorの色で塗りつぶされる。
0:塗りつぶしなし
1:全部塗りつぶし
2-4:模様付き

-文字描画
OLED.OLED_char(bx,by,char) - 1文字描く。サイズ8x8ピクセル。
OLED.OLED_string(bx,by,String) - 文字列を描く。サイズ8x8ピクセル。
OLED.OLED_char4(bx,by,char) - 1文字描く。サイズ4x8ピクセル。
OLED.OLED_string4(bx,by,String) - 文字列を描く。サイズ4x8ピクセル。
OLED.OLED_num(bx,by,variable) - 数値を描く。



-更新履歴-
2024/2/19 前のライブラリからの移植完了 1.0
2024/3/27 ピン用の定義追加 1.1
2025/2/12 反転用関数追加 1.2
