#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include "DataMotion.h"

class Parser
{
    public:
        Parser(QString file);
        void parse();

    private:
        QString file;
        DataMotion data;
};

#endif // PARSER_H
