#include "funciones.h"

#define PULSADOR 3
typedef enum{
  ESPERA,
  SELECCION,
  DISPENSACION,
  RETIRADO
}estados;
estados maquina = ESPERA;
int dinero = 0;
bool mostrar_mensaje = true;
int precio_beb1=2;
int precio_beb2=5;
int precio_snacks=4;
int precio = 0;
int cambio=0;
int t=0;
int tiempo=0;
int tiempo_limite=40;
typedef enum{
  NINGUNO,
  BEBIDA1,
  BEBIDA2,
  SNACKS,
}productos;
productos producto = NINGUNO;
bool alcanza=false;
int estado_pulsador=0;
bool retirado=false;

void setup() 
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("BIENVENIDO, INGRESE EL MONTO DE DINERO QUE USTED TIENE");
  pinMode(PULSADOR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PULSADOR), retirar_producto, FALLING);
}

void loop() 
{
  switch (maquina)
  {
    case ESPERA:
    dinero = Serial.parseInt();
    if (dinero > 0)
    {
      maquina = SELECCION;
      mostrar_mensaje=true;
    }
    break;
    case SELECCION:
    if (mostrar_mensaje)
    {
      mostrar_menu();
    }
    producto = Serial.parseInt();
    if (producto==4)
    {
      producto=3;
    }
    if (producto==1 || producto==2 || producto==3)
    {
      datos_producto();
      calcular_cambio();
    }
    else if (producto!=0)
    {
      Serial.println("El valor ingresado no corresponde a un producto, ingrese un valor correcto");
    }
    if (alcanza)
    {
      maquina = DISPENSACION;
    }
    break;
    case DISPENSACION:
    mostrarBarraDeCarga(t);
    mostrar_mensaje=true;
    maquina = RETIRADO;
    break;
    case RETIRADO:
    if (mostrar_mensaje)
    {
      Serial.println("Su producto ha sido entregado, retírelo por favor");
      mostrar_mensaje=false;
    }
    break;
  }
}

void mostrar_menu()
{
  Serial.print("Usted tiene ");
  Serial.print(dinero);
  Serial.println(" Bs.");
  Serial.println("ESTE ES NUESTRO MENÚ");
  Serial.println("1->Bebida 1---------2 Bs");
  Serial.println("2->Bebida 2---------5 Bs");
  Serial.println("3->Snack 1----------4 Bs");
  Serial.println("4->Snack 2----------4 Bs");
  Serial.println("Para escoger un producto, ingrese el número que está delante de cada producto.");
  mostrar_mensaje=false; 
}

void datos_producto()
{
  switch (producto)
  {
    case BEBIDA1:
    precio=precio_beb1;
    t=2000;
    break;
    case BEBIDA2:
    precio=precio_beb2;
    t=4000;
    break;
    case SNACKS:
    precio=precio_snacks;
    t=1000;
    break;
  }
}

void calcular_cambio()
{
  cambio = dinero - precio;
  if (cambio>0)
  {
    Serial.print("Su cambio es de ");
    Serial.print(cambio);
    Serial.println(" Bs.");
  }
  if (cambio>=0)
  {
    alcanza=true;
  }
}

void retirar_producto()
{
  if (millis()-tiempo > tiempo_limite)
  {
    Serial.println("Producto retirado");
    tiempo=millis();
    dinero=0;
    producto=0;
    alcanza=false;
    maquina = ESPERA;
  }
}