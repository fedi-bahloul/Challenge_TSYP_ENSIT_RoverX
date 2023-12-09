from machine import Pin
from time import sleep
from i2c_lcd import I2cLcd
#lcd adress
DEFAULT_I2C_ADDR=0x27
#lcd screen initize/ pin:D1 and D2
i2c=I2C(scl=Pin(5),sda=Pin(4),freq=9000)
lcd =I2cLcd(i2c,DEFAULT_I2C_ADDR,2,16)
gas=Pin(16,Pin.IN)
ledr=Pin(14,Pin.OUT)
ledg=Pin(12,Pin.OUT)
zamara=Pin(13,Pin.OUT)
while True:
    print (gas.value())
    sleep(0.1)
    if gas.value()==0:
        lcd.clear()
        lcd.move_to(0,0)
        lcd.putstr("   famma gas")
        ledg.off()
        zamara.on()
        ledr.on()
        sleep(1)
    else:
        lcd.clear()
        lcd.move_to(0,0)
        lcd.putstr("   jawek behi")
        zamara.off()
        ledr.off()
        ledg.on()
        sleep(1)
        
        
