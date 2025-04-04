# Proyecto: Control de Puerta con RFID, Ultrasonidos y Servo

Este proyecto implementa un sistema de apertura de puerta basado en RFID, sensores de ultrasonidos y un servo motor. Permite abrir la puerta con una tarjeta autorizada, mantenerla abierta mientras haya un obstáculo detectado y cerrarla automáticamente tras 10 segundos. Además, incluye un modo de cierre forzado con un botón.

## Componentes Utilizados

- **Arduino Uno**
- **Módulo RFID RC522** (para lectura de tarjetas)
- **Servo motor** (para simular la apertura y cierre de la puerta)
- **Sensor de ultrasonidos HC-SR04** (para detectar obstáculos)
- **Botón** (para cierre forzado)
- **Protoboard y cables**

## Conexiones

| Componente | Pin Arduino |
|------------|------------|
| RFID RC522 (SDA) | 10 |
| RFID RC522 (SCK) | 13 |
| RFID RC522 (MOSI) | 11 |
| RFID RC522 (MISO) | 12 |
| RFID RC522 (RST) | 8 |
| Servo motor (señal) | 9 |
| Sensor ultrasónico (Trig) | 7 |
| Sensor ultrasónico (Echo) | 6 |
| Botón (con resistencia pull-up interna) | 5 |

## Funcionamiento

1. **Esperando tarjeta**: El sistema está en espera de que se acerque una tarjeta RFID.
2. **Verificación de tarjeta**:
   - Si la tarjeta es válida, la puerta se abre y se mantiene abierta.
   - Si no es válida, no ocurre nada.
3. **Mantenimiento de apertura**:
   - La puerta se mantiene abierta por 10 segundos.
   - Si el sensor ultrasónico detecta un obstáculo, el temporizador se reinicia.
4. **Cierre forzado**:
   - Si el botón se mantiene presionado durante 2 segundos, la puerta se cierra inmediatamente.

## Instalación y Uso

1. **Clonar el repositorio**:
   ```bash
   git clone  https://github.com/iaFonso2025/Proyecto.git
   cd puerta-rfid
   ```
2. **Abrir el código en Arduino IDE**.
3. **Cargar el programa en Arduino**.
4. **Colocar la tarjeta RFID autorizada sobre el lector para abrir la puerta**.
5. **Comprobar los mensajes en el monitor serie para verificar el funcionamiento**.

## Salida por Consola (Ejemplo)

```plaintext
Esperando tarjeta...
UID detectado: 93 D0 2C 16
Puerta abierta
Distancia: 15 cm
Distancia: 8 cm (Objeto detectado, reiniciando temporizador)
Puerta cerrada
```

## Mejoras Futuras

- Integrar un sistema de registro de accesos.
- Agregar una pantalla LCD para mostrar mensajes.
- Implementar autenticación con múltiples tarjetas.

## Licencia

Este proyecto está bajo la licencia MIT. Puedes modificarlo y usarlo libremente.

