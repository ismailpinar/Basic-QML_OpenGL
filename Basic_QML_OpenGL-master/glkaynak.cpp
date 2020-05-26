#include "glkaynak.h"


#include "cizimislemi.h"

#include <QtGui/QOpenGLFramebufferObject>

#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>



class GlKaynakInFboRenderer : public QQuickFramebufferObject::Renderer
{
public:
    GlKaynakInFboRenderer()
    {
        logo.initialize();
    }

    void render() {
        logo.render();
        update();


    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(60);
        return new QOpenGLFramebufferObject(size, format);
    }

    CizimIslemi logo;


};

QQuickFramebufferObject::Renderer *GlKaynak::createRenderer() const
{
    return new GlKaynakInFboRenderer();
}
