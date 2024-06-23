//Hola mi gente
//Integrantes:
//Euroza Rodriguez Diego Rodrigo
//Isidro Gomez Cesar Octavio

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// cambios para mí jaja nadie sabe nooooo
#define ANCHO_PANTALLA 128 // Ancho de la pantalla OLED
#define ALTO_PANTALLA 64 // Alto de la pantalla OLED
#define OLED_RESET -1 // Pin reset incluido en algunos modelos de pantallas (-1 si no disponemos de pulsador). 
#define DIRECCION_PANTALLA 0x3C //Dirección de comunicacion: 0x3D para 128x64, 0x3C para 128x32
#define LF_WIDTH 32
#define LF_HEIGHT 32
#define LB_WIDTH 32
#define LB_HEIGHT 32
// nooooo jaja xddd
// nose mis  momos nose xd
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, OLED_RESET);

const unsigned char PROGMEM lf []  = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0x60, 0x00, 
    0x00, 0x03, 0x60, 0x00, 0x00, 0x36, 0x60, 0x00, 0x00, 0x7c, 0xc0, 0x00, 0x00, 0x7a, 0x80, 0x00, 
    0x00, 0xfa, 0x80, 0x00, 0x00, 0xfa, 0xc0, 0x00, 0x00, 0xf9, 0x60, 0x00, 0x00, 0x7c, 0xb0, 0x00, 
    0x00, 0x7e, 0x58, 0x00, 0x00, 0xbf, 0x29, 0x00, 0x00, 0xdf, 0x8f, 0x00, 0x00, 0xfb, 0x8f, 0x00, 
    0x00, 0xb9, 0xcf, 0x00, 0x00, 0x9c, 0x8f, 0x00, 0x00, 0x8e, 0x87, 0x00, 0x00, 0x57, 0x03, 0x00, 
    0x00, 0x6b, 0x84, 0x00, 0x00, 0x31, 0xcc, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char PROGMEM lb []  = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x03, 0xc0, 0x00, 0x00, 0x0e, 0xf0, 0x00, 0x00, 0x1e, 0x70, 0x00, 0x00, 0x1e, 0x38, 0x00, 
    0x00, 0x12, 0x18, 0x00, 0x00, 0x30, 0x08, 0x00, 0x00, 0x38, 0x1c, 0x00, 0x00, 0x3c, 0x3c, 0x00, 
    0x00, 0x3c, 0x3c, 0x00, 0x00, 0x38, 0x1c, 0x00, 0x00, 0x30, 0x08, 0x00, 0x00, 0x12, 0x18, 0x00, 
    0x00, 0x1e, 0x38, 0x00, 0x00, 0x1e, 0x70, 0x00, 0x00, 0x0e, 0xe0, 0x00, 0x00, 0x03, 0xc0, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const int Trigger = 10;   //Pin digital  para el Trigger del sensor ULTRASONICO
const int Echo = 9;   //Pin digital  para el Echo del sensor ULTRASONICO
long t; // tiempo que demora en llegar el eco
long d = 100; // distancia en centimetros
int bandera = 0;
int alarma = 0;       

void setup() {
    Serial.begin(9600);
    if(!display.begin(SSD1306_SWITCHCAPVCC, DIRECCION_PANTALLA)) {
        Serial.println(F("Fallo en la asignacion de SSD1306"));
        while (true); // detener si hay error
    }
    display.clearDisplay();
    pinMode(2, INPUT);    
    pinMode(3, INPUT);    
    pinMode(4, OUTPUT);   
    pinMode(5, OUTPUT);   
    pinMode(6, OUTPUT);   
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(11, OUTPUT); // luces
    pinMode(Trigger, OUTPUT); // pin como salida
    pinMode(Echo, INPUT);  // pin como entrada
    digitalWrite(Trigger, LOW); // Inicializamos el pin con 0
    digitalWrite(11, LOW); // Inicializamos el pin con 0
}
 
