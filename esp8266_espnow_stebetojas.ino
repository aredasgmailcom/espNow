/* * PROCESORIUS: ESP8266 (NodeMCU)
 * APRAŠYMAS: Etaloninis imtuvas be ekrano. 
 * Naudojamas palyginti signalo priėmimo kokybę su ESP32-C3.
 * Rezultatus siunčia į Serial Monitor (115200 baud).
 */

#include <ESP8266WiFi.h>
#include <espnow.h>

struct MyData {
    char zinute[32];
    int skaicius;
};

MyData incomingData;

int dBmToPercent(int dbm) {
    if(dbm <= -100) return 0;
    if(dbm >= -30) return 100;
    return map(dbm, -100, -30, 0, 100);
}

void onDataRecv(uint8_t * mac, uint8_t *incoming, uint8_t len) {
    memcpy(&incomingData, incoming, sizeof(incomingData));
    int rssi = WiFi.RSSI(); 
    int percent = dBmToPercent(rssi);

    Serial.print("SK: ");
    Serial.print(incomingData.skaicius);
    Serial.print(" | RSSI: ");
    Serial.print(rssi);
    Serial.print("dBm | STIPRUMAS: ");
    Serial.print(percent);
    Serial.println("%");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    if (esp_now_init() != 0) return;

    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(onDataRecv);
    
    Serial.println("Etalonas laukia signalo...");
}

void loop() {}
