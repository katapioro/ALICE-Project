/*Alice project controler 
 * Stanisław Zachorowski (zstaszek@gmail.com)
 * Katarzyna Pióro
 * 2022
 */
//libraries
#include <OneWire.h> // one wire protocol
#include <DallasTemperature.h> // DS18B20 thermometer handling

//pin declaration
#define LEDindicator 4
#define PWM 5
#define button 3
#define contactor 2

//variable declaration 
float temp = 0; //themperature
int order = 0; //serial orders 
volatile int system_state = LOW; // system state
volatile int fan_state = LOW; // fans state

//thermometer declaration
OneWire OneWire(12);
DallasTemperature thermometer(&OneWire);

//physical button turning ON/OFF
void changeOfStates() {
  if(system_state == HIGH)
  {
    system_state = LOW;
    digitalWrite(LEDindicator,LOW);
    digitalWrite(contactor, HIGH);
    Serial.println("Power OFF button");
    delay(500);
  }
  else
  {
    system_state = HIGH;
    digitalWrite(LEDindicator,HIGH);
    digitalWrite(contactor, LOW);
    Serial.println("Power ON button");
    delay(500);  
  }  
}

//serial connection handling 
void checkSerial() 
{
  if (Serial.available()>0) //chcecking if serial connection is available
  { 
    order = Serial.read(); // readong orrder from serial
    if(order == '0')  //checking order and performing given tasks
    {
      system_state = LOW;
      digitalWrite(LEDindicator,LOW);
      digitalWrite(contactor,HIGH);
      Serial.println("Power OFF");
      delay (100);
    }
    else if(order == '1')
    {
      system_state = HIGH;
      digitalWrite(LEDindicator,HIGH);
      digitalWrite(contactor,LOW);
      Serial.println("Power ON");
      delay(100);
    }
    else if(order == '2')
    {
      fan_state = HIGH;
      Serial.println("Fans automatic controll");     
    }
    else if(order == '3')
    {
      fan_state = LOW;
      analogWrite(PWM, 0);
      Serial.println("Fans OFF");
    }
    else if(order == '4')
    {
      fan_state = LOW;
      analogWrite(PWM, 250);
      Serial.println("Fans full power");
    }
    else if(order == '5')
    {
      Serial.println("0 - Power OFF");
      Serial.println("1 - Power ON");
      Serial.println("2 - Fans automatic controll");
      Serial.println("3 - Fans OFF");
      Serial.println("4 - Fans full power");
      Serial.println("5 - HELP");
    }
    else
    {
      Serial.println(temp);
    }
  }
}

void setup() {
  pinMode(contactor, OUTPUT); //power contactor pin
  pinMode(PWM, OUTPUT); //PWM controll pin
  pinMode(button, INPUT_PULLUP); //button pin
  pinMode(LEDindicator, OUTPUT); //LED pin
  
  Serial.begin(9600); //serial conection start
  thermometer.begin(); //sensor reading start
  
  digitalWrite(LEDindicator,HIGH);
}

void loop() 
{
  //themperature read
  thermometer.requestTemperatures();
  temp = thermometer.getTempCByIndex(0);
 //fan power controll according to measured temperature        
 if (fan_state == HIGH)
  {
    if (temp > 35)
     {
         analogWrite(PWM, 250);
     }
     else if (temp > 30)
     {
         analogWrite(PWM, 200);
     }
     else if (temp > 25)
     {
         analogWrite(PWM, 150);
     }
     else if (temp > 20)
     {
        analogWrite(PWM, 100);
     }
     else if (temp > 0)
     {
        analogWrite(PWM, 50);
     }
     else
     {
        analogWrite(PWM, 200);
     }
  }
 // button push detection 
 if(digitalRead(button) == LOW) 
 {
   changeOfStates();
 }
  checkSerial();
}
