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

#include "BMP.h"
#include "logorenderer.h"
#include <QPainter>
#include <QPaintEngine>
#include <math.h>
#include <ucgenleme.h>

#include <GL/glu.h>

#include <GL/gl.h>

#include <GL/freeglut.h>

#include <QDebug>
#include <QQuickItem>

#include <math.h>
#include <cstdlib>
#include <iostream>
#include <fstream>


GLint viewport[4];
GLdouble model_view[16];
GLdouble projection[16];

float* vertices;
int verticesSize;
float *textcoord;
float *normals;

GLuint texture_id;


float konumX = 0;
float KonumY = 0;

float donmeAcisiY;
float donmeAcisiX;
float donmeAcisiZ = 180;
float mercek = 1;






LogoRenderer::LogoRenderer()
{

}




LogoRenderer::~LogoRenderer()
{

}


void LogoRenderer::initialize()
{


    tiklananGLNoktasi();
    VerileriDoldur();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    QOpenGLShader *vshader1 = new QOpenGLShader(QOpenGLShader::Vertex, &program1);
    const char *vsrc1 =
        "attribute highp vec4 vertex;\n"
        "attribute mediump vec3 normal;\n"
        "uniform mediump mat4 matrix;\n"
        "varying mediump vec4 color;\n"
        "void main(void)\n"
        "{\n"
        "    vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));\n"
        "    float angle = max(dot(normal, toLight), 0.0);\n"
        "    vec3 col = vec3(0.40, 1.0, 0.0);\n"
        "    color = vec4(col * 0.2 + col * 0.8 * angle, 1.0);\n"
        "    color = clamp(color, 0.0, 1.0);\n"
        "    gl_Position = matrix * vertex;\n"
        "}\n";
    vshader1->compileSourceCode(vsrc1);

    QOpenGLShader *fshader1 = new QOpenGLShader(QOpenGLShader::Fragment, &program1);
    const char *fsrc1 =
        "varying mediump vec4 color;\n"
        "void main(void)\n"
        "{\n"
        "    gl_FragColor = color;\n"
        "}\n";
    fshader1->compileSourceCode(fsrc1);

    program1.addShader(vshader1);
    program1.link();



}





void LogoRenderer::render()
{
    program1.bind();
    program1.release();

    glDepthMask(true);


    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();



    glOrtho(-konumX - (Genislik / 2.0), - konumX + ( Genislik / 2.0), -KonumY - (Yukseklik / 2.0), -KonumY + (Yukseklik / 2.0), -(1000 * Genislik) / 2.0, (1000 * Genislik) / 2.0);
    glViewport(0, 0, Genislik,Yukseklik);

    glScaled(mercek,mercek,mercek);


    glRotatef(donmeAcisiX, 1, 0, 0);
    glRotatef(donmeAcisiY, 0, 1, 0);
    glRotatef(donmeAcisiZ, 0, 0, 1);



    glPushMatrix();


    glGetIntegerv(GL_VIEWPORT, viewport);

    glGetDoublev(GL_MODELVIEW_MATRIX, model_view);

    glGetDoublev(GL_PROJECTION_MATRIX, projection);


    float isik[3] = {-900,-500,0};

    Isiklandirma(isik);




    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY);

    glBindTexture(GL_TEXTURE_2D, texture_id);


    glTexCoordPointer( 2, GL_FLOAT, 0, textcoord );
    glVertexPointer( 3, GL_FLOAT, 0, vertices );
    glNormalPointer(GL_FLOAT, 0, normals);


    glDrawArrays( GL_TRIANGLES, 0, verticesSize);



    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();



}




void LogoRenderer::VerileriDoldur()
{
    veriDoldur veri;

    veriler = veri.Doldur();

    Ucgenleme ucgenler;

    outputTriangles = ucgenler.Ucgenle(veriler);






    ObjeOlustur(outputTriangles);

    CizimResminiHafizayaAl();

}





