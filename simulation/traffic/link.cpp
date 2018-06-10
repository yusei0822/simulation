#include <autogl.h>
#include <math.h>
#include <vector>
#include "node.h"
#include "link.h"
#include "calculation.h"

using namespace std;

extern vector<NODE> NODE;

void LINK::CONFIG(int StartNodeID, int EndNodeID ,double LinkSpeedLimit){
  Used=1;

  StartX=NODE[StartNodeID].X();
  StartY=NODE[StartNodeID].Y();
  EndX=NODE[EndNodeID].X();
  EndY=NODE[EndNodeID].Y();

  Length=length(StartX, StartY, EndX, EndY);

  DirectionX=(EndX-StartX)/Length;

  DirectionY=(EndY-StartY)/Length;

  SpeedLimit=LinkSpeedLimit;

}

int LINK::USED(){
  return Used;
}

double LINK::DIRECTION_X(){
  return DirectionX;
}

double LINK::DIRECTION_Y(){
  return DirectionY;
}

double LINK::START_X(){
  return StartX;
}

double LINK::START_Y(){
  return StartY;
}

double LINK::END_X(){
  return EndX;
}

double LINK::END_Y(){
  return EndY;
}

double LINK::SPEED_LIMIT(){
  return SpeedLimit;
}
