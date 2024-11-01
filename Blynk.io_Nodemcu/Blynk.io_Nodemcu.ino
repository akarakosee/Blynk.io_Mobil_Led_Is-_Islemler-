/*********************************************************
Nesnelerin İnterneti ve Uygulamaları
*********************************************************/ 

#define BLYNK_TEMPLATE_ID "TMPL6NeoyQJtL"
#define BLYNK_TEMPLATE_NAME "TemplateName"
#define BLYNK_PRINT Serial 

#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h> 

char auth[] = "BlynkToken"; // Blynk token 
char ssid[] = "WifiAdı"; // Wi-Fi adı 
char pass[] = "WifiSifresi"; // Wi-Fi şifresi 

BLYNK_WRITE(V0) {
  digitalWrite(D0, param.asInt());
}

void setup() {
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  Blynk.run();
  sendTemperature(); // Sıcaklık verisini Blynk'e gönder
}

// Sıcaklık verisini A0 pininden oku ve Blynk'e gönder
void sendTemperature() {
  int analogValue = analogRead(A0); // LM35'ten okunan değer
  float voltage = analogValue * (3.3 / 1023.0); // Gerilimi hesapla (3.3V NodeMCU için)
  float temperatureC = voltage * 100; // Sıcaklığı hesapla (LM35 10mV/°C hassasiyetinde)
  
  Serial.print("Sıcaklık: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  Blynk.virtualWrite(V1, temperatureC); // Sıcaklık değerini Blynk V1 pinine gönder
  delay(1000); // 1 saniye bekle
}
