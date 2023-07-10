// * Code writing started on 2023-03-09
// *
// * Copyright (c) Smart_Cane [Kim JaeHyeon, Kim SuJin, Seo JinHyeok]
// *
// * This source code is licensed under th MIT license found in the LICENSE file in the
// * root directory of this source tree.
// *
// * This code provides instructions for operating a Smart Cane
// *
// * The distance of the infrared sensor is defined as "infrared," while the ultrasonic sensor 
// * located at the bottom of the cane is defined as "distanceA," and the ultrasonic sensor 
// * located at the top of the cane is defined as "distanceB."
// *

#include <SoftwareSerial.h>
SoftwareSerial HC06(6, 7);        
SoftwareSerial gpsSerial(11, 12);  

int distanceA = 0;
int distanceB = 0;
int infrared = 0;
int vibrationValue = 0;
const int trigA = 2;
const int echoA = 3;
const int trigB = 4;
const int echoB = 5;

// 센서 별 감지 거리
unsigned int INFRARED_THRESHOLD = 400;    
unsigned int DISTANCE_A_THRESHOLD1 = 50;  
unsigned int DISTANCE_A_THRESHOLD2 = 35; 
unsigned int DISTANCE_B_THRESHOLD = 70;  

// Tone delay 값
const unsigned int TONE_DURATION1 = 250;   
const unsigned int TONE_DURATION2 = 70;    

// 센서 주파수 값
const unsigned int INFRARED_TONE = 500;    
const unsigned int DISTANCE_A_TONE = 300;  
const unsigned int DISTANCE_B_TONE = 350;  

void setup() {
  Serial.begin(9600);
  HC06.begin(9600);
  gpsSerial.begin(9600);
  pinMode(trigA, OUTPUT);
  pinMode(echoA, INPUT);
  pinMode(trigB, OUTPUT);
  pinMode(echoB, INPUT);
  pinMode(8, INPUT);
  pinMode(9, 2);
  pinMode(10, 2);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  UpdateValues();
  CheckPlayTone();
  CheckGPS();
  SendValues();
  delay(100);
}

void UpdateValues() {
  infrared = analogRead(A0);

  digitalWrite(trigA, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigA, LOW);
  distanceA = pulseIn(echoA, HIGH) * 340 / 2 / 10000;

  digitalWrite(trigB, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigB, LOW);
  distanceB = pulseIn(echoB, HIGH) * 340 / 2 / 10000;

  vibrationValue = analogRead(A1);

  Serial.print(" INFRARED : ");
  Serial.print(infrared);
  Serial.print(" Distance A: ");
  Serial.print(distanceA);
  Serial.print(" Distance B: ");
  Serial.println(distanceB);
  Serial.print(" VIBRATION : ");
  Serial.println(vibrationValue);

  HC06.println(infrared);
  HC06.println(distanceA);
  HC06.println(distanceB);
}

void playTone(unsigned int frequency, unsigned int duration) {
  tone(8, frequency, 90);
  delay(duration);
  noTone(8);
}

void CheckPlayTone() {
  static int distanceA_previous = 0;

  if (infrared <= INFRARED_THRESHOLD) {
    playTone(INFRARED_TONE, TONE_DURATION2);
  } else if ((distanceA_previous - distanceA) >= 150) {
    playTone(DISTANCE_A_TONE, TONE_DURATION2);
    playTone(DISTANCE_A_TONE, TONE_DURATION2);
  } else if (distanceA <= DISTANCE_A_THRESHOLD1 && distanceA > DISTANCE_A_THRESHOLD2) {
    playTone(DISTANCE_A_TONE, TONE_DURATION1);
  } else if (distanceA <= DISTANCE_A_THRESHOLD2) {
    playTone(DISTANCE_A_TONE, TONE_DURATION2);
  } else if (distanceB <= DISTANCE_B_THRESHOLD) {
    int mappedValue = map(distanceB, 0, DISTANCE_B_THRESHOLD, 700, DISTANCE_B_TONE);
    playTone(mappedValue, TONE_DURATION2);
  }

  if (vibrationValue >= 800) {
    HC06.println(10059);
    delay(200);
  }

  if (digitalRead(9) == LOW) {
    HC06.println(10009);
    delay(200);
  }

  if (digitalRead(10) == LOW) {
    HC06.println(10010);
    delay(200);
  }

  distanceA_previous = distanceA;
}

void CheckGPS() {
  if (gpsSerial.available()) {
    String nmeaSentence = gpsSerial.readStringUntil('\n'); 

    // 데이터 파싱
    if (nmeaSentence.startsWith("$GNGGA")) {
      int comma1 = nmeaSentence.indexOf(',', 0);
      int comma2 = nmeaSentence.indexOf(',', comma1 + 1);
      int comma3 = nmeaSentence.indexOf(',', comma2 + 1);
      int comma4 = nmeaSentence.indexOf(',', comma3 + 1);

      String latitudeValue = nmeaSentence.substring(comma2 + 1, comma3);
      String longitudeValue = nmeaSentence.substring(comma4 + 1);

      int latitude = latitudeValue.toInt();
      int longitude = longitudeValue.toInt();

      HC06.println(latitude);
      HC06.println(longitude);
    }
  }
}

void SendValues() {
  if (HC06.available()) {
    String receivedData = HC06.readStringUntil('\n'); 

    // 데이터 파싱
    int commaIndex1 = receivedData.indexOf(',');
    int commaIndex2 = receivedData.indexOf(',', commaIndex1 + 1);
    int commaIndex3 = receivedData.indexOf(',', commaIndex2 + 1);
    int commaIndex4 = receivedData.indexOf(',', commaIndex3 + 1);
    int commaIndex5 = receivedData.indexOf(',', commaIndex4 + 1);

    if (commaIndex1 != -1 && commaIndex2 != -1 && commaIndex3 != -1) {
      // 각 값들을 추출하여 변수에 할당
      String value1Str = receivedData.substring(commaIndex1 + 1, commaIndex2);
      String value2Str = receivedData.substring(commaIndex2 + 1, commaIndex3);
      String value3Str = receivedData.substring(commaIndex3 + 1, commaIndex4);
      String value4Str = receivedData.substring(commaIndex4 + 1, commaIndex5);
      String value5Str = receivedData.substring(commaIndex5 + 1);

      // 추출한 값들을 정수형으로 변환하여 변수에 할당
      INFRARED_THRESHOLD = value1Str.toInt();
      DISTANCE_A_THRESHOLD1 = value3Str.toInt();
      DISTANCE_B_THRESHOLD = value5Str.toInt();

      // 변경된 값을 출력
      Serial.print("INFRARED_THRESHOLD: ");
      Serial.println(INFRARED_THRESHOLD);
      Serial.print("DISTANCE_A_THRESHOLD1: ");
      Serial.println(DISTANCE_A_THRESHOLD1);
      Serial.print("DISTANCE_B_THRESHOLD: ");
      Serial.println(DISTANCE_B_THRESHOLD);
    }
  }
}