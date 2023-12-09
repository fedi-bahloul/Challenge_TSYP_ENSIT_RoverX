#include <DHT.h>
#include <Wire.h>
#include <SFE_BMP180.h>
#define IR 2
#include <Ping.h>
#include <PubSubClient.h>
#include <MQ7.h>

void setup() {
  serial.begin(9600);

}
 void GetTemperature(float*t)
 {
  DHT.dht::read11(DHT11_pin)
  *t=DHT.temperature;
  }

  void GetHumidity(float*h)
 {
  DHT.dht::read11(DHT11_pin)
  *h=DHT.humidity;
  }

///// 
void Setup_pression(){
  myPress.begin();
  myPress.SetOversampleRate(7);
  myPress.enableEventFlags();
  myPress.SetModeBarometer();
}
float GetPressure(){
  return myPress.readPressure();
}
//////Distance///
int detection = LOW ;

 void setup(){
  Serial.begin(9600);
  pinMode(IR, INPUT);
 }
 void loop()
 {
  detection = digitalRead(IR);
  Serial.println(detection);
  delay(1000);
 }

 NewPing impulsion(trigPin, echoPin);
 float GetDisatance(){
  return impultion.ping_cm();
 }
 //////// Monoxyde de carbone///
  float get_Co (float ratio){
    float ppm = 0.0 ;
    ppm =37143 * pow (ratio,-3.178);
    return ppm; 
  }
  float GetCo(){
    val = analogRead(sensorPin);
    Vrl = val * (5.00 / 1024.0 );
    Rs = 20000 * (5.00 -vrl)/ vrl;
    ratio =Rs/Ro ; 
    return ratio ;
  }
  ///////// luminisité////

 float getVale(int val){
  if( val<800 and val>=250)
  {
    return 6277.199*exp(-(val-50)/30.142)+140.245;
  }
  else{
    if (val<250 and val>=50){
      return 466.21*exp(val-250)/82.479);
    }
    else{
      if(val<50){
        return 601440*exp(-val/10.182)-725.038;
      }
    }
  }
  return 0.0;
 }
 ///ou //
  void setup_light(){
    lightMeter.begin();
  }
 uint16_t GetLum(){
  return lightMeter.readLightLevel();
 }
 ///// Gyroscope////

 void setup_gyro () [
Wire.beginTransmission (MPU);
Wire.write(0x6B); // PWR_MGMT_1 register 
Wire.write(0); // set to zero (wakes up the MPU-6050) 
Wire.endTransmission (true);
}
void GetPosition(float pitch, float roll, float troisieme) {
Wire.beginTransmission (MPU);
Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
Wire.endTransmission (false);

Wire.requestFrom(MPU, 6, true); // request a total of 14 registers. 
AcX-Wire.read()<<8(Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
AcY-Wire.read()<<8 (Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L) 
AcZ-Wire.read()<<8 Wire.read(); // 0x3F (ACCEL_ZOUT_H) 0x40 (ACCEL ZOUT_L)

az (float)AcZ;
ax = (float)AcX;
ay (float)AcY;
*roll= 180*(atan2 (ay, az))/M_PI;//calcule l'angle de roulis
*pitch 180*(atan2 (ax, az))/M_PI://calcule l'angle de tangage
*troisieme 180* (atan2 (ax,ay))/M_PI;
}
/////
void loop() {
  

}
