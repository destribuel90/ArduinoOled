//Hola mi gente
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//probando esto
#define ANCHO_PANTALLA 128 // Ancho de la pantalla OLED
#define ALTO_PANTALLA 64 // Alto de la pantalla OLED
#define OLED_RESET     -1 // Pin reset incluido en algunos modelos de pantallas (-1 si no disponemos de pulsador). 
#define DIRECCION_PANTALLA 0x3C //Dirección de comunicacion: 0x3D para 128x64, 0x3C para 128x32
const int Trigger = 10;   //Pin digital  para el Trigger del sensor ULTRASONICO
const int Echo = 9;   //Pin digital  para el Echo del sensor ULTRASONICO
long t; //timepo que demora en llegar el eco
long d=100; //distancia en centimetros
int bandera=0;
 float grados= 40; 
 int alarma=0;       
 xdddd 
void setup() {
    Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, DIRECCION_PANTALLA)) {
    Serial.println(F("Fallo en la asignacion de SSD1306"));
  }
    display.clearDisplay();
    Serial.begin(9600);
    pinMode(2, INPUT);    
    pinMode(3, INPUT);    
    pinMode(4, OUTPUT);   
    pinMode(5, OUTPUT);   
    pinMode(6, OUTPUT);   
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    /////
    pinMode(11, OUTPUT); //luces
    pinMode(Trigger, OUTPUT); //pin como salida
    pinMode(Echo, INPUT);  //pin como entrada
    digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
    digitalWrite(11, LOW);//Inicializamos el pin con 0
}
 
void loop() {
  
  while(alarma==0) 
  {
       digitalWrite(4,LOW); 
       digitalWrite(5,LOW);
       digitalWrite(6,LOW); 
       digitalWrite(7,LOW);

        int value = analogRead(A0);
        float millivolts = (value / 1023.0) * 500;
        int grados = millivolts; 

        if(grados>=50){
        alarma=1; //ALARMA ACTIVADA
        }
        Serial.println(grados);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println("Temperatura:");
        display.println(grados);
        display.display();
        distancia();
        //se muestra la cara normal
  }
   //se muestra la cara enfadada
  //FUNCION PARA TONO DE SIRENA
distancia();
 digitalWrite(8,HIGH); 
 for(int i=0;i<=100;i++){
   direccion();
   delay(1);
 }
distancia();
  digitalWrite(8,LOW);
 for(int i=0;i<=100;i++){
   direccion();
   delay(1);
 }

        if(d<=20){
        controlBT();
        bandera=0;
        }
 
}



/////////////////////////////////////////////////////////////
void distancia()
{
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  Serial.println(d);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Distancia:");
  display.println(d);
  display.display();
}
//////////////////////////////////////////
void controlBT(){
while(bandera==0){
  if (Serial.available())
  {
    char dato=Serial.read();
    Serial.print("Dato recibido: ");
    Serial.println(dato);
    //aqui se muestra la cara enfadada
    switch (dato) {
      case 'F':
         digitalWrite(4,LOW);
         digitalWrite(5,HIGH);
         digitalWrite(6,HIGH);
         digitalWrite(7,LOW);
        break;
      case 'L':
          digitalWrite(4,HIGH);
         digitalWrite(5,LOW);
         digitalWrite(6,HIGH);
         digitalWrite(7,LOW);
         
        break;
      case 'R':
        digitalWrite(4,LOW);
         digitalWrite(5,HIGH);
         digitalWrite(6,LOW);
         digitalWrite(7,HIGH);
        break;
      case 'B':
         digitalWrite(5,LOW);
         digitalWrite(4,HIGH);
         digitalWrite(7,HIGH);
         digitalWrite(6,LOW);
        break;
      case 'X':
        bandera=1;
        break;
      case 'T':
        digitalWrite(11,HIGH);
        break;
      case 'C':
        digitalWrite(11,LOW);
        break;

      default:
       digitalWrite(4,LOW); 
       digitalWrite(5,LOW);
       digitalWrite(6,LOW); 
       digitalWrite(7,LOW);
  }
  }
}
}
//////////////////////////////////////


void direccion()
{
  
          if((digitalRead(2)==0) && (digitalRead(3)==0) )
        {
         digitalWrite(4,LOW);
         digitalWrite(5,HIGH);
         digitalWrite(6,HIGH);
         digitalWrite(7,LOW);
        }
        
        if(digitalRead(2)==0 && digitalRead(3)==1 )
        {
         digitalWrite(4,LOW);
         digitalWrite(5,HIGH);
         digitalWrite(6,LOW);
         digitalWrite(7,HIGH);
        }
        
        if(digitalRead(2)==1 && digitalRead(3)==0 )
        {
         digitalWrite(4,HIGH);
         digitalWrite(5,LOW);
         digitalWrite(6,HIGH);
         digitalWrite(7,LOW);
        }

        if(d<=20){
       digitalWrite(4,LOW); 
       digitalWrite(5,LOW);
       digitalWrite(6,LOW); 
       digitalWrite(7,LOW);
       //Serial.println("muro");
       //se muestra el tache
        }
}