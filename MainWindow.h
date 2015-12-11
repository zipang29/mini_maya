#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QGLViewer/qglviewer.h>
#include "Cube.h"
#include "DataMotion.h"

class Cube;
class Tools;

class MainWindow : public QGLViewer
{
    public:
        MainWindow(QWidget *parent);

    protected :
        virtual void init();
        virtual void draw();
        virtual void animate();
        virtual QString helpString() const;

    private:
        Cube * cube;
        DataMotion * data;
        QCursor cursor;

        QLabel * icon;

        Tools * tools;
};

#endif
