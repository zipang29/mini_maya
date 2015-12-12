#include "Face.h"

Face::Face(Point * A, Point * B, Point * C, Point * D)
{
    a = A;
    b = B;
    c = C;
    d = D;
}

void Face::draw(bool highlighted)
{
    glBegin(GL_QUADS);
        glNormal3d(nx, ny, nz);
        if (!highlighted)
            glColor3ub(color.red(), color.green(), color.blue());
        else
            glColor3ub(255, 255, 255);
        glVertex3d(a->x(), a->y(), a->z());
        glVertex3d(b->x(), b->y(), b->z());
        glVertex3d(c->x(), c->y(), c->z());
        glVertex3d(d->x(), d->y(), d->z());
    glEnd();
}

void Face::setColor(QColor c)
{
    color = c;
}

void Face::setNormal(GLdouble nx, GLdouble ny, GLdouble nz)
{
    this->nx = nx;
    this->ny = ny;
    this->nz = nz;
}
