#include "AppControl.h"
#include <Arduino.h>
#include <M5Stack.h>
#include "MdLcd.h"// MdLcd.hをインクルードする
MdLcd mlcd;//インスタンス化
MdWBGTMonitor mwbgt;//インスタンス化
MdMusicPlayer mmplay;//インスタンス化
MdMeasureDistance mmdist;//インスタンス化

MdDateTime mdtime;//MdDateTimeからインスタンスを生成
double g_drul=0;


const char* g_str_orange[] = {
    COMMON_ORANGE0_IMG_PATH,
    COMMON_ORANGE1_IMG_PATH,
    COMMON_ORANGE2_IMG_PATH,
    COMMON_ORANGE3_IMG_PATH,
    COMMON_ORANGE4_IMG_PATH,
    COMMON_ORANGE5_IMG_PATH,
    COMMON_ORANGE6_IMG_PATH,
    COMMON_ORANGE7_IMG_PATH,
    COMMON_ORANGE8_IMG_PATH,
    COMMON_ORANGE9_IMG_PATH,
};

const char* g_str_blue[] = {
    COMMON_BLUE0_IMG_PATH,
    COMMON_BLUE1_IMG_PATH,
    COMMON_BLUE2_IMG_PATH,
    COMMON_BLUE3_IMG_PATH,
    COMMON_BLUE4_IMG_PATH,
    COMMON_BLUE5_IMG_PATH,
    COMMON_BLUE6_IMG_PATH,
    COMMON_BLUE7_IMG_PATH,
    COMMON_BLUE8_IMG_PATH,
    COMMON_BLUE9_IMG_PATH,
};




//ボタンAが押されたら引数trueをもってくるのでフラグが変わる
void AppControl::setBtnAFlg(bool flg)
{
    m_flag_btnA_is_pressed = flg;
}
//ボタンBが押されたら引数trueをもってくるのでフラグが変わる
void AppControl::setBtnBFlg(bool flg)
{
    m_flag_btnB_is_pressed = flg;
}
//ボタンCが押されたら引数trueをもってくるのでフラグが変わる
void AppControl::setBtnCFlg(bool flg)
{
    m_flag_btnC_is_pressed = flg;
}
//すべてのボタンのフラグをfalseに戻す
void AppControl::setBtnAllFlgFalse()
{
    m_flag_btnA_is_pressed = false;
    m_flag_btnB_is_pressed = false;
    m_flag_btnC_is_pressed = false;
}

State AppControl::getState()
{
    return m_state;
}

void AppControl::setState(State state)
{
    m_state = state;
}

Action AppControl::getAction()
{
    return m_action;
}

void AppControl::setAction(Action action)
{
    m_action = action;
}

void AppControl::setStateMachine(State state, Action action)
{
    setState(state);
    setAction(action);
}



//現在のフォーカス状態を取得するために使用
FocusState AppControl::getFocusState()
{
    return m_focus_state;
}
//フォーカス状態を設定するために使用
void AppControl::setFocusState(FocusState fs)
{
    m_focus_state = fs;
}





//タイトル画面を表示
void AppControl::displayTitleInit()
{mlcd.displayJpgImageCoordinate(TITLE_IMG_PATH,TITLE_X_CRD,TITLE_Y_CRD);
}

//メニュー画面を表示
void AppControl::displayMenuInit()
{
mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);//熱中症画面を表示
mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);//ミュージック画面を表示
mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);//距離測定画面を表示
mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH,MENU_DATE_X_CRD,MENU_DATE_Y_CRD);//距離測定画面を表示
mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH,DOWN_X_CRD,UP_Y_CRD);//下矢印を表示
mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH,UP_X_CRD,UP_Y_CRD);//上矢印を表示
mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH,DECIDE_X_CRD,DECIDE_Y_CRD);//決定を表示
}

