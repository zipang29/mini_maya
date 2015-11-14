#include "Cube.h"

#include <QGLViewer/qglviewer.h>
#include <QVector>
#include <QDebug>
#include "parser.h"

Cube::Cube()
{
    this->init();
}

void Cube::init()
{
    this->currentMode = Actions::RESIZE;
    this->lineNumber = 0;
    this->data = Parser::getDataMotion();

    // Initialisation des positions des vertex du cube
    //face droite
    x_FD_BD = 1;
    y_FD_BD = -1;
    z_FD_BD = 1;
    x_FD_BG = 1;
    y_FD_BG = -1;
    z_FD_BG = -1;
    x_FD_HG = 1;
    y_FD_HG = 1;
    z_FD_HG = -1;
    x_FD_HD = 1;
    y_FD_HD = 1;
    z_FD_HD = 1;
}

void Cube::draw()
{
    glBegin(GL_QUADS);
        glColor3ub(255, 0, 0); //face rouge => face haut
        glVertex3d(1, 1, 1);
        glVertex3d(1, 1, -1);
        glVertex3d(-1, 1, -1);
        glVertex3d(-1, 1, 1);

        glColor3ub(0, 255, 0); //face verte => face droite => FD
        glVertex3f(x_FD_BD, y_FD_BD, z_FD_BD);
        glVertex3f(x_FD_BG, y_FD_BG, z_FD_BG);
        glVertex3f(x_FD_HG, y_FD_HG, z_FD_HG);
        glVertex3f(x_FD_HD, y_FD_HD, z_FD_HD);

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
    QVector<QVector<float>> lineStart = this->data->getDataLine(this->lineNumber);
    QVector<QVector<float>> lineEnd;
    if (this->lineNumber+1 < this->data->getData()->size())
        lineEnd = this->data->getDataLine(this->lineNumber + 1);
    if (lineEnd.isEmpty())
        this->lineNumber = 0;// on recommence l'annimation
    else
    {
        QVector<float> mainDroite1 = lineStart.at(4);
        QVector<float> mainDroite2 = lineEnd.at(4);

        QVector<float> distance = this->data->calculDistance(&mainDroite1, &mainDroite2);

        x_FD_BD = distance.at(0);
        x_FD_BG = distance.at(0);
        x_FD_HD = distance.at(0);
        x_FD_HG = distance.at(0);
    }

    this->lineNumber++;
}
