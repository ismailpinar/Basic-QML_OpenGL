



#ifndef CIZIMISLEMI_H
#define CIZIMISLEMI_H

#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>

#include <QMouseEvent>
#include <QOpenGLFunctions_3_3_Core>
#include <QQuickFramebufferObject>
#include <QTime>
#include <QVector>

#include <iostream>
#include <cstdio>
#include <math.h>
#include <Nokta.h>
#include <veridoldur.h>

#include "hesaplamalar.h"
#include <QObject>


#include <clip2tri/clip2tri.h>

#include <FTGL/FTGLExtrdFont.h>

using namespace std;
using namespace c2t;



class CizimIslemi: public QObject{

    Q_OBJECT



public slots:

      void tiklananPiksel(int msg1,int msg);
      void onBasildi(int msg1,int msg);
      void onBirakildi(int msg1,int msg);
      void onSurukleniyor(int msg1,int msg);
      void onSileBasildi(int durum);
      void onMercekDegisti(double mercek);


public:

     Q_INVOKABLE QStringList tiklananGLNoktasi();





    ~CizimIslemi();
    CizimIslemi();

    void render();
    void initialize();

    int Genislik = 1000;
    int Yukseklik = 700;


    vector<c2t::Point> Ucgenle();



    vector<vector<c2t::Point>> ucgenlenecekVeri;



private:




    QList<Nokta> veriler;


    void UcgenCiz(vector<c2t::Point>);

    QOpenGLShaderProgram program1;



    vector<Point> outputTriangles;

    GLdouble glX, glY, glZ = 10;

    int pikselAralikDegeri = 100;
    int yaklasimPayi = 49;

    Hesaplamalar hesapla;




    void CizimResminiHafizayaAl();

    void Isiklandirma(float isikPozisyonu[]);

    Point hareketeBaslamaNoktasi;
    Point hareketiBitirmeNoktasi;

    bool CizimiOynat;


    void IzgaraCiz();
    void KirmiziNoktaCiz(Nokta nokta);
    void ParcalariCiz();
    Point TiklananPikseliYuvarla(int x, int y);
    void SonParcayiSil();
    void UzunlukYaz();

    void AciYaz();
    void YaziYaz(FTExtrudeFont *font,float uzunluk, float konumx, float konumy,Nokta renkIc,Nokta renkDis);
    bool BirlesenParcaKontrolu(Nokta yeniNokta);
    void UzunlukEkle();
    void AciEkle();
    bool KirmiziNoktaKontrolu(Nokta yeniNokta);
};
#endif

