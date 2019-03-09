//-----------------------------------------------------------Motor---------------------------------------------------------------//
//declaration of variables & object
#include <SoftwareSerial.h>
#include <Cytron_G15Shield.h>
#define G15_lf 1
#define G15_lb 2
#define G15_rf 3
#define G15_rb 4
#define G15_dl 5
#define G15_dr 6
#define G15_s 7
#define LED 13
Cytron_G15Shield g15(2, 3, 8); // SoftwareSerial: Rx, Tx and Control pin
//-----------------------------------------------------------Functions---------------------------------------------------------------//
void setup() {
  //initialize the arduino main board's serial/UART and Control Pins
  //CTRL pin for G15 =3 and AX12 =8
  g15.begin(38400); 
  g15.setWheelMode(G15_lf);
  g15.setWheelMode(G15_lb);
  g15.setWheelMode(G15_rf);
  g15.setWheelMode(G15_rb);
  g15.setWheelMode(G15_dl);
  g15.setWheelMode(G15_dr);
  g15.setWheelMode(G15_s);
  Serial.begin(9600); //Start the serial on computer
  delay(1000);
}

void turnleft(int speed, int time)
{
  g15.setWheelMode(G15_lf);
  g15.setWheelMode(G15_lb);
  g15.setWheelMode(G15_rf);
  g15.setWheelMode(G15_rb);
  g15.setWheelSpeed(G15_lf,speed,CW); 
  g15.setWheelSpeed(G15_lb,speed,CW);
  g15.setWheelSpeed(G15_rf,speed,CW);
  g15.setWheelSpeed(G15_rb,speed,CW);
  delay(time);
}

void turnright(int speed, int time)
{
  g15.setWheelMode(G15_lf);
  g15.setWheelMode(G15_lb);
  g15.setWheelMode(G15_rf);
  g15.setWheelMode(G15_rb);
  g15.setWheelSpeed(G15_lf,speed,CCW); 
  g15.setWheelSpeed(G15_lb,speed,CCW);
  g15.setWheelSpeed(G15_rf,speed,CCW);
  g15.setWheelSpeed(G15_rb,speed,CCW);
  delay(time);
}

void moveforward(int speed, int time)
{
  g15.setWheelMode(G15_lf);
  g15.setWheelMode(G15_lb);
  g15.setWheelMode(G15_rf);
  g15.setWheelMode(G15_rb);
  g15.setWheelSpeed(G15_lf,speed,CW); 
  g15.setWheelSpeed(G15_lb,speed,CW);
  g15.setWheelSpeed(G15_rf,speed,CCW);
  g15.setWheelSpeed(G15_rb,speed,CCW);
  delay(time);
}

void movebackward(int speed, int time)
{
  g15.setWheelMode(G15_lf);
  g15.setWheelMode(G15_lb);
  g15.setWheelMode(G15_rf);
  g15.setWheelMode(G15_rb);
  g15.setWheelSpeed(G15_lf,speed,CCW); 
  g15.setWheelSpeed(G15_lb,speed,CCW);
  g15.setWheelSpeed(G15_rf,speed,CW);
  g15.setWheelSpeed(G15_rb,speed,CW);
  delay(time);
}

void stop_motion(int time)
{
  g15.exitWheelMode(G15_lf);
  g15.exitWheelMode(G15_lb);
  g15.exitWheelMode(G15_rf);
  g15.exitWheelMode(G15_rb);
  delay(time);
}

void loop() {
  if (digitalRead(7)==LOW && digitalRead(6)==LOW && digitalRead(5)==LOW && digitalRead(4)==HIGH) {
    Serial.println("Turning Left");
    turnleft(300,0);
  }
  else if (digitalRead(7)==LOW && digitalRead(6)==LOW && digitalRead(5)==HIGH && digitalRead(4)==LOW) {
    turnright(300,0);
  }
  else if (digitalRead(7)==LOW && digitalRead(6)==LOW && digitalRead(5)==HIGH && digitalRead(4)==HIGH) {
    moveforward(300,0);
  }
  else if (digitalRead(7)==LOW && digitalRead(6)==HIGH && digitalRead(5)==LOW && digitalRead(4)==LOW) {
    movebackward(300,0);
  }
  else if (digitalRead(7)==LOW && digitalRead(6)==HIGH && digitalRead(5)==LOW && digitalRead(4)==LOW) {
    movebackward(300,0);
  }
  else if (digitalRead(7)==LOW && digitalRead(6)==HIGH && digitalRead(5)==LOW && digitalRead(4)==LOW) {
    movebackward(300,0);
  }
  else if (digitalRead(7)==LOW && digitalRead(6)==LOW && digitalRead(5)==LOW && digitalRead(4)==LOW) {
    stop_motion(10);
  }
  else {
    stop_motion(10);
  }
}
