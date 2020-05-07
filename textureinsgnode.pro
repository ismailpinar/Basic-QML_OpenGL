QT += qml quick

HEADERS += fboinsgrenderer.h \
    Nokta.h \
    clip2tri/clip2tri.h \
    clipper/clipper.hpp \
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
SOURCES += fboinsgrenderer.cpp main.cpp \
    clip2tri/clip2tri.cpp \
    clipper/clipper.cpp \
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

OTHER_FILES += \
    main.qml
