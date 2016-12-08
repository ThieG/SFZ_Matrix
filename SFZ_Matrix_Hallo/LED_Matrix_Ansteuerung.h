#ifndef _LED_Matrix_Ansteuerung_h
#define _LED_Matrix_Ansteuerung_h



#define MARTIX_DIM   5 /* x/y dimension - 5x5 matrix */

class LED_Matrix {
  private:
    byte AktuelleAnzeige[MARTIX_DIM];
    byte Zeile;

  public:
    void begin(void);
    void clear(void);
    void setFrame(const byte* newFrame);
    void moveFrame(byte x, byte y);
    void refresh(void);
};

#endif