void LogoRenderer::ObjeOlustur(vector<Point> outputTriangles)
{

    vertices= new float[9*outputTriangles.size()]; //3 coordiantes per vertex
    normals= new float[9*outputTriangles.size()]; //3 coordiantes per vertex
    textcoord= new float[6*outputTriangles.size()]; //3 coordiantes per vertex


    float maxX = outputTriangles[0].x;
    float maxY = outputTriangles[0].y;
    float minX = outputTriangles[0].x;
    float minY = outputTriangles[0].y;

    for(int i=0;i<outputTriangles.size()/3;i++)
    {
        vertices[(i*9)+0] = outputTriangles[3*i].x;
        vertices[(i*9)+1] = outputTriangles[3*i].y;
        vertices[(i*9)+2] = 100;

        vertices[(i*9)+3] = outputTriangles[3*i+1].x;
        vertices[(i*9)+4] = outputTriangles[3*i+1].y;
        vertices[(i*9)+5] = 100;

        vertices[(i*9)+6] = outputTriangles[3*i+2].x;
        vertices[(i*9)+7] = outputTriangles[3*i+2].y;
        vertices[(i*9)+8] = 100;

       minX = std::min(std::min(std::min(outputTriangles[3*i].x,outputTriangles[3*i + 1].x) ,outputTriangles[3*i + 2].x),minX);
       minY = std::min(std::min(std::min(outputTriangles[3*i].y,outputTriangles[3*i + 1].y) ,outputTriangles[3*i + 2].y),minY);
       maxX = std::max(std::max(std::max(outputTriangles[3*i].x,outputTriangles[3*i + 1].x) ,outputTriangles[3*i + 2].x),maxX);
       maxY = std::max(std::max(std::max(outputTriangles[3*i].y,outputTriangles[3*i + 1].y) ,outputTriangles[3*i + 2].y),maxY);


    }



    for(int i=0;i<outputTriangles.size()/3;i++)
    {
        textcoord[(i*6)+0] = (outputTriangles[3*i].x - minX) / (maxX -minX);
        textcoord[(i*6)+1] = (outputTriangles[3*i].y - minY) / (maxY -minY);


        textcoord[(i*6)+2] = (outputTriangles[3*i+1].x- minX) / (maxX -minX);
        textcoord[(i*6)+3] = (outputTriangles[3*i+1].y- minY) / (maxY -minY);


        textcoord[(i*6)+4] = (outputTriangles[3*i+2].x- minX) / (maxX -minX);
        textcoord[(i*6)+5] = (outputTriangles[3*i+2].y- minY) / (maxY -minY);

    }


    for(int i=0;i<outputTriangles.size()/3;i++)
    {
        normals[(i*9)+0] = 1;
        normals[(i*9)+1] = 0;
        normals[(i*9)+2] = 0;

        normals[(i*9)+3] = 1;
        normals[(i*9)+4] = 0;
        normals[(i*9)+5] = 0;

        normals[(i*9)+6] = 1;
        normals[(i*9)+7] = 0;
        normals[(i*9)+8] = 0;

    }




    verticesSize = outputTriangles.size();

}

void LogoRenderer::CizimResminiHafizayaAl()
{
    BMP bmp ("bakir.bmp");


    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);



    GLubyte resimDatasi[bmp.bmp_info_header.height][bmp.bmp_info_header.width][4];



    int boyut = bmp.bmp_info_header.width * bmp.bmp_info_header.height * 3;



    int i, j, c = 0;

    for (i = 0; i < bmp.bmp_info_header.height; i++) {
       for (j = 0; j < bmp.bmp_info_header.width; j++) {

          resimDatasi[i][j][2] = (GLubyte) bmp.data[0 + c + (i* bmp.bmp_info_header.width)+ j];
          resimDatasi[i][j][1] = (GLubyte) bmp.data[1 + c + (i* bmp.bmp_info_header.width)+ j];
          resimDatasi[i][j][0] = (GLubyte) bmp.data[2 + c + (i* bmp.bmp_info_header.width)+ j];
          resimDatasi[i][j][3] = (GLubyte) 255;
          c = c+2;
       }



    }


    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmp.bmp_info_header.width, bmp.bmp_info_header.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, resimDatasi);

   // glBindTexture(GL_TEXTURE_2D, 0);
}




