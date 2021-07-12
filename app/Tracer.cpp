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

float Tracer::calc_prop_value() {
  const float Kp = 0.83;     //① sample04 の実験結果を反映する
  const int target = 10;     //② sample04 の実験結果を反映する
  const int bias = 0;
  
  int diff = colorSensor.getBrightness() - target; //③ 偏差求める
  return (Kp * diff + bias); //④ 調整値を求める
}

void Tracer::run() {
  msg_f("running...", 1);
  float turn = calc_prop_value(); //① 比例制御の調整値を求める
  int pwm_l = pwm + turn; //② 基準値と調整値を使って操作量を求める
  int pwm_r = pwm - turn; //② 基準値と調整値を使って操作量を求める
  leftWheel.setPWM(pwm_l);  
  rightWheel.setPWM(pwm_r); 
}
