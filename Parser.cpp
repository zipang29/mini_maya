#include "Parser.h"
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QVector>
#include <QCoreApplication>

DataMotion * Parser::data = NULL;

Parser::Parser()
{

}

Parser::Parser(QString file)
{
    this->file = file;
    Parser::data = new DataMotion(DataModes::FILE);
}

bool Parser::parse()
{
    QFile f(this->file);
    if (!f.exists())
    {
        qCritical() << "Le fichier n'existe pas : " << this->file;
        return false;
    }
    if (!f.open(QIODevice::ReadOnly))
    {
        qCritical() << "Impossible d'ouvrir le fichier " << this->file;
        return false;
    }


    QRegExp reg("\\s+");

    QString strNbOfFrames = f.readLine();
    int nbOfFrames = ((QString)(strNbOfFrames.split(reg).at(1))).toInt();
    this->data->setNbOfFrames(nbOfFrames);

    QString strNbOfCameras = f.readLine();
    int nbOfCameras = ((QString)(strNbOfCameras.split(reg).at(1))).toInt();
    this->data->setNbOfCameras(nbOfCameras);

    QString strNbOfMarkers = f.readLine();
    int nbOfMarkers = ((QString)(strNbOfMarkers.split(reg).at(1))).toInt();
    this->data->setNbOfMarquers(nbOfMarkers);

    QString strFrequency = f.readLine();
    int frequency = ((QString)(strFrequency.split(reg).at(1))).toInt();
    this->data->setFrequency(frequency);

    QString strNbOfAnalog = f.readLine();
    int nbOfAnalog = ((QString)(strNbOfAnalog.split(reg).at(1))).toInt();
    this->data->setNbOfAnalog(nbOfAnalog);

    QString strAnalogFrequency = f.readLine();
    int analogFrequency = ((QString)(strAnalogFrequency.split(reg).at(1))).toInt();
    this->data->setAnalogFrequency(analogFrequency);

    QString description = f.readLine();

    QString timetamp = f.readLine();

    QString dataType = f.readLine(); // DATA_INCLUDED

    QString names = f.readLine(); // On ignore les noms des marqueurs
    QStringList splitNames = names.split(reg);

    int i = 0;
    while (!f.atEnd())
    {
        QString line = f.readLine();
        QStringList splitLine = line.split(reg);

        int j = 0;
        //QVector<QVector<float>> lineVec;
        for (i=0; i<nbOfMarkers; i++)
        {
            Point * p = new Point(splitNames.at(j+1));
            p->x() = ((QString)splitLine.at((i*3)+2)).toDouble();
            p->y() = ((QString)splitLine.at((i*3+1)+2)).toDouble();
            p->z() = ((QString)splitLine.at((i*3+2)+2)).toDouble();
            data->addPoint(p);
            j++;
            //QVector<float> positionMarqueur(3);
            //positionMarqueur[0] = ((QString)splitLine.at((i*3)+2)).toFloat();
            //positionMarqueur[1] = ((QString)splitLine.at((i*3+1)+2)).toFloat();
            //positionMarqueur[2] = ((QString)splitLine.at((i*3+2)+2)).toFloat();
            //lineVec.push_back(positionMarqueur);
        }
        //this->data->addDataMotion(lineVec);
    }
    return true;
}

void Parser::setDataMotion(DataMotion * data)
{
    Parser::data = data;
}

DataMotion * Parser::getDataMotion()
{
    return data;
}
