#ifndef _LED_Matrix_Ansteuerung_h
#define _LED_Matrix_Ansteuerung_h



#define DIM 5 // x/y dimension - 5x5 matrix
#define DIM1 (DIM-1)

typedef byte Frame[DIM];


class LED_Matrix {
  private:
    byte AktuelleAnzeige[DIM];
    byte Zeile;

  public:
    void begin(void);
    void clear(void);
    void setFrame(const byte* newFrame);

    void refresh(void);
};

#endif