// ボタンの押下に応じてフラグを切り替え
void AppControl::focusChangeImg(FocusState current_state, FocusState next_state){

if(current_state == MENU_WBGT && next_state == MENU_MUSIC){
    setFocusState(MENU_MUSIC);
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH, MENU_MUSIC_X_CRD, MENU_MUSIC_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, MENU_WBGT_X_CRD, MENU_WBGT_Y_CRD);
  }
  else if(current_state == MENU_MUSIC&&next_state == MENU_MEASURE){
    setFocusState(MENU_MEASURE);
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH, MENU_MEASURE_X_CRD, MENU_MEASURE_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, MENU_MUSIC_X_CRD, MENU_MUSIC_Y_CRD);
  }
  else if(current_state == MENU_MEASURE && next_state == MENU_DATE){
    setFocusState(MENU_DATE);
    mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH, MENU_DATE_X_CRD, MENU_DATE_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, MENU_MEASURE_X_CRD, MENU_MEASURE_Y_CRD);
  }
  else if(current_state == MENU_DATE&&next_state == MENU_WBGT){
    setFocusState(MENU_WBGT);
     mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_X_CRD, MENU_WBGT_Y_CRD);
     mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, MENU_DATE_X_CRD, MENU_DATE_Y_CRD);
  }
  

  else if(current_state == MENU_WBGT && next_state == MENU_DATE){
    setFocusState(MENU_DATE);
     mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH, MENU_DATE_X_CRD, MENU_DATE_Y_CRD);
     mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, MENU_WBGT_X_CRD, MENU_WBGT_Y_CRD);
  }

  else if(current_state == MENU_DATE && next_state == MENU_MEASURE){
    setFocusState(MENU_MEASURE);
      mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH, MENU_MEASURE_X_CRD, MENU_MEASURE_Y_CRD);
      mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, MENU_DATE_X_CRD, MENU_DATE_Y_CRD);
    
  }
  else if(current_state == MENU_MEASURE&&next_state == MENU_MUSIC){
    setFocusState(MENU_MUSIC);
     mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH, MENU_MUSIC_X_CRD, MENU_MUSIC_Y_CRD);
     mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, MENU_MEASURE_X_CRD, MENU_MEASURE_Y_CRD);
  }
  else if(current_state == MENU_MUSIC && next_state == MENU_WBGT){
    setFocusState(MENU_WBGT);
      mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_X_CRD, MENU_WBGT_Y_CRD);
      mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, MENU_MUSIC_X_CRD, MENU_MUSIC_Y_CRD);
    
  }
  
    
}

void AppControl::displayWBGTInit()
{
mlcd.fillBackgroundWhite();//背景白に変更
mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, DATEBACK_X_CRD, DATEBACK_Y_CRD);//戻る
mlcd.displayJpgImageCoordinate(WBGT_SAFE_IMG_PATH, SAFE_X_CRD, SAFE_Y_CRD);//安全
mlcd.displayJpgImageCoordinate(WBGT_HUMIDITY_IMG_PATH, HUMIDITY_X_CRD, HUMIDITY_Y_CRD);//湿度
mlcd.displayJpgImageCoordinate(WBGT_TEMPERATURE_IMG_PATH, TEMPERATURE_X_CRD, TEMPERATURE_Y_CRD);//温度
mlcd.displayJpgImageCoordinate(WBGT_DEGREE_IMG_PATH, DO_X_CRD, DO_Y_CRD);//c
mlcd.displayJpgImageCoordinate(WBGT_PERCENT_IMG_PATH, PARCENTE_X_CRD, PARCENTE_Y_CRD);//%
mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, NETTYUUSYODOTTO_X_CRD, NETTYUUSYODOTTO_Y_CRD);//
mlcd.displayJpgImageCoordinate(COMMON_ORANGEDOT_IMG_PATH, NETTYUUSYODOTTOSITUDO_X_CRD, NETTYUUSYODOTTOSITUDO_Y_CRD);//
}