void loop() {
    while(alarma == 0) {
        digitalWrite(4, LOW); 
        digitalWrite(5, LOW);
        digitalWrite(6, LOW); 
        digitalWrite(7, LOW);

        int value = analogRead(A0);
        float millivolts = (value / 1023.0) * 500;
        int grados = millivolts; 

        if(grados >= 50) {
            display.clearDisplay();
            display.drawBitmap((display.width() - LF_WIDTH) / 2, ((display.height() - LF_HEIGHT) / 2) + 7, lf, LF_WIDTH, LF_HEIGHT, WHITE);
            display.display();
             d = 100;
             alarma = 1;
            break;
            // ALARMA ACTIVADA
        }
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(2, 2);
        display.print("Temperatura:");
        display.println(grados);
        display.setCursor(2, 13);
        display.println("Distancia:");
        display.println(distancia());
        display.display();
    }
    // FUNCION PARA TONO DE SIRENA
    distancia();
    digitalWrite(8, HIGH); 
    for(int i = 0; i <= 100; i++) {
        direccion();
        delay(1);
    }
    distancia();
    digitalWrite(8, LOW);
    for(int i = 0; i <= 100; i++) {
        direccion();
        delay(1);
    }

    if(d <= 20) {
        controlBT();
        bandera = 0;
    }
}
//xdddd
float distancia() {
    digitalWrite(Trigger, HIGH);
    delayMicroseconds(10); // Enviamos un pulso de 10us
    digitalWrite(Trigger, LOW);
    t = pulseIn(Echo, HIGH); // obtenemos el ancho del pulso
    d = t / 59; // escalamos el tiempo a una distancia en cm
    return d;
}

void controlBT() {
    display.clearDisplay(); 
    display.drawBitmap((display.width() - LB_WIDTH) / 2, ((display.height() - LB_HEIGHT) / 2) + 7, lb, LB_WIDTH, LB_HEIGHT, WHITE);
    display.display();
    while(bandera == 0) {
        if (Serial.available()) {
            char dato = Serial.read();
            Serial.print("Dato recibido: ");
            Serial.println(dato);
            switch (dato) {
                case 'F':
                    digitalWrite(5, LOW);
                    digitalWrite(4, HIGH);
                    digitalWrite(7, HIGH);
                    digitalWrite(6, LOW);
                    break;
                case 'L':
                    digitalWrite(4, HIGH);
                    digitalWrite(5, LOW);
                    digitalWrite(6, HIGH);
                    digitalWrite(7, LOW);
                    break;
                case 'R':
                    digitalWrite(4, LOW);
                    digitalWrite(5, HIGH);
                    digitalWrite(6, LOW);
                    digitalWrite(7, HIGH);
                    break;
                case 'B':
                    digitalWrite(4, LOW);
                    digitalWrite(5, HIGH);
                    digitalWrite(6, HIGH);
                    digitalWrite(7, LOW);
                    break;
                case 'X':
                    bandera = 1;
                    break;
                case 'T':
                    digitalWrite(11, HIGH);
                    break;
                case 'C':
                    digitalWrite(11, LOW);
                    break;
                default:
                    digitalWrite(4, LOW); 
                    digitalWrite(5, LOW);
                    digitalWrite(6, LOW); 
                    digitalWrite(7, LOW);
            }
        }
    }
}

void direccion() {
    if((digitalRead(2) == 0) && (digitalRead(3) == 0)) {
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(6, LOW);
    }
    if(digitalRead(2) == 0 && digitalRead(3) == 1) {
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(6, HIGH);
    }
    if(digitalRead(2) == 1 && digitalRead(3) == 0) {
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
    }
    if(d <= 20) {
        digitalWrite(4, LOW); 
        digitalWrite(5, LOW);
        digitalWrite(6, LOW); 
        digitalWrite(7, LOW);
    }
}
