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
}

void AppControl::displayTempHumiIndex()
{
}

void AppControl::displayMusicInit()
{
}

void AppControl::displayMusicStop()
{
}

void AppControl::displayMusicTitle()
{
}

void AppControl::displayNextMusic()
{
}

void AppControl::displayMusicPlay()
{
}

//画面の初期化
void AppControl::displayDateInit()
{
mlcd.fillBackgroundWhite();//背景白に変更
mlcd.displayJpgImageCoordinate(DATE_NOTICE_IMG_PATH, TIMEMENU_X_CRD, TIMEMENU_Y_CRD);
mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, DATEBACK_X_CRD, DATEBACK_Y_CRD);
}




void AppControl::displayMeasureDistance()
{
    g_drul=mmdist.getDistance();
delay(200);
//測定距離表示        
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

        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
        case 0:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH, THOUSANDSPLACE_X_CRD, THOUSANDSPLACE_Y_CRD);
    
        }
        switch(num[1]){
        case 1:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);

        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
        case 0:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH, TENSPLACE_X_CRD, TENSPLACE_Y_CRD);
    
        }
        switch(num[2]){
        case 1:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);

        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
        case 0:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH, ONESPLACE_X_CRD, ONESPLACE_Y_CRD);
    
        }
        switch(num[3]){
        case 1:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);

        case 2:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        case 3:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        case 4:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        case 5:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        case 6:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        case 7:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        case 8:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        case 9:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
        case 0:
        mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH, FIRSTDECIMALPOINT_X_CRD, FIRSTDECIMALPOINT_Y_CRD);
    
        }
}

void AppControl::displayMeasureInit()
{
mlcd.fillBackgroundWhite();//背景白に変更
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
                delay(2000);

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
                delay(2000);
                break;

            case DO:
            Serial.println("WBGT,DO");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
                break;

            case EXIT:
            Serial.println("WBGT,EXIT");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
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
                delay(2000);
                //音楽再生
            //停止画面表示
            //現在の曲表示
                break;
            
            case DO:
            Serial.println("MUSIC_STOP,DO");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
            //右ボタンを押下→次の曲を表示
                break;

            case EXIT:
            Serial.println("MUSIC_STOP,EXIT");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
                break;

            default:
            Serial.println("MUSIC_STOP,default");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
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
                delay(2000);
                break;

            case DO:
            Serial.println("MUSIC_PLAY,DO");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
                break;

            case EXIT:
            Serial.println("MUSIC_PLAY,EXIT");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
                break;

            default:
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
                displayMeasureInit();
                displayMeasureDistance();
        
                
                
                //戻る処理
                if(m_flag_btnA_is_pressed){
                    setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                    setStateMachine(MEASURE, DO);
                };
                break;

            case DO://何もしない
            Serial.println("MEASURE,DO");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                setStateMachine(MEASURE, EXIT);
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
                if(m_flag_btnA_is_pressed){
                    setBtnAllFlgFalse();//すべてのフラグをfalseに戻す
                    setStateMachine(DATE, DO);
                };
                
                break;

            case DO://何もしない
            Serial.println("DATE,DO");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                setStateMachine(DATE, EXIT);
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
