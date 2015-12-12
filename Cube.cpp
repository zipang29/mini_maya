#include "Cube.h"

#include <QGLViewer/qglviewer.h>
#include <QVector>
#include <QDebug>
#include <qmath.h>
#include "parser.h"
#include <QMessageBox>
#include <QtTest/QtTest>

Cube::Cube(Tools * parent, QGLViewer *viewer)
{
    tools = parent;
    this->viewer = viewer;
    this->init();
}

void Cube::init()
{
    this->resolution = QApplication::desktop();
    this->currentMode = Modes::PAUSE;
    this->lineNumber = 0;
    this->data = Parser::getDataMotion();

    // Angle de rotation
    angleX = 0;
    angleY = 0;
    angleZ = 0;

    // Initialisation des positions des vertex du cube
    pointG = new Point("G");
    pointG->x() = 1;
    pointG->y() = -1;
    pointG->z() = 1;

    pointC = new Point("C");
    pointC->x() = 1;
    pointC->y() = -1;
    pointC->z() = -1;

    pointB = new Point("B");
    pointB->x() = 1;
    pointB->y() = 1;
    pointB->z() = -1;

    pointF = new Point("F");
    pointF->x() = 1;
    pointF->y() = 1;
    pointF->z() = 1;

    pointA = new Point("A");
    pointA->x() = -1;
    pointA->y() = 1;
    pointA->z() = -1;

    pointE = new Point("E");
    pointE->x() = -1;
    pointE->y() = 1;
    pointE->z() = 1;

    pointD = new Point("D");
    pointD->x() = -1;
    pointD->y() = -1;
    pointD->z() = -1;

    pointH = new Point("H");
    pointH->x() = -1;
    pointH->y() = -1;
    pointH->z() = 1;

    Face * faceHaut = new Face(pointF, pointB, pointA, pointE);
    faceHaut->setNormal(0, 1, 0);
    faceHaut->setColor(QColor(255, 0, 0));

    Face * faceDroite = new Face(pointG, pointC, pointB, pointF);
    faceDroite->setNormal(1, 0, 0);
    faceDroite->setColor(QColor(0, 255, 0));

    Face * faceBas = new Face(pointH, pointD, pointC, pointG);
    faceBas->setNormal(0, -1, 0);
    faceBas->setColor(QColor(0, 0, 255));

    Face * faceGauche = new Face(pointE, pointA, pointD, pointH);
    faceGauche->setNormal(-1, 0, 0);
    faceGauche->setColor(QColor(255, 255, 0));

    Face * faceDerriere = new Face(pointB, pointC, pointD, pointA);
    faceDerriere->setNormal(0, 0, -1);
    faceDerriere->setColor(QColor(0, 255, 255));

    Face * faceAvant = new Face(pointG, pointF, pointE, pointH);
    faceAvant->setNormal(0, 0, 1);
    faceAvant->setColor(QColor(255, 0, 255));

    listFace.push_back(faceHaut);
    listFace.push_back(faceDroite);
    listFace.push_back(faceBas);
    listFace.push_back(faceGauche);
    listFace.push_back(faceDerriere);
    listFace.push_back(faceAvant);
}

void Cube::draw(int selectedName)
{
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    glRotatef(angleZ, 0, 0, 1);

    for (int i=0; i<listFace.size(); i++)
    {
        glPushMatrix();
        if (selectedName == i)
            listFace.at(i)->draw(true);
        else
            listFace.at(i)->draw();
        glPopMatrix();
    }
}

void Cube::drawWithNames()
{
    for (int i=0; i<listFace.size(); i++)
    {
        glPushName(i);
        listFace.at(i)->draw();
        glPopName();
    }
}

