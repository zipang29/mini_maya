#include "Tools.h"
#include <QDesktopWidget>
#include "MainWindow.h"
#include <QSlider>
#include <QGridLayout>

Tools::Tools() : QWidget()
{
    setWindowState(Qt::WindowMaximized);
    setWindowTitle("Mini bee");

    icon = new QLabel();
    icon->setPixmap(QPixmap(":/outils/redimention.png"));
    icon->setMaximumHeight(150);

    gl = new MainWindow(this);

    QGridLayout * mainLayout = new QGridLayout();
    mainLayout->addWidget(icon, 0, 2);
    mainLayout->addWidget(gl, 1, 0, 1, 4);

    setLayout(mainLayout);
}

Modes::Mode Tools::nextTool(int value)
{
    Modes::Mode mode = Modes::PAUSE;
    if (value == 0)
    {
        icon->setPixmap(QPixmap(":/outils/redimention.png"));
        mode = Modes::RESIZE;
    }
    else if (value == 1)
    {
        icon->setPixmap(QPixmap(":/outils/rotation.png"));
        mode = Modes::ROTATE;
    }
    else if (value == 2)
    {
        icon->setPixmap(QPixmap(":/outils/twist.png"));
        mode = Modes::TWIST;
    }
    else if (value == 3)
    {
        icon->setPixmap(QPixmap(":/outils/selection.png"));
        mode = Modes::SELECT;
    }
    else if (value == 4)
    {
        icon->setPixmap(QPixmap(":/outils/extrude.png"));
        mode = Modes::EXTRUDE;
    }
    return mode;
}

Modes::Mode Tools::detectCurrentMode(DataMotion * data, int lineNumber)
{
    Modes::Mode result = Modes::PAUSE;

    Point * poignetD = data->getPoint(lineNumber, "PR");
    Point * doigtsD = data->getPoint(lineNumber, "DR");

    Point * poignetG = data->getPoint(lineNumber, "PL");
    Point * doigtsG = data->getPoint(lineNumber, "DL");

    if (poignetD == NULL || doigtsD == NULL || poignetG == NULL || doigtsG == NULL)
        return Modes::PAUSE;

    double distanceMainDroite = data->calculDistance3D(poignetD, doigtsD);
    double distanceMainGauche = data->calculDistance3D(poignetG, doigtsG);

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
            double distance = data->calculDistance3D(doigtsG, doigtsD);
            int max = 5;
            int value = qRound((distance * max) / 1000);
            if (value > 5)
                value = 5;
            if (value < 0)
                value = 0;
            result = nextTool(value);
        }
    }

    return result;
}

MainWindow * Tools::getGlWidget()
{
    return gl;
}

Tools::~Tools()
{
}
