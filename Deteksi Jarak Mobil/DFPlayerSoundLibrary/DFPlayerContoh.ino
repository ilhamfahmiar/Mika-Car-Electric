#include <SoftwareSerial.h>
#include "DFPlayerMudah.h"
SoftwareSerial mySerial(10,11); //RX TX
static int8_t Send_buf[8] = {0} ;
  
void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(500);
  inisial();
  atur_suara(25);
}

void loop() 
{
 mainkan(5);
 delay(1000);
 mundur();
 delay(1000);
 mainkan(6);
 delay(1000);
 lanjut();
 delay(1000);
}

void sendCommand(int8_t command, int16_t dat)
{ delay(20);
  Send_buf[0] = 0x7e; //
  Send_buf[1] = 0xff; //
  Send_buf[2] = 0x06; //
  Send_buf[3] = command; //
  Send_buf[4] = 0x00;//
  Send_buf[5] = (int8_t)(dat >> 8);//datah
  Send_buf[6] = (int8_t)(dat); //datal
  Send_buf[7] = 0xef; //
  for(uint8_t i=0; i<8; i++)//
  { mySerial.write(Send_buf[i]);  
  }
}

void inisial(){
 sendCommand(CMD_SEL_DEV,DEV_TF);    
 delay(20);
 sendCommand(CMD_PLAY_W_VOL,0X0F01);
 delay(20);
} 

void atur_suara(int besar){
 sendCommand(CMD_SET_VOLUME,besar);
 delay(20);
}

void mainkan(int urutan){
 sendCommand(CMD_PLAY_W_INDEX,urutan);
 delay(20);
}

void lanjut(){
 sendCommand(CMD_NEXT_SONG,0);
 delay(20);
}

void mundur(){
 sendCommand(CMD_PREV_SONG,0);
 delay(20);
}
