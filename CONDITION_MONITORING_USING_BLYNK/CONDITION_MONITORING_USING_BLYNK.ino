#define BLYNK_TEMPLATE_ID "..........."
#define BLYNK_TEMPLATE_NAME ".........."

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG


#define USE_ESP32_DEV_MODULE


#include "BlynkEdgent.h"

#define VIRTUAL_PIN_ACS712_1 V4
#define VIRTUAL_PIN_ACS712_2 V3
#define VIRTUAL_PIN_TEMP_1 V0
#define VIRTUAL_PIN_TEMP_2 V1
#define VIRTUAL_PIN_TEMP_3 V2

long lastsample1 = 0;
long lastsample2 = 0;
long Samplesum1 = 0;
long Samplesum2 = 0;
long Samplecount1 = 0;
long Samplecount2 = 0;
int sensorPin1 = 35; 
int sensorPin2 = 36; 
int dataPin1 = 34; 
int dataPin2 = 33;  
int dataPin3 = 32; 
float vpc = (3.5 / 4095) * 1000;

#define TEMPERATURE_SAMPLE_INTERVAL 1000 

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(dataPin1, INPUT);
  pinMode(dataPin2, INPUT);
  pinMode(dataPin3, INPUT);
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  
  currentsensor1();
  currentsensor2();
 
  static unsigned long lastTempSampleTime = 0;
  if (millis() - lastTempSampleTime >= TEMPERATURE_SAMPLE_INTERVAL) {
    temperaturesensor1();
    temperaturesensor2();
    temperaturesensor3();
    lastTempSampleTime = millis();
  }
}

void currentsensor1(){
  if (millis() > lastsample1) {
    float s = analogRead(sensorPin1) - 2760;
    Serial.println(s); 
    Samplesum1 += y * y; 
    Samplecount1++;
    lastsample1 = millis();
  }
  if (Samplecount1 == 1000) {
    float mean = Samplesum1 / Samplecount1;
    float rms = sqrt(mean);
    float mV = rms / 100; 
    
    Serial.print("Current sensor 1 - The final rms: ");
    Serial.println(mV, 2); 
    
    Blynk.virtualWrite(VIRTUAL_PIN_ACS712_1, mV);
 
    Samplesum1 = 0;
    Samplecount1 = 0;
  }
}

void currentsensor2(){
  if (millis() > lastsample2) {
    float s = analogRead(sensorPin2) - 2760;
    Serial.println(s); 
    float y = s * vpc;
    Samplesum2 += y * y; 
    Samplecount2++;
    lastsample2 = millis();
  }
  if (Samplecount2 == 1000) {
    float mean = Samplesum2 / Samplecount2;
    float rms = sqrt(mean);
    float mV = rms / 100; 
    
    Serial.print("Current sensor 2 - The final rms: ");
    Serial.println(mV, 2); 
    
    Blynk.virtualWrite(VIRTUAL_PIN_ACS712_2, mV);
 
    Samplesum2 = 0;
    Samplecount2 = 0;
  }
}

void temperaturesensor1(){
  float totalTemp = 0; 
  int numReadings = 100; 
  for (int i = 0; i < numReadings; i++) {
    int data = analogRead(dataPin1);
    Serial.println(data);
    float temp = 0.266 * data - 332; 
    totalTemp += temp; 
    delay(50); 
  }
  float avgTemp = totalTemp / numReadings; 
  Serial.print("Temperature sensor 1 - Average Temperature: ");
  Serial.println(avgTemp);
  Blynk.virtualWrite(VIRTUAL_PIN_TEMP_1, avgTemp);
}

void temperaturesensor2(){
float totalTemp = 0; 
  int numReadings = 100; 
  for (int i = 0; i < numReadings; i++) {
    int data = analogRead(dataPin2);
    Serial.println(data);
    float temp = 0.266 * data - 332; 
    totalTemp += temp; 
    delay(50); 
  }
  float avgTemp = totalTemp / numReadings; 
  Serial.print("Temperature sensor 2 - Average Temperature: ");
  Serial.println(avgTemp);
  Blynk.virtualWrite(VIRTUAL_PIN_TEMP_2, avgTemp);  
}

void temperaturesensor3(){
 float totalTemp = 0; 
  int numReadings = 100; 
  for (int i = 0; i < numReadings; i++) {
    int data = analogRead(dataPin3);
    Serial.println(data);
    float temp = 0.266 * data - 332; 
    totalTemp += temp; 
    delay(50); 
  }
  float avgTemp = totalTemp / numReadings; 
  Serial.print("Temperature sensor 3 - Average Temperature: ");
  Serial.println(avgTemp);
  Blynk.virtualWrite(VIRTUAL_PIN_TEMP_3, avgTemp); 
}