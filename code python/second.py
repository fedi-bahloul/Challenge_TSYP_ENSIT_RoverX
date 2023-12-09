from machine import Pin,I2C,ADC
from time import sleep
from i2c_lcd import I2cLcd
import dht
import network
import urequests as request

connectionwifi=network.WLAN(network.STA_IF)
connectionwifi.active(True)
connectionwifi.connect('ENSIT-ETUD','Etud@2022')
sleep(1)
while not connectionwifi.isconnected():
    print('connection in progress')
    #how to coonect to ubidots
print("Device connected to the internet")
urlpost = 'http://things.ubidots.com/api/v1.6/devices/esp'
token = 'BBFF-plxQGyZQ2Pe8ZFtEgzSO0BaY7UyBsa'
urlget = 'http://things.ubidots.com/api/v1.6/devices/esp/led/lv'
headers ={'X-auth-Token':token , 'Content-Type' : 'application/json'}
#declaration Soil sensor D5
soil_sensor=ADC(0)
#soil_sensor=Pin(14,Pin.IN) #digital

#declaration DHT
dht_sensor=dht.DHT11(Pin(16))
led=Pin(12,Pin.OUT)
pump=Pin(13,Pin.OUT)
#LCD ADRESSE
DEFAULT_I2C_ADDR=0X27
#LCD SCREEN INITIALIZE /Pin:D1 and D2
i2c = I2C(scl=Pin(5),sda=Pin(4),freq=300000)
lcd = I2cLcd(i2c,DEFAULT_I2C_ADDR,2 ,16)
lcd.move_to(0,0)
lcd.putstr('SMART IRRIGATION')

while True:
    data={'Temperature':int(dht_sensor.temperature()), 'Humidity':int(dht_sensor.humidity())}
    DataEnvoyer=request.post(url = urlpost, headers =headers, json= data)
    DataRecevoir=request.get(url = urlget, headers =headers)
    print(DataRecevoir.text)
    if DataRecevoir.text=="0.0":
        led.off()
    else:
        led.on()
    """lcd.move_to(0,0)
    lcd.putstr('SMART IRRIGATION')
    dht_sensor.measure()
    print(soil_sensor.read())
    lcd.move_to(0,1)
    lcd.putstr('T:')
    lcd.move_to(2,1)
    lcd.putstr(str(int(dht_sensor.temperature())))
    print(dht_sensor.humidity())
    lcd.move_to(5,1)
    lcd.putstr('H:')
    lcd.move_to(7,1)
    lcd.putstr(str(int(dht_sensor.humidity())))
    lcd.move_to(10,1)
    lcd.putstr('D:')
    lcd.move_to(12,1)
    lcd.putstr(str(int(soil_sensor.read())))
    sleep(1)
    lcd.clear()
    if (soil_sensor.read()>800) :
         print('DRY Sand')
         pump.value(1)
    else:
         print('WET Sand')
         pump.value(0)"""
         
    