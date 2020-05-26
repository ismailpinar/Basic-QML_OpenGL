#include "hesaplamalar.h"
#include "QDebug"


Hesaplamalar::Hesaplamalar()
{

}

float Hesaplamalar::AciHesapla(Nokta nokta0,Nokta nokta1,Nokta nokta2)
{


    float aci;

    float v1 = UzunlukHesapla(nokta2, nokta0);

    float v2 = UzunlukHesapla(nokta2, nokta1);

    float v0 = UzunlukHesapla(nokta1, nokta0);


    float uzaklik;

    uzaklik = abs((nokta0.y - nokta1.y) * nokta2.x + (nokta1.x - nokta0.x) * nokta2.y   + nokta1.y * nokta0.x -nokta1.x * nokta0.y) / v0;

    float deger = uzaklik/v2;

    if(deger > 1)
    {
        deger = 1;
    }
    else if(deger<-1)
    {
        deger = -1;
    }

    aci =  asin(deger);


    if(pow(v0,2) + pow(v2,2) == pow(v1,2))
    {
        aci = M_PI / 2.0f;
    }
    else if(pow(v0,2) + pow(v2,2) < pow(v1,2))
    {
        aci = M_PI - aci;
    }

    aci = RadyusToDerece(aci);

    return aci;


}

float Hesaplamalar::UzunlukHesapla(Nokta nokta1, Nokta nokta2)
{

    float uzunluk = sqrt(pow(nokta1.x - nokta2.x,2) + pow(nokta1.y - nokta2.y,2)) ;

    return uzunluk;
}

float Hesaplamalar::RadyusToDerece(float radyus)
{

    return (180.0f * radyus) / M_PI;
}
