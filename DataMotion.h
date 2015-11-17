#ifndef DATAMOTION_H
#define DATAMOTION_H

#include <QString>
#include <QVector>
#include "Enum.h"

class DataMotion
{
    public:
        DataMotion();
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


        void addDataMotion(QVector<QVector<float> > line);
        QVector<float> calculDistance(QVector<float> * p1, QVector<float> * p2);
        Axes::Axe determineAxe(QVector<float> * p1, QVector<float> * p2);
        float calculerAngle(float A, float B, float C, char angle);// calcul l'angle "angle" à partir des 3 points d'un triangle

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

        QVector<QVector<QVector<float>>> * data;//line; censor; position X|Y|Z
};

#endif // DATAMOTION_H
