#include <SoftwareSerial.h>
#include "DFPlayerMudah.h"
SoftwareSerial mySerial(10, 11); //RX TX
static int8_t Send_buf[8] = {0} ;
//pin arduino yang digunakan
#define trigPin 2
#define echoPin 3

// Tentukan jarak maksimum yang ingin kita ping (dalam sentimeter). Jarak sensor maksimum adalah 400-500 cm
#define MAX_DISTANCE 300

NewPing sonar = NewPing(trigPin, echoPin, MAX_DISTANCE);


void setup() {
  //Baut komunikasi yang disettingkan di serial monitor
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(500);
  inisial();
  atur_suara(30);
}

void loop() {
  Serial.print("Jarak Pembacaan = ");
  Serial.print(sonar.ping_cm());  //nilai jarak yang terbaca
  Serial.print(" cm ");

  //contoh pengondisian menggunakan IF, jika jarak terdeteksi pada jarak samadengan 300cm dan lebih dari itu maka led built in akan blinking
  if (sonar.ping_cm() >= 100 )
  {
    Serial.println(" Jarak Aman ");
    delay(5000);
  }
  else if (sonar.ping_cm() < 100)
  {
    Serial.println(" Awas Jarak Mobil terlalu dekat = Play 0003.mp3");
    mainkan(3);
    delay(5000);
  }

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
  for (uint8_t i = 0; i < 8; i++) //
  { mySerial.write(Send_buf[i]);
  }
}

void inisial() {
  sendCommand(CMD_SEL_DEV, DEV_TF);
  delay(20);
  sendCommand(CMD_PLAY_W_VOL, 0X0F01);
  delay(20);
}

void atur_suara(int besar) {
  sendCommand(CMD_SET_VOLUME, besar);
  delay(20);
}

void mainkan(int urutan) {
  sendCommand(CMD_PLAY_W_INDEX, urutan);
  delay(20);
}
