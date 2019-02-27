//-----------------------------------------------------------Motor---------------------------------------------------------------//
//declaration of variables & object
#include <G15.h>    // include the library
#define LED_BOARD 13
word ERROR=0;
byte DATA[10]; 
word STATUS;

//declare G15 Class Object
//servo1 ID=0x01
G15 servo1(0x01); 
G15 servo2(0x02); 
G15 servo3(0x03); 
G15 servo4(0x04); 
//-----------------------------------------------------------Bluetooth---------------------------------------------------------------//
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); //TX 2, RX 3

byte data[5];
int serInIndx  = 0;    // index of serInString[] in which to insert the next incoming byte
int serOutIndx = 0;    // index of the outgoing serInString[] array;
int dely = 250;

void setup() {
  //initialize the arduino main board's serial/UART and Control Pins
  //CTRL pin for G15 =3 and AX12 =8
  G15ShieldInit(19200,3,8); 

  //call the init function to init servo obj
  servo1.init(); 
  servo2.init(); 
  servo3.init(); 
  servo4.init(); 

  servo1.SetWheelMode();
  servo2.SetWheelMode();
  servo3.SetWheelMode();
  servo4.SetWheelMode();

  Serial.begin(9600); //Start the serial on computer
  mySerial.begin(9600); //Start the serial on bluetooth

  delay(1000);
}

void turnleft(int speed, int time)
{
  servo1.SetWheelSpeed(0x01F4,CW); 
  servo2.SetWheelSpeed(0x01F4,CW); 
  servo3.SetWheelSpeed(0x01F4,CW); 
  servo4.SetWheelSpeed(0x01F4,CW);
  delay(time);
}

void turnright(int speed, int time)
{
  servo1.SetWheelSpeed(0x01F4,CCW); 
  servo2.SetWheelSpeed(0x01F4,CCW); 
  servo3.SetWheelSpeed(0x01F4,CCW); 
  servo4.SetWheelSpeed(0x01F4,CCW);
  delay(time);
}

void moveforward(int speed, int time)
{
  servo1.SetWheelSpeed(0x01F4,CW); 
  servo2.SetWheelSpeed(0x01F4,CW); 
  servo3.SetWheelSpeed(0x01F4,CCW); 
  servo4.SetWheelSpeed(0x01F4,CCW);
  delay(time);
}

void movebackward(int speed, int time)
{
  servo1.SetWheelSpeed(0x01F4,CCW); 
  servo2.SetWheelSpeed(0x01F4,CCW); 
  servo3.SetWheelSpeed(0x01F4,CW); 
  servo4.SetWheelSpeed(0x01F4,CW);
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

void stop_motion(int time)
{
  servo1.SetWheelSpeed(0x0000,CCW); 
  servo2.SetWheelSpeed(0x0000,CCW); 
  servo3.SetWheelSpeed(0x0000,CW); 
  servo4.SetWheelSpeed(0x0000,CW);
  delay(time);
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
}
