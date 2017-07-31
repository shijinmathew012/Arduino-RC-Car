#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int throttle;
int aileron;
int reverse;
double normaileron;
double normThrottle;
double leftM;
double rightM;

void setup() {

  Serial.begin(9600);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
}

void loop() {
  throttle = pulseIn(14, HIGH);
  aileron = pulseIn(15, HIGH);
  reverse = pulseIn(16, HIGH);

  normaileron = map(aileron, 1000, 2000, -255, 255);
  normThrottle = map(throttle, 1000, 2000, 0, 255);
  normaileron = constrain(normaileron, -255, 255);
  normThrottle = constrain(normThrottle, 0, 255);

  leftM = normThrottle + normaileron;
  leftM = constrain(leftM, 0, 255);
  rightM = normThrottle - normaileron;
  rightM = constrain(rightM, 0, 255);
  Serial.print(leftM);
  Serial.print("     ");
  Serial.println(rightM);

  if (reverse > 1700) {
    motor1.setSpeed(leftM);
    motor2.setSpeed(leftM);
    motor3.setSpeed(rightM);
    motor4.setSpeed(rightM);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    delay(10);
  }
  else {


    motor1.setSpeed(leftM);
    motor2.setSpeed(leftM);
    motor3.setSpeed(rightM);
    motor4.setSpeed(rightM);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    delay(10);



  }
}
