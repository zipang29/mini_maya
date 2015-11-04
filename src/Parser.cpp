#include "Parser.h"
#include <QFile>

Parser::Parser(QString file)
{
    this->file = file;
}

void Parser::parse()
{
    QFile f(this->file);
    if (!f.open(QIODevice::ReadOnly))
        qCritical() << "Impossible d'ouvrir le fichier " << this->file;

}
