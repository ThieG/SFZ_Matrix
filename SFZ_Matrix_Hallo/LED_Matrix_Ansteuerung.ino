#include <avr/pgmspace.h> // store variables in ROM

#include "LED_Matrix_Ansteuerung.h"

extern int SongDuration;

/* Smaller value -> all tunes play faster; bigger -> slower. Recommend you don't change this, but
instead use playTune() to pass different beatLength values to parseTune() for different songs */
const int beatLength = 50; 

byte Zeile = 0;
Frame* curFrame;    // currently displayed frame ptr
Frame  curFrameBuf; // & buffer
int curFrameIdx;
int curFrameCnt;
int curFrameSpeed;
const Frame* curFrameSet;

// col[xx] of leds - anodes
// these are the arduino pins assigned to each column
int SpaltenPins[DIM] =  {7, 8, 11,12,13}; //{13,12,11,8,7}; //{7, 8, 11,12,13};

// row[xx] of leds - cathodes
// these are the arduino pins assigned to each row
int ZeilenPins[DIM] = {2,3,4,5,6}; //{6,5,4,3,2};


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Matrix Module Initalization
*
*            Hier werdern die I/O Pins entsprechend der Vorgaben in 
*            spalten[] und zeilen[] als Ausgang definiert.
*/
/*------------------------------------------------------------------------------------------------*/
void initMatrix()
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
void clearMatrix() {
  setFrame(blankFrame, 0, 1, 1);
}




// select a frame to display
// idx = 0 -> FRAMDECNT-1
void setFrame(const Frame* FrameSet, int idx, int Cnt, int Speed) 
{
  for (int i = 0; i < DIM ; i++)
  {
    curFrameBuf[i] = pgm_read_byte_near((&FrameSet[idx][i])); // Necessary casts and dereferencing, just copy.
  }
  curFrameCnt = Cnt;
  curFrameIdx = idx;
  curFrameSpeed = Speed;
  curFrameSet = FrameSet;
}


void NextFrame()
{
  if (curFrameCnt > 0)
  {
    if (Cnt >= curFrameSpeed)  // time ticks
    {
      curFrameCnt--;
      setFrame(curFrameSet, curFrameIdx,  curFrameCnt, curFrameSpeed);    // select frame for display
      curFrameIdx++;
      Cnt = 0;
      Serial.println(curFrameCnt,DEC);
    }
    else 
    {
      Cnt++;
    }
  }
}

bool isFrameSetRunning()
{
  return (curFrameCnt>0 ? true : false);
}

// Interrupt routine
// each time display() is called, it turns off the previous row
// and turns on the next row
byte bitMask = B00000011;
int Cnt;




void updateMatrix() 
{
  /* Ersteinmal die vorherige Zeile ausschalten. */
  digitalWrite(ZeilenPins[Zeile], HIGH);  // Turn whole previous row off

  /* Dann, die neue Zeile anschauen, bzw. wieder die erste Zeile.... */
  if (++Zeile == DIM) {
    Zeile = 0u;
  }

  byte curCol = curFrame[0u][Zeilen];
  for (int j=0;j < DIM;j++)
  {
    if ((curCol>>j)&1)
    {
      digitalWrite(SpaltenPins[j],HIGH); 
    }
    else
    {
      digitalWrite(SpaltenPins[j],LOW);
    }
  }

  /* Aber jezt, die Zeile und somit die LEDs auf einmal einschalten! */
  digitalWrite(ZeilenPins[Zeile], LOW); 

  if (curFrameCnt > 0 && curFrameSpeed > 0)   // speed == 0 => external control
  {
    NextFrame();
  }
}
