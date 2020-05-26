#Author: İsmail PINAR
#Date:   17.05.2020
#info: 	 i.pinar6616@outlook.com

QT += qml quick

HEADERS += fboinsgrenderer.h \
    BMP.h \
    Nokta.h \
    cizimislemi.h \
    clip2tri/clip2tri.h \
    clipper/clipper.hpp \
    glkaynak.h \
    hesaplamalar.h \
    logorenderer.h \
    poly2tri/common/shapes.h \
    poly2tri/common/utils.h \
    poly2tri/poly2tri.h \
    poly2tri/sweep/advancing_front.h \
    poly2tri/sweep/cdt.h \
    poly2tri/sweep/sweep.h \
    poly2tri/sweep/sweep_context.h \
    ucgenleme.h \
    veridoldur.h
SOURCES += fboinsgrenderer.cpp \
    cizimislemi.cpp \
    clip2tri/clip2tri.cpp \
    clipper/clipper.cpp \
    frmCizim.cpp \
    glkaynak.cpp \
    hesaplamalar.cpp \
    logorenderer.cpp \
    poly2tri/common/shapes.cc \
    poly2tri/sweep/advancing_front.cc \
    poly2tri/sweep/cdt.cc \
    poly2tri/sweep/sweep.cc \
    poly2tri/sweep/sweep_context.cc \
    ucgenleme.cpp \
    veridoldur.cpp

LIBS += -lGL -lGLU -lglut


INCLUDEPATH += ../shared

RESOURCES += textureinsgnode.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/quick/scenegraph/textureinsgnode
INSTALLS += target



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lftgl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lftgl
else:unix: LIBS += -L$$PWD/./ -lftgl

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
