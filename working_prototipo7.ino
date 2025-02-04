//librerias
#include <ESP32Servo.h> 
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

//OLED
#define OLED_CS   10  // Chip Select
#define OLED_DC   9   // Data/Command
#define OLED_RES  21  // Reset
#define OLED_CLK  12  // Clock (SCK)
#define OLED_MOSI 11  // Data (MOSI)

// Inicializar pantalla OLED SSD1309 en SPI
U8G2_SSD1309_128X64_NONAME2_F_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RES);

//SERVOMOTORES
Servo brazo;     // Crea una instancia del objeto Servo
int pinBrazo = 42; // Cambia según el pin que uses para el servo
Servo dispensador;  // El servo se llama dispensador
int dispensadorPin = 3; //El pin del dispensador es el 42

//SENSOR DE DISTANCIA
const int pinSensor = 14; //pin del sensor de obstaculos
int ledAlerta = 5;

// Botones y LEDs
const int botonExcelente = 45; // Botón Verde
const int ledExcelente = 40;   // LED Verde

const int botonBien = 48; // Botón Amarillo
const int ledBien = 39;   // LED Amarillo

const int botonNormal = 47; // Botón Blanco
const int ledNormal = 38;  // LED Blanco

const int botonMal = 19; // Botón Azul
const int ledMal = 37;   // LED Azul

const int botonHorrible = 20; // Botón Rojo
const int ledHorrible = 36;   // LED Rojo

// Arrays para no volverme loca
const int botones[] = {botonExcelente, botonBien, botonNormal, botonMal, botonHorrible};
const int leds[] = {ledExcelente, ledBien, ledNormal, ledMal, ledHorrible};

int i;  // Contador Multipropósito

void setup ()
{

Serial.begin(115200); // inicalizando comunicacion serial a 115200 baudios

//SAlUDO
pinMode (pinSensor, INPUT); // modulo ky 032 detecto de obstaculos
brazo.attach(pinBrazo, 500, 2500); //configuracion del servo para simulacion de saludo
pinMode(ledAlerta, OUTPUT);
digitalWrite(ledAlerta, LOW);

//Dispensador
dispensador.attach(dispensadorPin, 500, 2500); // Inicializamos la posición del servo
dispensador.write(0);

//CONFIGURACION OLED
u8g2.begin();  // Iniciar pantalla OLED
u8g2.setFont(u8g2_font_ncenB10_tr);  // Fuente más grande

// Configuración de Botones y LEDS
for (i = 0; i < 5; i++) {
    pinMode(botones[i], INPUT); //botones como entrada
    pinMode(leds[i], OUTPUT); //Leds como salida
    digitalWrite(leds[i], LOW); // LEDs apagados al inicio
  }
}


