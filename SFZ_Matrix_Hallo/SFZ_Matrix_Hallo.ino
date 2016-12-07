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
#include "ABC.h"
#include "Zahlen.h"


#define BUTTON_PIN      A0
#define LED_UPDATE_MATRIX_ZYKLUS_MS 1u

LED_Matrix Matrix;

unsigned long nextUpdateMatrix = 0u;
unsigned long nextTestAnzeigeUpdate = 0u;
int nextTestAnzeigeIndex = 0u;

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
    nextTestAnzeigeUpdate = systemZeit + 5000u;

    Serial.print("Schreibe Zeichen: ");
    Serial.println(nextTestAnzeigeIndex);
    for(byte i=0u; i<DIM;i++) {
      byte dings = AbcFrames[nextTestAnzeigeIndex][i] | B10000000;
      Serial.println(dings, BIN);
    }
    Serial.println("--------------");
    
    Matrix.setFrame(AbcFrames[nextTestAnzeigeIndex]);
    nextTestAnzeigeIndex++;
    if (nextTestAnzeigeIndex >= ABC_FRAME_CNT){
      nextTestAnzeigeIndex = 0u;
    }
    
  }

  
}