void Cube::animate()
{
    this->currentMode = tools->detectCurrentMode(data, lineNumber, currentMode);
    switch(this->currentMode)
    {
        case Modes::RESIZE:
        {
            qDebug() << "Redimention :";

            Point * phalangeDroite1 = data->getPoint(lineNumber, "FR");
            Point * phalangeDroite2 = data->getPoint(lineNumber+1, "FR");

            Point * poignetGauche = data->getPoint(lineNumber, "PL");
            Point * doigtsGauche = data->getPoint(lineNumber, "DL");

            if (phalangeDroite1 == NULL || phalangeDroite2 == NULL || poignetGauche == NULL || doigtsGauche == NULL)
                return;

            QVector<float> distance = data->calculDistance(phalangeDroite1, phalangeDroite2);
            Axes::Axe axe = data->determineAxe(poignetGauche, doigtsGauche);

            if (axe == Axes::X || axe == Axes::ALL)
            {
                qDebug() << "axe X";
                float d = distance.at(Coordonnees::X) / 40; // 40 détermine l'échelle à laquelle le cube va être redimentionné (pour rester dans des proportions acceptables)

                pointB->x() += d;
                pointF->x() += d;
                pointG->x() += d;
                pointC->x() += d;

                pointA->x() -= d;
                pointE->x() -= d;
                pointD->x() -= d;
                pointH->x() -= d;
            }
            if (axe == Axes::Y || axe == Axes::ALL)
            {
                qDebug() << "axe Y";
                float d = distance.at(Coordonnees::X) / 40;

                pointA->y() += d;
                pointE->y() += d;
                pointF->y() += d;
                pointB->y() += d;

                pointD->y() -= d;
                pointH->y() -= d;
                pointG->y() -= d;
                pointC->y() -= d;
            }
            if (axe == Axes::Z || axe == Axes::ALL)
            {
                qDebug() << "axe Z";
                float d = distance.at(Coordonnees::X) / 40;

                pointA->z() += d;
                pointB->z() += d;
                pointD->z() += d;
                pointC->z() += d;

                pointE->z() -= d;
                pointF->z() -= d;
                pointH->z() -= d;
                pointG->z() -= d;
            }

            if (axe == Axes::UNDEFINED)
                qCritical() << "L'/les axe(s) de redimentionnement n'a/n'ont' pas pu être(s) déterminé(s).";
        }
        break;
        case Modes::ROTATE:
        {
            qDebug() << "Rotation : ";

            Point * phalangeDroite1 = data->getPoint(lineNumber, "FR");
            Point * phalangeDroite2 = data->getPoint(lineNumber+1, "FR");

            Point * poignetGauche = data->getPoint(lineNumber, "PL");
            Point * doigtsGauche = data->getPoint(lineNumber, "DL");

            if (phalangeDroite1 == NULL || phalangeDroite2 == NULL || poignetGauche == NULL || doigtsGauche == NULL)
                return;

            Axes::Axe axe = data->determineAxe(poignetGauche, doigtsGauche);
            float angleRotation = 0;
            QVector<float> distance = data->calculDistance(phalangeDroite1, phalangeDroite2);

            if (axe == Axes::X || axe == Axes::ALL)
            {
                qDebug() << "axe X";
                angleRotation = distance.at(Axes::X);//(distance.at(Axes::X) / 360) * 100;
                angleX += angleRotation;// Todo a calculer à partir des données
                if (angleX > 360)
                    angleX = 0;
            }
            if (axe == Axes::Y || axe == Axes::ALL)
            {
                qDebug() << "axe Y";
                angleRotation = distance.at(Axes::X);//(distance.at(Axes::X) / 360) * 100;
                angleY += angleRotation;// Todo a calculer à partir des données
                if (angleY > 360)
                    angleY = 0;
            }
            if (axe == Axes::Z || axe == Axes::ALL)
            {
                qDebug() << "axe Z";
                angleRotation = distance.at(Axes::X);//(distance.at(Axes::X) / 360) * 100;
                angleZ += angleRotation;// Todo a calculer à partir des données
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
            Point * p = data->getPoint(lineNumber, "DL");

            if (p == NULL)
                return;

            curseur.setX(qAbs(p->y()));// Y == X pour effectuer le mapping des coordonnées
            curseur.setY(qAbs(p->x()));
            qDebug() << curseur;
            this->c.setPos(curseur.x(), curseur.y());

            Point * poignetD = data->getPoint(lineNumber, "PR");
            Point * doigtsD = data->getPoint(lineNumber, "DR");

            if (poignetD == NULL || doigtsD == NULL)
                return;

            double distanceMainDroite = data->calculDistance3D(poignetD, doigtsD);
            if (distanceMainDroite > 80 && distanceMainDroite < 100) // clic
            {
                QTest::mouseClick(viewer, Qt::RightButton);
                this->currentMode = Modes::PAUSE;
            }
        }
        break;
        case Modes::EXTRUDE:
        {
            qDebug() << "Extrusion :";
        }
        break;
        case Modes::PAUSE:
        {

        }
        break;
        case Modes::CHANGE_TOOL:
        {

        }
        break;
        default:
            qCritical() << "Le mode sélectionné n'existe pas.";
        break;
    }

    this->lineNumber++;
}

void Cube::setCursor(QCursor c)
{
    this->c = c;
}

void Cube::changeMode(Modes::Mode mode)
{
    this->currentMode = mode;
}

Cube::~Cube()
{
    resolution->deleteLater();
    data->deleteLater();
}
