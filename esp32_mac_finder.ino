#include <WiFi.h>

void setup() {
  // ESP32-C3 Mini USB nustatymai
  Serial.begin(115200);
  
  // Laukiame, kol Serial prievadas taps aktyvus (svarbu C3 modeliui)
  while (!Serial) {
    delay(10);
  }

  WiFi.mode(WIFI_STA);
  Serial.println("\n--- MAC PAIEŠKA PRADĖTA ---");
}

void loop() {
  // Spausdiname MAC adresą kas 2 sekundes
  Serial.print("Tavo ESP32-C3 MAC adresas: ");
  Serial.println(WiFi.macAddress());
  
  Serial.println("Laukiu... (atidarykite Serial Monitor)");
  Serial.println("------------------------------------------");
  
  delay(2000); 
}
