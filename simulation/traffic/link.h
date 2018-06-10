class LINK
{
  int ID;
  int Used;
  double Length;
  double DirectionX;
  double DirectionY;
  double StartX;
  double StartY;
  double EndX;
  double EndY;
  double SpeedLimit;

public:

  void CONFIG(int StartNodeID, int EndNodeID, double LinkSpeedLimit);
  int USED();
  double DIRECTION_X();
  double DIRECTION_Y();
  double START_X();
  double START_Y();
  double END_X();
  double END_Y();
  double SPEED_LIMIT();
};
