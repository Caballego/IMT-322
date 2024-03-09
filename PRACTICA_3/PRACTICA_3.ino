#define PULSADOR1 2
#define PULSADOR2 3
#define LED 4
volatile int contador=0;
volatile int frecuencia=0;
int delay_frecuencia=0;
int contador2=0;
const int tiempo_limite = 40;
long tiempo = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("INICIADO");
  Serial.print("Número de interrupciones: ");
  Serial.println(contador);
  pinMode(PULSADOR1, INPUT_PULLUP);
  pinMode(PULSADOR2, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  attachInterrupt(digitalPinToInterrupt(PULSADOR1), actualizar_contador, RISING);
  attachInterrupt(digitalPinToInterrupt(PULSADOR2), reiniciar_contador, RISING);
}

void loop() 
{
  if (frecuencia==0)
  {
    delay_frecuencia=500;
  }
  else if (frecuencia==1)
  {
    delay_frecuencia=1000;
  }
  else
  {
    delay_frecuencia=1500;
  }
  digitalWrite(LED, HIGH);
  delay(delay_frecuencia);
  digitalWrite(LED, LOW);
  delay(delay_frecuencia);
}

void actualizar_contador()
{
  if (millis()-tiempo > tiempo_limite)
  {
    contador++;
    Serial.print("Número de interrupciones: ");
    Serial.println(contador);
    tiempo=millis();
  }
}

void reiniciar_contador()
{
  if (millis()-tiempo > tiempo_limite)
  {
    contador=0;
    Serial.println("Contador reiniciado-Frecuencia del led actualizada");
    Serial.println("Número de interrupciones: 0");
    if (frecuencia!=2)
    {
      frecuencia++;
    }
    else
    {
      frecuencia=0;
    }
  }
}