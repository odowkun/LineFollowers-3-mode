// Kadek Yudha Ananda Putra 
// Ig ; @ydha_ananda


#include <AFMotor.h>
#define speedRatio    1.0f

int inh = A5;         //ena
int selA = A4;        //A
int selB = A3;        //B
int selC = A2;        //C
int sensor_depan = A1; //Out
int data_sensor_depan[8];

const int MOTOR_1 = 1;
const int MOTOR_2 = 2;
const int MOTOR_3 = 3;
const int MOTOR_4 = 4;

AF_DCMotor motor1(MOTOR_1, MOTOR12_1KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor2(MOTOR_2, MOTOR12_1KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor3(MOTOR_3, MOTOR34_1KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor4(MOTOR_4, MOTOR34_1KHZ); // create motor object, 64KHz pwm
void setup() {
  pinMode (inh, OUTPUT);
  pinMode (selA, OUTPUT);
  pinMode (selB, OUTPUT);
  pinMode (selC, OUTPUT);
  
  // put your setup code here, to run once:
  motor1.setSpeed(speedRatio * 200);          // set the motor speed to 0-255
  motor2.setSpeed(speedRatio * 200);
  motor3.setSpeed(speedRatio * 200);
  motor4.setSpeed(speedRatio * 200);

  Serial.begin(9600); 
}

void loop() {
  sensing();

  int maxSensor = 0;
  int idxSensor = 0;
  for (byte i = 0; i < 8; i++) // iterasi = i, tidak perlu di deklarasi
  {
    if (maxSensor < data_sensor_depan[i])
    {
      maxSensor = data_sensor_depan[i];
      idxSensor = i;
    }
  }

  if ((idxSensor == 3 || (idxSensor == 4)) && abs(data_sensor_depan[3] - data_sensor_depan[4]) < 40)
  {
    //lurus
    maju();
  }
  else
  {
    switch (idxSensor)
    {
      case 0:                         //kiri tajam
        kiri_tajam();
        break;
        
      case 1:                         //kiri kuat
        kiri_kuat();
        break;

      case 2:                         //kiri
        kiri();
        break;

      case 3:                         //kiri halus
        kiri_halus();
        break;

      case 4:                         //kanan halus
        kanan_halus();
        break;

      case 5:                         //kanan
        kanan();
        break;

      case 6:                         //kanan kuat
        kanan_kuat();
        break;

      case 7:                         //kanan tajam
        kanan_tajam();
        break;
    }
  }
  
}

//motor1 => roda kiri depan 
//motor2 => roda kiri belakang
//motor3 => roda kanan belakang
//motor4 => roda kanan depan
void maju() {
  motor1.setSpeed(speedRatio * 150);
  motor2.setSpeed(speedRatio * 150);
  motor3.setSpeed(speedRatio * 150);
  motor4.setSpeed(speedRatio * 150);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void kiri_tajam(){
  motor2.setSpeed(speedRatio * 115);
  motor3.setSpeed(speedRatio * 115);
  motor4.setSpeed(speedRatio * 115);
  motor1.setSpeed(speedRatio * 115);
  motor1.run(BACKWARD);
  motor3.run(FORWARD);
  motor2.run(BACKWARD);
  motor4.run(FORWARD);
}

void kiri_kuat(){
  motor2.setSpeed(speedRatio * 15);
  motor3.setSpeed(speedRatio * 125);
  motor1.setSpeed(speedRatio * 15);
  motor4.setSpeed(speedRatio * 125);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor1.run(BACKWARD);
  motor4.run(FORWARD);
}

void kiri(){
  motor2.setSpeed(speedRatio * 35);
  motor3.setSpeed(speedRatio * 135);
  motor1.setSpeed(speedRatio * 35);
  motor4.setSpeed(speedRatio * 135);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor1.run(FORWARD);
}

void kiri_halus(){
  motor2.setSpeed(speedRatio * 60);
  motor3.setSpeed(speedRatio * 115);
  motor1.setSpeed(speedRatio * 60);
  motor4.setSpeed(speedRatio * 115);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor1.run(FORWARD);
}

void kanan_halus(){
  motor2.setSpeed(speedRatio * 115);
  motor3.setSpeed(speedRatio * 60);
  motor1.setSpeed(speedRatio * 115);
  motor4.setSpeed(speedRatio * 60);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor1.run(FORWARD);
}

void kanan(){
  motor2.setSpeed(speedRatio * 135);
  motor3.setSpeed(speedRatio * 35);
  motor1.setSpeed(speedRatio * 135);
  motor4.setSpeed(speedRatio * 35);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor1.run(FORWARD);
}

void kanan_kuat(){
  motor2.setSpeed(speedRatio * 125);
  motor3.setSpeed(speedRatio * 15);
  motor3.setSpeed(speedRatio * 125);
  motor4.setSpeed(speedRatio * 15);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor1.run(FORWARD);
  motor4.run(BACKWARD);
}

void kanan_tajam(){
  motor2.setSpeed(speedRatio * 115);
  motor3.setSpeed(speedRatio * 115);
  motor4.setSpeed(speedRatio * 115);
  motor1.setSpeed(speedRatio * 115);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor1.run(FORWARD);
  motor4.run(BACKWARD);
}

void sensing() {
  digitalWrite(inh, LOW);
  digitalWrite(selA, LOW);
  digitalWrite(selB, LOW);
  digitalWrite(selC, LOW);
  delay(5);
  data_sensor_depan[0] = analogRead(sensor_depan);
  digitalWrite(selA, HIGH);
  digitalWrite(selB, LOW);
  digitalWrite(selC, LOW);
  delay(5);
  data_sensor_depan[1] = analogRead(sensor_depan);
  digitalWrite(selA, LOW);
  digitalWrite(selB, HIGH);
  digitalWrite(selC, LOW);  
  delay(5);
  data_sensor_depan[2] = analogRead(sensor_depan);
  digitalWrite(selA, HIGH);
  digitalWrite(selB, HIGH);
  digitalWrite(selC, LOW);
  delay(5);
  data_sensor_depan[3] = analogRead(sensor_depan);
  digitalWrite(selA, LOW);
  digitalWrite(selB, LOW);
  digitalWrite(selC, HIGH);
  delay(5);
  data_sensor_depan[4] = analogRead(sensor_depan);
  digitalWrite(selA, HIGH);
  digitalWrite(selB, LOW);
  digitalWrite(selC, HIGH);
  delay(5);
  data_sensor_depan[5] = analogRead(sensor_depan);
  digitalWrite(selA, LOW);
  digitalWrite(selB, HIGH);
  digitalWrite(selC, HIGH);
  delay(5);
  data_sensor_depan[6] = analogRead(sensor_depan);
  digitalWrite(selA, HIGH);
  digitalWrite(selB, HIGH);
  digitalWrite(selC, HIGH);
  delay(5);
  data_sensor_depan[7] = analogRead(sensor_depan);
}
void tampil_sensor() {
  Serial.print(data_sensor_depan[0]);
  Serial.print(", ");
  Serial.print(data_sensor_depan[1]);
  Serial.print(", ");
  Serial.print(data_sensor_depan[2]);
  Serial.print(", ");
  Serial.print(data_sensor_depan[3]);
  Serial.print(", ");
  Serial.print(data_sensor_depan[4]);
  Serial.print(", ");
  Serial.print(data_sensor_depan[5]);
  Serial.print(", ");
  Serial.print(data_sensor_depan[6]);
  Serial.print(", ");
  Serial.println(data_sensor_depan[7]);
} 
