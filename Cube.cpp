#include "Cube.h"

#include <QGLViewer/qglviewer.h>
#include <QVector>
#include <QDebug>
#include <qmath.h>
#include "parser.h"

Cube::Cube()
{
    this->init();
}

void Cube::init()
{
    this->currentMode = Modes::ROTATE;
    this->lineNumber = 0;
    this->data = Parser::getDataMotion();

    // Angle de rotation
    angleX = 0;
    angleY = 0;
    angleZ = 0;

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

    x_A = -1;
    y_A = 1;
    z_A = -1;

    x_E = -1;
    y_E = 1;
    z_E = 1;

    x_D = -1;
    y_D = -1;
    z_D = -1;

    x_H = -1;
    y_H = -1;
    z_H = 1;
}

void Cube::draw()
{
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    glRotatef(angleZ, 0, 0, 1);
    glBegin(GL_QUADS);

        glColor3ub(255, 0, 0); //face rouge => face haut
        glVertex3d(x_F, y_F, z_F);
        glVertex3d(x_B, y_B, z_B);
        glVertex3d(x_A, y_A, z_A);
        glVertex3d(x_E, y_E, z_E);

        glColor3ub(0, 255, 0); //face verte => face droite => FD
        glVertex3f(x_G, y_G, z_G);
        glVertex3f(x_C, y_C, z_C);
        glVertex3f(x_B, y_B, z_B);
        glVertex3f(x_F, y_F, z_F);

        glColor3ub(0, 0, 255); //face bleue => fasse bas
        glVertex3d(x_H, y_H, z_H);
        glVertex3d(x_D, y_D, z_D);
        glVertex3d(x_C, y_C, z_C);
        glVertex3d(x_G, y_G, z_G);

        glColor3ub(255, 255, 0); //face jaune => face gauche
        glVertex3d(x_E, y_E, z_E);
        glVertex3d(x_A, y_A, z_A);
        glVertex3d(x_D, y_D, z_D);
        glVertex3d(x_H, y_H, z_H);

        glColor3ub(0, 255, 255); //face cyan => face derrière
        glVertex3d(x_B, y_B, z_B);
        glVertex3d(x_C, y_C, z_C);
        glVertex3d(x_D, y_D, z_D);
        glVertex3d(x_A, y_A, z_A);

        glColor3ub(255, 0, 255); //face magenta => face avant
        glVertex3d(x_G, y_G, z_G);
        glVertex3d(x_F, y_F, z_F);
        glVertex3d(x_E, y_E, z_E);
        glVertex3d(x_H, y_H, z_H);
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
            case Modes::RESIZE:
            {
                qDebug() << "Redimention :";
                QVector<float> mainDroite1 = lineStart.at(4);
                QVector<float> mainDroite2 = lineEnd.at(4);

                QVector<float> mainGaucheInterieur = lineStart.at(6);
                QVector<float> mainGaucheExtreminte = lineStart.at(7);

                QVector<float> distance = this->data->calculDistance(&mainDroite1, &mainDroite2);
                Axes::Axe axe = this->data->determineAxe(&mainGaucheInterieur, &mainGaucheExtreminte);

                if (axe == Axes::X || axe == Axes::ALL)
                {
                    qDebug() << "axe X";
                    float d = distance.at(0) / 40; // 40 détermine l'échelle à laquelle le cube va être redimentionné (pour rester dans des proportions acceptables)

                    x_B += d;
                    x_F += d;
                    x_G += d;
                    x_C += d;

                    x_A -= d;
                    x_E -= d;
                    x_D -= d;
                    x_H -= d;
                }
                if (axe == Axes::Y || axe == Axes::ALL)
                {
                    qDebug() << "axe Y";
                    float d = distance.at(1) / 40;

                    y_A += d;
                    y_E += d;
                    y_F += d;
                    y_B += d;

                    y_D -= d;
                    y_H -= d;
                    y_G -= d;
                    y_C -= d;
                }
                if (axe == Axes::Z || axe == Axes::ALL)
                {
                    qDebug() << "axe Z";
                    float d = distance.at(2) / 40;

                    z_A += d;
                    z_B += d;
                    z_D += d;
                    z_C += d;

                    z_E -= d;
                    z_F -= d;
                    z_H -= d;
                    z_G -= d;
                }

                if (axe == Axes::UNDEFINED)
                    qCritical() << "L'/les axe(s) de redimentionnement n'a/n'ont' pas pu être(s) déterminé(s).";
            }
            break;
            case Modes::ROTATE:
            {
                qDebug() << "Rotation : ";
                Axes::Axe axe = Axes::X;

                if (axe == Axes::X || axe == Axes::ALL)
                {
                    qDebug() << "axe X";
                    angleX++;// Todo a calculer à partir des données
                    if (angleX > 360)
                        angleX = 0;
                }
                if (axe == Axes::Y || axe == Axes::ALL)
                {
                    qDebug() << "axe Y";
                    angleY++;// Todo a calculer à partir des données
                    if (angleY > 360)
                        angleY = 0;
                }
                if (axe == Axes::Z || axe == Axes::ALL)
                {
                    qDebug() << "axe Z";
                    angleZ++;// Todo a calculer à partir des données
                    if (angleZ > 360)
                        angleZ = 0;
                }
                if (axe == Axes::UNDEFINED)
                    qCritical() << "L'/les axe(s) de redimentionnement n'a/n'ont' pas pu être(s) déterminé(s).";
            }
            break;
            case Modes::TWIST:
            {
                qDebug() << "Twist :";
            }
            break;
            case Modes::SELECT:
            {
                qDebug() << "Selection :";
            }
            break;
            case Modes::EXTRUDE:
            {
                qDebug() << "Extrusion :";
            }
            break;
            default:
                qCritical() << "Le mode sélectionné n'existe pas.";
            break;
        }
    }

    this->lineNumber++;
}