void AppControl::displayTempHumiIndex()
{   double t=0;
    double h=0;
    WbgtIndex i=SAFE;
    mwbgt.getWBGT(&t,&h,&i);
Serial.println("h=");  
        Serial.println(h);
        Serial.println("t=");  
        Serial.println(t);
        Serial.println("i=");
        Serial.println(i);
  
        
  int num1[3] = { 0 };
  // 各桁を取り出す
    
	    
        if(0<static_cast<int>(h / 10) % 10){
        num1[0]= static_cast<int>(h / 10) % 10;}//十の位
        if(0<static_cast<int>(h) % 10){
        num1[1] =static_cast<int>(h) % 10;}// 一の位
        
        num1[2] =static_cast<int>(h * 10) % 10;// 少数第一の位
        Serial.println("num1=");
       
        Serial.println(num1[0]);
        Serial.println(num1[1]);
        Serial.println(num1[2]);

        int num2[3] = { 0 };
  // 各桁を取り出す
    
	    
        if(0<static_cast<int>(t / 10) % 10){
        num2[0]= static_cast<int>(t / 10) % 10;}//十の位
        if(0<static_cast<int>(t) % 10){
        num2[1] =static_cast<int>(t) % 10;}// 一の位
        
        num2[2] =static_cast<int>(t * 10) % 10;// 少数第一の位
        Serial.println("num2=");
       
        Serial.println(num2[0]);
        Serial.println(num2[1]);
        Serial.println(num2[2]);
        switch(i){
    case SAFE:
    Serial.println("SAFE"); 
    mlcd.displayJpgImageCoordinate(WBGT_SAFE_IMG_PATH, SAFE_X_CRD, SAFE_Y_CRD);//安全
    break;
    case ATTENTION:
    Serial.println("ATTENTION");
    mlcd.displayJpgImageCoordinate(WBGT_ATTENTION_IMG_PATH, SAFE_X_CRD, SAFE_Y_CRD);//安全
    break;
    case ALERT:
    Serial.println("ALERT");
    mlcd.displayJpgImageCoordinate(WBGT_ALERT_IMG_PATH, SAFE_X_CRD, SAFE_Y_CRD);//安全
    break;
    case HIGH_ALERT:
    Serial.println("HIGH_ALERT");
    mlcd.displayJpgImageCoordinate(WBGT_HIGH_ALERT_IMG_PATH, SAFE_X_CRD, SAFE_Y_CRD);//安全
    break;
    case DANGER:
    Serial.println("DANGER");
    mlcd.displayJpgImageCoordinate(WBGT_DANGER_IMG_PATH, SAFE_X_CRD, SAFE_Y_CRD);//安全
    break;
  }
  switch(num1[0]){
         case 1:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH, TEN_X_CRD, TEN_Y_CRD);
        break;
        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH, TEN_X_CRD, TEN_Y_CRD);
        break;
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH, TEN_X_CRD, TEN_Y_CRD);
        break;
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH, TEN_X_CRD, TEN_Y_CRD);
        break;
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH, TEN_X_CRD, TEN_Y_CRD);
        break;
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH, TEN_X_CRD, TEN_Y_CRD);
        break;
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH, TEN_X_CRD, TEN_Y_CRD);
        break;
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH, TEN_X_CRD, TEN_Y_CRD);
        break;
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH, TEN_X_CRD, TEN_Y_CRD);
        break;
        case 0:
        //mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        break;
    
        }
        switch(num1[1]){
        case 1:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH, JU_X_CRD, TEN_Y_CRD);
        break;

        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH, JU_X_CRD, TEN_Y_CRD);
        break;
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH, JU_X_CRD, TEN_Y_CRD);
        break;
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH, JU_X_CRD, TEN_Y_CRD);
        break;
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH, JU_X_CRD, TEN_Y_CRD);
        break;
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH, JU_X_CRD, TEN_Y_CRD);
        break;
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH, JU_X_CRD, TEN_Y_CRD);
        break;
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH, JU_X_CRD, TEN_Y_CRD);
        break;
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH, JU_X_CRD, TEN_Y_CRD);
        break;
        case 0:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH, JU_X_CRD, TEN_Y_CRD);
        break;
    
        }
        switch(num1[2]){
        case 1:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH, ITI_X_CRD, TEN_Y_CRD);
        break;

        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH, ITI_X_CRD, TEN_Y_CRD);
        break;
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH, ITI_X_CRD, TEN_Y_CRD);
        break;
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH, ITI_X_CRD, TEN_Y_CRD);
        break;
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH, ITI_X_CRD, TEN_Y_CRD);
        break;
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH, ITI_X_CRD, TEN_Y_CRD);
        break;
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH, ITI_X_CRD, TEN_Y_CRD);
        break;
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH, ITI_X_CRD, TEN_Y_CRD);
        break;
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH, ITI_X_CRD, TEN_Y_CRD);
        break;
        case 0:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH, ITI_X_CRD, TEN_Y_CRD);
        break;
    
        }
