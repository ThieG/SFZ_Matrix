/*!
****************************************************************************************************
* \file      SFZ_Matrix_Hallo.ino
*
* \ingroup   MATRIX
*
*            Arduino Software für die 5x5 LED Matrix im SFZ Wangen
*
****************************************************************************************************
*/
/*!
****************************************************************************************************
* \defgroup MATRIX     5x5 LED Matrix Ansteuerung
****************************************************************************************************
*/
#include <avr/pgmspace.h>    /* const Variablen im ROM ablegen und so... */
#include <EEPROM.h>

#include "LED_Matrix_Ansteuerung.h"

#define BUTTON_PIN      A5
#define LED_UPDATE_MATRIX_ZYKLUS_MS 1u
#define LED_WECHSEL_ANZEIGE_MS  5000u

LED_Matrix Matrix;

unsigned long nextUpdateMatrix = 0u;
unsigned long nextTestAnzeigeUpdate = 0u;


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Arduino Setup
*
*            Wird beim Start des Programms (entweder nach dem uebertragen auf das Board oder 
*            nach Druecken des Reset-Tasters) einmalig aufgerufen, 
*            um z. B. Pins als Eingang oder Ausgang zu definieren.
*/
/*------------------------------------------------------------------------------------------------*/
void setup() {

  Serial.begin(9600);
  
  Matrix.begin();
  Matrix.clear();

  Serial.println("Hallo erst mal!");

  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);  // set pullup on analog pin 0 

  randomSeed(analogRead(1u));
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Arduino Main Loop
*
*            Wird durchgehend immer wieder durchlaufen, solange das Arduino-Board eingeschaltet ist.
*/
/*------------------------------------------------------------------------------------------------*/
void loop() {

  unsigned long systemZeit = millis();
  if (systemZeit > nextUpdateMatrix) {
    nextUpdateMatrix = systemZeit + LED_UPDATE_MATRIX_ZYKLUS_MS;
    Matrix.refresh();
  }
  
  if (systemZeit > nextTestAnzeigeUpdate) {
    nextTestAnzeigeUpdate = systemZeit + LED_WECHSEL_ANZEIGE_MS;
    
    byte naechsteAnzeige[MATRIX_DIM];
    for(byte i=0u; i<MATRIX_DIM; i++) {
      naechsteAnzeige[i] = random(0, B00011111);
    }
   
    Matrix.setFrame(TestFrame);
    
  }

  
}


