from machine import Pin
from time import sleep
gas=Pin(16,Pin.IN)
ledr=Pin(14,Pin.OUT)
ledg=Pin(12,Pin.OUT)
zamara=Pin(13,Pin.OUT)
while True:
    print (gas.value())
    sleep(0.1)
    if gas.value()==0:
        ledg.off()
        zamara.on()
        ledr.on()
    else:
        zamara.off()
        ledr.off()
        ledg.on()