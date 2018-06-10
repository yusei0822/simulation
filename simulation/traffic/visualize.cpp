#include <iostream>
#include <autogl.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <vector>
// #include "buildnetwork.h"
// #include "drawer.h"
// #include "car.h"
// #include "config.h"

using namespace std;

extern double PresentTime;
extern double TimeStep;

//再描画
static void redrawView();

//アイドルイベント
static void idleEvent();

// Animateボタン用関数
static void animateButtonCallback();

// Quitボタン用関数
static void quitButtonCallback();

int CarID = 0;
double Size;
// vector<CAR> CAR(CarMax);

void visualize()
{
  //ビューのパラメータ設定
  AutoGL_SetBackgroundColor(1, 1, 1);
  AutoGL_SetViewSize(200);           //ビューの大きさ
  AutoGL_SetViewCenter(0, 0, 0);     //注視点
  AutoGL_SetViewDirection(0, 0, 1);  //視線方向

  AutoGL_SetViewRedrawCallback(redrawView);

 /* おまじない */
  AutoGL_SetMode2D(AUTOGL_MODE_2D_SCALE);  /* マウスで回転 */
  AutoGL_SetDefaultCallbackInMode2D(NULL);
  AutoGL_EnableDragInMode2D();             /* ドラッグ有効 */
  AutoGL_EnableIdleEvent();
  AutoGL_SetPanelInMode2D();               /* 移動拡大縮小など */

  /* Animateボタンをつける */

  AutoGL_AddCallback(animateButtonCallback, "animateButtonCallback");
  AutoGL_SetLabel("Animate");

  /* Quitボタンをつける */
  AutoGL_AddCallback(quitButtonCallback, "qiutButtonCallback");
  AutoGL_SetLabel("Quit");

  Size=AutoGL_GetViewSize();

  //乱数指定
  srand((unsigned)time(NULL));

  // BuildNetwork();
}

void redrawView()
{
  // drawRoad();
  // drawSignal();
  // drawCar();
}

void animateButtonCallback(void)
{
    static int idleEventIsOn = 0;

    if (idleEventIsOn)
    {
        AutoGL_SetIdleEventCallback(NULL);
        idleEventIsOn = 0;
    }
    else
    {
        AutoGL_SetIdleEventCallback(idleEvent);
        idleEventIsOn = 1;
    }
}

void GENERATE_CAR()
{
  //for ノードに対してgenerateを実行する
  // node.generate();



  // int NodeID;
  // int LinkID;
  // double Velocity;
  // int Destination;
  //
  // Velocity=10;//(m/s)
  //
  // int P=rand()%16;
  // switch(P%4)
  //   {
  //   case 0 :
  //     Destination=TurnLeft;
  //     break;
  //   case 1 :
  //     Destination=TurnRight;
  //     break;
  //   default :
  //     Destination=GoStraight;
  //     break;
  //   }
  // NodeID=7*(int)(P/4);
  // LinkID=6*(int)(P/4);
  //
  // CAR[CarID].INITIAL_CONFIG(NodeID, LinkID, CarID, Velocity, Destination);
  // CarID++;
  //
  // if(CarID>CarMax)
  //   {
  //     CarID=0;
  //   }
}

//一つのタイムステップ
void idleEvent()
{
  PresentTime += TimeStep;

  int P=rand();
  if((int)P%2 == 0 && (int)(PresentTime*10)%20 == 0)
    {
      GENERATE_CAR();
    }

  AutoGL_DrawView();


}

void quitButtonCallback()
{
    exit(EXIT_SUCCESS);
}
