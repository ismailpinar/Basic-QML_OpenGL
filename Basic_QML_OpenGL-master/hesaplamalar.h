#ifndef HESAPLAMALAR_H
#define HESAPLAMALAR_H

#include "Nokta.h"
#include <math.h>





class Hesaplamalar
{
public:
    Hesaplamalar();
    float AciHesapla(Nokta nokta1,Nokta nokta2,Nokta nokta3);

    float UzunlukHesapla(Nokta nokta1,Nokta nokta2);

    float RadyusToDerece(float radyus);

};

#endif // HESAPLAMALAR_H
