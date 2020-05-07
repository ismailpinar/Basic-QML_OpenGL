#include "veridoldur.h"

veriDoldur::veriDoldur()
{

}

QList<Nokta> veriDoldur::Doldur()
{

    QList<Nokta> noktalar;

    Nokta n;

    n.x = 0; n.y =0; n. z=0;
    noktalar.append(n);
    n.x = 10; n.y = 40; n.z=0;
    noktalar.append(n);
    n.x = 10; n.y = 120  ; n.z=0;
    noktalar.append(n);
    n.x = 50; n.y = 160; n.z=0;
    noktalar.append(n);
    n.x = 50; n.y = 240; n.z=0;
    noktalar.append(n);

    n.x = -50; n.y = 240; n.z=0;
    noktalar.append(n);
    n.x = -50; n.y = 120; n.z=0;
    noktalar.append(n);
    n.x = -10; n.y = 120; n.z=0;
    noktalar.append(n);
    n.x = -10; n.y = 40; n.z=0;
    noktalar.append(n);

    return noktalar;

}













