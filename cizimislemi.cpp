#include "cizimislemi.h"

#include "BMP.h"
#include <QPainter>
#include <QPaintEngine>
#include <math.h>
#include <ucgenleme.h>

#include <GL/glu.h>

#include <GL/gl.h>

#include <GL/freeglut.h>

#include <QDebug>
#include <QList>
#include <QQuickItem>

#include <math.h>
#include <cstdlib>
#include <iostream>
#include <fstream>


GLint Viewport[4];
GLdouble Modelview[16];
GLdouble Projection[16];

float* Vertices;
int VerticesSize;
float *Textcoord;
float *Normals;

GLuint textureId;


float KonumX = 0;
float KonumY = 0;

float DonmeAcisiY = 0;
float DonmeAcisiX;
float DonmeAcisiZ = 0;
float Mercek = 1;

QList<Nokta> noktalar;

bool cizimYap = true;




CizimIslemi::CizimIslemi()
{

}




CizimIslemi::~CizimIslemi()
{

}


void CizimIslemi::initialize()
{



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





void CizimIslemi::render()
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



    glOrtho(-0 - (Genislik / 2.0), - 0 + ( Genislik / 2.0), -0 - (Yukseklik / 2.0), -0 + (Yukseklik / 2.0), -(10000 * Genislik) / 2.0, (10000 * Genislik) / 2.0);

    glViewport(0, 0, Genislik,Yukseklik);

    IzgaraCiz();


    glTranslated(KonumX,KonumY,0);


    glScaled(Mercek,Mercek,Mercek);


    glRotatef(DonmeAcisiX, 1, 0, 0);
    glRotatef(DonmeAcisiY, 0, 1, 0);
    glRotatef(DonmeAcisiZ, 0, 0, 1);



    glPushMatrix();


    glGetIntegerv(GL_VIEWPORT, Viewport);

    glGetDoublev(GL_MODELVIEW_MATRIX, Modelview);

    glGetDoublev(GL_PROJECTION_MATRIX, Projection);


    glPushMatrix();

    Nokta nokta;
    nokta.x = 0;
    nokta.y = 0;
    nokta.z = 100;

    if(noktalar.size()>0)
    {
        nokta.x = noktalar[noktalar.size() - 1].x;
        nokta.y = noktalar[noktalar.size() - 1].y;
    }

    ParcalariCiz();

    KirmiziNoktaCiz(nokta);

    glPopMatrix();





    glPopMatrix();



}

void CizimIslemi::ParcalariCiz()
{
    glLineWidth(1.5);
    glColor3d(0.4,0.4,0.4);

    glBegin(GL_LINE_STRIP);

    glVertex3d(0,0,100);

    for(int i=0;i<noktalar.size();i++)
    {
        glVertex3d(noktalar[i].x,noktalar[i].y,100);
    }

    glEnd();
}

void CizimIslemi::KirmiziNoktaCiz(Nokta nokta)
{

    glColor3d(0.9,0.0,0);
    glBegin(GL_QUADS);
    glVertex3d(nokta.x - 3/Mercek,nokta.y - 3/Mercek,100);
    glVertex3d(nokta.x + 3/Mercek,nokta.y - 3/Mercek,100);
    glVertex3d(nokta.x + 3/Mercek,nokta.y + 3/Mercek,100);
    glVertex3d(nokta.x - 3/Mercek,nokta.y + 3/Mercek,100);
    glEnd();
}



void CizimIslemi::IzgaraCiz()
{
    for(int i=-500;i<500;i=i+pikselAralikDegeri)
    {
        glLineWidth(1);
        glColor3d(0.4,0.4,0);
        glBegin(GL_LINES);
        glVertex3d(i,-Yukseklik/2.0,0);
        glVertex3d(i,Yukseklik/2.0,0);
        glEnd();
    }

    for(int i=-Yukseklik/2;i<Yukseklik/2;i=i+pikselAralikDegeri)
    {
        glLineWidth(1);
        glColor3d(0.4,0.4,0);
        glBegin(GL_LINES);
        glVertex3d(-Genislik/2.0 ,i,0);
        glVertex3d(Genislik/2.0,i,0);
        glEnd();
    }


}


QStringList CizimIslemi::tiklananGLNoktasi()
{

    QStringList noktax;

    noktax.append(QString::number(glX));
    noktax.append(QString::number(glY));


    if (cizimYap == true)
    {
        Nokta nokta;
        nokta.x = glX; nokta.y = glY;
        noktalar.append(nokta);
    }


    return noktax;
}






void CizimIslemi::tiklananPiksel(int x ,int y)
{

    Point nokta = TiklananPikseliYuvarla(x, y);

    gluUnProject(nokta.x, nokta.y, 0, Modelview, Projection, Viewport, &glX, &glY, &glZ);

}

Point CizimIslemi::TiklananPikseliYuvarla(int x ,int y)
{
    float xYaklasim = x%pikselAralikDegeri;
    float yYaklasim = y%pikselAralikDegeri;


    if(xYaklasim < yaklasimPayi)
    {
        x = x - xYaklasim;
    }
    else if(xYaklasim > pikselAralikDegeri - yaklasimPayi)
    {
        x = x + (pikselAralikDegeri - xYaklasim);
    }

    if(yYaklasim < yaklasimPayi)
    {
        y = y - yYaklasim;
    }
    else if(yYaklasim > pikselAralikDegeri - yaklasimPayi)
    {
        y = y + (pikselAralikDegeri - yYaklasim);
    }

    return {x,y};
}

void CizimIslemi::onBasildi(int x, int y)
{
    cizimYap = true;

    hareketeBaslamaNoktasi.x = x;
    hareketeBaslamaNoktasi.y = y;

}

void CizimIslemi::onBirakildi(int x, int y)
{
    hareketeBaslamaNoktasi.x = hareketiBitirmeNoktasi.x;
    hareketeBaslamaNoktasi.y = hareketiBitirmeNoktasi.y;


}

void CizimIslemi::onSurukleniyor(int x, int y)
{

    cizimYap = false;


    if (((hareketeBaslamaNoktasi.x) == hareketiBitirmeNoktasi.x)&& (hareketeBaslamaNoktasi.y == hareketiBitirmeNoktasi.y)) { cizimYap = true; return; }

        if (!CizimiOynat)
        {
            DonmeAcisiY = (x - hareketeBaslamaNoktasi.x) + DonmeAcisiY;
            DonmeAcisiX = (y - hareketeBaslamaNoktasi.y) + DonmeAcisiX;

        }
        else
        {
            KonumY = -((-y + hareketeBaslamaNoktasi.y) - KonumY);
            KonumX = (-(-x + hareketeBaslamaNoktasi.x) + ( KonumX));

        }

        hareketeBaslamaNoktasi.x = x;
        hareketeBaslamaNoktasi.y = y;


}



void CizimIslemi::onSileBasildi(int durum)
{
    SonParcayiSil();
}

void CizimIslemi::onMercekDegisti(double gelenMercek)
{
    Mercek = gelenMercek;
}

void CizimIslemi::SonParcayiSil()
{

    if(noktalar.size()>0)
    {
        noktalar.removeAt(noktalar.size() - 1);
    }


}

