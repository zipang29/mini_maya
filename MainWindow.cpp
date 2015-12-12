#include "MainWindow.h"
#include <math.h>
#include <stdlib.h> // RAND_MAX
#include <QDebug>
#include <QMessageBox>

using namespace qglviewer;
using namespace std;

MainWindow::MainWindow(QWidget * parent) : QGLViewer()
{
    tools = (Tools*) parent;
}

void MainWindow::init()
{
    restoreStateFromFile();
    glDisable(GL_LIGHTING);

    setMouseBinding(Qt::NoModifier, Qt::RightButton, SELECT);// Définit le bouton de sélection d'une face

    this->cube = new Cube(tools, this);

    glPointSize(3.0);
    setGridIsDrawn(false);
    setFPSIsDisplayed(true);
    //help();
    startAnimation();
}

void MainWindow::draw()
{
    this->cube->draw(selectedName());
}

void MainWindow::drawWithNames()
{
    this->cube->drawWithNames();
}

void MainWindow::animate()
{
    this->cube->setCursor(this->window()->cursor());
    this->cube->animate();
}

void MainWindow::postSelection(const QPoint& point)
{
    camera()->convertClickToLine(point, orig, dir);

    bool found;
    selectedPoint = camera()->pointUnderPixel(point, found);
    selectedPoint -= 0.01f*dir;
}

QString MainWindow::helpString() const
{
    return QString();
}
