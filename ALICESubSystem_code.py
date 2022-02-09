from gpiozero import LED, Button
from time import sleep
import RPi.GPIO as GPIO
import w1thermsensor

BUTTON_PIN = 24
RELAY_PIN = 25
FANS_PIN = 23
INDICATOR_PIN = 22

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(FANS_PIN, GPIO.OUT)

toggle = False
button = Button(BUTTON_PIN)
relay = LED(RELAY_PIN)
indicator = LED(INDICATOR_PIN)
sensor = w1thermsensor.W1ThermSensor()
fan = GPIO.PWM(FANS_PIN, 50)
fill = 50
fan.start(fill)

while (1):
    
    if(button.is_pressed and toggle==False):
        print("System is off")
        indicator.off()
        relay.off()
        toggle = True
        sleep(0.15)
    elif(button.is_pressed and toggle==True):
        print("System is on")
        indicator.on()
        relay.on()
        toggle = False
        sleep(0.15)
        
    temp = sensor.get_temperature()
    print(temp)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    if (temp>35):
        fan.ChangeDutyCycle(90)
    elif (temp>30):
        fan.ChangeDutyCycle(70)
    elif (temp>25):
        fan.ChangeDutyCycle(50)
    elif (temp>20):
        fan.ChangeDutyCycle(30)
    elif (temp>0):
        fan.ChangeDutyCycle(10)
    else:
        fan.ChangeDutyCycle(90)
    
    
