/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef LOGORENDERER_H
#define LOGORENDERER_H


#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>

#include <QMouseEvent>
#include <QOpenGLFunctions_3_3_Core>
#include <QTime>
#include <QVector>

#include <iostream>
#include <cstdio>
#include <math.h>
#include <Nokta.h>
#include <veridoldur.h>

#include <QObject>


#include <clip2tri/clip2tri.h>

using namespace std;
using namespace c2t;



class LogoRenderer: public QObject{

    Q_OBJECT



public slots:

      void tiklananPiksel(int msg1,int msg);
      void onBasildi(int msg1,int msg);
      void onBirakildi(int msg1,int msg);
      void onSurukleniyor(int msg1,int msg);
      void onOynatBasildi(int durum);
      void onMercekDegisti(double mercek);


public:

     Q_INVOKABLE QStringList tiklananGLNoktasi();





    ~LogoRenderer();
    LogoRenderer();

    void render();
    void initialize();

    int Genislik = 700;
    int Yukseklik = 700;


    vector<c2t::Point> Ucgenle();



    vector<vector<c2t::Point>> ucgenlenecekVeri;




private:




    QList<Nokta> veriler;


    void VerileriDoldur();
    void UcgenCiz(vector<c2t::Point>);

    QOpenGLShaderProgram program1;



    vector<Point> outputTriangles;

    GLdouble glX, glY, glZ = 10;





    void CizimResminiHafizayaAl();
    void ObjeOlustur(vector<Point> outputTriangles);

    void Isiklandirma(float isikPozisyonu[]);

    Point hareketeBaslamaNoktasi;
    Point hareketiBitirmeNoktasi;

    bool CizimiOynat;


};
#endif
