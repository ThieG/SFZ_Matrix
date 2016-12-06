#ifndef _LED_Matrix_Ansteuerung_h
#define _LED_Matrix_Ansteuerung_h



#define DIM 5 // x/y dimension - 5x5 matrix
#define DIM1 (DIM-1)

typedef byte Frame[DIM];



void initMatrix(void);
void clearMatrix(void);

void setFrame(const Frame* FrameSet, int idx, int Cnt, int Speed);
void updateMatrix(void);

#endif
