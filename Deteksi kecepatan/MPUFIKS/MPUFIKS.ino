#include<Wire.h>
 
const int MPU_addr=0x68; //I2C address
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;// //Nilai minimum dan maksimum yang berasal dari //akselerometer sambil berdiri diam untuk kalibrasi
int maxVal=402;

double x;
double y;
double z;
void setup(){
Wire.begin();
//aktivasi sensor
Wire.beginTransmission(MPU_addr);// memulai komunikasi dengan MPU
Wire.write(0x6B); // mengirim permintaan start register (mengaktifkan/nonaktif) standby
Wire.write(0); // setting permintaan start(membangunkan) register
Wire.endTransmission(true); // permintaan pesan berhenti 
Serial.begin(9600);
}
void loop(){
Wire.beginTransmission(MPU_addr); // memulai komunikasi dengan MPU
Wire.write(0x3B); // address accelerometer (ACCEL_XOUT_H)
Wire.endTransmission(false); // restart
Wire.requestFrom(MPU_addr,14,true); // request 14 register
AcX=Wire.read()<<8|Wire.read();// namun yang dipakai 3 register //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
AcY=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
AcZ=Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
int xAng = map(AcX,minVal,maxVal,-90,90);    //map(value, fromLow, fromHigh, toLow, toHigh)// dijadikan -90 atau 90
int yAng = map(AcY,minVal,maxVal,-90,90); 
int zAng = map(AcZ,minVal,maxVal,-90,90); 

x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI); //pitch // RAD_TO_DEG x57.29577951308232
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI); //roll
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

/*if ((x>=90 && x<=270)||(y>=90 && y<=270)){
  Serial.print("masuk");
  Serial.println();
}*/
Serial.print("pitch= ");
Serial.print(x, 3);
Serial.print("   ");
 
Serial.print("roll= ");
Serial.print(y, 3);
Serial.println();
//Serial.println("-----------------------------------------");
delay(100);
}
