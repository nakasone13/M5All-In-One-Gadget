//全定数
/* インクルードガード */
#pragma once

// button gpio number
#define BTN_A_GPIO 39
#define BTN_B_GPIO 38
#define BTN_C_GPIO 37

// UltraSonic pin
#define ECHO_PIN 5
#define TRIG_PIN 2

// MENUjpg image path
#define TITLE_IMG_PATH "/images/title/title.jpg"//タイトル画面画像
#define MENU_WBGT_IMG_PATH "/images/menu/monitor.jpg"//メニュー熱中症モニター画面
#define MENU_WBGT_FOCUS_IMG_PATH "/images/menu/monitor_focus.jpg"//熱中症モニター赤
#define MENU_MUSIC_IMG_PATH "/images/menu/music.jpg"//音楽プレイヤー画面画像
#define MENU_MUSIC_FOCUS_IMG_PATH "/images/menu/music_focus.jpg"//音楽プレイヤー緑画面画像
#define MENU_MEASURE_IMG_PATH "/images/menu/measure.jpg"//距離測定白
#define MENU_MEASURE_FOCUS_IMG_PATH "/images/menu/measure_focus.jpg"//距離測定黄色画面画像
#define MENU_DATE_IMG_PATH "/images/menu/date.jpg"//時刻表示白
#define MENU_DATE_FOCUS_IMG_PATH "/images/menu/date_focus.jpg"//時刻表示青
// WBGTjpg image path
#define WBGT_SAFE_IMG_PATH "/images/wbgt/safe.jpg"//安全黄色画像
#define WBGT_ATTENTION_IMG_PATH "/images/wbgt/attention.jpg"//注意
#define WBGT_ALERT_IMG_PATH "/images/wbgt/alert.jpg"//警戒
#define WBGT_HIGH_ALERT_IMG_PATH "/images/wbgt/high_alert.jpg"//厳重警戒
#define WBGT_DANGER_IMG_PATH "/images/wbgt/danger.jpg"//危険
#define WBGT_TEMPERATURE_IMG_PATH "/images/wbgt/temperature.jpg"//タイトル画面画像
#define WBGT_HUMIDITY_IMG_PATH "/images/wbgt/humidity.jpg"//湿度
#define WBGT_DEGREE_IMG_PATH "/images/wbgt/degree.jpg"//C。
#define WBGT_PERCENT_IMG_PATH "/images/wbgt/percent.jpg"//％
// MUSICjpg image path
#define MUSIC_NOWPLAYING_IMG_PATH "/images/music/nowplaying.jpg"//nowplaying
#define MUSIC_NOWSTOPPING_IMG_PATH "/images/music/nowstopping.jpg"//nowstopping
// MESUREjpg image path
#define MEASURE_NOTICE_IMG_PATH "/images/measure/measure.jpg"//距離測定中
#define MEASURE_CM_IMG_PATH "/images/measure/cm.jpg"//CM
// DATEjpg image path
#define DATE_NOTICE_IMG_PATH "/images/date/notice.jpg"//時刻表示
#define DATE_SLASH_IMG_PATH "/images/date/slash.jpg"//スラッシュ
#define DATE_COLON_IMG_PATH "/images/date/colon.jpg"//：

#define COMMON_BUTTON_BACK_IMG_PATH "/images/common/button/back.jpg"//戻る画像
#define COMMON_BUTTON_DECIDE_IMG_PATH "/images/common/button/decide.jpg"//決定画像
#define COMMON_BUTTON_DOWN_IMG_PATH "/images/common/button/down.jpg"//下画像
#define COMMON_BUTTON_NEXT_IMG_PATH "/images/common/button/next.jpg"//次の曲画像
#define COMMON_BUTTON_PLAY_IMG_PATH "/images/common/button/play.jpg"//再生画像
#define COMMON_BUTTON_STOP_IMG_PATH "/images/common/button/stop.jpg"//停止画面画像
#define COMMON_BUTTON_UP_IMG_PATH "/images/common/button/up.jpg"//上画像
#define COMMON_BUTTON_FILLWHITE_IMG_PATH "/images/common/button/fillwhite.jpg"//タイトル画面画像

#define COMMON_ORANGE1_IMG_PATH "/images/common/orange_number/1.jpg"//タイトル画面画像
#define COMMON_ORANGE2_IMG_PATH "/images/common/orange_number/2.jpg"//タイトル画面画像
#define COMMON_ORANGE3_IMG_PATH "/images/common/orange_number/3.jpg"//タイトル画面画像
#define COMMON_ORANGE4_IMG_PATH "/images/common/orange_number/4.jpg"//タイトル画面画像
#define COMMON_ORANGE5_IMG_PATH "/images/common/orange_number/5.jpg"//タイトル画面画像
#define COMMON_ORANGE6_IMG_PATH "/images/common/orange_number/6.jpg"//タイトル画面画像
#define COMMON_ORANGE7_IMG_PATH "/images/common/orange_number/7.jpg"//タイトル画面画像
#define COMMON_ORANGE8_IMG_PATH "/images/common/orange_number/8.jpg"//タイトル画面画像
#define COMMON_ORANGE9_IMG_PATH "/images/common/orange_number/9.jpg"//タイトル画面画像
#define COMMON_ORANGE0_IMG_PATH "/images/common/orange_number/0.jpg"//タイトル画面画像
#define COMMON_ORANGEDOT_IMG_PATH "/images/common/orange_number/dot.jpg"//タイトル画面画像
#define COMMON_ORANGEFILLWHITE_IMG_PATH "/images/common/orange_number/fillwhite.jpg"//タイトル画面画像

