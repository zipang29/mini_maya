#ifndef FACE_H
#define FACE_H

#include "qQualisysRT/src/point.h"
#include <QColor>
#include <QGLViewer/qglviewer.h>

class QualisysRT::Point;

using namespace QualisysRT;

class Face
{
    public:
        Face(Point * A, Point * B, Point * C, Point * D);
        void draw(bool highlighted = false);
        void drawWithNames();
        void setColor(QColor c);
        void setNormal(GLdouble nx, GLdouble ny, GLdouble nz);

    private:
        Point * a;
        Point * b;
        Point * c;
        Point * d;

        QColor color;

        //normal
        GLdouble nx;
        GLdouble ny;
        GLdouble nz;
};

#endif // FACE_H
