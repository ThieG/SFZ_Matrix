#ifndef _LED_Matrix_Ansteuerung_h
#define _LED_Matrix_Ansteuerung_h



#define MATRIX_DIM   5 /* x/y dimension - 5x5 matrix */

class LED_Matrix {
  private:
    byte AktuelleAnzeige[MATRIX_DIM];
    byte Zeile;

  public:
    void begin(void);
    void clear(void);
    void setFrame(const byte* newFrame);
    void moveFrame(byte x, byte y);
    void refresh(void);
};

const byte TestFrame[MATRIX_DIM] = {
  B10001,
  B01010,
  B00100,
  B01010,
  B10001
};

#endif
