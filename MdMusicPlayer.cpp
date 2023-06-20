#include "MdMusicPlayer.h"
#include "AudioFileSourceID3.h"
#include "AudioFileSourceSD.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

AudioGeneratorMP3* mp3;
AudioFileSourceSD* file;
AudioOutputI2S* out;
AudioFileSourceID3* id3;

File musicfolder;
File entry;
//musicフォルダを開き、次に再生する楽曲を グローバル変数entry にセットする。
void MdMusicPlayer::init()//音楽プレイヤーの初期化
{
    //pinMode(10, OUTPUT);

    SD.begin();
    musicfolder = SD.open("/music");
    if (!musicfolder) {
        // musicフォルダが無かった場合、開けなかった場合
        Serial.println("musicfolder open error");
    } else {
        entry = musicfolder.openNextFile();
    }
}
//グローバル変数entry　にセットされた楽曲のファイル名を取得しそれを返す。
char* MdMusicPlayer::getTitle()//音楽ファイルのファイル名を表示する
{
    return (char*)entry.name();
}


//グローバル変数entry に次の楽曲をセットする。次の音楽ファイルがない場合、フォルダの先頭に戻り一番最初のファイルを次の楽曲としてセットする。
void MdMusicPlayer::selectNextMusic()//次の音楽ファイルを開く
{
    entry = musicfolder.openNextFile();
    if (!entry) {
        musicfolder.rewindDirectory();
        entry = musicfolder.openNextFile();
        Serial.println("return latestfile");
    }
}
//グローバル変数file, id3, out, mp3 の各クラスのインスタンスを生成し、そのアドレスを格納する音楽ファイルのデコードを開始する。
void MdMusicPlayer::prepareMP3()//音楽ファイルの再生に必要なインスタンスの生成とデコードを開始する
{
    file = new AudioFileSourceSD(entry.path());
    id3 = new AudioFileSourceID3(file);
    out = new AudioOutputI2S(0, 1); // Output to builtInDAC
    out->SetOutputModeMono(true);
    out->SetGain(0.045);
    mp3 = new AudioGeneratorMP3();
    mp3->begin(id3, out);
}
//音楽ファイルが現在デコード中かを確認し、デコード中ならtrue、そうでないならfalseを返す。
bool MdMusicPlayer::isRunningMP3()//音楽ファイルを再生中か確認する
{
    return mp3->isRunning();
}
//音楽ファイルを再生するために楽曲データのデコードを行う。次のデータがある場合はtrue、データがない（楽曲の終了時）はfalseを返す
bool MdMusicPlayer::playMP3()//音楽ファイルを再生する
{
    return mp3->loop();
}
//音楽ファイルのデコードを停止する。
void MdMusicPlayer::stopMP3()//音楽ファイルの再生を停止する
{
    mp3->stop();
}
