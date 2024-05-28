#include <Wire.h>

// Pines para LEDs
const int ledRojo = 7;
const int ledVerde = 8;
const int ledAmarillo = 9;

// Pines para Pulsadores
const int botonAbrir = 2;
const int botonCerrar = 3;
const int botonBloquear = 4;
bool bandera = false;

// Variables para el manejo de estados
enum EstadoPuerta {CERRADA, ABIERTA, BLOQUEADA};
EstadoPuerta estadoActual = CERRADA;
String contra = "";

unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;   

void setup() {
  Wire.begin(0x08); // Inicia I2C en dirección 0x08
  Wire.onReceive(receiveEvent); // Registra función para recibir datos
  Wire.onRequest(requestEvent); // Registra función para enviar datos cuando sea solicitado

  Serial.begin(9600);

  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);

  pinMode(botonAbrir, INPUT_PULLUP);
  pinMode(botonCerrar, INPUT_PULLUP);
  pinMode(botonBloquear, INPUT);
  attachInterrupt(digitalPinToInterrupt(botonAbrir), abrirPuerta, FALLING);
  attachInterrupt(digitalPinToInterrupt(botonCerrar), cerrarPuerta, FALLING);
  actualizarEstadoPuerta();
}

void loop() {
  if(Serial.available()>0){
    contra = Serial.readStringUntil('\n');
  }
  if(!digitalRead(botonBloquear)){
      if(contra == "1234"){
        if (bandera)
        {
          desbloquearPuerta();
        }
        else
        {
          bloquearPuerta();
        }
        contra = "";
      }
  }
}

void abrirPuerta() {
   if (bandera == false)
    { 
    if (estadoActual == CERRADA) {
      estadoActual = ABIERTA;
      actualizarEstadoPuerta();
    }
  }
}

void cerrarPuerta() {
  if (bandera == false)
  {
    if (estadoActual == ABIERTA || estadoActual == BLOQUEADA) {
      estadoActual = CERRADA;
      actualizarEstadoPuerta();
    }
  }
}

void bloquearPuerta() {
  unsigned long tiempoActual = millis();
  if ((tiempoActual - lastDebounceTime) > debounceDelay) {
    if (estadoActual == CERRADA) {
      // Aquí puedes implementar la lógica para la contraseña
      String password = leerPassword();
      if (password == "1234") {
        estadoActual = BLOQUEADA;
        actualizarEstadoPuerta();
        bandera = true;
      }
    } else if (estadoActual == BLOQUEADA) {
      // Aquí puedes implementar la lógica para la contraseña
      String password = leerPassword();
      if (password == "1234") {
        estadoActual = CERRADA;
        actualizarEstadoPuerta();
        bandera = true;
      }
    }
    lastDebounceTime = tiempoActual;
  }
}
void desbloquearPuerta(){
  unsigned long tiempoActual = millis();
  if ((tiempoActual - lastDebounceTime) > debounceDelay) {
    if(bandera){
      bandera = false;
      Serial.println("DESBLOQUEADA");
      estadoActual = CERRADA;
      actualizarEstadoPuerta();
    }
    lastDebounceTime = tiempoActual;
  }
}

void actualizarEstadoPuerta() {
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarillo, LOW);

  switch (estadoActual) {
    case CERRADA:
      digitalWrite(ledRojo, HIGH);
      break;
    case ABIERTA:
      digitalWrite(ledVerde, HIGH);
      break;
    case BLOQUEADA:
      digitalWrite(ledAmarillo, HIGH);
      break;
  }
  enviarEstadoSerial();
}

void enviarEstadoSerial() {
  String estado;
  switch (estadoActual) {
    case CERRADA:
      estado = "CERRADA";
      break;
    case ABIERTA:
      estado = "ABIERTA";
      break;
    case BLOQUEADA:
      estado = "BLOQUEADA";
      break;
  }
  Serial.println("Estado de la puerta: " + estado);
}

String leerPassword() {
  // Implementar la lectura de contraseña desde el puerto serial
  // Aquí se simula con una contraseña fija
  return "1234";
}

void receiveEvent(int howMany) {
  if (howMany > 0) {
    byte comando = Wire.read();
    switch (comando) {
      case 1: // Comando para abrir puerta
        abrirPuerta();
        break;
      case 2: // Comando para cerrar puerta
        cerrarPuerta();
        break;
      case 3: // Comando para bloquear/desbloquear puerta
        bloquearPuerta();
        break;
    }
  }
}

void requestEvent() {
  Wire.write((byte)estadoActual); // Enviar el estado actual de la puerta
}