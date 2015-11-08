#include "Cube.h"

#include <QGLViewer/qglviewer.h>
#include <QVector>
#include <QDebug>

Cube::Cube()
{
    this->init();
}

void Cube::init()
{
    this->currentMode = Actions::RESIZE;
}

void Cube::draw()
{
    glBegin(GL_QUADS);
        glColor3ub(255, 0, 0); //face rouge => face haut
        glVertex3d(1, 1, 1);
        glVertex3d(1, 1, -1);
        glVertex3d(-1, 1, -1);
        glVertex3d(-1, 1, 1);

        glColor3ub(0, 255, 0); //face verte => face droite
        glVertex3d(1, -1, 1);
        glVertex3d(1, -1, -1);
        glVertex3d(1, 1, -1);
        glVertex3d(1, 1, 1);

        glColor3ub(0, 0, 255); //face bleue => fasse bas
        glVertex3d(-1, -1, 1);
        glVertex3d(-1, -1, -1);
        glVertex3d(1, -1, -1);
        glVertex3d(1, -1, 1);

        glColor3ub(255, 255, 0); //face jaune => face gauche
        glVertex3d(-1, 1, 1);
        glVertex3d(-1, 1, -1);
        glVertex3d(-1, -1, -1);
        glVertex3d(-1, -1, 1);

        glColor3ub(0, 255, 255); //face cyan => face derrière
        glVertex3d(1, 1, -1);
        glVertex3d(1, -1, -1);
        glVertex3d(-1, -1, -1);
        glVertex3d(-1, 1, -1);

        glColor3ub(255, 0, 255); //face magenta => face avant
        glVertex3d(1, -1, 1);
        glVertex3d(1, 1, 1);
        glVertex3d(-1, 1, 1);
        glVertex3d(-1, -1, 1);
    glEnd();
}

void Cube::animate()
{

}
