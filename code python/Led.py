from machine import Pin
from time import sleep
ledr=Pin(14,Pin.OUT)
ledy=Pin(12,Pin.OUT)
ledg=Pin(13,Pin.OUT)
while True:  
    ledr.on()
    sleep(0.5)
    ledr.off()
    ledy.on()
    sleep(0.5)
    ledy.off()
    ledg.on()
    sleep(1)
    ledg.off()
    ledy.on()
    sleep(0.5)
    ledy.off()
    ledr.on()
    sleep(0.5)
    
#led.value(1)
