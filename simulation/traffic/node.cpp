#include <iostream>
#include "node.h"

// 初期設定
void NODE::CONFIG(int ConfigID, double ConfigX, double ConfigY)
{
  ID=ConfigID;
  x=ConfigX;
  y=ConfigY;
  Used=1;
}

// x座標を取得
double NODE::X()
{
  return x;
}

// y座標を取得
double NODE::Y()
{
  return y;
}

double NODE::USED()
{
  return Used;
}
