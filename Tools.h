#ifndef TOOLS_H
#define TOOLS_H

#include <QWidget>
#include "Enum.h"
#include "DataMotion.h"
#include "MainWindow.h"
#include <QLabel>

class MainWindow;

class Tools : public QWidget
{
    Q_OBJECT

    public:
        Tools();
        ~Tools();
        Modes::Mode detectCurrentMode(DataMotion * data, int lineNumber);
        MainWindow * getGlWidget();
        Modes::Mode nextTool(int value);
        QString modeToString();

    private:
        MainWindow * gl;
        QLabel * icon;
        Modes::Mode tmpMode;
};

#endif // TOOLS_H
