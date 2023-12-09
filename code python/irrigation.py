from machine import Pin,I2C,ADC
from time import sleep
from i2c_lcd import I2cLcd
import dht
import network
import urequests  as request
# pin D5
#soil_sensor=Pin(14,Pin.IN)
motor=Pin(13,Pin.OUT)
soil_sensor=ADC(0)
dht_sensor= dht.DHT11(Pin(16))
#lcd adress
DEFAULT_I2C_ADDR=0x27
#lcd screen initize/ pin:D1 and D2
i2c=I2C(scl=Pin(5),sda=Pin(4),freq=3000)
lcd =I2cLcd(i2c,DEFAULT_I2C_ADDR,2,16)
connectionwifi = network.WLAN(network.STA_IF)
connectionwifi.active(True)
connectionwifi.connect('ENSIT-ETUD','Etud@2022')
sleep(1)
while not connectionwifi.isconnected():
        print("cennection in progress")
print("device connected")
urlpost='http://things.ubidots.com/api/v1.6/devices/esp'
token="BBFF-plxQGyZQ2Pe8ZFtEgzSO0BaY7UyBsav"
urlget='http://things.ubidots.com/api/v1.6/devices/esp/led/lv'
headers={'X-auth-Token':token , 'Content-Type' : 'application/json'}

lcd.move_to(0,0)
lcd.putstr("smart irrigation by")
lcd.move_to(4,1)
lcd.putstr("khaled")
sleep(2)
lcd.clear()
while True:
    sleep(1)
    dht_sensor.measure()
    data={"temperature":int(dht_sensor.temperature()),'humidity': int(dht_sensor.humidity())}
    DataEnvoyer= request.post(url=urlpost, headers=headers, json= data)
    
    """print(soil_sensor.read())
    lcd.move_to(0,0)
    lcd.putstr("siol humidity : " +str(soil_sensor.read()))
    
    if soil_sensor.read()>800:
        lcd.move_to(5,1)
        lcd.putstr("dry soil")
        motor.value(1)
        print("on")
    else:
        lcd.move_to(0,1)
        lcd.putstr("wet soil")
        motor.value(0)
        print("off")
    sleep(0.5)
    lcd.clear()    
   
    if soil_sensor.()==0 :
        lcd.putstr("wet")
        sleep(1)
        lcd.clear()
    else :
        lcd.putstr("dry")
        sleep(1)
        lcd.clear()
    dht_sensor.measure()
    lcd.move_to(0,0)
    lcd.putstr("temperature : "+str(dht_sensor.temperature()))
    lcd.move_to(0,1)
    lcd.putstr("humidity : "+str(dht_sensor.humidity()))
    sleep(2)
    lcd.clear()"""


