#include <drawlib.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* --- 変数宣言 --- */
  float wait_time = 0.01; /* drawlibの待機時間 */

    /* バー */
  int barh = 20;   /* バーの高さ */
  int bardiv = 7;  /* バーの幅を画面の何分割にするか */
  int barw = DL_WIDTH / bardiv; /* バーの幅 */
  int barx = barw * (bardiv / 2); /* バーの位置(X座標) */
  int bary = 240;
  int t, k, x, y; /* dl_get_event用 */

    /* 得点 */
  int score = 0; /* スコア */
  int sx = DL_WIDTH / 2 - 150, sy = 50; /* スコアの表示位置(X座標, Y座標) */
  char sscore[10]; /* スコアを文字列化するための文字列 */

    /* スタート */
  int start = 0, end = 0; /* 開始，終了画面のループ判定用 */
  
    /* 血痕 */
  int bx = rand()%320, by = rand()%240, blv = 1, bt = 0, bh = 250;
   
  dl_initialize(1.0);
  
    /* --- 開始画面の表示 --- */
  dl_stop();
  dl_clear(DL_C("black"));
  dl_text("PUSH 'F' to start", 180, 250, 1.0, DL_C("white"), 1);
  dl_resume();
  
   /* --- Fキーが押されるまで待機 --- */
  start = 0;
  while(start == 0) {/* Fキーが押されたら start を 1 にする */ 
   while (dl_get_event(&t, &k, &x, &y)) {
     if (t == DL_EVENT_KEY && k == 'f') start = 1;
   dl_wait(wait_time);
   }
  }
  
    /* メインループ */
  while(1) {
    
    /* 入力キーの処理 */
    while (dl_get_event(&t, &k, &x, &y)) {
      if (t == DL_EVENT_KEY) {
        /* Dキーが押されたらバーのX座標を右にずらす */ 
      if (barx > 545){
        }else{
      if (k == 'd') {
          barx += 20;
         }
         }
        /* Aキーが押されたらバーのX座標を左にずらす */ 
      if (barx <= 0){
        }else{
      if (k == 'a') {
          barx -= 20;
         }
         }
        /* Wキーが押されたらバーのY座標を上にずらす */ 
      if (bary <= 0){
        }else{
      if (k == 'w') {
          bary -= 20;
         }
         }
        /* Sキーが押されたらバーのY座標を下にずらす */ 
      if (bary > 450){
        }else{
      if (k == 's') {
          bary += 20;
         }
         }
      }
    }
    /* 当たり判定 */
    if (((bx-barx-(barw/2))*(bx-barx-(barw/2)))<1000 && ((by-bary-(barh/2))*(by-bary-(barh/2)))<150){
    blv = 1;

    /* 血痕表示 */
    bx = rand()%320;
    by = rand()%240;
    score++;
    
    /* 難易度変化 */
    if (score == 5){
    bh -= 50;
    }
    if (score == 10){
    bh -= 50;
    }
    if (score == 15){
    bh -= 50;
    }
    bt = 0;
      }else{
    bt++;
      }
    /* 血痕レベル上昇 */
    if (bt >= bh){
    blv = 2;
    }
    if (bt >= bh*2){
    blv = 3;
    }
    if (bt >= bh*3){
    blv = 4;
    }
//    printf("%d,\n",bh);

    /* ゲームオーバー判定 */
    if (blv == 4)break;
    
    /* 描画処理 */
    dl_stop();
    dl_clear(DL_RGB(255,239,213));
    
    /* 血痕 */
    if (blv == 1){
    dl_circle(bx, by, 20, DL_RGB(255,0,0), 1, 1);
     }else if (blv == 2){
    dl_circle(bx, by, 40, DL_RGB(220,20,60), 1, 1);
    dl_circle(bx, by, 20, DL_RGB(255,0,0), 1, 1);
     }else if (blv == 3){
    dl_circle(bx, by, 60, DL_RGB(178,34,34), 1, 1);
    dl_circle(bx, by, 40, DL_RGB(220,20,60), 1, 1);
    dl_circle(bx, by, 20, DL_RGB(255,0,0), 1, 1);
      }
    
    /* 絆創膏 */
    dl_rectangle(barx, bary, barx + barw, bary + barh, DL_RGB(222,184,135), 1, 1);
    dl_rectangle(barx +20, bary +3, barx + barw -20, bary + barh -3, DL_RGB(245,222,179), 1, 1);
    
    /* 得点 */
    sprintf(sscore, "%5d", score);
    dl_text(sscore, sx, sy, 2.0, DL_C("black"), 2);
    dl_resume();
    dl_wait(wait_time);
   }
    
    /* ゲームオーバー */
    dl_stop();
    dl_clear(DL_C("black"));
    sprintf(sscore, "%5d", score);
    dl_text(sscore, sx, sy, 2.0, DL_C("white"), 2);
    dl_text("GAME OVER", 230, 220, 1.0, DL_C("white"), 1);
    dl_text("push 'F' to quit", 200, 300, 1.0, DL_C("white"), 1);
    dl_resume();
    
    while(end == 0) {
    while (dl_get_event(&t, &k, &x, &y)) {
     if (t == DL_EVENT_KEY && k == 'f')end = 1;
	}
   dl_wait(wait_time);
  }
  return 0;
}