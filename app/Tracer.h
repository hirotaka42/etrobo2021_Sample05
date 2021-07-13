/**
 * @file Tracer.h
 * @brief モーター制御
 * @author hirotaka42,Yuu-stack
 */

#include "ev3api.h"
#include "Motor.h"       // <1>
#include "ColorSensor.h" // <2>
#include "util.h"        // <3>
#include "Clock.h"  // <3>


using namespace ev3api;  // <4>

class Tracer {  // <1>
public:
  static const int MOTOR_PWM_MAX = 100;
  static const int MOTOR_PWM_MIN = -100;
  Tracer();
  void run();       // <2>
  void init();
  void terminate();
  /**
   * モータにPWM値をセット
   * @param pwm PWM値
   */
  void setRightMotorPwm(const int pwm);
  void setLeftMotorPwm(const int pwm);

  /**
   * 停止する
   */
  void stopMotor();

  /**
   * 自タスクスリープ
   * @param milliSec スリープ時間(ミリ秒)
   */
  void sleep(int milliSec = 10);


private:
  ev3api::Motor rightWheel;
  ev3api::Motor leftWheel;
  ev3api::Clock clock;
  
  ColorSensor colorSensor; // <3>
  const int8_t mThreshold = 20;  // <4>
  const int8_t pwm = (Motor::PWM_MAX) / 6;
  /**
   * モータに設定するPWM値の制限
   * @param value 入力されたPWM値
   * @return 制限されたPWM値
   */
  int limitPwmValue(const int value);

  float calc_prop_value(); //① calc_prop_value メソッドを追加した
};
