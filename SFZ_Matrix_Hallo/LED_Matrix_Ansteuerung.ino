#include <avr/pgmspace.h> // store variables in ROM

#include "LED_Matrix_Ansteuerung.h"


// col[xx] of leds - anodes
// these are the arduino pins assigned to each column
int SpaltenPins[DIM] =  {7, 8, 11,12,13};

// row[xx] of leds - cathodes
// these are the arduino pins assigned to each row
int ZeilenPins[DIM] = {2,3,4,5,6}; 


const byte IdleFrame[DIM] = {
 B10001,
 B01010,
 B00100,
 B01010,
 B10001
};

const byte blankFrame[DIM] = {
 B00000,
 B00000,
 B00000,
 B00000,
 B00000
};


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Matrix Module Initalization
*
*            Hier werdern die I/O Pins entsprechend der Vorgaben in 
*            spalten[] und zeilen[] als Ausgang definiert.
*/
/*------------------------------------------------------------------------------------------------*/
void LED_Matrix::begin(void)
{
 
  // sets the pins as output
  for (int i = 0; i < DIM; i++) {
    pinMode(SpaltenPins[i], OUTPUT);
    pinMode(ZeilenPins[i], OUTPUT);
  }

  // set up cols and rows (set display to dark)
  for (int i = 0; i < DIM; i++) {
    digitalWrite(SpaltenPins[i], LOW);
  }

  for (int i = 0; i < DIM; i++) {
    digitalWrite(ZeilenPins[i], HIGH);
  }
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Alle Matrix LEDs ausschalten
*
*            Mit dieser Funktion werden alle LEDs der Matrix ausgeschalten.
*/
/*------------------------------------------------------------------------------------------------*/
void LED_Matrix::clear(void) {
  setFrame(blankFrame);
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Matrix LEDs ein/ausschalten
*
*            Diese Funktion muss zyklisch alle 1ms aufgerufen werden und setzt nacheinander
*            die Spalten und Zeilen Pins für die aktuelle Anzeige.
*/
/*------------------------------------------------------------------------------------------------*/
void LED_Matrix::setFrame(const byte* FrameSet) 
{  
  for (int i = 0; i < DIM ; i++)
  {
    AktuelleAnzeige[i] = FrameSet[i];
    byte dings = AktuelleAnzeige[i] | B10000000;
    Serial.println(dings, BIN);
  }
}





/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Matrix LEDs ein/ausschalten
*
*            Diese Funktion muss zyklisch alle 1ms aufgerufen werden und setzt nacheinander
*            die Spalten und Zeilen Pins für die aktuelle Anzeige.
*/
/*------------------------------------------------------------------------------------------------*/
void LED_Matrix::refresh(void) 
{
  /* Ersteinmal die vorherige Zeile ausschalten. */
  digitalWrite(ZeilenPins[Zeile], HIGH);  

  /* Dann, die neue Zeile anschauen, bzw. wieder die erste Zeile.... */
  if (++Zeile == DIM) {
    Zeile = 0u;
  }

  /* Aktuelle Spalte LED ein/aus schalten .... */
  byte Spalte = AktuelleAnzeige[Zeile];
  for (int j=0u; j<DIM; j++) {
    if ((Spalte >> j) & 1u){
      digitalWrite(SpaltenPins[j],HIGH); 
    } else {
      digitalWrite(SpaltenPins[j],LOW);
    }
  }

  /* Aber jezt, die Zeile und somit die LEDs auf einmal einschalten! */
  digitalWrite(ZeilenPins[Zeile], LOW); 

}
