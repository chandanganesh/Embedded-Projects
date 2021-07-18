#include "Servo.h"
#define D4 A0
#define D5 A1
#define D6 A2
#define trigPin A4
#define echoPin A3

int RightMotorIn1 = 8;
int RightMotorIn2 = 9;
int LeftMotorIn1 = 10;
int LeftMotorIn2 = 11;
int D1 = 2;
int D2 = 3;
int D3 = 4;
int soil = 12;
int buzz = 7;
Servo servo1;
int pump =5;
long duration;
int ultraread;
void setup() 
{
 Serial.begin(9600);
 servo1.attach(13);
 pinMode(D1,INPUT);
 pinMode(D2,INPUT);
 pinMode(D3,INPUT);
 pinMode(D4,INPUT);
 pinMode(D5,INPUT);
 pinMode(D6,INPUT); 
 pinMode(soil,INPUT);
 pinMode(buzz,OUTPUT);
 pinMode(RightMotorIn1,OUTPUT);
 pinMode(RightMotorIn2,OUTPUT);
 pinMode(LeftMotorIn1,OUTPUT);
 pinMode(LeftMotorIn2,OUTPUT);
 pinMode(pump,OUTPUT);
 pinMode(trigPin, OUTPUT); 
 pinMode(echoPin, INPUT);
 }

String Text;

void loop()
{ 
  
 if(Serial.available() > 0)
  {
    Text = Serial.readString();
  }
  servo1.write(72);
  Serial.println("\t \t \t \t\t\t\t\t    FIRE FIGHTING ROBOT \n\n") ;
  Serial.println("Select the MODE of Operation: \n\n\n") ;
  delay(1000);
  digitalWrite(buzz,HIGH);
  delay(1000);
  digitalWrite(buzz,LOW);
  
  while(1)
  { 
    
    if(Serial.available() > 0)
  {
    Text = Serial.readString();
  }
  if(Text == "manual")
  { 
    Serial.println("\t\t\t Manual MODE :"); 
    delay(1000);
    Manual();
    Text = "0"; 
  } 
  else if(Text == "automatic")
  {     
    Serial.println("\t\t\t Auto MODE   :");
    delay(1000);
    Auto(); 
    Text = "0";     
  }
 }
}

 void Manual(void)
 {
  while(1)
 { 
  
  Stop();
  if(Serial.available() > 0)
 
  {
    Text = Serial.readString();
  }
  Stop();
  
    if ((Text == "w") || (Text == "W"))
    { 
    Ultrasonic();
      if (ultraread < 40)
      {
        Stop();
        Buzzer();
        Manual();
      }
      else 
      {
        Serial.println("\t\t\t\t       Forward") ;
        Forward();
        delay(60);
        Manual();
      }
    }
    else if ((Text == "s") || (Text == "S"))
    {
     Serial.println("\t\t\t\t       Reverse") ;
     Reverse();
     delay(600);
     Text="0";
     Manual();
    }
    else if ((Text == "a") || (Text == "A"))
    {
     Serial.println("\t\t\t\t       Left") ;
     Left();
     delay(600);
     Text="0";
     Manual();
    }
    else if ((Text == "d") || (Text == "D"))
    {
     Serial.println("\t\t\t\t       Right");
     Right();
     delay(600); 
     Text="0";
     Manual();
    }
    else if ((Text == "q") || (Text == "Q"))
    {
     Serial.println("\t\t\t\t       Stop");
     Stop(); 
     delay(500);
     Text="0";
     Manual();
    }
    else if (Text == "automatic")
    {
     Serial.println("\n\n\n\n\t\t\t Auto MODE   :");
     Auto();     
     Text = "0";
    }
 }
 }
 

 void Auto(void)
 {
 { while(1)
 {
  
  if(Serial.available() > 0)
  {
    Text = Serial.readString();
  }
   Serial.println("\t\t\t\t       RED OR GREEN :");
   delay(1000);
   Text = "0"; 
   while(1)
   {  
    if(Serial.available() > 0)
  {
    Text = Serial.readString();
  }  
   if(Text == "red")
   {
    Serial.println("\t\t\t\t\t\t     RED");
    Red();
    delay(1000);
    Text="0";     
   }
   else if (Text == "green")
   {
    Serial.println("\t\t\t\t\t\t     GREEN :");
    Green();
    delay(1000);
    Text="0";
   }
   else if (Text == "manual")
    {
     Serial.println("\n\n\n\n\t\t\t Manual MODE :");
     Manual();
     Text = "0"; 
    }
   }
 } 
 }
 }

