#include <esp_now.h>
#include <WiFi.h>
#include <U8g2lib.h>
#include <Wire.h>

// SCL=6, SDA=5
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, 6, 5);

struct MyData {
    char zinute[32];
    int skaicius;
};

MyData incomingData;
int lastNumber = -1; // Sekame paskutinį rodytą skaičių

void onDataRecv(const esp_now_recv_info_t * recv_info, const uint8_t *data, int len) {
    memcpy(&incomingData, data, sizeof(incomingData));
    
    // Atnaujiname ekraną TIK jei skaičius pasikeitė
    if (incomingData.skaicius != lastNumber) {
        lastNumber = incomingData.skaicius;

        u8g2.clearBuffer(); // Naudojame šitą, bet optimizuotai
        
        // Pasirenkame tvarkingą, didelį skaičių šriftą
        u8g2.setFont(u8g2_font_logisoso32_tn); 
        
        // Tavo rasta "saugi zona" (X=35, Y=55)
        // Jei skaičius vienaženklis, galime pastumti labiau į centrą
        int xPos = (lastNumber < 10) ? 45 : 35; 
        
        u8g2.setCursor(xPos, 55); 
        u8g2.print(lastNumber);
        
        u8g2.sendBuffer(); // Viską išsiunčiame vienu kartu
    }
}

void setup() {
    Wire.begin(5, 6);
    u8g2.begin();
    u8g2.setContrast(255);
    
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(40, 45, "WAIT");
    u8g2.sendBuffer();

    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) return;
    esp_now_register_recv_cb(onDataRecv);
}

void loop() {
    // Tuščia
}
