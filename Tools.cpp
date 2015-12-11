#include "Tools.h"
#include <QDesktopWidget>
#include "MainWindow.h"
#include <QSlider>

//Tools * Tools::t = NULL;

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

    //connect(this, SIGNAL(valueChanged(int)), this, SLOT(nextTool(int)));
    //connect(this, SIGNAL(valueChanged(int)), ui.selecteur, SLOT(setValue(int)));
    //connect(this, SIGNAL(valueChanged(int)), ui.selecteur, SLOT(setValue(int)));
    //connect(this, SIGNAL(changeTool()), this, SLOT(nextTool()));
}

void Tools::nextTool(int value)
{
    qDebug() << "ok" << value;
    if (value == 0)
        icon->setPixmap(QPixmap(":/outils/redimention.png"));
    else if (value == 1)
        icon->setPixmap(QPixmap(":/outils/rotation.png"));
    else if (value == 2)
        icon->setPixmap(QPixmap(":/outils/twist.png"));
    else if (value == 3)
        icon->setPixmap(QPixmap(":/outils/selection.png"));
    else if (value == 4)
        icon->setPixmap(QPixmap(":/outils/extrude.png"));
    else
        qDebug() << "erreur";
}

Modes::Mode Tools::detectCurrentMode(DataMotion * data, int lineNumber, Modes::Mode currentMode)
{
    Modes::Mode result = Modes::PAUSE;

    Point * poignetD = data->getPoint(lineNumber, "PR");
    Point * doigtsD = data->getPoint(lineNumber, "DR");

    Point * poignetG = data->getPoint(lineNumber, "PL");
    Point * doigtsG = data->getPoint(lineNumber, "DL");

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
            nextTool(value);
        }
    }

    return result;
}

MainWindow * Tools::getGlWidget()
{
    return gl;
}

/*Tools * Tools::getInstance()
{
    if (Tools::t == NULL)
    {
        Tools::t = new Tools();
    }
    return Tools::t;
}*/

Tools::~Tools()
{
}