void Red(void)
{
  while(1)
{ if ((digitalRead(D1)==1) && (digitalRead(D2)==1) && (digitalRead(D3)==1) && (analogRead(A0) < 100)  && (analogRead(A1) < 100) && (analogRead(A2) < 100))
  {
    Stop();    
  }
  else
  {
  
  if ((digitalRead(D1)==1) && (digitalRead(D2)==1) && (digitalRead(D3)==1) && (analogRead(A0) < 200) && (analogRead(A1) < 200 ))
  {
    Stop();    
  }
  else
  {
    if(digitalRead(D1)==0) 
    {
      analogWrite(A1,0);
      Right();
      delay(30);
      Stop();
      delay(1000);
      Buzzer();
      Buzzer();
      
    }
    else if(digitalRead(D2)==0)
    {
      
      analogWrite(A1,0);
      Stop();
      while(1)
      { 
        Buzzer();
        Buzzer();
        
      if (analogRead(A5) < 35)
      {
       Stop();
       Pump();
       analogWrite(A1,0);
       Red();        
      }
      else if (analogRead(A5) > 700 ) 
      {
       analogWrite(A1,1023);
       Forward();
       delay(70); 
       Stop();
       delay(500);
       analogWrite(A1,HIGH);
       Red();
      }
      else if (analogRead(A5) >= 800 )
      {       
       Red();
      }
        
    }
    }
    else if(digitalRead(D3)==0)
    {
      analogWrite(A1,0);
      Left();
      delay(30);
      Stop();
      delay(1000);
      Buzzer();
  Buzzer();
      
    }
    else if((digitalRead(D1)==0) && (digitalRead(D2)==0) && (digitalRead(D3)==0))
    {
      analogWrite(A1,0); 
      Stop();
      Buzzer();
  Buzzer();
    }
    else if (analogRead(A0) > 200)
    { while(1)
     {
      if (digitalRead(D1) == 1)
      {
        Left();
        delay(30);
       }
       else
       {
        Stop();
        Red();
       }
     }
    }

    else if ((analogRead(A1) > 200) || (analogRead(A2) > 200))
    { while(1)
     {
      if (digitalRead(D1) == 1)
      {
        Left();
        delay(30);
       }
       else
       {
        Stop();
        Red();
       }
     }
    }
  

  
 else if (Text == "green")
 {
  Stop();
  Serial.println("\t\t\t\t\t\t     GREEN :");
  Green();
 }
 else if (Text == "manual")
 {
  
  Serial.println("\n\n\n\n\t\t\t Manual MODE :");
  Stop();
  Manual();
}
}
}
}
}

void Green(void)
{ 
  while(1)
{ 
  if(Serial.available() > 0)
  {
    Text = Serial.readString();
  }
   if (Text == "green")
  { Serial.println("\t\t\t\t\t\t             Enter the Distance:");
  delay(5000);
   while(1)
  
  {
    if(Serial.available() > 0)
  {
    Text = Serial.readString();
  } 
  
  while(1)
  {   
   count();
   Auto();   
     }
  }
  }
  }
 }
 void count(void)
 {
  if (Text =="1")
  {
    Greendis();
    Auto();
  }
  else if (Text =="2")
  {
    Greendis();
    Greendis();
    Auto();    
  }
  else if (Text =="3")
  {
    Greendis();
    Greendis();
    Greendis();
    Auto();
   }
 }

void Greendis(void)
{ 
   Down();
    Test();
    if(Text =="DRY")
    {    
      Up();
      delay(5000);
      Reverse();
      delay(1000);
      Stop();
      Pump();
      digitalWrite(buzz,HIGH);
      delay(3000);
      digitalWrite(buzz,LOW);
      
    }
    else if (Text == "WET")
    {
     Up();
     delay(5000);
     Reverse();
     delay(1000);
     Stop();
     
    } 
  }

void Test()
{ delay(2000);
  if(digitalRead(soil) == 0)
  {
   
   Up();
   Text="WET";
   }
  else
  {
    
    Text="DRY";
  }
}

void Diserror(void)
{
  Serial.println("\t\t\t\t\t\t\t     Please enter Distance:");
}
void Up(void)
{
  Text="0";
  servo1.write(72);
  delay(300);
}

void Down(void)
{ 
  Text="0";
  servo1.write(180);
  delay(300);
}

void Buzzer(void)
{
 digitalWrite(buzz,HIGH);
 delay(50);
 digitalWrite(buzz,LOW);
 delay(50);
 }
 void Pump(void)
 {
  Serial.println("\t\t\t\t\t\t\t\t\t\t Water");
  digitalWrite(pump,HIGH);
  delay(300);
  digitalWrite(pump,LOW);
  delay(100);
  }

void Ultrasonic(void)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  ultraread= duration*0.034/2;
    
}


void Forward(void)
{
  digitalWrite(RightMotorIn1,HIGH);
  digitalWrite(RightMotorIn2,LOW);
  digitalWrite(LeftMotorIn1,LOW);
  digitalWrite(LeftMotorIn2,HIGH); 
 }

void Reverse(void)
{
  digitalWrite(RightMotorIn1,LOW);
  digitalWrite(RightMotorIn2,HIGH);
  digitalWrite(LeftMotorIn1,HIGH);
  digitalWrite(LeftMotorIn2,LOW); 
 }

void Stop(void)
{
  digitalWrite(RightMotorIn1,LOW);
  digitalWrite(RightMotorIn2,LOW);
  digitalWrite(LeftMotorIn1,LOW);
  digitalWrite(LeftMotorIn2,LOW);
}

void Right(void)
{
  digitalWrite(RightMotorIn1,HIGH);
  digitalWrite(RightMotorIn2,LOW);
  digitalWrite(LeftMotorIn1,HIGH);
  digitalWrite(LeftMotorIn2,LOW);
}

void Left(void)
{
  digitalWrite(RightMotorIn1,LOW);
  digitalWrite(RightMotorIn2,HIGH);
  digitalWrite(LeftMotorIn1,LOW);
  digitalWrite(LeftMotorIn2,HIGH);
} 
