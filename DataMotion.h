#ifndef DATAMOTION_H
#define DATAMOTION_H

#include <QString>
#include <QVector>
#include <QtCore>
#include "Enum.h"
#include "qQualisysRT/src/qtm.h"
#include <QThread>
#include <QList>
#include "qQualisysRT/src/point.h"

using namespace QualisysRT;

class DataMotion : public QObject
{
    Q_OBJECT

    public:
        DataMotion(DataModes::DataMode mode, QHostAddress * address = NULL);
        void setNbOfFrames(int nb);
        void setNbOfCameras(int nb);
        void setNbOfMarquers(int nb);
        void setFrequency(int freq);
        void setNbOfAnalog(int nb);
        void setAnalogFrequency(int freq);
        void setDescription(QString description);
        void setTimestamp(QString timestamp);
        void setTypeOfData(QString type);
        QVector<QVector<QVector<float>>> * getData();
        QVector<QVector<float> > getDataLine(int line);
        DataModes::DataMode getMode();
        QVector<Point *> *getNextLine(int line);
        Point * getPoint(int n, QString name);
        int getMaxFrame(); // Retourne le nombre maximum de frame actuel disponible


        void addDataMotion(QVector<QVector<float> > line);
        QVector<float> calculDistance(Point *p1, Point *p2);
        double calculDistance3D(QVector<float> * p1, QVector<float> * p2);
        Axes::Axe determineAxe(Point * p1, Point * p2);
        double calculerAngle(float A, float B, float C, char angle);// calcul l'angle "angle" à partir des 3 points d'un triangle
        double calculerAngleA(QVector<float> A, QVector<float> B, QVector<float> C);

        ~DataMotion();

    private:
        int nbOfFrames;
        int nbOfCameras;
        int nbOfMarkers;
        int frequency;
        int nbOfAnalog;
        int analogFrequency;
        QString description;
        QString timestamp;
        QString typeOfData;

        DataModes::DataMode mode;

        // mode fichier
        QVector<QVector<QVector<float>>> * data;//line; censor; position X|Y|Z

        //mode temps réel
        QVector<QVector<float>> realTimeData;
        QVector<QVector<Point*>*> * points;//line ; censor ; pos
        int currentLine;

        QHostAddress * address;
        QThread* thread;
        QualisysRT::QTM* qtm;
        int frame;
        int pointNb;
        int target;

        void stop();

    private Q_SLOTS:
        void started();
        void stopped();
        void failedToStart(QString error);

        void pointUpdated();

};

#endif // DATAMOTION_H
