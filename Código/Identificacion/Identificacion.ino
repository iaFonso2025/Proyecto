#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 8  // Pin 8 para el reset del RC522
#define SS_PIN 10  // Pin 10 para el SS (SDA) del RC522

MFRC522 mfrc522(SS_PIN, RST_PIN); // Creamos el objeto para el RC522

void setup() {
    Serial.begin(9600); // Iniciamos la comunicación serial
    SPI.begin();        // Iniciamos el bus SPI
    mfrc522.PCD_Init(); // Iniciamos el MFRC522
    Serial.println("Aproxime la tarjeta para leer su UID...");
}

void loop() {
    // Revisamos si hay una nueva tarjeta presente
    if (mfrc522.PICC_IsNewCardPresent()) {  
        // Seleccionamos una tarjeta
        if (mfrc522.PICC_ReadCardSerial()) {
            // Enviamos serialmente su UID
            Serial.print("Card UID:");
            for (byte i = 0; i < mfrc522.uid.size; i++) {
                Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                Serial.print(mfrc522.uid.uidByte[i], HEX);   
            } 
            Serial.println();
            // Terminamos la lectura de la tarjeta actual
            mfrc522.PICC_HaltA();         
        }      
    }    
}
