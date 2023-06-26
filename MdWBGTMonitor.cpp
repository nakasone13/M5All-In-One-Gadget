#include <Arduino.h>
#include "MdWBGTMonitor.h"
#include "DrTHSensor.h"
#include "M5All-In-One-Gadget.h"

DrTHSensor drthsensor;//インスタンス作成

void MdWBGTMonitor::init(){
    drthsensor.init();
}
//取得した温湿度を基に、アラートの分類分けを行う
void MdWBGTMonitor::getWBGT(double* temperature, double* humidity, WbgtIndex* index){
    //double *temperature=0;
    //double *humidity=0;
    init();
    drthsensor.getTempHumi(temperature,humidity);
    //*temperature=*t
    //*humidity=*h

    int calc_index=0.6*(*temperature)+0.12*(*humidity);
    Serial.println("calc_index=");  
        Serial.println(calc_index);
if(calc_index>0&&calc_index<15){
*index=SAFE;
}else if(calc_index>=15&&calc_index<=24){
*index=ATTENTION;
}else if(calc_index>=24&&calc_index<=27){
*index=ALERT;
}else if(calc_index>=27&&calc_index<=30){
*index=HIGH_ALERT;
}else {
*index=DANGER;
}

}


  
