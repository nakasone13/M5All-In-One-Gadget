#include "MdDateTime.h"
#include <Arduino.h>

//コンストラクター
MdDateTime::MdDateTime()
{
    Serial2.begin(9600);
}

//現在の日付の取得
String MdDateTime::readDate()
{
    int i = 0;
    char c = 0;
    while (Serial2.available() > 0) {
        c = Serial2.read();
        gps.encode(c);
    }
    char date[11];
    snprintf(date, sizeof(date), "%04d/%02d/%02d", gps.date.year(), gps.date.month(), gps.date.day());
    Serial.println(date);
    return String(date);
}
//現在の時刻の取得
String MdDateTime::readTime()
{
    int i = 0;
    char c = 0;
    while (Serial2.available() > 0) {
        c = Serial2.read();
        gps.encode(c);
    }
    char time[11];
    snprintf(time, sizeof(time), "%02d:%02d:%02d", gps.time.hour() + 9, gps.time.minute(), gps.time.second());
    Serial.println(time);
    return String(time);
}