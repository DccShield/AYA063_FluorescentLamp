//--------------------------------------------------------------------------------
// あらかじめ設定された点灯条件を再生するスケッチ
// [SeqLight.cpp]
// Copyright (c) 2020 Ayanosuke(Maison de DCC)
// https://desktopstation.net/bb/index.php
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------
// SeqLightクラス
//--------------------------------------------------------------------------------
#include <Arduino.h>
#include"SeqLight.h"

// コンストラクタ
SeqLight::SeqLight( unsigned char ch, unsigned char mode)
{
  port = ch;
  pinMode(port, OUTPUT);
  state = ST_IDLE;
  
  switch(mode){
    case 0: ptn = ptn1;
    break;
    case 1: ptn = ptn1;
    break;
    case 2: ptn = ptn2;
    break;
    default: ptn = ptn1;
    break;
  }
}  

void SeqLight::OnOff(unsigned char sw)
{
  if( sw == 0)
    state = ST_OFF;
  else if( sw == 1)
    state = ST_ON;
}

//---------------------------------------------------------------------
// FX効果ステートマシン
// 10ms周期で起動
// unsigned chart ptn[4][5]{{'I',0,0,1},{'S',20,255,1},{'S',40,0,1},{'E',0,0,1}};
//---------------------------------------------------------------------
void SeqLight::stateCheck(){

  switch(state){
    case ST_IDLE:
                break;

     case ST_ON:
                adr = 0;
                pwmRef = 0;
                analogWrite( port, pwmRef );          
                state = ST_FARST;
                break;
    case ST_OFF:
                adr = 0;
                pwmRef = 0;
                analogWrite( port, 0 );          
                state = ST_IDLE;
                break;
 
    case ST_FARST: //3
                pwmRef = ptn[adr][2];
                analogWrite( port, pwmRef ); 
                nowPwm = pwmRef;
                nextPwm = ptn[adr+1][2];
                styTime = ptn[adr+1][1];
              
                if(styTime == 0 || ptn[adr+1][0]=='O' ){
                  deltPwm = nextPwm - nowPwm;
                } else
                  deltPwm = (nextPwm - nowPwm) / (float)styTime;             
               
                if(nextPwm - nowPwm == 0){
                  updownFlg = STY;
                  state = ST_STAY;
                  break;
                } else if(nextPwm - nowPwm < 0)
                  updownFlg = DOWN;
                else
                  updownFlg = UP;
                if(ptn[adr+1][0]=='O')
                  state = ST_STAY;                
                else
                  state = ST_RUN;
                break;
                
    case ST_STAY://4
                  styTime --;
                  if(styTime <= 0)
                    state = ST_NEXT;
                  break;

    case ST_RUN://5
                  pwmRef = pwmRef + deltPwm;
                  if((updownFlg == DOWN) && (pwmRef <= nextPwm)){
                    analogWrite( port,(int)nextPwm);
                    state = ST_NEXT;
                  } else if((updownFlg == UP) && (pwmRef >= nextPwm)){
                    analogWrite( port,(int)nextPwm);
                    state = ST_NEXT;
                  } else {
                    analogWrite( port,(int)pwmRef);
                  }
                  if(ptn[adr][0]=='O')
                    state = ST_STAY;
                  break;
    case ST_NEXT://6
                  adr++;
                 
                  if(ptn[adr][0]=='E'){
                    state = ST_IDLE;
                    break;
                  }
                  if(ptn[adr][0]=='L'){
                    adr = 0;
                    state = ST_FARST;
                    break;
                  }
                  
                  nowPwm = ptn[adr-1][2];
                  nextPwm = ptn[adr][2];
                  styTime = ptn[adr][1];
                if(styTime == 0|| ptn[adr][0]=='O'){
                  deltPwm = nextPwm - nowPwm;
                } else
                  deltPwm = (nextPwm - nowPwm) / (float)styTime;
                  if(nextPwm - nowPwm == 0){
                    updownFlg = STY;
                    styTime = ptn[adr][1];
                    state = ST_STAY;
                    break;
                  }
                  else if(nextPwm - nowPwm < 0)
                    updownFlg = DOWN;
                  else
                    updownFlg = UP;
                  state = ST_RUN;
                  break;
    default:
                  break;
  }
}
