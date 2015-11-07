#include "Parser.h"
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <Constantes.h>
#include <QVector>

Parser::Parser(QString file)
{
    this->file = file;
}

void Parser::parse()
{
    QFile f(this->file);
    if (!f.open(QIODevice::ReadOnly))
        qCritical() << "Impossible d'ouvrir le fichier " << this->file;

    QString strNbOfFrames = f.readLine();
    int nbOfFrames = ((QString)(strNbOfFrames.split(SEPARATOR).at(1))).toInt();

    QString strNbOfCameras = f.readLine();
    int nbOfCameras = ((QString)(strNbOfCameras.split(SEPARATOR).at(1))).toInt();

    QString strNbOfMarkers = f.readLine();
    int nbOfMarkers = ((QString)(strNbOfMarkers.split(SEPARATOR).at(1))).toInt();

    QString strFrequency = f.readLine();
    int frequency = ((QString)(strFrequency.split(SEPARATOR).at(1))).toInt();

    QString strNbOfAnalog = f.readLine();
    int nbOfAnalog = ((QString)(strNbOfAnalog.split(SEPARATOR).at(1))).toInt();

    QString strAnalogFrequency = f.readLine();
    int analogFrequency = ((QString)(strNbOfAnalog.split(SEPARATOR).at(1))).toInt();

    QString description = f.readLine();

    QString timetamp = f.readLine();

    QString dataType = f.readLine(); // DATA_INCLUDED

    f.readLine(); // On ignore les noms des marqueurs

    int i = 0;
    while (!f.atEnd())
    {
        QString line = f.readLine();
        QStringList splitLine = line.split(SEPARATOR);
        for (i=0; i<nbOfMarkers; i++)
        {
            QVector<float> positionMarqueur(3);
            positionMarqueur[0] = ((QString)splitLine.at(i*3)).toFloat();
            positionMarqueur[1] = ((QString)splitLine.at(i*3+1)).toFloat();
            positionMarqueur[2] = ((QString)splitLine.at(i*3+2)).toFloat();
        }
    }
}
