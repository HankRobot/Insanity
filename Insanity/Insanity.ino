//-----------------------------------------------------------Solar Shield---------------------------------------------------------------//
const int analogInPin = A0;  // Analog input pin that the VBAT pin is attached to
int BatteryValue = 0;        // value read from the VBAT pin
float outputValue = 0;        // variable for voltage calculation
//-----------------------------------------------------------Motor---------------------------------------------------------------//
//declaration of variables & object
#include <SoftwareSerial.h>
Cytron_G15Shield g15(2, 3, 8); // SoftwareSerial: Rx, Tx and Control pin
#define LED_BOARD 13
#define G15_lf 1
#define G15_lb 2
#define G15_rf 3
#define G15_rb 4
#define G15_dl 5
#define G15_dr 6
#define G15_s 7
#define LED 13
//-----------------------------------------------------------Bluetooth---------------------------------------------------------------//
SoftwareSerial mySerial(4, 5); //TX 4, RX 5
byte data[5];
int serInIndx  = 0;    // index of serInString[] in which to insert the next incoming byte
int serOutIndx = 0;    // index of the outgoing serInString[] array;
int dely = 250;
//-----------------------------------------------------------Functions---------------------------------------------------------------//
void setup() {
  //initialize the arduino main board's serial/UART and Control Pins
  //CTRL pin for G15 =3 and AX12 =8
  g15.begin(19200); 

  //call the init function to init servo obj
  g15.setWheelMode(G15_lf);
  g15.setWheelMode(G15_lb);
  g15.setWheelMode(G15_rf);
  g15.setWheelMode(G15_rb);

  Serial.begin(9600); //Start the serial on computer
  mySerial.begin(9600); //Start the serial on bluetooth

  delay(1000);
}

void turnleft(int speed, int time)
{
  g15.SetWheelSpeed(G15_lf,512,CW); 
  g15.SetWheelSpeed(G15_lb,512,CW);
  g15.SetWheelSpeed(G15_rf,512,CW);
  g15.SetWheelSpeed(G15_rb,512,CW);
  delay(time);
}

void turnright(int speed, int time)
{
  g15.SetWheelSpeed(G15_lf,512,CCW); 
  g15.SetWheelSpeed(G15_lb,512,CCW);
  g15.SetWheelSpeed(G15_rf,512,CCW);
  g15.SetWheelSpeed(G15_rb,512,CCW);
  delay(time);
}

void moveforward(int speed, int time)
{
  g15.SetWheelSpeed(G15_lf,512,CW); 
  g15.SetWheelSpeed(G15_lb,512,CW);
  g15.SetWheelSpeed(G15_rf,512,CCW);
  g15.SetWheelSpeed(G15_rb,512,CCW);
  delay(time);
}

void movebackward(int speed, int time)
{
  g15.SetWheelSpeed(G15_lf,512,CCW); 
  g15.SetWheelSpeed(G15_lb,512,CCW);
  g15.SetWheelSpeed(G15_rf,512,CW);
  g15.SetWheelSpeed(G15_rb,512,CW);
  delay(time);
}

void stop_motion(int time)
{
  servolf.SetWheelSpeed(0x0000,CCW); 
  servolb.SetWheelSpeed(0x0000,CCW); 
  servorf.SetWheelSpeed(0x0000,CW); 
  servorb.SetWheelSpeed(0x0000,CW);
  delay(time);
}

