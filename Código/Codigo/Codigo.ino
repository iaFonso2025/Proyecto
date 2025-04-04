#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

const int RST_PIN=8;
const int SS_PIN=10;
const int SERVO_PIN=9;
const int TRIG_PIN=7;
const int ECHO_PIN=6;
const int BOTON_PIN=5;
const int TIEMPO_ABIERTO=10000; // 10 segundos
const int DISTANCIA_MINIMA=10; // Distancia mínima para detectar un obstáculo (cm)

MFRC522 rfid(SS_PIN, RST_PIN);
Servo servo;
bool puertaAbierta=false;
unsigned long tiempoInicio=0;

// UID de la tarjeta autorizada (modifícalo con tu tarjeta)
byte tarjetaAutorizada[] = {0x12, 0x34, 0x56, 0x78};

void setup() {
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();
    servo.attach(SERVO_PIN);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BOTON_PIN, INPUT_PULLUP);
    servo.write(0);  // Puerta cerrada al iniciar
}

void loop() {
    if (tarjetaValida()) abrirPuerta();

    if (puertaAbierta) {
        if (obstaculoDetectado()) tiempoInicio = millis();

        if (botonForzado()) {
            cerrarPuerta();
            return;
        }

        if (millis() - tiempoInicio >= TIEMPO_ABIERTO) {
            if (!obstaculoDetectado()) cerrarPuerta();
            else tiempoInicio = millis();
        }
    }
}

bool tarjetaValida() {
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        Serial.print("UID detectado: ");
        for (byte i = 0; i < rfid.uid.size; i++) {
            Serial.print(rfid.uid.uidByte[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        // Compara el UID leído con el autorizado
        for (byte i = 0; i < 4; i++) {
            if (rfid.uid.uidByte[i] != tarjetaAutorizada[i]) {
                return false; // No es la tarjeta correcta
            }
        }
        return true; // Tarjeta válida
    }
    return false;
}

void abrirPuerta() {
    servo.write(90);  
    puertaAbierta = true;
    tiempoInicio = millis(); // Inicia el temporizador
    Serial.println("Puerta abierta");
}

void cerrarPuerta() {
    servo.write(0);  
    puertaAbierta = false;
    Serial.println("Puerta cerrada");
}

bool obstaculoDetectado() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duracion = pulseIn(ECHO_PIN, HIGH);
    int distancia = duracion * 0.034 / 2;

    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");

    return distancia < DISTANCIA_MINIMA;
}

bool botonForzado() {
    static unsigned long tiempoPresionado = 0;

    if (digitalRead(BOTON_PIN) == LOW) {
        if (tiempoPresionado == 0) {
            tiempoPresionado = millis(); // Empieza a contar el tiempo
        }
        if (millis() - tiempoPresionado >= 2000) { // Si se mantiene 2 seg
            Serial.println("Cierre forzado activado");
            return true;
        }
    } else {
        tiempoPresionado = 0; // Reiniciar contador cuando se suelta
    }

    return false;
}
  