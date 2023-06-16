#include "DrUltraSonic.h"
#include "M5All-In-One-Gadget.h"
#include <Arduino.h>
//コンストラクターメンバ変数格納とPINモードの設定
DrUltraSonic::DrUltraSonic(int echo_pin ,int trig_pin){
   m_echo_pin =echo_pin;
   m_trig_pin=trig_pin;
}


//超音波が返ってくるまでの時間の取得
double DrUltraSonic:: measureReturnTime(){

    double t; //ｔはμ秒単位
  //double distance = 0;

  //超音波の発生
  digitalWrite(m_echo_pin, HIGH);//入力
  delayMicroseconds(10);
  digitalWrite(m_trig_pin, LOW);//出力

//返ってくるまでの時間測定
  t = pulseIn(m_echo_pin, HIGH, 2000000); //ECHOピンのパルスがHIGHになった時間を変数tに格納
Serial.print("t=");
Serial.println(t);

  return t;
}