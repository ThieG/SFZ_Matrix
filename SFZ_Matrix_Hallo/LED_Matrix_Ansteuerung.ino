#include <avr/pgmspace.h> // store variables in ROM

#include "LED_Matrix_Ansteuerung.h"


byte Zeile = 0;

Frame  AktuelleAnzeige; // & buffer


// col[xx] of leds - anodes
// these are the arduino pins assigned to each column
int SpaltenPins[DIM] =  {7, 8, 11,12,13};

// row[xx] of leds - cathodes
// these are the arduino pins assigned to each row
int ZeilenPins[DIM] = {2,3,4,5,6}; 


const Frame IdleFrame[1u] PROGMEM = {
{B10001,
 B01010,
 B00100,
 B01010,
 B10001}
};

const Frame blankFrame[1u] PROGMEM =
{B00000,
 B00000,
 B00000,
 B00000,
 B00000};


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Matrix Module Initalization
*
*            Hier werdern die I/O Pins entsprechend der Vorgaben in 
*            spalten[] und zeilen[] als Ausgang definiert.
*/
/*------------------------------------------------------------------------------------------------*/
void initMatrix(void)
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
void clearMatrix(void) {
  setFrame(blankFrame, 0, 1, 1);
}




/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Matrix LEDs ein/ausschalten
*
*            Diese Funktion muss zyklisch alle 1ms aufgerufen werden und setzt nacheinander
*            die Spalten und Zeilen Pins für die aktuelle Anzeige.
*/
/*------------------------------------------------------------------------------------------------*/
void setFrame(const Frame* FrameSet, int idx, int Cnt, int Speed) 
{  
  for (int i = 0; i < DIM ; i++)
  {
    AktuelleAnzeige[i] = pgm_read_byte_near((&FrameSet[idx][i])); // Necessary casts and dereferencing, just copy.
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
void updateMatrix(void) 
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
