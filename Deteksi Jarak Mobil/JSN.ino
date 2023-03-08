#define trigPin 2
#define echoPin 3
long durasi;
int jarak;


void setup() {
  // put your setup code here, to run once:
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  durasi = pulseIn(echoPin, HIGH);
  jarak = durasi * 0.034/2;

  Serial.print("Jarak : ");
  Serial.print(jarak);
  Serial.println(" CM");
  delay(500);

  if (jarak >= 100){
      Serial.println("Jarak Aman");
      delay(2000);
    }else if (jarak <= 100){
      Serial.print("AWAS NABRAK");
     // mainkan(3);
      delay(2000);
      }

}