QStringList LogoRenderer::tiklananGLNoktasi()
{
    QStringList nokta;

    nokta.append(QString::number(glX));
    nokta.append(QString::number(glY));



    return nokta;
}






void LogoRenderer::tiklananPiksel(int x ,int y)
{
    gluUnProject(x, y, 0, model_view, projection, viewport, &glX, &glY, &glZ);

}

void LogoRenderer::onBasildi(int x, int y)
{

    hareketeBaslamaNoktasi.x = x;
    hareketeBaslamaNoktasi.y = y;

}

void LogoRenderer::onBirakildi(int x, int y)
{
    hareketeBaslamaNoktasi.x = hareketiBitirmeNoktasi.x;
    hareketeBaslamaNoktasi.y = hareketiBitirmeNoktasi.y;


}

void LogoRenderer::onSurukleniyor(int x, int y)
{


    if (((hareketeBaslamaNoktasi.x) == hareketiBitirmeNoktasi.x)&& (hareketeBaslamaNoktasi.y == hareketiBitirmeNoktasi.y)) { return; }

        if (!CizimiOynat)
        {
            donmeAcisiY = (x - hareketeBaslamaNoktasi.x) + donmeAcisiY;
            donmeAcisiX = (y - hareketeBaslamaNoktasi.y) + donmeAcisiX;

        }
        else
        {
            KonumY = -((-y + hareketeBaslamaNoktasi.y) - KonumY);
            konumX = (-(-x + hareketeBaslamaNoktasi.x) + ( konumX));

        }

        hareketeBaslamaNoktasi.x = x;
        hareketeBaslamaNoktasi.y = y;

}

void LogoRenderer::onOynatBasildi(int durum)
{
    if(durum == 1)
    {
        CizimiOynat = true;
    }
    else if(durum == 0)
    {
        CizimiOynat = false;
    }
}

void LogoRenderer::onMercekDegisti(double gelenMercek)
{
    mercek = gelenMercek;
}





void LogoRenderer::Isiklandirma(float isikPozisyonu[])
{


    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    //Işık için bir slot aç
    glEnable(GL_LIGHT0);



    GLfloat lmKa[] =  { 0.1f, 0.1f, 0.1f, 1.0f };


    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0f);

    // -------------------------------------------
    // Spotlight Attenuation


    GLfloat spot_direction[] = { signbit(isikPozisyonu[0])* -1, signbit(isikPozisyonu[1]) * -1, signbit(isikPozisyonu[2]) * 1 };
    GLfloat spot_exponent = 30;
    GLfloat spot_cutoff = 180;

    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

    float Kc = 1.0f;
    float Kl = 0.0f;
    float Kq = 0.0f;

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Kc);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);

    // Işık Özellikleri
    float ambientProperties2[4]  = { 0.5f, 0.5f, 0.5f, 1.0f };
    float diffuseProperties2[4]  = { 0.8f, 0.8f, 0.8f, 1.0f };
    float specularProperties2[4] = { 1.0f, 1.0f, 1.0f, 1.0f };



    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseProperties2);
    glLightfv(GL_LIGHT0, GL_POSITION, isikPozisyonu);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientProperties2);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularProperties2);

    // Malzeme Özellikleri
    float MatAmbient[4] = { 0.20f, 0.20f, 0.20f, 1.0f };
    float MatDiffuse[4]  = { 0.69f, 0.8f, 0.69f, 1.0f };
    float MatSpecular[4]  = { .94f, .94f, .94f, 1.0f };

    float MatShininess[1]  = { 10 };
    float MatEmission[4]  = { 0.05f, 0.05f, 0.05f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, MatEmission);



    GLfloat diffuseMaterial[4] = { 0.65, 0.65, 0.65, 1.0 };

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = {0.5, 1.0, 1.0, 0.0 };
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);


    glColorMaterial(GL_FRONT, GL_SPECULAR);



}



