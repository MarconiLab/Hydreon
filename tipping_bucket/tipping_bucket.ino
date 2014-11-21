#include <Wire.h>
// Pin correspondiente al RG11
int  bzero = 2; // El Pin 2  corresponde al RG11
// Pin correspondiente al LED
int  ledPin = 13;
// La variable tipo volatile  que comunica entre la
// función de interrupción y bucle principal (loop)
volatile int etat = HIGH ;
//delay time
int del=5;

int pulse=0; //pulse counter

#define BOUNCE_DURATION 50   // define an appropriate bounce time in ms for your switches
volatile unsigned long bounceTime=0; // variable to hold ms count to debounce a pressed switch
 
void  setup () {
    Wire.begin();
     Serial.begin(9600);
     Serial.println("Rain Sensor RG11 Tipping Bucket mode");
     Serial.println("Emulates a tipping bucket of 0.01 inch");
    // El pin conectado al botón se abre en modo INPUT
    pinMode (bzero, INPUT);  // Pin en modo entrada
    // Activación de la resistencia interna pull-up
    digitalWrite (bzero, HIGH );
    // La interrupción  0 monitorea los cambios de estado del pin 2.
    attachInterrupt(0, inter0, FALLING);
    // El pin está preparado para encender  el LED
    pinMode (ledPin, OUTPUT );
    
} // fin de setup

void  loop () {
  delay (del*1000);
  cli();
  float pul=pulse*0.01;
  Serial.print(pulse);
  Serial.print(" pulse = ");
  Serial.print(pul);
  Serial.print(" inch Rain every ");
  Serial.print(del);
  Serial.println(" seconds");
  pulse = 0;
  sei();
} 

void  inter0 ()   {  // Se ejecuta cuando se detecta un cambio de estado del Pin 2
  detachInterrupt(0); 
  cli();
  if (abs(millis() - bounceTime) > BOUNCE_DURATION)  
  {
     etat =! etat;  // Cambia el estado. De HIGH a LOW y de LOW a HIGH
     digitalWrite (ledPin, etat);   // encender o apagar el LED
     pulse++;
     Serial.println("interruption");// debugging
     bounceTime = millis();  // set whatever bounce time in ms is appropriate
 }
  sei();
  attachInterrupt(0, inter0, FALLING);

} // fin inter0
