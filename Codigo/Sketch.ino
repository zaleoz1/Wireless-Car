
// INCLUSÃO DE BIBLIOTECAS
#include "motor.h"
#include <SoftwareSerial.h>
#include "PiscaLed.h"

// DEFINIÇÕES DE PINOS
#define pinFarol 12
#define pinLanterna 3
#define pinBuzina 4

#define pinRx 5
#define pinTx 6

// DEFINIÇÕES
#define LIGADO HIGH
#define DESLIGADO LOW

// INSTANCIANDO OBJETOS
SoftwareSerial btSerial(pinRx, pinTx); // RX, TX

// DECLARAÇÃO DE FUNÇÕES
PiscaLed farol(pinFarol, 350);
PiscaLed lanterna(pinLanterna, 350);

// DECLARAÇÃO DE VARIÁVEIS
char comando;
bool estadoFarol, estadoLanterna, estadoPisca;

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  pinMode(pinBuzina, OUTPUT);

  digitalWrite(pinFarol, LOW);
  digitalWrite(pinLanterna, LOW);
  digitalWrite(pinBuzina, LOW);

  estadoFarol = estadoLanterna = estadoPisca = DESLIGADO;

  Serial.println("Fim Setup");
  delay(2000);
}

void loop() {

  if (estadoPisca) {
    farol.loop();
    lanterna.loop();
  }

  if (btSerial.available()) {
    comando = btSerial.read();
  }

  switch (comando) {
    case 'F': {
        moveFrente();
        break;
      }
    case 'I': {
        frenteDireita();
        break;
      }
    case 'G': {
        frenteEsquerda();
        break;
      }
    case 'R': {
        direita();
        break;
      }
    case 'L': {
        esquerda();
        break;
      }
    case 'B': {
        moveRe();
        break;
      }
    case 'H': {
        reEsquerda();
        break;
      }
    case 'J': {
        reDireita();
        break;
      }
    case 'W': {
        digitalWrite(pinFarol, HIGH);
        estadoFarol = LIGADO;
        break;
      }
    case 'w': {
        digitalWrite(pinFarol, LOW);
        estadoFarol = DESLIGADO;
        break;
      }
    case 'U': {
        digitalWrite(pinLanterna, HIGH);
        estadoLanterna = LIGADO;
        break;
      }
    case 'u': {
        digitalWrite(pinLanterna, LOW);
        estadoLanterna = DESLIGADO;
        break;
      }
    case 'V': {
        tone(pinBuzina, 380);
        break;
      }
    case 'v': {
        noTone(pinBuzina);
        break;
      }
    case 'X': {
        farol.play();
        lanterna.play();
        estadoPisca = LIGADO;
        break;
      }
    case 'x': {
        farol.stop();
        lanterna.stop();
        
        farol.loop();
        lanterna.loop();

        estadoPisca = DESLIGADO;

        if ( estadoLanterna) digitalWrite(pinLanterna, HIGH);
        else digitalWrite(pinLanterna, LOW);

        if ( estadoFarol) digitalWrite(pinFarol, HIGH);
        else digitalWrite(pinFarol, LOW);

        break;
      }
    default: {
        parar();
        break;
      }
  }
}


// IMPLEMENTO DE FUNÇÕES
