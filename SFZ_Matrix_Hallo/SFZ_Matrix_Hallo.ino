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
#include <EEPROM.h>

#include "LED_Matrix_Ansteuerung.h"


#define BUTTON_PIN      A0

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

  initMatrix();
  clearMatrix();

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
  
  
}


