from machine import Pin,I2C
from time import sleep
from i2c_lcd import I2cLcd
#lcd adress
DEFAULT_I2C_ADDR=0x27
#lcd screen initize/ pin:D1 and D2
i2c=I2C(scl=Pin(5),sda=Pin(4),freq=3000)
lcd =I2cLcd(i2c,DEFAULT_I2C_ADDR,2,16)
lcd.move_to(0,0)
lcd.putstr("   project by")
lcd.move_to(4,1)
lcd.putstr("khaled")
sleep(2)
lcd.clear()