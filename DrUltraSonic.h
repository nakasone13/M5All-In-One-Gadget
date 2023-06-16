/* インクルードガード */
#pragma once
#include "M5All-In-One-Gadget.h"
class DrUltraSonic // classの定義
{

int m_echo_pin;//メンバ変数
int m_trig_pin;//メンバ変数

//コンストラクター
private: // privateはクラス内からしかアクセスできない


public: // publicはどこからでもアクセス可能
DrUltraSonic(int echo_pin ,int trig_pin);
double measureReturnTime();//超音波を発生させてから返ってくるまでの時間を変数 ｔ に格納する。
};