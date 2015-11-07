#include <QGLViewer/qglviewer.h>

class MainWindow : public QGLViewer
{
    protected :
        virtual void draw();
        virtual void init();
        virtual void animate();
        virtual QString helpString() const;

    private:

};

