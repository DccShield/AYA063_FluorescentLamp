//--------------------------------------------------------------------------------
// あらかじめ設定された点灯条件を再生するスケッチ
// [SeqLight.h]
// Copyright (c) 2021 Ayanosuke(Maison de DCC)
// https://desktopstation.net/bb/index.php
//
// 蛍光灯専用にカスタム
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//--------------------------------------------------------------------------------
#ifndef SeqLight_h
#define SeqLight_h

  enum{
    FastOn = 1,
    SlowOn,
    TriangleWave,
    Random,
    MarsLight,
    FlashLight,
    SinglePulesStrobe,
    DoublePulseStrobe,
    MediumPulseStrobo,
    FluorescentLamp,
    BrokenFluorescentLamp,
  };

  enum{
        OFF = 0,
        ON,
  };


class SeqLight
{
public:
  SeqLight(unsigned char ch,unsigned char mode);
  void stateCheck();
  void OnOff(unsigned char sw);
  
private:
  int state;// = ST_IDLE;
  unsigned char port;
  unsigned char mode;
  char updownFlg;

  unsigned char adr = 0;      // アドレス
  
  float pwmRef =0;
  float deltPwm;            // 10msあたりのpwm増加量
  
  int nowPwm;
  int nextPwm;
  int styTime;

  unsigned char (*ptn)[3];
  
  enum{
    ST_IDLE = 0,
    ST_ON,
    ST_OFF,
    ST_FARST,
    ST_STAY,
    ST_RUN,
    ST_NEXT,
  };

  enum{
    DOWN = 0,
    STY,
    UP,
  };

//FX効果
//Cmd,Time,Val,Frq
//I:初期状態,O:出力,S:スイープ,L:ループ,E:終了

unsigned char ptn1[12][3]={
                          {'I',  0,  0},
                          {'O', 10,125},
                          {'O',  0,  0},
                          {'O',  0, 55},
                          {'O', 20,  0},
                          {'O',  0,  0},
                          {'O', 10,125},
                          {'O',  0,  0},
                          {'O', 10, 50},
                          {'O', 50, 40},
                          {'O', 50,255},
                          {'E',  0, 0}}; //グロー管蛍光灯(Fluorescent lamp)

unsigned char ptn2[9][3]={
                          {'I',  0,  0},
                          {'O',  0,255},
                          {'O',  0,  0},
                          {'O',  0,255},
                          {'O', 30,  0},
                          {'O', 30, 40},
                          {'O', 50,255},
                          {'O', 70,  0},
                          {'L',  0,  0}}; //グロー管蛍光灯切れそう(broken Fluorescent lamp
};

#endif
