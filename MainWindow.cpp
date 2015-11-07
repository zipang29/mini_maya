#include "MainWindow.h"
#include <math.h>
#include <stdlib.h> // RAND_MAX

using namespace qglviewer;
using namespace std;

void MainWindow::init()
{
    restoreStateFromFile();
    glDisable(GL_LIGHTING);

    this->cube = new Cube();

    glPointSize(3.0);
    setGridIsDrawn();
    //help();
    startAnimation();
}

void MainWindow::draw()
{
    this->cube->draw();
}

void MainWindow::animate()
{
    this->cube->animate();
}

QString MainWindow::helpString() const
{
    return QString();
}
