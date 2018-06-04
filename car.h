class Car{
private:
  // つぎのタイムステップでの加速度
  double acceleration;
  // 現在の速度
  double velocity;
  // x座標
  double x;
  // xの移動量
  double dx;


public:
  // コンストラクタの宣言
  Car(double velocity);
  // 加速度を決定する関数
  void accelerate();

  void run();



};
