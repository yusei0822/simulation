class Car{
private:
  // 現在の速度
  int velocity;
  // x座標
  int x;
  // xの移動量
  int dx;

public:
  // コンストラクタの宣言
  Car(int);
  // 速度を決定する関数
  void accelerate();
};
