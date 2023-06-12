#include "AppControl.h"
#include <Arduino.h>
#include <M5Stack.h>

MdLcd mlcd;//インスタンス化
MdWBGTMonitor mwbgt;//インスタンス化
MdMusicPlayer mmplay;//インスタンス化
MdMeasureDistance mmdist;//インスタンス化
MdDateTime mdtime;//インスタンス化

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

FocusState AppControl::getFocusState()
{
    return m_focus_state;
}

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
{mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
}

void AppControl::focusChangeImg(FocusState current_state, FocusState next_state)
{
}
//熱中症画面を表示
void AppControl::displayWBGTInit()
{mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
}

void AppControl::displayTempHumiIndex()
{
}
//ミュージック画面を表示
void AppControl::displayMusicInit()
{mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);
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
//距離測定画面を表示
void AppControl::displayMeasureInit()
{mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);
}
//下矢印を表示
void AppControl::displaydownarrowInit()
{mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH,DOWN_X_CRD,UP_Y_CRD);
}
//上矢印を表示
void AppControl::displayuparrowInit()
{mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH,UP_X_CRD,UP_Y_CRD);
}
//決定を表示
void AppControl::displaydecisionInit()
{mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH,DECIDE_X_CRD,DECIDE_Y_CRD);
}

void AppControl::displayMeasureDistance()
{
}

//時刻表示画面を表示
void AppControl::displayDateInit()
{mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH,MENU_DATE_X_CRD,MENU_DATE_Y_CRD);
}

void AppControl::displayDateUpdate()
{
}

void AppControl::controlApplication()
{
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
                delay(2000);
                Serial.println("MENU,ENTRY");

                        //メニュー画面表示
                        mlcd.fillBackgroundWhite();//背景白に変更
                        displayMenuInit();
                        
                        displayMusicInit();//音楽プレイヤー
                        displayMeasureInit();//距離測定
                        displayDateInit();//時刻表示
                        displaydownarrowInit();//下矢印
                        displayuparrowInit();//上矢印
                        displaydecisionInit();//決定

                break;

            case DO:
            Serial.println("MENU,DO");
            //中ボタンを押下
                Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);

                break;

            case EXIT:
            Serial.println("MENU,EXIT");
                Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
            default:
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
                delay(2000);
                break;

            case DO:
            Serial.println("MEASURE,DO");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
                break;

            case EXIT:
            Serial.println("MEASURE,EXIT");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
                break;

            default:
                break;
            }

            break;

        case DATE:

            switch (getAction()) {
            case ENTRY:
            Serial.println("DATE,ENTRY");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
                break;

            case DO:
            Serial.println("DATE,DO");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
                break;

            case EXIT:
            Serial.println("DATE,EXIT");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
                break;

            default:
            Serial.println("DATE,ENTRY");
            Serial.println(m_flag_btnA_is_pressed);
                Serial.println(m_flag_btnB_is_pressed);
                Serial.println(m_flag_btnC_is_pressed);
                delay(2000);
                break;
            }

        default:
            break;
        }
    }
}
