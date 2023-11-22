#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 10); // CE, CSN
const uint64_t address= 0xE8E8F0F0E1LL;

int sensorPin = A0;                //The pin where we connect the sensor.
int sensor=A0;
int thresholdValue = 600;         //Threshold value for water level.
int buzzerPin = 8;                //The pin to which we connect the buzzer.
int data;                         //The value read from the sensor.
int isThere = 0;
int distance = 0;

void setup() {  
  pinMode(sensor,INPUT);       //We are setting the pin to which the sensor is connected as an INPUT.
  pinMode(buzzerPin, OUTPUT);  //We are setting the pin to which the buzzer is connected as an OUTPUT. 
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() { 

 if (radio.available()) {
    radio.read(&distance, sizeof(distance));
    Serial.print("distance=");
    Serial.println(distance);
  }
  data = analogRead(sensorPin);    //We are reading analog data from the sensor.
  if(veri > thresholdValue){       //If the sensor data exceeds the threshold value, the code inside the 'if' statement is executed.
    Serial.println("It's raining."); 
    digitalWrite(buzzerPin, HIGH); 
    delay(250);
    digitalWrite(buzzerPin, LOW);
    delay(250);
    isThere = 1; 
    
    
  }
  else{                            //If the sensor data is less than the threshold value, the code inside the 'else' statement is executed.
    digitalWrite(buzzerPin, LOW);
    Serial.println("It's not raining.");
    delay(500);
    isThere = 0;

  }
}

 


