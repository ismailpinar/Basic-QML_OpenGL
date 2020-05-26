#ifndef UCGENLEME_H
#define UCGENLEME_H

#include <clip2tri/clip2tri.h>
#include <QList>
#include <Nokta.h>

using namespace std;
using namespace c2t;

class Ucgenleme
{
public:

    Ucgenleme();

    vector<Point> Ucgenle(QList<Nokta>);
private:
};

#endif // UCGENLEME_H
