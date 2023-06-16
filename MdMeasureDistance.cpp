#include "MdMeasureDistance.h"
#include "DrUltraSonic.h"
#include "M5All-In-One-Gadget.h"

DrUltraSonic drultrasonic=DrUltraSonic(ECHO_PIN ,TRIG_PIN);//DrUltraSonicクラスからインスタンス作成

//距離を取得する
double MdMeasureDistance::getDistance() {
 double distance=0;
 
 double t =drultrasonic.measureReturnTime();

  if (t > 0) {
    distance = (340.0 / 1000000) * t * 0.5 * 100; //m→cmなので100倍する
  } 
  else {
    distance = 0;
  }

 return distance;
}
