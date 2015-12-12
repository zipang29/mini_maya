#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QGLViewer/qglviewer.h>
#include "Cube.h"
#include "DataMotion.h"

class Cube;
class Tools;
class QLabel;

class MainWindow : public QGLViewer
{
    public:
        MainWindow(QWidget *parent);

    protected :
        virtual void init();
        virtual void draw();
        virtual void drawWithNames();
        virtual void animate();
        virtual void postSelection(const QPoint& point);
        virtual QString helpString() const;

    private:
        Cube * cube;
        DataMotion * data;
        QCursor cursor;

        QLabel * icon;

        Tools * tools;

        // Sélection de face à la souris
        qglviewer::Vec orig, dir, selectedPoint;
};

#endif
