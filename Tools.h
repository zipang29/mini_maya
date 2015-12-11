#ifndef TOOLS_H
#define TOOLS_H

#include <QWidget>
#include "ui_tools.h"
#include "Enum.h"
#include "DataMotion.h"
#include "MainWindow.h"

class MainWindow;

class Tools : public QWidget
{
    Q_OBJECT

    public:
        Tools();
        ~Tools();
        Modes::Mode detectCurrentMode(DataMotion * data, int lineNumber, Modes::Mode currentMode);
        //static Tools * getInstance();
        MainWindow * getGlWidget();

    public Q_SLOTS:
        void nextTool(int value);

    private:
        MainWindow * gl;
        QLabel * icon;
        //static Tools * t;
};

#endif // TOOLS_H
