#ifndef _LED_Matrix_Ansteuerung_h
#define _LED_Matrix_Ansteuerung_h

#define DIM 5 // x/y dimension - 5x5 matrix
#define DIM1 (DIM-1)

typedef byte Frame[DIM];

extern Frame* curFrame;
extern Frame  curFrameBuf;
extern int curFrameIdx;
extern int curFrameCnt;

void initMatrix();
void clearMatrix();

void setFrame(const Frame* FrameSet, int idx, int Cnt, int Speed);
void display();

#endif
