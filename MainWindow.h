#include <QGLViewer/qglviewer.h>
#include "Cube.h"

class MainWindow : public QGLViewer
{
    protected :
        virtual void init();
        virtual void draw();
        virtual void animate();
        virtual QString helpString() const;

    private:
        Cube * cube;
};

