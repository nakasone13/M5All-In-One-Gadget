/* インクルードガード */
#pragma once

#include <M5Stack.h>

class MdMusicPlayer // classの定義
{
private: // privateはクラス内からしかアクセスできない
public: // publicはどこからでもアクセス可能
    void init();//音楽プレイヤーの初期化
    char* getTitle();//音楽ファイルのファイル名を表示する
    void selectNextMusic();//次の音楽ファイルを開く
    void prepareMP3();//音楽ファイルの再生に必要なインスタンスの生成とデコードを開始する
    bool isRunningMP3();//音楽ファイルを再生中か確認する
    bool playMP3();//音楽ファイルを再生する
    void stopMP3();//音楽ファイルの再生を停止する
};