switch(num2[0]){
         case 1:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE1_IMG_PATH, TEN_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE2_IMG_PATH, TEN_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE3_IMG_PATH, TEN_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE4_IMG_PATH, TEN_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE5_IMG_PATH, TEN_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE6_IMG_PATH, TEN_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE7_IMG_PATH, TEN_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE8_IMG_PATH, TEN_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE9_IMG_PATH, TEN_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 0:
        //mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        break;
    
        }
        switch(num2[1]){
        case 1:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE1_IMG_PATH, JU_X_CRD, SITUDOITI_Y_CRD);
        break;

        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE2_IMG_PATH, JU_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE3_IMG_PATH, JU_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE4_IMG_PATH, JU_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE5_IMG_PATH, JU_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE6_IMG_PATH, JU_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE7_IMG_PATH, JU_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE8_IMG_PATH, JU_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE9_IMG_PATH, JU_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 0:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE0_IMG_PATH, JU_X_CRD, SITUDOITI_Y_CRD);
        break;
    
        }
        switch(num2[2]){
        case 1:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE1_IMG_PATH, ITI_X_CRD, SITUDOITI_Y_CRD);
        break;

        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE2_IMG_PATH, ITI_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE3_IMG_PATH, ITI_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE4_IMG_PATH, ITI_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE5_IMG_PATH, ITI_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE6_IMG_PATH, ITI_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE7_IMG_PATH, ITI_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE8_IMG_PATH, ITI_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE9_IMG_PATH, ITI_X_CRD, SITUDOITI_Y_CRD);
        break;
        case 0:
        mlcd.displayJpgImageCoordinate(COMMON_ORANGE0_IMG_PATH, ITI_X_CRD, SITUDOITI_Y_CRD);
        break;
    
        }

        delay(3000);
}

void AppControl::displayMusicInit()
{mlcd.fillBackgroundWhite();//背景白に変更
mlcd.displayJpgImageCoordinate(COMMON_BUTTON_PLAY_IMG_PATH, PLAY_X_CRD, PLAY_Y_CRD);//再生
mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, DATEBACK_X_CRD, DATEBACK_Y_CRD);//戻る
mlcd.displayJpgImageCoordinate(COMMON_BUTTON_NEXT_IMG_PATH, NEXTSONG_X_CRD, NEXTSONG_Y_CRD);//次の曲
mlcd.displayJpgImageCoordinate(MUSIC_NOWSTOPPING_IMG_PATH, NOWSTOPPING_X_CRD, NOWSTOPPING_Y_CRD);//NOWSTOPPING
}

void AppControl::displayMusicStop()
{/*
if (!mmplay.playMP3()) {
    mmplay.stopMP3();
    
}*/
}

void AppControl::displayMusicTitle()
{
char* title =mmplay.getTitle();
mlcd.displayText(title,SONGTITLE_X_CRD,SONGTITLE_Y_CRD);
}

void AppControl::displayNextMusic()
{/*mmplay.selectNextMusic();*/
}

void AppControl::displayMusicPlay()
{/*音楽再生中でない場合
 */
}


//画面の初期化
void AppControl::displayDateInit()
{
mlcd.fillBackgroundWhite();//背景白に変更
mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, DATEBACK_X_CRD, DATEBACK_Y_CRD);//戻る
mlcd.displayJpgImageCoordinate(DATE_NOTICE_IMG_PATH, TIMEMENU_X_CRD, TIMEMENU_Y_CRD);
}




