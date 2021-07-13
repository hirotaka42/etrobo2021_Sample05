/**
 * @file Tracer.cpp
 * @brief モーター制御
 * @author hirotaka42,Yuu-stack
 */

#include "Tracer.h" // <1>

Tracer::Tracer() : leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_3) {}

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
  float turn = calc_prop_value();
  int pwm_l = pwm + turn;
  int pwm_r = pwm - turn;
  setRightMotorPwm(pwm_l);  
  setLeftMotorPwm(pwm_r); 
  
  // 10ミリ秒待機
    sleep();


}

// 上限下限値の設定
int Tracer::limitPwmValue(const int value)
{
  if(value > MOTOR_PWM_MAX) {
    return MOTOR_PWM_MAX;
  } else if(value < MOTOR_PWM_MIN) {
    return MOTOR_PWM_MIN;
  }
  return value;
}

// PWM値を右モータにセット
void Tracer::setRightMotorPwm(const int pwm)
{
  rightWheel.setPWM(pwm);
}

// PWM値を左モータにセット
void Tracer::setLeftMotorPwm(const int pwm)
{
  leftWheel.setPWM(pwm);
}

//モータを停止
void Tracer::stopMotor()
{
  leftWheel.stop();
  rightWheel.stop();
}

//スリープ
void Tracer::sleep(int milliSec)
{
  clock.sleep(milliSec);
}

