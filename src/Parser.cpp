#include "Parser.h"
#include <QFile>
#include <QDebug>

Parser::Parser(QString file)
{
    this->file = file;
}

void Parser::parse()
{
    QFile f(this->file);
    if (!f.open(QIODevice::ReadOnly))
        qCritical() << "Impossible d'ouvrir le fichier " << this->file;
    QList<QByteArray> nbOfFrames = f.readLine().split(' ');
    qDebug() << nbOfFrames;
    QString nbOfCameras = f.readLine();
    QString nbOfMarkers = f.readLine();
    QString frequency = f.readLine();
    QString nbOfAnalog = f.readLine();
    QString analogFrequency = f.readLine();
    QString description = f.readLine();
    QString timetamp = f.readLine();
    QString dataType = f.readLine(); // DATA_INCLUDED
    f.readLine(); // On ignore le nom des marqueurs

    while (!f.atEnd())
    {

    }
}
