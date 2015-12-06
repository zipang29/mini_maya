#include "Tools.h"
#include <QDesktopWidget>
#include "MainWindow.h"
#include <QSlider>

Tools * Tools::t = NULL;

Tools::Tools()
{
    ui.setupUi(this);
    this->setWindowTitle("Outils");
    int width = QApplication::desktop()->screenGeometry().width();
    this->setGeometry(0, 30, width, 150);
    this->setFixedSize(width, 150);
    connect(ui.selecteur, SIGNAL(valueChanged(int)), this, SLOT(nextTool(int)));
    //connect(this, SIGNAL(changeTool()), this, SLOT(nextTool()));
}

void Tools::nextTool(int value)
{
    if (value == 0)
        ui.icon->setPixmap(QPixmap(":/outils/redimention.png"));
    if (value == 1)
        ui.icon->setPixmap(QPixmap(":/outils/rotation.png"));
    if (value == 2)
        ui.icon->setPixmap(QPixmap(":/outils/twist.png"));
    if (value == 3)
        ui.icon->setPixmap(QPixmap(":/outils/selection.png"));
    if (value == 4)
        ui.icon->setPixmap(QPixmap(":/outils/extrude.png"));
}

Modes::Mode Tools::detectCurrentMode(DataMotion * data, QVector<QVector<float>> lineStart, QVector<QVector<float>> lineEnd)
{
    Modes::Mode result = Modes::PAUSE;

    QVector<float> poignetD = lineStart.at(2);
    QVector<float> doigtsD = lineStart.at(0);

    QVector<float> poignetG = lineStart.at(5);
    QVector<float> doigtsG = lineStart.at(3);

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
            double distance = data->calculDistance3D(&doigtsG, &doigtsD);
            qDebug() << "Distance : " << distance;
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