#define COMMON_BLUE1_IMG_PATH "/images/common/blue_number/1.jpg"//タイトル画面画像
#define COMMON_BLUE2_IMG_PATH "/images/common/blue_number/2.jpg"//タイトル画面画像
#define COMMON_BLUE3_IMG_PATH "/images/common/blue_number/3.jpg"//タイトル画面画像
#define COMMON_BLUE4_IMG_PATH "/images/common/blue_number/4.jpg"//タイトル画面画像
#define COMMON_BLUE5_IMG_PATH "/images/common/blue_number/5.jpg"//タイトル画面画像
#define COMMON_BLUE6_IMG_PATH "/images/common/blue_number/6.jpg"//タイトル画面画像
#define COMMON_BLUE7_IMG_PATH "/images/common/blue_number/7.jpg"//タイトル画面画像
#define COMMON_BLUE8_IMG_PATH "/images/common/blue_number/8.jpg"//タイトル画面画像
#define COMMON_BLUE9_IMG_PATH "/images/common/blue_number/9.jpg"//タイトル画面画像
#define COMMON_BLUE0_IMG_PATH "/images/common/blue_number/0.jpg"//タイトル画面画像
#define COMMON_BLUEDOT_IMG_PATH "/images/common/blue_number/dot.jpg"//タイトル画面画像
#define COMMON_BLUEFILLWHITE_IMG_PATH "/images/common/blue_number/fillwhite.jpg"//タイトル画面画像

//TITLE jpg image coordinate
#define TITLE_X_CRD 0
#define TITLE_Y_CRD 0


// MENU jpg image coordinate
#define MENU_WBGT_X_CRD 0 //熱中症画面X座標
#define MENU_WBGT_Y_CRD 0 //熱中症画面Y座標
#define MENU_MUSIC_X_CRD 0 //音楽プレーヤー画面X座標
#define MENU_MUSIC_Y_CRD 50 //音楽プレーヤー画面Y座標
#define MENU_DATE_X_CRD 0 //時刻プレーヤー画面X座標
#define MENU_DATE_Y_CRD 150 //時刻プレーヤー画面Y座標
#define MENU_MEASURE_X_CRD 0 //距離プレーヤー画面X座標
#define MENU_MEASURE_Y_CRD 100 //距離プレーヤー画面Y座標
// MENU jpg image coordinate
#define UP_X_CRD 0 //上矢印X座標
#define UP_Y_CRD 200 //上矢印Y座標
// MENU jpg image coordinate
#define DOWN_X_CRD 240//下矢印X座標
#define DOWN_Y_CRD 200//下矢印Y座標
#define DECIDE_X_CRD 120//決定X座標
#define DECIDE_Y_CRD 200//決定Y座標

// WBGT jpg image coordinate

// Music jpg image coordinate
#define PLAY_X_CRD 0//再生X座標
#define PLAY_Y_CRD 200//再生Y座標
#define NOWSTOPPING_X_CRD 0//NOWSTOPPPINGX座標
#define NOWSTOPPING_Y_CRD 0//NOWSTOPPPINGY座標
#define NEXTSONG_X_CRD 240//NEXTSONGX座標
#define NEXTSONG_Y_CRD 200//NEXTSONGY座標
#define NOWPLAYYING_X_CRD 0//NOWPLAYYING座標
#define NOWPLAYYING_Y_CRD 0//NOWPLAYYING座標
#define SONGNAME_X_CRD 10//NOWPLAYYING座標
#define SONGNAME_Y_CRD 120//NOWPLAYYING座標

// Measure jpg image coordinate
#define THOUSANDSPLACE_X_CRD 10//千の位X座標
#define THOUSANDSPLACE_Y_CRD 100//千の位Y座標
#define TENSPLACE_X_CRD 53//十の位X座標
#define TENSPLACE_Y_CRD 100//十の位Y座標
#define ONESPLACE_X_CRD 96//一の位X座標
#define ONESPLACE_Y_CRD 100//一の位Y座標
#define DECIMALPOINT_X_CRD 139//小数点X座標
#define DECIMALPOINT_Y_CRD 100//小数点Y座標
#define FIRSTDECIMALPOINT_X_CRD 182//小数点第一位X座標
#define FIRSTDECIMALPOINT_Y_CRD 100//小数点第一位Y座標
#define CM_X_CRD 240//cmX座標
#define CM_Y_CRD 100//cmY座標

// Date jpg image coordinate
#define TIMEMENU_X_CRD 0//時刻表示X座標
#define TIMEMENU_Y_CRD 0//時刻表示Y座標
#define DATEBACK_X_CRD 120//戻るX座標
#define DATEBACK_Y_CRD 200//戻るY座標



typedef enum {
    TITLE,
    MENU,
    WBGT,
    MUSIC_STOP,
    MUSIC_PLAY,
    MEASURE,
    DATE
} State;

typedef enum {
    ENTRY,
    DO,
    EXIT
} Action;

typedef enum {
    MENU_WBGT,
    MENU_MUSIC,
    MENU_MEASURE,
    MENU_DATE
} FocusState;

typedef enum {
    SAFE,
    ATTENTION,
    ALERT,
    HIGH_ALERT,
    DANGER
} WbgtIndex;
