#include "DataMotion.h"
#include <QDebug>
#include <qmath.h>

DataMotion::DataMotion()
{
    this->data = new QVector<QVector<QVector<float>>>();
}

void DataMotion::setNbOfFrames(int nb)
{
    this->nbOfFrames = nb;
}

void DataMotion::setNbOfCameras(int nb)
{
    this->nbOfCameras = nb;
}

void DataMotion::setNbOfMarquers(int nb)
{
    this->nbOfMarkers = nb;
}

void DataMotion::setFrequency(int freq)
{
    this->frequency = freq;
}

void DataMotion::setNbOfAnalog(int nb)
{
    this->nbOfAnalog = nb;
}

void DataMotion::setAnalogFrequency(int freq)
{
    this->analogFrequency = freq;
}

void DataMotion::setDescription(QString description)
{
    this->description = description;
}

void DataMotion::setTimestamp(QString timestamp)
{
    this->timestamp = timestamp;
}

void DataMotion::setTypeOfData(QString type)
{
    this->typeOfData = type;
}

void DataMotion::addDataMotion(QVector<QVector<float>> line)
{
    this->data->push_back(line);
}

QVector<QVector<QVector<float>>> * DataMotion::getData()
{
    return this->data;
}

QVector<QVector<float>> DataMotion::getDataLine(int line)
{
    return data->at(line);
}

QVector<float> DataMotion::calculDistance(QVector<float> * p1, QVector<float> * p2)
{
    QVector<float> result;

    result.push_back(p1->at(Axes::Z) - p2->at(Axes::Z));
    result.push_back(p1->at(Axes::X) - p2->at(Axes::X));
    result.push_back(p1->at(Axes::Y) - p2->at(Axes::Y));

    return result;
}

Axes::Axe DataMotion::determineAxe(QVector<float> * p1, QVector<float> * p2)
{
    QVector<float> distance = calculDistance(p1, p2);

    float max = qAbs(distance.at(0));// Ne pas remplacer 0 par Axes::X car cela a des effets de bords

    for (int i=1; i<distance.size(); i++)
    {
        max = qMax(qAbs(max), qAbs(distance.at(i)));
    }
    qDebug() << distance;

    if (-max == distance.at(Axes::Z))
        return Axes::ALL;
    if (max == qAbs(distance.at(Axes::Z)))
        return Axes::Z;
    if (max == qAbs(distance.at(Axes::X)))
        return Axes::X;
    //if (max == qAbs(distance.at(Axes::Y)))
      //  return Axes::Y;
    if (max == qAbs(distance.at(Axes::Y)))
        return Axes::Y;


    return Axes::UNDEFINED; // Inutile, juste pour la forme
}

float DataMotion::calculerAngle(float A, float B, float C, char angle)
{
    float A2 = qPow(A, 2);
    float B2 = qPow(B, 2);
    float C2 = qPow(C, 2);
    if (angle == 'A')
    {
        return qAcos((B2 + C2 - A2) / 2 * B * C);
    }
    if (angle == 'B')
    {
        return qAcos((A2 + C2 - B2) / 2 * A * C);
    }
    if (angle == 'C')
    {
        return qAcos((A2 + B2 - C2) / 2 * A * B);
    }
    return 0;
}


