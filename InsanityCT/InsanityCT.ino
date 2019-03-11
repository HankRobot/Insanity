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
  g15.begin(115200); 
  g15.setWheelMode(G15_lf);
  g15.setWheelMode(G15_lb);
  g15.setWheelMode(G15_rf);
  g15.setWheelMode(G15_rb);
  g15.exitWheelMode(G15_dl);
  g15.exitWheelMode(G15_dr);
  g15.exitWheelMode(G15_s);
  Serial.begin(9600); //Start the serial on computer
  delay(1000);
}

void turnleft(int speed, int time){
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

void turnright(int speed, int time){
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

void moveforward(int speed, int time){
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

void movebackward(int speed, int time){
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

void stop_motion(int time){
  g15.exitWheelMode(G15_lf);
  g15.exitWheelMode(G15_lb);
  g15.exitWheelMode(G15_rf);
  g15.exitWheelMode(G15_rb);
  delay(time);
}

void turnangle(int start,int endd,double timee, int ID){
  double x = abs((((start-endd)/timee)/378)  * 1023);
  Serial.println(x);
  g15.setSpeed(ID,x);
  g15.setPosAngle(ID,endd);
}

void setangle(int ID,int start){
  g15.setSpeed(ID, 200); // Set G15 (ID = 1) speed to 500,
  g15.setPosAngle(ID, start);
}

void excavate(){
  //first step
  setangle(G15_dl,270);
  setangle(G15_dr,90);
  setangle(G15_s,350);
  delay(1000);

  //second step
  turnangle(270,270,1.0,G15_dl);
  turnangle(90,90,1.0,G15_dr);
  turnangle(350,290,1.0,G15_s);
  delay(1000);

  //third step
  turnangle(270,205,2.0,G15_dl);
  turnangle(90,155,2.0,G15_dr);
  turnangle(290,290,2.0,G15_s);
  delay(2000);

  //fourth step
  turnangle(205,270,2.0,G15_dl);
  turnangle(155,90  ,2.0,G15_dr);
  turnangle(290,290,2.0,G15_s);
  delay(2000);

  //fifth step
  turnangle(270,270,1.0,G15_dl);
  turnangle(90,90  ,1.0,G15_dr);
  turnangle(290,350,1.0,G15_s);
  delay(1000);

}

void shake(){

}

void pullup(){
  
}

void pulldown(){
  
}

void loop() {
  /*
  if (digitalRead(7)==LOW && digitalRead(6)==LOW && digitalRead(5)==LOW && digitalRead(4)==HIGH) { //0001
    turnleft(500,0);
  }
  else if (digitalRead(7)==LOW && digitalRead(6)==LOW && digitalRead(5)==HIGH && digitalRead(4)==LOW) { //0010
    turnright(500,0);
  }
  else if (digitalRead(7)==LOW && digitalRead(6)==LOW && digitalRead(5)==HIGH && digitalRead(4)==HIGH) { //0011
    moveforward(500,0);
  }
  else if (digitalRead(7)==LOW && digitalRead(6)==HIGH && digitalRead(5)==LOW && digitalRead(4)==LOW) { //0100
    movebackward(500,0);
  }
  else if (digitalRead(7)==LOW && digitalRead(6)==HIGH && digitalRead(5)==LOW && digitalRead(4)==HIGH) { //0101
    excavate();
  }
  else if (digitalRead(7)==LOW && digitalRead(6)==HIGH && digitalRead(5)==HIGH && digitalRead(4)==LOW) { //0110
    shake();
  }
  else if (digitalRead(7)==LOW && digitalRead(6)==HIGH && digitalRead(5)==HIGH && digitalRead(4)==HIGH) { //0111
    pullup();
  }
  else if (digitalRead(7)==HIGH && digitalRead(6)==LOW && digitalRead(5)==LOW && digitalRead(4)==LOW) { //0111
    pulldown();
  }
  else {
    stop_motion(10);
  }
  */
  excavate();
  delay(5000);
}
