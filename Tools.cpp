#include "Tools.h"
#include <QDesktopWidget>
#include "MainWindow.h"

Tools * Tools::t = NULL;

Tools::Tools()
{
    ui.setupUi(this);
    this->setWindowTitle("Outils");
    int width = QApplication::desktop()->screenGeometry().width();
    this->setGeometry(0, 30, width, 150);
    this->setFixedSize(width, 150);
    //connect(this, SIGNAL(changeTool()), this, SLOT(nextTool()));
}

void Tools::nextTool()
{
    qDebug() << "ok==================================================";
}

Modes::Mode Tools::detectCurrentMode(DataMotion * data, QVector<QVector<float>> line)
{
    Modes::Mode result = Modes::PAUSE;

    QVector<float> poignetD = line.at(2);
    QVector<float> doigtsD = line.at(0);

    QVector<float> poignetG = line.at(5);
    QVector<float> doigtsG = line.at(3);

    double distanceMainDroite = data->calculDistance3D(&poignetD, &doigtsD);
    double distanceMainGauche = data->calculDistance3D(&poignetG, &doigtsG);

    if (distanceMainGauche > 80 && distanceMainGauche < 100)
    {
        if (distanceMainDroite > 80 && distanceMainDroite < 100)
        {
            result = Modes::PAUSE;
            qDebug() << "Mode : PAUSE";
        }
        else
        {
            result = Modes::CHANGE_TOOL;
            qDebug() << "Mode : CHANGE_TOOL";
        }
    }

    return result;
}

Tools * Tools::getInstance()
{
    if (Tools::t == NULL)
    {
        Tools::t = new Tools();
    }
    return Tools::t;
}
