//#include <TinyGPS++.h> 
#include <SoftwareSerial.h> //komunikasi dengan mengirimkan data per-bit secara berurutan dan bergantian.
#include "CTBot.h"
#include <Wire.h>
// konfig gyro
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ ,GyX,GyY,GyZ;
int minVal=265;
int maxVal=402;
double x, y, z;

// konfig telegram
String ssid  = "UNDIKANet"    ; //String ssid  = "UNDIKANet"  "SemangatPagi:)"  "Redmi"  "11alfa12"
String pass  = "SemangatPagi:)"; 
String token = "5392374459:AAGN2esvLxLMMd-IseysxJiC_jI2p4TiE0U"   ; 
CTBot myBot;
const int id = 1398193021;
String test = "FItur Terkoneksi";

// konfig flex dan metode
float fl1 = 36, fl2 = 39, fl3 = 34, fl4 = 35 ;
float a = 0.3; // nilai permulusan
float fd1, fd2, fd3, fd4; //nilai sebelumnya (Flex lama)nilai lama 
float s1, s2, s3, s4; // simpan data sementara 
float do1, do2, do3, do4; // simpan data awal atau data original

// konfig gps
/*int GPSBaud = 9600; // baud default
TinyGPSPlus gps; // Membuat objek TinyGPS++
int RXPin = 19, TXPin = 18; 
float latitude, longitude; 
SoftwareSerial gpsSerial(RXPin, TXPin); // Mmbuat koneksi serial dengan nama "gpsSerial"*/
void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0);
  Wire.endTransmission(true);
  pinMode(fl1,INPUT);
  pinMode(fl2,INPUT);
  pinMode(fl3,INPUT);
  pinMode(fl4,INPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  //gpsSerial.begin(GPSBaud);
  Serial.println("Starting TelegramBot...");
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  if (myBot.testConnection()){
    Serial.println("\ntestConnection OK");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    myBot.sendMessage(id,test);}
  else{
    Serial.println("\ntestConnection N.O.K");}
}
void loop(){
  //TBMessage msg;
  String link ;
  /*while(gpsSerial.available())
    gps.encode(gpsSerial.read());
    if(gps.location.isUpdated())
      latitude = gps.location.lat();  
      longitude = gps.location.lng();// https://maps.google.com/maps?q=     // www.google.com/maps/place/
      link = "Ada kecelakaan di https://maps.google.com/maps?q=" + String(latitude,6) + "," + String(longitude,6);*/
      link = "Ada kecelakaan di https://maps.google.com/maps?q=-7.311265,112.782249" ;
 flexexpo();
 mpu(); //((fd1>=1200)||(fd2>=1200)||(fd3>=1200)||(fd4>=1200)||(x>=90 && x<=270)||(y>=90 && y<=270))
 if ((fd1>=1000)||(fd2>=1000)||(fd3>=1000)||(fd4>=1000)||(x>=90 && x<=270)||(y>=90 && y<=270)){
   Serial.println(link);
   //delay(1000);
   myBot.sendMessage(id,link);
   //myBot.sendMessage(msg.sender.id, link); 
   //delay (1000);
 }
}
void flexexpo (){
  do1 = analogRead(fl1);
  do2 = analogRead(fl2);
  do3 = analogRead(fl3);
  do4 = analogRead(fl4);
  // flex1
  s1 = a * do1 + (1-a) * fd1 ;
  fd1 = s1 ; 
  // flex2
  s2 = a * do2 + (1-a) * fd2 ;
  fd2 = s2 ;
  // flex3
  s3 = a * do3 + (1-a) * fd3 ;
  fd3 = s3 ;
  // flex4
  s4 = a * do4 + (1-a) * fd4 ;
  fd4 = s4 ;
  //Serial.println(fd4);
}
void mpu(){
Wire.beginTransmission(MPU_addr); 
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);
AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();
AcZ=Wire.read()<<8|Wire.read();

int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,90);

x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
}
