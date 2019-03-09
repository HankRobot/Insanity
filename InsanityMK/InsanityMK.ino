int left[4]={0,0,0,1};
int right[4]={0,0,1,0};
int forward[4]={0,0,1,1};
int reverse[4]={0,1,0,0};
int excavate[4]={0,1,0,1};
int shake[4]={0,1,1,0};
int towup[4]={1,0,0,1};
int towdown[4]={1,0,1,0};

int pincount=0;
char cmd;
int i;

void setup() {
  // put your setup code here, to run once:
  for (i=4; i<8; i++)
  {
    pinMode(i,OUTPUT);
  }

  Serial.begin(9600);
  Serial.println("HELLO");

}

void loop() 
{
  if(Serial.available()>0)
  {
    cmd = Serial.read();

    if (cmd=='L')
    {
      digitalWrite(13,HIGH);
      Serial.println("cmd");
      pincount=0;
      for (i=7; i>3; i--)
      {
        digitalWrite(i,left[pincount]);
        pincount++;
      }
      delay(100);
      Serial.flush();
    }

    else if (cmd=='R')
    {
      Serial.println("cmd");
      digitalWrite(13,HIGH);
      pincount=0;
      for (i=7; i>3; i--)
      {
        digitalWrite(i,right[pincount]);
        pincount++;
      }
      delay(100);
      Serial.flush();
    }

    else if (cmd=='F')
    {
      Serial.println("cmd");
      digitalWrite(13,HIGH);
      pincount=0;
      for (int i=7; i>3; i--)
      {
        digitalWrite(i,forward[pincount]);
        pincount++;
      }
      delay(100);
      Serial.flush();
    }

    else if (cmd=='B')
    {
      Serial.println("cmd");
      digitalWrite(13,HIGH);
      pincount=0;
      for (int i=7; i>3; i--)
      {
        digitalWrite(i,reverse[pincount]);
        pincount++;
      }
      delay(100);
      Serial.flush();
    }

    else if (cmd=='E')
    {
      pincount=0;
      for (int i=7; i>3; i--)
      {
        digitalWrite(i,excavate[pincount]);
        pincount++;
      }
      delay(100);
      Serial.flush();
    }

    else if (cmd=='S')
    {
      pincount=0;
      for (int i=7; i>3; i--)
      {
        digitalWrite(i,shake[pincount]);
        pincount++;
      }
      delay(100);
      Serial.flush();
    }

    else if (cmd=='U')
    {
      pincount=0;
      for (int i=7; i>3; i--)
      {
        digitalWrite(i,towup[pincount]);
        pincount++;
      }
      delay(100);
      Serial.flush();
    }

    else if (cmd=='D')
    {
      pincount=0;
      for (int i=7; i>3; i--)
      {
        digitalWrite(i,towdown[pincount]);
        pincount++;
      }
      delay(100);
      Serial.flush();
    }

    else if (cmd=='X')
    {
      pincount=0;
      for (int i=7; i>3; i--)
      {
        digitalWrite(i,0);
        pincount++;
      }
      delay(100);
      Serial.flush();
    }

    else 
    {
      for (int i=7; i>3; i--)
      {
        digitalWrite(i,0);
        pincount++;
      }
      digitalWrite(13,LOW);
      //STOP ROBOT?
      delay(100);
      Serial.flush();
    }
  }
}