void AppControl::displayMeasureDistance()
{
    g_drul=mmdist.getDistance();
delay(200);
//測定距離表示      
            mlcd.displayJpgImageCoordinate(MEASURE_CM_IMG_PATH, CM_X_CRD, CM_Y_CRD);//cm
            mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, DECIMALPOINT_X_CRD, DECIMALPOINT_Y_CRD);//小数点
        //g_drulはグローバル宣言メジャーディスタンス関数により小数点第二位までの数字を代入済
        Serial.println("g_drul=");
        Serial.println(g_drul);
        int num[4] = { 0 };
	    // 各桁を取り出す
    
	    //num[0] = g_drul / 1000;
	    if (0<static_cast<int>(g_drul / 100) % 10){
       num[0] = static_cast<int>(g_drul / 100) % 10;}//百の位
        if(0<static_cast<int>(g_drul / 10) % 10){
        num[1]= static_cast<int>(g_drul / 10) % 10;}//十の位
        if(0<static_cast<int>(g_drul) % 10){
        num[2] =static_cast<int>(g_drul) % 10;}// 一の位
	
        num[3] =static_cast<int>(g_drul * 10) % 10;// 少数第一の位

        //  double decimalPart = (g_drul - static_cast<int>(g_drul)) * 10; // 小数部分の一桁を取り出す
        // double decimalFirstDigit = static_cast<int>(decimalPart);       // 小数点第一位の数字
        Serial.println(num[0]);
        Serial.println(num[1]);
        Serial.println(num[2]);
        Serial.println(num[3]);
        delay(2000);



            switch(num[0]){
         case 1:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        break;
        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        break;
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        break;
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        break;
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        break;
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        break;
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        break;
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        break;
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        break;
        case 0:
        //mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        break;
    
        }
        switch(num[1]){
        case 1:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        break;

        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        break;
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        break;
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        break;
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        break;
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        break;
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        break;
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        break;
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        break;
        case 0:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        break;
    
        }
        switch(num[2]){
        case 1:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        break;

        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        break;
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        break;
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        break;
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        break;
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        break;
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        break;
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        break;
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        break;
        case 0:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        break;
    
        }
        switch(num[3]){
        case 1:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        break;

        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        break;
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        break;
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        break;
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        break;
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        break;
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
       
        break;
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        break;
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        break;
        case 0:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        break;
    
        }
}

void AppControl::displayMeasureInit()
{
mlcd.displayJpgImageCoordinate(MEASURE_NOTICE_IMG_PATH, TIMEMENU_X_CRD, TIMEMENU_Y_CRD);
mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, DATEBACK_X_CRD, DATEBACK_Y_CRD);
}

/*
int digit;
for(int i=0;i=digit;i++){
 g_drul=g_drul%10
digit++;
   int[digit]=g_drul;//配列に逆からの数値を埋め込む
}

// 小数部分の各桁の数字を取り出して配列に格納（逆順）
while (digit < 10 && g_drul != 0.0) {
    int temp = static_cast<int>(g_drul * 10); // 一桁分の数字を取得
    x[digit] = temp; // 配列に逆順で格納
    g_drul = (g_drul * 10) - temp; // 小数部分から取り出した桁を減算
    digit++;
}

for(int i=0;i<digit/2;i++){
 int temp=x[i];//作業用変数t
 x[i]=x[digit-i-1];//最初の桁の数字を最後の桁の数字と交換
 x[digit-i-1]=temp;
 Serial.println("反転成功");
Serial.println("g_drul=");
Serial.println(g_drul);

}
*/






void AppControl::displayDateUpdate()
{
Serial.println(mdtime.readDate());
Serial.println(mdtime.readTime());
mlcd.displayDateText(mdtime.readDate(), 10, 100);
mlcd.displayDateText(mdtime.readTime(), 40, 150);
}

