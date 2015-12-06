#ifndef TOOLS_H
#define TOOLS_H

#include <QtWidgets>
#include "ui_tools.h"
#include "Enum.h"
#include "DataMotion.h"

class Tools : public QWidget
{
    Q_OBJECT

    public:
        Tools();
        Modes::Mode detectCurrentMode(DataMotion * data, QVector<QVector<float>> lineStart, QVector<QVector<float>> lineEnd);
        static Tools * getInstance();

    public Q_SLOTS:
        void nextTool();

    private:
        Ui::tools ui;
        //DataMotion * data;
        static Tools * t;

};

#endif // TOOLS_H
