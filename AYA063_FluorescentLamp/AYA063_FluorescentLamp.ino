//--------------------------------------------------------------------------------
// あらかじめ設定された点灯条件を再生するスケッチ
// 蛍光灯専用
// [AYA063_FluorescentLamp.ino]
// Copyright (c) 2021 Ayanosuke(Maison de DCC)
//
// 2021/8/20 SeqLed.inoからの移植
//           蛍光灯専用に既存パターン削除 ※SeqLightクラスを4つ生成させるとRAMがかなり消費される
//
// http://maison-dcc.sblo.jp/ http://dcc.client.jp/ http://ayabu.blog.shinobi.jp/
// https://twitter.com/masashi_214
//
// DCC電子工作連合のメンバーです
// https://desktopstation.net/tmi/ https://desktopstation.net/bb/index.php
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//
// Atiny85 PB4(3pin) analog
// Atiny85 PB3(2pin) digital
// Atint85 PB1(6pin) analog
// Atiny85 PB0(5pin) analog
//--------------------------------------------------------------------------------

#include "SeqLight.h"
  
unsigned long PreviosTime = 0;
unsigned long PreviosTime2 = 0;

SeqLight LedA = SeqLight(4,1);
SeqLight LedB = SeqLight(3,2);  // これだけDigital出力なので、蛍光灯キレそうなやつを実演
SeqLight LedC = SeqLight(1,1);
SeqLight LedD = SeqLight(0,1);

void setup() {
  PreviosTime = millis();
  PreviosTime2 = PreviosTime;
  LedA.OnOff(ON);
  LedB.OnOff(ON);
  LedC.OnOff(ON);
  LedD.OnOff(ON);
}

void loop() {
  static int sel = 0;
  if( (millis() - PreviosTime ) >= 10 ){  // 10:10msec 前回から10ms経過したかチェック
    PreviosTime = millis();
    LedA.stateCheck();
    LedB.stateCheck();
    LedC.stateCheck();
    LedD.stateCheck();
  }
  if( (millis() - PreviosTime2 ) >= 5000 ){  // 5000:5000msec 前回から5000ms経過したかチェック
    PreviosTime2 = millis();
    switch(sel){
      case OFF:
              LedA.OnOff(OFF);
              LedB.OnOff(OFF);
              LedC.OnOff(OFF);
              LedD.OnOff(OFF);
              sel = 1;
              break;
      case ON:
              LedA.OnOff(ON);
              LedB.OnOff(ON);
              LedC.OnOff(ON);
              LedD.OnOff(ON);
              sel = 0;
              break;                            
      default:
              break;
    }
  }
}
