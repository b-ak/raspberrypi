#!/usr/bin/env python

import time
import RPi.GPIO as GPIO
import urllib2

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(27, GPIO.OUT)

state = True

LIGHT_PIN = 7   # photoresistor pin
EVENT = 'fridge_alert'
BASE_URL = 'https://maker.ifttt.com/trigger/'
KEY = 'micKeyM0use_06102015'

# Configure the GPIO pin
GPIO.setmode(GPIO.BCM)
GPIO.setup(LIGHT_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def send_event():
    for i in range(0,3):
    	GPIO.output(27,True)
    	time.sleep(1)
    	GPIO.output(27,False)
    	time.sleep(1)

    # It's so easy to concatenate a string 
    response = urllib2.urlopen(BASE_URL + EVENT + '/with/key/' + KEY)
    print(response.read())

try:
    print("I'm watching the door")
    while True:
        if GPIO.input(LIGHT_PIN) == 0:
            # Its light (door open)
            send_event()
            # Do nothing until the doior is closed again
            while GPIO.input(LIGHT_PIN) == 0:
                time.sleep(0.1)
            # Do nothing for a further minute anyway
            print("Wait a minute")
            time.sleep(60)
            print("Monitoring again")

finally:
    print('Cleaning up GPIO')
    GPIO.cleanup()

