#ifndef GLKAYNAK_H
#define GLKAYNAK_H




#include <QtQuick/QQuickFramebufferObject>

class CizimIslemi;

class GlKaynak : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    Renderer *createRenderer() const;





};

#endif // GLKAYNAK_H
