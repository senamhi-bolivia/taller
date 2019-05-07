/*
  Creado: Paolo Patruno (p.patruno@iperbole.bologna.it) y Luis del Valle (ldelvalleh@programarfacil.com)
 
  Compártelo a todo el mundo :)
*/

#include <JC_Button.h> // https://github.com/JChristensen/JC_Button

// numero de LED
#define NUMLED 3

Button myBtn1(2); // define the button
Button myBtn2(3); // define the button

// Variable global de velocidad
volatile int velocidad = 20;
// Constantes de velocidad máxima, mínima y cuanto aumenta
const int maxima = 1000;
const int minima = 10;
const int aumenta = 20;
 
// Array con los números de los pines donde están conectados
// los LEDs de las luces del coche fantástico
int leds[NUMLED] = {7,8,9};
 
void setup() {
  // Inicializamos los pines de los LEDs como salida y a estado bajo
  for (int i = 0; i < NUMLED; i++)
  {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
 
  // Asignamos la velocidad mínima
  velocidad = minima;

  myBtn1.begin(); // initialize the button object
  myBtn2.begin(); // initialize the button object
   
  // Configuramos los pines de interrupciones para que
  // detecten un cambio de bajo a alto
  attachInterrupt(digitalPinToInterrupt(2),button1changed , CHANGE);
  attachInterrupt(digitalPinToInterrupt(3),button2changed , CHANGE);
 
}
 
void loop() {
  swapLed();

  if (myBtn1.wasReleased()) velocidadMenos();
  if (myBtn2.wasReleased()) velocidadMas();

}

void swapLed()
{
  // Este primer bucle recorre el array de izquierda a derecha
  for (int i = 0; i < NUMLED; i++)
  {
    // Solo para el segundo pin y consecutivos apagamos el pin anterior
    // En el caso de 0 no hace falta ya que por defecto está apagado
    // Cuidado que nos salimos del rango del array 0-1=-1 no existe este elemento
    if (i > 0)
    {
      // Apagamos el LED a la izquierda
      digitalWrite(leds[i - 1], LOW);
    }
 
    // Encendemos en el LED en el que estamos
    digitalWrite(leds[i], HIGH);
 
    // Esperamos el tiempo marcado por velocidad
    delay(velocidad);
 
    if (i == NUMLED-1)
    {
      // Apagamos el último LED encendido, el elemento 5 del array
      digitalWrite(leds[i], LOW);
    }
  }
}

void button1changed()
{
  myBtn1.read();
}
void button2changed()
{
  myBtn2.read();
}

// disminuye la velocidad
void velocidadMenos()
{
  // Disminuimos el valor establecido
  velocidad = velocidad - aumenta;
 
  // Si hemos llegado a la velocidad mínima no disminuímos más
  if (velocidad < minima)
  {
    velocidad = minima;
  }
}
 
// aumenta la velocidad
void velocidadMas()
{
  // Aumentamos el valor establecido
  velocidad = velocidad + aumenta;
 
  // Si hemos llegado a la velocidad máxima no aumentamos más
  if (velocidad > maxima)
  {
    velocidad = maxima;
  }
}