void readSerialString ()
{
  byte data0;
  byte data1;
  byte data2;
  byte data3;
  byte data4;
  if (mySerial.available())
  {
    data0 = mySerial.read();
    data1 = mySerial.read();
    data2 = mySerial.read();
    data3 = mySerial.read();
    data4 = mySerial.read();
    if (data0 == 255 && data1 == 255 && data2 != 255 && data3 != 255 && data4 != 255)
    {
      //if all goes well
      data[0] = data0;
      data[1] = data1;
      data[2] = data2;
      data[3] = data3;
      data[4] = data4;
    }
    else if (data0 != 255 && data1 == 255 && data2 == 255 && data3 != 255 && data4 != 255)
    {
      // 255 heading shifts to the left
      data[0] = data1;
      data[1] = data2;
      data[2] = data3;
      data[3] = data4;
      data[4] = mySerial.read();
    }
    else if (data0 != 255 && data1 != 255 && data2 == 255 && data3 == 255 && data4 != 255)
    {
      // 255 heading shifts to the left again
      data[0] = data2;
      data[1] = data3;
      data[2] = data4;
      data[3] = mySerial.read();
      data[4] = mySerial.read();
    }
    else if (data0 != 255 && data1 != 255 && data2 != 255 && data3 == 255 && data4 == 255)
    {
      // 255 heading shifts to the left double
      data[0] = data3;
      data[1] = data4;
      data[2] = mySerial.read();
      data[3] = mySerial.read();
      data[4] = mySerial.read();
    }
    else if (data0 == 255 && data1 != 255 && data2 != 255 && data3 == 255 && data4 != 255)
    {
      // 255 heading shifts to the left double
      data[1] = mySerial.read(); //this reads the leftover 255
      data[2] = mySerial.read();
      data[3] = mySerial.read();
      data[4] = mySerial.read();
    }
    else if (data0 == 255 && data1 == 255 && data2 == 255 && data3 == 255 && data4 == 255)
    {
      data[0] = 255;
      data[1] = 255;
      data[2] = 255;
      data[3] = 255;
      data[4] = 255;
    }
    serInIndx = 5;
  }
}

void printSerialString()
{
  if ( serInIndx > 0)
  {
    Serial.print("Arduino memorized that you said: ");
    for (serOutIndx = 0; serOutIndx < serInIndx; serOutIndx++)
    {
      Serial.print(data[serOutIndx]);    //print out the byte at the specified index
    }
    serOutIndx = 0;
    serInIndx  = 0;
    Serial.println();
  }
}

void printBatteryVoltage(){
  // read the analog in value:
    BatteryValue = analogRead(analogInPin);
    // Calculate the battery voltage value
    outputValue = (float(BatteryValue)*5)/1023*2;
    // print the results to the serial monitor:
    Serial.print("Analog value = " );
    Serial.print(BatteryValue);
    Serial.print("\t voltage = ");
    Serial.println(outputValue);
    Serial.print("V \n");
    // wait 10 milliseconds before the next loop
    // for the analog-to-digital converter to settle
    // after the last reading:
    delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (data[2] == 120 && data[3] == 117 && data[4] == 112)
  {
    moveforward(120, 0);
    mySerial.flush();
  }
  if (data[2] == 120 && data[3] == 117 && data[4] == 114)
  {
    stop_motion(20);
    mySerial.flush();
  }
  if (data[2] == 120 && data[3] == 108 && data[4] == 112)
  {
    turnleft(120, 0);
    mySerial.flush();
  }
  if (data[2] == 120 && data[3] == 108 && data[4] == 114)
  {
    stop_motion(0);
    mySerial.flush();
  }
  if (data[2] == 120 && data[3] == 114 && data[4] == 112)
  {
    turnright(120, 0);
    mySerial.flush();
  }
  if (data[2] == 120 && data[3] == 114 && data[4] == 114)
  {
    stop_motion(20);
    mySerial.flush();
  }
  if (data[2] == 120 && data[3] == 100 && data[4] == 112)
  {
    movebackward(120, 0);
    mySerial.flush();
  }
  if (data[2] == 120 && data[3] == 100 && data[4] == 114)
  {
    stop_motion(20);
    mySerial.flush();
  }
  if (data[0] == 255 && data[1] == 255 && data[2] == 255 && data[3] == 255 && data[4] == 255)
  {
    dely = 250;
    mySerial.flush();
  }
  readSerialString();
  delay(dely);
  printSerialString();
  //mySerial.flush();
  //printBatteryVoltage();
}