void loop ()
{
if (digitalRead(pinSensor) == LOW) 
{ 
//si el sensor detecta una persona al frente
Serial.println("Persona Detectada");
delay(500); 
brazo.write(0);
digitalWrite(ledAlerta, LOW);

//mostrar mensajes en la pantalla oled
unsigned long tiempoInicio = millis();
  mostrarMensajes("Hola");
  delay(2000);
  mostrarMensajes("Soy ABA");
  delay(2000);
  mostrarMensajes("Tu    Robot   Emocional");
  delay(2000);
  mostrarMensajes("Me Interesa Tu Estado De Animo,");
  delay(2000);
  mostrarMensajes("Presiona uno  de los    Botones");

  esperarBoton(); //Esperar hasta que un boton sea apretado

//Boton y Led Verde estado Excelente
if (digitalRead(botonExcelente) == HIGH) { 
    while (digitalRead(botonExcelente) == HIGH) {
      if (millis() - tiempoInicio >= 3000) {  // Si pasan 3 segundos
        digitalWrite(ledExcelente, HIGH); // Enciende el LED
        mostrarMensajes("  Estado:   Excelente");
        delay(2000);
        digitalWrite(ledExcelente, LOW); // Apaga el LED
        break;
      }
    }
  }

//Boton y Led amarillo estado bien
  else if (digitalRead(botonBien) == HIGH) {
    while (digitalRead(botonBien) == HIGH) {
      if (millis() - tiempoInicio >= 3000) {  // Si pasan 3 segundos
        digitalWrite(ledBien, HIGH); // Enciende el LED
        mostrarMensajes("  Estado:    Bien");
        delay(2000);
        digitalWrite(ledBien, LOW); // Apaga el LED
        break;
      }
    }
  }

// boton y led blanco estado normal
  else if (digitalRead(botonNormal) == HIGH) {
    while (digitalRead(botonNormal) == HIGH) {
      if (millis() - tiempoInicio >= 3000) {  // Si pasan 3 segundos
        digitalWrite(ledNormal, HIGH); // Enciende el LED
        mostrarMensajes("  Estado:    Normal");
        delay(2000);
        digitalWrite(ledNormal, LOW); // Apaga el LED
        break;
      }
    }
  }

//boton y led azul estado mal
  else if (digitalRead(botonMal) == HIGH) {
    while (digitalRead(botonMal) == HIGH) {
      if (millis() - tiempoInicio >= 3000) {  // Si pasan 3 segundos
        digitalWrite(ledMal, HIGH); // Enciende el LED
        mostrarMensajes("  Estado:   Mal");
        delay(2000);
        digitalWrite(ledMal, LOW); // Apaga el LED
        break;
      }
    }
  }

// boton y led rojo estado horrible
  else if (digitalRead(botonHorrible) == HIGH) {
    while (digitalRead(botonHorrible) == HIGH) {
      if (millis() - tiempoInicio >= 3000) {  // Si pasan 3 segundos
        digitalWrite(ledHorrible, HIGH); // Enciende el LED
        mostrarMensajes("  Estado:  Horrible");
        delay(2000);
        digitalWrite(ledHorrible, LOW); // Apaga el LED
        break;
      } 
    }
  }
  
  //continuamos mostrando mensajes en la oled
  mostrarMensajes("Toma...");
  delay(1500);
  mostrarMensajes("Para Que Te   Sientas   Mucho");
  delay(2000);
  mostrarMensajes("MEJOR :)");
  delay(2000);

//dispensar pastillas
dispensador.write(90); // Mueve el servo a 0 grados
  delay(1000);
dispensador.write(0); // Mueve el servo a 180 grados
  delay(1000);

  mostrarMensajes("Nos Vemos");
  delay(2000);

  mostrarMensajes(";)");
  delay(2000);


}


//SI NO HAY NADIE AL FRENTE
else { 
Serial.println("No hay nadie al frente");
delay(500);
digitalWrite (ledAlerta, HIGH);
for (int pos = 0; pos <= 180; pos++) {
    brazo.write(pos); // Mueve a la posición actual
    delay(7);          // Espera un poco para suavizar el movimiento
  }
  for (int pos = 180; pos >= 0; pos--) {
    brazo.write(pos); // Mueve a la posición actual
    delay(7);          // Espera un poco para suavizar el movimiento
  }


}
}



// Función para mostrar mensajes en la OLED con centrado correcto
void mostrarMensajes(String mensaje) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);  // Fuente más grande

    int maxCharsPerLine = 12;  // Máx caracteres por línea en fuente más grande
    int numLines = (mensaje.length() + maxCharsPerLine - 1) / maxCharsPerLine;

    int startY = (64 - (numLines * 14)) / 2;  // Centrar verticalmente

    for (int i = 0; i < numLines; i++) {
        String linea = mensaje.substring(i * maxCharsPerLine, (i + 1) * maxCharsPerLine);
        int textWidth = u8g2.getUTF8Width(linea.c_str());  // Obtener ancho del texto
        int xPos = (128 - textWidth) / 2;  // Calcular centrado horizontal
        u8g2.setCursor(xPos, startY + i * 14);
        u8g2.print(linea);
    }

    u8g2.sendBuffer();  // Mostrar en pantalla
    delay(500);
}

// Función para esperar la presión de un botón
void esperarBoton() {
  bool botonPresionado = false;
  
  // Esperar hasta que cualquiera de los botones se presione
  while (!botonPresionado) {
    for (int i = 0; i < 5; i++) {
      if (digitalRead(botones[i]) == HIGH) { // Si algún botón es presionado
        botonPresionado = true;
        break;
      }
    }
  }
}
