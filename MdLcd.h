/* インクルードガード */
#pragma once

#include"M5All-In-One-Gadget.h"
#include <Arduino.h>

class MdLcd // classの定義
{
private: // privateはクラス内からしかアクセスできない
public: // publicはどこからでもアクセス可能
    void displayJpgImage(const char* path);
    void displayJpgImageCoordinate(const char* path, uint16_t x, uint16_t y);
    void clearDisplay();//背景無し（黒）
    void fillBackgroundWhite();//背景白
    void displayText(const char* text, int x, int y);
    void displayDateText(String text, int x, int y);
};
