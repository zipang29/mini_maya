#ifndef PARSER_H
#define PARSER_H

#include <QString>

class Parser
{
    public:
        Parser(QString file);
        void parse();

    private:
        QString file;
};

#endif // PARSER_H
