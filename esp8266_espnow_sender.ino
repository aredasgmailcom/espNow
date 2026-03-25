#include <ESP8266WiFi.h>
#include <espnow.h>

// --- GAVĖJO MAC ADRESAS (Tavo ESP32-C3) ---
uint8_t broadcastAddress[] = {0x28, 0x37, 0x2F, 0x69, 0x59, 0x30};

// Struktūra duomenims siųsti (turi sutapti su imtuvo struktūra)
struct __attribute__((packed)) MyData {
    char zinute[32];
    int skaicius;
};

MyData dataToSend;
unsigned int counter = 0;

// Funkcija, kuri praneša, ar pavyko išsiųsti
void onDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Siuntimo būsena: ");
  if (sendStatus == 0) {
    Serial.println("Pristatyta sėkmingai!");
  } else {
    Serial.println("Klaida siunčiant.");
  }
}

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW klaida");
    return;
  }

  // Nustatome siuntėjo rolę
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  
  // Registruojame atgalinį ryšį apie siuntimą
  esp_now_register_send_cb(onDataSent);
  
  // Pridedame gavėją į sąrašą
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  
  Serial.println("Siuntėjas paruoštas.");
}

void loop() {
  // Paruošiame duomenis
  strcpy(dataToSend.zinute, "Sveikas, C3 Mini!");
  dataToSend.skaicius = counter++;

  // Siunčiame duomenis
  esp_now_send(broadcastAddress, (uint8_t *) &dataToSend, sizeof(dataToSend));

  delay(2000); // Siųsti kas 2 sekundes
}