void AppControl::controlApplication()
{
    mmplay.init();//音楽プレーヤーの初期化
    while (1) {

        switch (getState()) {
        case TITLE:
            switch (getAction()) {
            case ENTRY:
                /*
                ** まずはここにタイトル画面の表示処理を呼び出してみよう。
                ** タイトル画面表示の関数はdisplayTitleInit()である。
                ** この関数の中身はまだ何もないので、この関数にタイトル画面表示処理を書いてみよう。
                */
                displayTitleInit();//タイトル画面呼び出し
                Serial.println("TITLE,ENTRY");
                setStateMachine(TITLE, DO);
                break;

            case DO:
                Serial.println("TITLE,DO");
                //もし、ボタンA、BCが押されたらEXITへ
                if((m_flag_btnA_is_pressed)||(m_flag_btnB_is_pressed)||(m_flag_btnC_is_pressed)==true){
                setStateMachine(TITLE, EXIT);
                };
                Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                

                //左、右、中ボタンのいずれかを押下でEXITへ
                //setStateMachine(TITLE, EXIT);
                break;

            case EXIT:
            Serial.println("TITLE,EXIT");
            setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
            setStateMachine(MENU, ENTRY);
                break;

            default:
            Serial.println("TITLE,default");
                break;
            }

            break;

        case MENU:

            switch (getAction()) {
            case ENTRY:
                Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                
                Serial.println("MENU,ENTRY");

                        //メニュー画面表示
                        mlcd.fillBackgroundWhite();//背景白に変更
                        displayMenuInit();
                        setStateMachine(MENU, DO);
                break;

            case DO:
            Serial.println("MENU,DO");
            //中ボタンを押下
                Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                

                //ボタンを押すとm_focus_state = fs;を設定する
                //m_focus_state = fs;だと画像の色を変える処理をする
                //現在のフォーカス状態を取得するために使用
           //setFocusState(MENU_WBGT);
     //mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_X_CRD, MENU_WBGT_Y_CRD);

                //下矢印を押すと
                if(m_flag_btnC_is_pressed){

                 switch( getFocusState()){
                 case MENU_WBGT:
                  focusChangeImg(MENU_WBGT,MENU_MUSIC);
                  setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                 
                     break;
                 case MENU_MUSIC:
                  focusChangeImg(MENU_MUSIC,MENU_MEASURE);
                  setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                 
                   break;
                  case MENU_MEASURE:
                  focusChangeImg(MENU_MEASURE,MENU_DATE);
                  setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                
                         break;
                    case MENU_DATE:
                      focusChangeImg(MENU_DATE,MENU_WBGT);
                      setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                 
                    }

                
                }

   
                
                //上矢印を押すと
                if(m_flag_btnA_is_pressed){

                 switch( getFocusState()){
                 case MENU_WBGT:
                  focusChangeImg(MENU_WBGT,MENU_DATE);
                  setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
               
                     break;
                 case MENU_DATE:
                 focusChangeImg(MENU_DATE,MENU_MEASURE);
                 setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                
                   break;
                  case MENU_MEASURE:
                 focusChangeImg(MENU_MEASURE,MENU_MUSIC);
                 setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                 
                         break;
                    case MENU_MUSIC:
                     focusChangeImg(MENU_MUSIC,MENU_WBGT);
                     setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
              
                    }

                
                }

                //決定を押すとステートマシン遷移する
                if(m_flag_btnB_is_pressed){
                    setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                 setStateMachine(MENU, EXIT);

                }



                break;

            case EXIT:
            Serial.println("MENU,EXIT");
                Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                
                
            //フォーカス当たっているところへ移動する
               
                 switch( getFocusState()){
                 case MENU_WBGT:
                  //熱中症モニタ画面表示
                        
                        setStateMachine(WBGT, ENTRY);
                         
               
                     break;
                 case MENU_DATE:
                 //熱中症モニタ画面表示
                        
                        setStateMachine(DATE, ENTRY);
                         
                
                   break;
                  case MENU_MEASURE:
                 //熱中症モニタ画面表示
                        
                        setStateMachine(MEASURE, ENTRY);
                        
                 
                         break;
                    case MENU_MUSIC:
                     //熱中症モニタ画面表示
                       
                        setStateMachine(MUSIC_STOP, ENTRY);
                         
                    }
                

                break;
            }

            break;

        case WBGT:

            switch (getAction()) {
            case ENTRY:
            Serial.println("WBGT,ENTRY");
                Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                displayWBGTInit();
                
                setStateMachine(WBGT, DO);
                break;

            case DO:
            Serial.println("WBGT,DO");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);


            
            while(1){
                displayTempHumiIndex();
                
                delay(100);
                if(m_flag_btnB_is_pressed){
                    setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                 
                 break;
                }
            }setStateMachine(WBGT, EXIT);






                if(m_flag_btnB_is_pressed){
                    setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                 setStateMachine(WBGT, EXIT);
                }
                break;

            case EXIT:
            Serial.println("WBGT,EXIT");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                setStateMachine(MENU, ENTRY);
                break;

            default:
            Serial.println("WBGT,default");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
                break;
            }

            break;

        case MUSIC_STOP:
            switch (getAction()) {
            case ENTRY:
            Serial.println("MUSIC_STOP,ENTRY");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                displayMusicInit();
                setStateMachine(MUSIC_STOP, DO);
                //音楽再生
            //停止画面表示
            //現在の曲表示
                break;
            
            case DO:
            Serial.println("MUSIC_STOP,DO");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
             setStateMachine(MUSIC_STOP, EXIT);
                break;

            case EXIT:
            Serial.println("MUSIC_STOP,EXIT");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                 displayMusicTitle();

                //再生を押すとステートマシン遷移する
                if(m_flag_btnA_is_pressed){
                    setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                delay(200);
                 setStateMachine(MUSIC_PLAY, ENTRY);
                }
                //戻るを押すとステートマシン遷移する
                if(m_flag_btnB_is_pressed){
                    setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                 setStateMachine(MENU, ENTRY);
                }
                //次の曲を押すとステートマシン遷移する
                if(m_flag_btnC_is_pressed){
                    setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                    mmplay.selectNextMusic();
                    char* title =mmplay.getTitle();
                    mlcd.displayText(title,SONGTITLE_X_CRD,SONGTITLE_Y_CRD);
                 //setStateMachine(MUSIC_PLAY, ENTRY);
                }
                break;

            }

            break;

        case MUSIC_PLAY:

            switch (getAction()) {
            case ENTRY:
            Serial.println("MUSIC_PLAY,ENTRY");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                mlcd.fillBackgroundWhite();//背景白に変更
                mlcd.displayJpgImageCoordinate(COMMON_BUTTON_STOP_IMG_PATH, PLAY_X_CRD, PLAY_Y_CRD);//再生
                mlcd.displayJpgImageCoordinate(MUSIC_NOWPLAYING_IMG_PATH, NOWSTOPPING_X_CRD, NOWSTOPPING_Y_CRD);//NOWPlaying
                displayMusicTitle();
                setStateMachine(MUSIC_PLAY, DO);
                break;

            case DO:
            Serial.println("MUSIC_PLAY,DO");
            delay(3000);
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                //音楽再生処理
               
               mmplay.prepareMP3();
               while(1){
                mmplay.playMP3();
                if((m_flag_btnA_is_pressed==true)||(mmplay.isRunningMP3()==false)){
                    setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                    mmplay.stopMP3();
                    Serial.println("stopMP3");
                     setStateMachine(MUSIC_PLAY, EXIT);
                    break;          
                    }      
               }     
                Serial.println("prepareMP3");
                delay(3000);

                break;

            case EXIT:
            Serial.println("MUSIC_PLAY,EXIT");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                setStateMachine(MUSIC_STOP, ENTRY);
                break;           
            }

            break;

        case MEASURE:

            switch (getAction()) {
            case ENTRY:
            Serial.println("MEASURE,ENTRY");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                
                mlcd.fillBackgroundWhite();//背景白に変更
                Serial.println("背景白に変更");
                
        
                
                setStateMachine(MEASURE, DO);
                
                
                break;

            case DO://何もしない
                Serial.println("MEASURE,DO");
                 Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);

                displayMeasureInit();
                displayMeasureDistance();
                //戻る処理
                if(m_flag_btnB_is_pressed){
                    setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                    setStateMachine(MEASURE, EXIT);
                };

                break;

            case EXIT://何もしない
            Serial.println("MEASURE,EXIT");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                setStateMachine(MENU, ENTRY);
                break;

            
                
            }

            break;

        case DATE://

            switch (getAction()) {
            case ENTRY:
            Serial.println("DATE,ENTRY");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);

                displayDateInit();//画面呼び出し
                displayDateUpdate();
                 setStateMachine(DATE, DO);
                
                break;

            case DO://何もしない
            Serial.println("DATE,DO");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);

                displayDateUpdate();
                if(m_flag_btnB_is_pressed){
                    setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                    setStateMachine(DATE, EXIT);
                };
                
                break;

            case EXIT://何もしない
            Serial.println("DATE,EXIT");
            Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                setStateMachine(MENU, ENTRY);
                break;

            
            }

        
            
        }
    }
}
