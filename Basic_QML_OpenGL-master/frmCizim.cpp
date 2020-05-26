/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
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

#include <QGuiApplication>

#include <QtQuick/QQuickView>

#include <QQmlEngine>
#include <QQmlContext>

#include "cizimislemi.h"
#include "fboinsgrenderer.h"
#include "glkaynak.h"
#include "logorenderer.h"


int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<FboInSGRenderer>("SceneGraphRendering", 1, 0, "Renderer");
    LogoRenderer msg;


    //qmlRegisterType<GlKaynak>("SceneGraphRendering", 1, 0, "Renderer");
    //CizimIslemi msg;




    QQuickView view;




    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.engine()->rootContext()->setContextProperty("msg", &msg);


    view.setSource(QUrl("qrc:/frmCizim.qml"));

    QObject *item = view.rootObject();

    QObject::connect(item, SIGNAL(tiklananNokta(int,int)),&msg, SLOT(tiklananPiksel(int,int)));
    QObject::connect(item, SIGNAL(onBasildi(int,int))     ,&msg, SLOT(onBasildi(int,int)));
    QObject::connect(item, SIGNAL(onBirakildi(int,int))   ,&msg, SLOT(onBirakildi(int,int)));
    QObject::connect(item, SIGNAL(onSurukleniyor(int,int)),&msg, SLOT(onSurukleniyor(int,int)));

    QObject::connect(item, SIGNAL(onMercekDegisti(double)),&msg, SLOT(onMercekDegisti(double)));

    //QObject::connect(item, SIGNAL(onSileBasildi(int)),    &msg, SLOT(onSileBasildi(int)));
    QObject::connect(item, SIGNAL(onOynatBasildi(int)),    &msg, SLOT(onOynatBasildi(int)));










    view.show();

    return app.exec();
}
