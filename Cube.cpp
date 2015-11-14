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
    x_G = 1;
    y_G = -1;
    z_G = 1;

    x_C = 1;
    y_C = -1;
    z_C = -1;

    x_B = 1;
    y_B = 1;
    z_B = -1;

    x_F = 1;
    y_F = 1;
    z_F = 1;
}

void Cube::draw()
{
    glBegin(GL_QUADS);
        glColor3ub(255, 0, 0); //face rouge => face haut
        glVertex3d(x_F, y_F, z_F);
        glVertex3d(x_B, y_B, z_B);
        glVertex3d(-1, 1, -1);
        glVertex3d(-1, 1, 1);

        glColor3ub(0, 255, 0); //face verte => face droite => FD
        glVertex3f(x_G, y_G, z_G);
        glVertex3f(x_C, y_C, z_C);
        glVertex3f(x_B, y_B, z_B);
        glVertex3f(x_F, y_F, z_F);

        glColor3ub(0, 0, 255); //face bleue => fasse bas
        glVertex3d(-1, -1, 1);
        glVertex3d(-1, -1, -1);
        glVertex3d(x_C, y_C, z_C);
        glVertex3d(x_G, y_G, z_G);

        glColor3ub(255, 255, 0); //face jaune => face gauche
        glVertex3d(-1, 1, 1);
        glVertex3d(-1, 1, -1);
        glVertex3d(-1, -1, -1);
        glVertex3d(-1, -1, 1);

        glColor3ub(0, 255, 255); //face cyan => face derrière
        glVertex3d(x_B, y_B, z_B);
        glVertex3d(x_C, y_C, z_C);
        glVertex3d(-1, -1, -1);
        glVertex3d(-1, 1, -1);

        glColor3ub(255, 0, 255); //face magenta => face avant
        glVertex3d(x_G, y_G, z_G);
        glVertex3d(x_F, y_F, z_F);
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
        switch(this->currentMode)
        {
            case Actions::RESIZE:
                QVector<float> mainDroite1 = lineStart.at(4);
                QVector<float> mainDroite2 = lineEnd.at(4);

                QVector<float> distance = this->data->calculDistance(&mainDroite1, &mainDroite2);

                x_G = distance.at(0);
                x_C = distance.at(0);
                x_B = distance.at(0);
                x_F = distance.at(0);
            break;
            case Actions::ROTATE:

            break;
            case Actions::TWIST:

            break;
            case Actions::SELECT:

            break;
            case Actions::EXTRUDE:

            break;
            default:
                qCritical() << "Le mode sélectionné n'existe pas.";
            break;
        }
    }

    this->lineNumber++;
}
