#ifndef CUBE_H
#define CUBE_H


#include "enum.h"
#include "DataMotion.h"
#include <QVector>
#include <QCursor>
#include <QDesktopWidget>
#include <QApplication>
#include "qQualisysRT/src/point.h"
#include "Tools.h"
#include "Face.h"
#include <QList>

class Tools;

class Cube : public QObject
{
    Q_OBJECT

    public:
        Cube(Tools * parent, QGLViewer * viewer);
        void init();
        void draw(int selectedName);
        void drawWithNames();
        void animate();
        void changeMode(Modes::Mode mode);
        void setCursor(QCursor c);
        ~Cube();

    private:
        QDesktopWidget * resolution;
        QCursor c;
        Modes::Mode currentMode;
        int lineNumber;
        DataMotion * data;
        Tools * tools;
        QGLViewer * viewer;

        Point * pointG;
        Point * pointC;
        Point * pointB;
        Point * pointF;
        Point * pointA;
        Point * pointE;
        Point * pointD;
        Point * pointH;

        QList<Face*> listFace;

        float angleX;
        float angleY;
        float angleZ;

        // Selection
        QPoint curseur;
        int selectedFace;
};

#endif // CUBE_H
