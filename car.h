class Car{
private:
  // 現在の速度
  int velocity;
  // x座標,y座標
  int x,y;
  // 車の横、縦幅
  int width,height;

public:
  // コンストラクタの宣言
  Car(int);
  // 速度を決定する関数
  void accelerate();
};
