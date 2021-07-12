#include "Tracer.h" // <1>

Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_3) { // <2>
  }

void Tracer::init() {
  init_f("Tracer");
}

void Tracer::terminate() {
  msg_f("Stopped.", 1);
  leftWheel.stop();  // <1>
  rightWheel.stop();
}

void Tracer::run() {
  const float Kp = 0.83; //① 比例係数（1より小さい値で検討しましょう） 
  const int target = 10; //② 白と黒の中間値を目標値とする（測った値があれば、それを使いましょう）
  const int bias = 0;    //③ 調整値にいつも一定の値（バイアス）を追加しておきたい場合に設定する
  msg_f("running...", 1);
  int diff = colorSensor.getBrightness() - target; //④ 偏差を求める
  float turn = Kp * diff + bias; //⑤ 調整値を求める
  leftWheel.setPWM(pwm + turn);  //⑥ 左右の車輪に調整後の操作量を与えた
  rightWheel.setPWM(pwm - turn); //⑥ 左右の車輪に調整後の操作量を与えた
}
