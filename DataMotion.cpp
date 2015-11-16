#include "DataMotion.h"
#include <QDebug>

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
    result.push_back(p1->at(0) - p2->at(0));
    result.push_back(p1->at(1) - p2->at(1));
    result.push_back(p1->at(2) - p2->at(2));
    return result;
}

Axes::Axe DataMotion::determineAxe(QVector<float> * p1, QVector<float> * p2)
{
    QVector<float> distance = calculDistance(p1, p2);

    /*QVector<Axes::Axe> axes;
    if (qAbs(distance.at(0)) > 5) // détection axe x
    {
        axes.push_back(Axes::X);
    }
    if (qAbs(distance.at(1)) > 5) // détection axe y
    {
        axes.push_back(Axes::Y);
    }
    if (qAbs(distance.at(2)) > 5) // détection axe z
    {
        axes.push_back(Axes::Z);
    }

    if (axes.empty())
        return Axes::UNDEFINED;*/

    float max = qAbs(distance.at(0));

    for (int i=1; i<distance.size(); i++)
    {
        max = qMax(qAbs(max), qAbs(distance.at(i)));
    }

    if (max == qAbs(distance.at(0)))
        return Axes::X;
    if (max == qAbs(distance.at(1)))
        return Axes::Y;
    if (max == qAbs(distance.at(2)))
        return Axes::Z;

    return Axes::UNDEFINED;
}
