#define ALEATORIO 5
#define PLAY_PAUSE 4
#define SUBIR_VOLUMEN 2
#define BAJAR_VOLUMEN 3

//VARIABLES

volatile int temporizador=0;
volatile int volumen=5;
volatile bool aleatorio=false;
volatile int tiempo_rebote=40;
volatile int tiempo=0;
uint8_t numero_cancion=1;
volatile bool pausa=false;

void setup() 
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("REPRODUCTOR INICIADO");
  Serial.print("NIVEL DE VOLUMEN ACTUAL:");
  Serial.println(volumen);
  Serial.println("MODO ALEATORIO APAGADO");
  Serial.print("REPRODUCIENDO CANCION N°");
  Serial.println(numero_cancion);
  attachInterrupt(digitalPinToInterrupt(ALEATORIO),aleatoriedad,FALLING);
  attachInterrupt(digitalPinToInterrupt(PLAY_PAUSE),reproduccion,FALLING);
  attachInterrupt(digitalPinToInterrupt(SUBIR_VOLUMEN),subeVolumen,FALLING);
  attachInterrupt(digitalPinToInterrupt(BAJAR_VOLUMEN),bajaVolumen,FALLING);
  pinMode(ALEATORIO, INPUT_PULLUP);
  pinMode(PLAY_PAUSE, INPUT_PULLUP);
  pinMode(SUBIR_VOLUMEN, INPUT_PULLUP);
  pinMode(BAJAR_VOLUMEN, INPUT_PULLUP);
}

void loop() 
{
  if (pausa==false)
  {
    if (temporizador==0)
    {
      temporizador=5;
    }
    if (temporizador>0)
    {
      if (temporizador>9)
      {
        Serial.print("00:");
      }
      else
      {
        Serial.print("00:0");
      }
      Serial.println(temporizador);
      temporizador--;
      delay(1000);
      if (temporizador==0)
      {
        Serial.println("SIGUIENTE CANCIÓN");
        if (aleatorio==false)
        {
          numero_cancion++;
          if (numero_cancion==0)
          {
            numero_cancion++;
          }
        }
        else
        {
          numero_cancion=random(1,255);
        }
        Serial.print("REPRODUCIENDO CANCIÓN N°");
        Serial.println(numero_cancion);
      }
    }
  }
  else
  {
    if (temporizador>9)
      {
        Serial.print("00:");
      }
      else
      {
        Serial.print("00:0");
      }
    Serial.println(temporizador);
    Serial.println("REPRODUCCION PAUSADA");
    delay(1500);
  }
}

//FUNCIONES DE INTERRUPCIÓN

void aleatoriedad()
{
  if (millis()-tiempo > tiempo_rebote)
  {
    aleatorio=!aleatorio;
    if (aleatorio==true)
    {
      Serial.println("MODO ALEATORIO ENCENDIDO");
    }
    else
    {
      Serial.println("MODO ALEATORIO APAGADO");
    }
    tiempo=millis();
  }
}

void reproduccion()
{
  if (millis()-tiempo > tiempo_rebote)
  {
    pausa=!pausa;
    if (pausa==true)
    {
      Serial.println("REPRODUCCION PAUSADA");
    }
    else
    {
      Serial.println("REPRODUCCION REINICIADA");
    }
    tiempo=millis();
  }
}

void subeVolumen()
{
  if (millis()-tiempo > tiempo_rebote)
  {
    if (volumen<10)
    {
      volumen++;
    }  
    else
    {
      Serial.println("NIVEL DE VOLUMEN MÁXIMO");
    }
    Serial.print("NIVEL DE VOLUMEN ACTUAL:");
    Serial.println(volumen);
  }
}

void bajaVolumen()
{
  if (millis()-tiempo > tiempo_rebote)
  {
    if (volumen>0)
    {
      volumen--;
    }
    else
    {
      Serial.println("NIVEL DE VOLUMEN MÍNIMO");
    }
    Serial.print("NIVEL DE VOLUMEN ACTUAL:");
    Serial.println(volumen);
  }
}