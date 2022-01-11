#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 10); // CE, CSN
const uint64_t address= 0xE8E8F0F0E1LL;

int sensorPin = A0;                //Sensörü bağlayacağımız pin
int sensor=A0;
int esikDegeri = 600;              //Su miktarı için eşik değeri
int buzzerPin = 8;                 //Buzzerı bağlayacağımız pin
int veri;                          //Sensörden okuduğumuz değer
int varMi = 0;
int mesafe = 0;

void setup() {
  pinMode(sensor,INPUT);
  pinMode(buzzerPin, OUTPUT);  //Buzzer bağladığımız pini OUTPUT olarak ayarlıyoruz.  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() { 
  //int okunan = analogRead(sensor);
 if (radio.available()) {
    radio.read(&mesafe, sizeof(mesafe));
    Serial.print("mesafe=");
    Serial.println(mesafe);
  }
  veri = analogRead(sensorPin);    //Sensörden analog veriyi okuyoruz.
  if(veri > esikDegeri){
    Serial.println("Yagmur Var");//Sensör verisi eşik değerini geçerse if içerisindeki kodlar uygulanır.
    digitalWrite(buzzerPin, HIGH); 
    delay(250);
    digitalWrite(buzzerPin, LOW);
    delay(250);
    
    // char text1[11] = "Yagmur var";
    varMi = 1;
    //radio.write(&varMi, sizeof(varMi));
    
  }
  else{                            //Sensör verisi eşik değerinden küçük olursa if içerisindeki kodlar uygulanır.
    digitalWrite(buzzerPin, LOW);
    Serial.println("Yagmur Yok");
    delay(500);
    //char text[11] = "Yagmur Yok";
    varMi = 0;
    //radio.write(&varMi, sizeof(varMi));
  }
}

 


