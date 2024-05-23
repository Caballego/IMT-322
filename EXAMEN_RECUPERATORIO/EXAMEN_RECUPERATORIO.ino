//#include "ArduinoLowPower.h"

#define LED_VERDE 6
#define LED_ROJO 7
#define PULSADOR_INGRESO 2
#define PULSADOR_REINICIO 3
bool contrasena_correcta=false;
bool primer_tiempo=true;
bool tiempo_auxiliar=false;
bool mostrar_mensaje=true;
char contrasena[8]={'u', 'c', 'b', '.', '2', '0', '2', '4'};
char contrasena_ingresada[8];
long tiempo=0;
long tiempo2=0;
long tiempo_limite=7000;
long hora_reposo=180000;
long tiempo_db=0;
long tiempo_limite_db=30;
int i=0;
typedef enum
{
  CERRADA,
  ABIERTA,
  REPOSO
}estados;
estados cerradura = CERRADA;
int baudrate=9600;

void setup() 
{
  Serial.begin(baudrate);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(PULSADOR_INGRESO, INPUT_PULLUP);
  pinMode(PULSADOR_REINICIO, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PULSADOR_INGRESO), abrir_cerradura, FALLING);
  attachInterrupt(digitalPinToInterrupt(PULSADOR_REINICIO), reinicio_sistema, FALLING);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, HIGH);
}

void loop() 
{
  switch (cerradura)
  {
    case CERRADA:
    char caracter;
    if (i<8)
    {
      if (Serial.available())
      {
        if (primer_tiempo)
        {
          tiempo = millis();
          primer_tiempo=false;
          tiempo_auxiliar=true;
        }
        if (tiempo_auxiliar)
        {
          tiempo2=millis();
        }
        if (tiempo2-tiempo<tiempo_limite)
        {
          caracter = Serial.read();
          if (caracter!='\n')
          {
            contrasena_ingresada[i]=caracter;
            Serial.println(contrasena_ingresada[i]);
            i++;
          }
        }
        else if (mostrar_mensaje)
        {
          Serial.println("TIEMPO EXCEDIDO");
          mostrar_mensaje = false;
          delay(500);
          Serial.println("Ingrese la contraseña nuevamente");
          i=0;
          primer_tiempo=true;
        }
      }
    }
    if (i==8)
    {
      if (compareArray(contrasena_ingresada,contrasena))
      {
        if (mostrar_mensaje)
        {
          Serial.println("CONTRASEÑA CORRECTA");
          mostrar_mensaje=false;
        }
        contrasena_correcta=true;
        digitalWrite(LED_ROJO, LOW);
        digitalWrite(LED_VERDE, HIGH);
      }
      else
      {
        Serial.println("Contraseña incorrecta");
        delay(500);
        Serial.println("Ingrese la contraseña nuevamente");
        i=0;
        primer_tiempo = true;
      }
    }
    break;
    case ABIERTA:
    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_VERDE, HIGH);
    if (mostrar_mensaje)
    {
      Serial.println("BIENVENIDO");
      mostrar_mensaje=false;
    }
    break;
    case REPOSO:
    if (tiempo>800000)
    {
      //LowPower.sleep();
    }
    if (tiempo>900000)
    {
      //dummy();
    }
    break;
  }
}

void abrir_cerradura()
{
  if (millis()-tiempo_db > tiempo_limite_db)
  {
    if (contrasena_correcta)
    {
      cerradura = ABIERTA;
      mostrar_mensaje = true;
    }
    tiempo_db = millis();
  }
}

void reinicio_sistema()
{
  if (millis()-tiempo_db > tiempo_limite_db)
  {
    contrasena_correcta=false;
    cerradura = CERRADA;
    i=0;
    primer_tiempo=true;
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_ROJO, HIGH);
    mostrar_mensaje=true;
    contrasena_ingresada[1]='x';
    tiempo_db = millis();
  }
}

boolean compareArray(byte array1[],byte array2[])
{
  if(array1[0] != array2[0])return(false);
  if(array1[1] != array2[1])return(false);
  if(array1[2] != array2[2])return(false);
  if(array1[3] != array2[3])return(false);
  if(array1[4] != array2[4])return(false);
  if(array1[5] != array2[5])return(false);
  if(array1[6] != array2[6])return(false);
  if(array1[7] != array2[7])return(false);
  return(true);
}

void dummy()
{
  cerradura = CERRADA;
  i=0;
  contrasena_correcta = false;
}