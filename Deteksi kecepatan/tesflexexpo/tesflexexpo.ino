 
float fl1 = 36 ;
float fl2 = 39 ;
float fl3 = 34 ;
float fl4 = 35 ;
float a = 0.4; // nilai permulusan
float fd1, fd2, fd3, fd4; //nilai sebelumnya (Flex lama) 
float s1, s2, s3, s4; // simpan data sementara 
float do1, do2, do3, do4; // simpan data awal atau data original
void setup() {
  pinMode(fl1,INPUT);
  pinMode(fl2,INPUT);
  pinMode(fl3,INPUT);
  pinMode(fl4,INPUT);
  Serial.begin(115200);
}
  /*Serial.print("flexib ");
  Serial.print(do1);
  Serial.print("    ");*/
void loop(){
  // Reading potentiometer value
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
  Serial.print("flex1 ");
  Serial.print(do1, 3);
  Serial.print(" ");
  Serial.print("filter1 ");
  Serial.print(fd1, 3);
  Serial.print(" ");
  Serial.print("flex2 ");
  Serial.print(do2, 3);
  Serial.print(" ");
  Serial.print("ftr2 ");
  Serial.print(fd2, 3);
  Serial.print(" ");
  Serial.print("flex3 ");
  Serial.print(do3, 3);
  Serial.print("    ");
  Serial.print("ftr3 ");
  Serial.print(fd3, 3);
  Serial.print(" ");
  Serial.print("flex4 ");
  Serial.print(do4, 3);
  Serial.print("    ");
  Serial.print("ftr4 ");
  Serial.print(fd4, 3);
  Serial.print(" ");
  delay(50);
  Serial.println();
}
