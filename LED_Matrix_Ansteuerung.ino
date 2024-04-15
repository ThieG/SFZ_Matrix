#include <avr/pgmspace.h> // store variables in ROM

#include "LED_Matrix_Ansteuerung.h"


// col[xx] of leds - anodes
// these are the arduino pins assigned to each column
int SpaltenPins[MATRIX_DIM] =  {13, 8, 17, 10, 5};

// row[xx] of leds - cathodes
// these are the arduino pins assigned to each row
int ZeilenPins[MATRIX_DIM] = {9, 3, 2, 12, 15}; 


const byte IdleFrame[MATRIX_DIM] = {
 B10001,
 B01010,
 B00100,
 B01010,
 B10001
};

const byte blankFrame[MATRIX_DIM] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
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
  for (int i = 0; i < MATRIX_DIM; i++) {
    pinMode(SpaltenPins[i], OUTPUT);
    pinMode(ZeilenPins[i], OUTPUT);
  }

  // set up cols and rows (set display to dark)
  for (int i = 0; i < MATRIX_DIM; i++) {
    digitalWrite(SpaltenPins[i], LOW);
  }

  for (int i = 0; i < MATRIX_DIM; i++) {
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
  for (int i = 0; i < MATRIX_DIM ; i++) {
    AktuelleAnzeige[i] = FrameSet[i];    
  }
}

void LED_Matrix::moveFrame(byte x, byte y)
{
  for (int i = 0; i < MATRIX_DIM ; i++) {
    if(x > 0u) {
      byte tempZeile = (AktuelleAnzeige[i] & B11111111);
      for (byte i=0u; i<=x; i++){
        byte shiftBit = tempZeile & 1u; 
        tempZeile >>= 1u;
        tempZeile |= (shiftBit << MATRIX_DIM);
      }
      AktuelleAnzeige[i] = tempZeile;
    }
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
  if (++Zeile == MATRIX_DIM) {
    Zeile = 0u;
  }

  /* Aktuelle Spalte LED ein/aus schalten .... */
  byte Spalte = AktuelleAnzeige[Zeile];
  for (int j=0u; j<MATRIX_DIM; j++) {
    if ((Spalte >> j) & 1u){
      digitalWrite(SpaltenPins[j], HIGH); 
    } else {
      digitalWrite(SpaltenPins[j], LOW);
    }
  }

  /* Aber jezt, die Zeile und somit die LEDs auf einmal einschalten! */
  digitalWrite(ZeilenPins[Zeile], LOW); 

}
