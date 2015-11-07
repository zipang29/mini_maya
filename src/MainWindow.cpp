#include "MainWindow.h"

void MainWindow::init()
{
    restoreStateFromFile();
    glDisable(GL_LIGHTING);

    glPointSize(3.0);
    setGridIsDrawn();
    help();
    startAnimation();
}

void MainWindow::draw()
{
    glBegin(GL_QUADS);
        glNormal3d(-1, 0, 0);
        glVertex3d(-1, 1, 1);
        glVertex3d(-1, -1, 1);
        glVertex3d(-1, -1, -1);
        glVertex3d(-1, 1, -1);
    glEnd();
}

void MainWindow::animate()
{

}

QString MainWindow::helpString() const
{
    return QString();
}

