#include "MainWindow.h"
#include <math.h>
#include <stdlib.h> // RAND_MAX
#include <QDebug>

using namespace qglviewer;
using namespace std;

void MainWindow::init()
{
    restoreStateFromFile();
    glDisable(GL_LIGHTING);

    this->cube = new Cube();

    glPointSize(3.0);
    setGridIsDrawn(false);
    //help();
    startAnimation();
}

void MainWindow::draw()
{
    this->cube->draw();
}

void MainWindow::animate()
{
    this->cube->setCursor(this->window()->cursor());
    this->cube->animate();
}

QString MainWindow::helpString() const
{
    return QString();
}
