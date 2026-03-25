#include <ESP8266WiFi.h>

void setup() {
  // Pradedame Serial ryšį (115200 greičiu)
  Serial.begin(115200);
  delay(500); // Maža pauzė, kad spėtų atsibusti Serial monitorius
  
  Serial.println();
  Serial.println("--- ESP8266 MAC ADRESO PAIEŠKA ---");

  // Nustatome režimą
  WiFi.mode(WIFI_STA);
  
  // Išvedame MAC adresą į konsolę
  Serial.print("Sėkmė! Tavo įrenginio MAC: ");
  Serial.println(WiFi.macAddress());
  
  Serial.println("----------------------------------");
}

void loop() {
  // Loop paliekame tuščią
}
