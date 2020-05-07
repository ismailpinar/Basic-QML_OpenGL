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

#include "logorenderer.h"
#include <QPainter>
#include <QPaintEngine>
#include <math.h>
#include <ucgenleme.h>

#include <GL/glu.h>

#include <QDebug>
#include <QQuickItem>




GLint viewport[4];
GLdouble model_view[16];
GLdouble projection[16];


LogoRenderer::LogoRenderer()
{

}




LogoRenderer::~LogoRenderer()
{

}


void LogoRenderer::initialize()
{


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



    glOrtho(-KonumX - (Genislik / 2.0), -KonumX + ( Genislik / 2.0), -KonumY - (Yukseklik / 2.0), -KonumY + (Yukseklik / 2.0), -(1000 * Genislik) / 2.0, (1000 * Genislik) / 2.0);
    glViewport(0, 0, Genislik,Yukseklik);

    glScaled(.5,.5,.5);

    glTranslated(0,350,0);

    glRotated(180.0,1,0.0,0.0);

    glPushMatrix();

    UcgenCiz(outputTriangles);

    //YanKesitleriOlustur(veriler,100);


    glPopMatrix();


    glGetIntegerv(GL_VIEWPORT, viewport);

    glGetDoublev(GL_MODELVIEW_MATRIX, model_view);

    glGetDoublev(GL_PROJECTION_MATRIX, projection);
}



void LogoRenderer::VerileriDoldur()
{
    veriDoldur veri;

    veriler = veri.Doldur();

    Ucgenleme ucgenler;

    outputTriangles = ucgenler.Ucgenle(veriler);

}

void LogoRenderer::YanKesitleriOlustur(QList<Nokta> veriler,float genislik)
{
    glColor3d(1,0.4,0.5);


    for(int i=0;i<veriler.size()-1;i++)
    {
        glBegin(GL_QUADS);
        glVertex3d(veriler[i].x,veriler[i].y,veriler[i].z);
        glVertex3d(veriler[i+1].x,veriler[i+1].y,veriler[i].z);
        glVertex3d(veriler[i+1].x,veriler[i+1].y,veriler[i].z + genislik);
        glVertex3d(veriler[i].x,veriler[i].y,veriler[i].z + genislik);
        glEnd();

    }

}



void LogoRenderer::UcgenCiz(vector<Point> outputTriangles)
{
    glColor3d(1,0,0);


    for(int i=0;i<outputTriangles.size();i=i+3)
    {
        glBegin(GL_TRIANGLES);
        glVertex3d(outputTriangles[i].x,outputTriangles[i].y,0);
        glVertex3d(outputTriangles[i+1].x,outputTriangles[i+1].y,0);
        glVertex3d(outputTriangles[i+2].x,outputTriangles[i+2].y,0);
        glEnd();

    }

    glColor3d(1,1,0);


    for(int i=0;i<outputTriangles.size();i=i+3)
    {
        glBegin(GL_TRIANGLES);
        glVertex3d(outputTriangles[i].x,outputTriangles[i].y,100);
        glVertex3d(outputTriangles[i+1].x,outputTriangles[i+1].y,100);
        glVertex3d(outputTriangles[i+2].x,outputTriangles[i+2].y,100);
        glEnd();

    }


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





