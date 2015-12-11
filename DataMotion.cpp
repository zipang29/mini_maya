#include "DataMotion.h"
#include <QDebug>
#include <qmath.h>
#include <QCoreApplication>
#include <QList>
#include <qQualisysRT/src/point.h>

DataMotion::DataMotion(DataModes::DataMode mode, QHostAddress *address)
{
    data = new QVector<QVector<QVector<float>>>();
    mode = mode;
    address = address;
    currentLine = 0;
    points = new QVector<QVector<Point*>*>();

    frame = 0;
    target = 100;

    if (mode == DataModes::REAL_TIME)
    {
        thread = new QThread();
        thread->start();

        qtm = new QTM(*address);
        qtm->moveToThread(thread);

        connect(qtm, SIGNAL(started()), this, SLOT(started()));
        connect(qtm, SIGNAL(stopped()), this, SLOT(stopped()));
        connect(qtm, SIGNAL(failedToStart(QString)), this, SLOT(failedToStart(QString)));
        QMetaObject::invokeMethod(qtm, "start");
    }
}

DataModes::DataMode DataMotion::getMode()
{
    return mode;
}

void DataMotion::setNbOfFrames(int nb)
{
    nbOfFrames = nb;
}

void DataMotion::setNbOfCameras(int nb)
{
    nbOfCameras = nb;
}

void DataMotion::setNbOfMarquers(int nb)
{
    nbOfMarkers = nb;
}

void DataMotion::setFrequency(int freq)
{
    frequency = freq;
}

void DataMotion::setNbOfAnalog(int nb)
{
    nbOfAnalog = nb;
}

void DataMotion::setAnalogFrequency(int freq)
{
    analogFrequency = freq;
}

void DataMotion::setDescription(QString description)
{
    description = description;
}

void DataMotion::setTimestamp(QString timestamp)
{
    timestamp = timestamp;
}

void DataMotion::setTypeOfData(QString type)
{
    typeOfData = type;
}

void DataMotion::addDataMotion(QVector<QVector<float>> line)
{
    data->push_back(line);
}

QVector<QVector<QVector<float>>> * DataMotion::getData()
{
    return data;
}

QVector<QVector<float>> DataMotion::getDataLine(int line)
{
    if (this->mode == DataModes::FILE)
        return data->at(line);
    else
        return realTimeData;
}

QVector<float> DataMotion::calculDistance(Point * p1, Point * p2)
{
    QVector<float> result;

    result.push_back(p1->x() - p2->x());
    result.push_back(p1->y() - p2->y());
    result.push_back(p1->z() - p2->z());

    return result;
}

double DataMotion::calculDistance3D(Point * p1, Point * p2)
{
    /*double xd = p2->at(Coordonnees::X) - p1->at(Coordonnees::X);
    double yd = p2->at(Coordonnees::Y) - p1->at(Coordonnees::Y);
    double zd = p2->at(Coordonnees::Z) - p1->at(Coordonnees::Z);
    return qSqrt(xd*xd + yd*yd + zd*zd);*/
    return qSqrt(qPow(p2->x() - p1->x(), 2) + qPow(p2->y() - p1->y(), 2) + qPow(p2->z() - p1->z(), 2));
}

Axes::Axe DataMotion::determineAxe(Point * p1, Point * p2)
{
    QVector<float> distance = calculDistance(p1, p2);

    float max = qAbs(distance.at(0));// Ne pas remplacer 0 par Axes::X car cela a des effets de bords

    for (int i=1; i<distance.size(); i++)
    {
        max = qMax(qAbs(max), qAbs(distance.at(i)));
    }
    qDebug() << distance;

    Axes::Axe res = Axes::UNDEFINED;

    if (max == qAbs(distance.at(Coordonnees::X)))
        res = Axes::X;
    if (max == qAbs(distance.at(Coordonnees::Y)))
        res = Axes::Y;
    if (max == qAbs(distance.at(Coordonnees::Z)))
        res = Axes::Z;

    //if (distance.at(Coordonnees::X) < 8) // Ne fonctionne pas correctement
    //    res = Axes::ALL;

    return res;
}

