#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include "DataMotion.h"

class Parser
{
    public:
        Parser(QString file);
        bool parse();
        static DataMotion * getDataMotion();

    private:
        QString file;
        static DataMotion * data;
};

#endif // PARSER_H
