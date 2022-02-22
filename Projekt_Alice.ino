#include <OneWire.h>
#include <DallasTemperature.h>

#define diodaPWM 4
#define przycisk 3
#define stycznik 2

float temp = 0;
int order = 0;
OneWire OneWire(12);
DallasTemperature czujnik(&OneWire);
volatile int state = HIGH;

void funckjaObslugiPrzerwania() {
  if(state == HIGH)
  {
    state = LOW;
    digitalWrite(stycznik, LOW);
    Serial.println("wyłączono urządzenie");
    delay(200);
  }
  else
  {
    state = HIGH;
    digitalWrite(stycznik, HIGH);
    Serial.println("włączono urządzenie");
    delay(200);
    
  }
  
}


void checkSerial() 
{
  if (Serial.available()>0) 
  { 
    order = Serial.read();
    if(order == '1')
    {
      state = HIGH;
      digitalWrite(stycznik, HIGH);
      Serial.println("włączono urządzenie");
      delay(100);
    }
    else if(order == '0')
    {
      state = LOW;
      digitalWrite(stycznik, LOW);
      Serial.println("wyłączono urządzenie");
      delay (100);
    }
    else
    {
      Serial.println(temp);
    }
  }
}


void setup() {
  attachInterrupt(digitalPinToInterrupt(przycisk), funckjaObslugiPrzerwania, RISING);
  pinMode(stycznik, OUTPUT); //stycznik
  pinMode(diodaPWM, OUTPUT); //PWM
  Serial.begin(9600);
  czujnik.begin();
}

void loop() {
  czujnik.requestTemperatures();
  temp = czujnik.getTempCByIndex(0);
         if (temp > 35)
         {
             analogWrite(diodaPWM, 250);
         }
         else if (temp > 30)
         {
             analogWrite(diodaPWM, 200);
         }
         else if (temp > 25)
         {
             analogWrite(diodaPWM, 150);
         }
         else if (temp > 20)
         {
            analogWrite(diodaPWM, 100);
         }
         else if (temp > 0)
         {
            analogWrite(diodaPWM, 50);
         }
         else
         {
            analogWrite(diodaPWM, 200);
         }
  checkSerial();
}