double DataMotion::calculerAngle(float A, float B, float C, char angle)
{
    if (angle == 'A')
    {
        double AB = B - A;
        double AC = C - A;
        return (AB * AC) / qSqrt(qPow(AB, 2) + qPow(AC, 2));
        //return qAcos((B2 + C2 - A2) / 2.0 * B * C);
    }
    if (angle == 'B')
    {
        double BC = C - B;
        double BA = A - B;
        return (BC * BA) / qSqrt(qPow(BC, 2) + qPow(BA, 2));
        //return qAcos((A2 + C2 - B2) / 2 * A * C);
    }
    if (angle == 'C')
    {
        double CA = A - C;
        double CB = B - C;
        return (CA * CB) / qSqrt(qPow(CA, 2) + qPow(CB, 2));
        //return qAcos((A2 + B2 - C2) / 2 * A * B);
    }
    return 0;
}

double DataMotion::calculerAngleA(QVector<float> A, QVector<float> B, QVector<float> C)
{
    double Xa = A.at(Coordonnees::X);
    double Xb = B.at(Coordonnees::X);
    double Xc = C.at(Coordonnees::X);

    double Ya = A.at(Coordonnees::Y);
    double Yb = B.at(Coordonnees::Y);
    double Yc = C.at(Coordonnees::Y);

    double Za = A.at(Coordonnees::Z);
    double Zb = B.at(Coordonnees::Z);
    double Zc = C.at(Coordonnees::Z);

    double ABx = Xb - Xa;
    double ABy = Yb - Ya;
    double ABz = Zb - Za;

    double ACx = Xc - Xa;
    double ACy = Yc - Ya;
    double ACz = Zc - Za;

    double numerateur = (ABx) * (ACx) + (ABy) * (ACy) + (ABz) * (ACz);
    double denominateur = qSqrt(qPow(ABx, 2) + qPow(ABy, 2) + qPow(ABz, 2)) * qSqrt(qPow(ACx, 2) + qPow(ACy, 2) + qPow(ACz, 2));
    return qRadiansToDegrees(qCos(numerateur / denominateur));
}

void DataMotion::started()
{
    QList<Point*> points = this->qtm->points();
    this->pointNb = points.length();

    for (int i=0; i<points.size(); i++)
    {
        Point * p = points.at(i);
        connect(p, SIGNAL(updated()), this, SLOT(pointUpdated()));
    }
    /*foreach (QualisysRT::Point * p, points) {
        connect(p, SIGNAL(updated()), this, SLOT(pointUpdated()));
    }*/
}

void DataMotion::stopped()
{
    qApp->exit();
}

void DataMotion::failedToStart(QString error)
{
    qCritical() << error;
    qApp->exit();
}

void DataMotion::pointUpdated()
{
    static int count = 0;
    Point * p = qobject_cast<Point*>(sender());

    count++;
    if (count == pointNb)
    {
        frame++;
        count = 0;
        QVector<Point*> * l = new QVector<Point*>();
        points->push_back(l);
    }
    else
    {
        if (points->size() < pointNb)
        {
            int sizeV1 = points->size();
            QVector<Point*> * l = points->at(sizeV1);
            l->push_back(p);
        }
    }
    if (frame == target)
        stop();
}

void DataMotion::stop()
{
    QMetaObject::invokeMethod(qtm, "stop");
    disconnect(this, SIGNAL(pointUpdated()));
}

QVector<Point*> * DataMotion::getNextLine(int line)
{
    if (line < frame) // Si les données sont prêtes
    {
        return points->at(line);
    }
    else // Sinon on doit attendre
        return NULL;
}

Point * DataMotion::getPoint(int n, QString name)
{
    if (n < frame)
    {
        QVector<Point*> * line = points->at(n);
        for (int i=0; i<line->size(); i++)
        {
            if (line->at(i)->name() == name)
                return line->at(i);
        }
        return NULL;
    }
    else
        return NULL;
}

int DataMotion::getMaxFrame()
{
    return frame;
}

void DataMotion::addPoint(Point * p)
{
    if (points->empty())
        points->push_back(new QVector<Point*>);
    if (points->at(frame)->size() >= nbOfMarkers)
    {
        frame++;
        points->push_back(new QVector<Point*>());
    }

    points->at(frame)->push_back(p);
}

DataMotion::~DataMotion()
{
    qtm->deleteLater();
    thread->deleteLater();
    for (int i=0; i<points->size(); i++)
    {
        for (int j=0; j<points->at(i)->size();j++)
        {
            delete points->at(i)->at(j);
        }
        delete points->at(i);
    }
    delete points;
}
