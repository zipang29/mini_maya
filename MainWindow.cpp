#include "MainWindow.h"
#include <math.h>
#include <stdlib.h> // RAND_MAX

using namespace qglviewer;
using namespace std;

void MainWindow::init()
{
    restoreStateFromFile();
    glDisable(GL_LIGHTING);



    glPointSize(3.0);
    setGridIsDrawn();
    //help();
    startAnimation();
}

void MainWindow::draw()
{
    glBegin(GL_QUADS);
        glColor3ub(255,0,0); //face rouge
        glVertex3d(1,1,1);
        glVertex3d(1,1,-1);
        glVertex3d(-1,1,-1);
        glVertex3d(-1,1,1);

        glColor3ub(0,255,0); //face verte
        glVertex3d(1,-1,1);
        glVertex3d(1,-1,-1);
        glVertex3d(1,1,-1);
        glVertex3d(1,1,1);

        glColor3ub(0,0,255); //face bleue
        glVertex3d(-1,-1,1);
        glVertex3d(-1,-1,-1);
        glVertex3d(1,-1,-1);
        glVertex3d(1,-1,1);

        glColor3ub(255,255,0); //face jaune
        glVertex3d(-1,1,1);
        glVertex3d(-1,1,-1);
        glVertex3d(-1,-1,-1);
        glVertex3d(-1,-1,1);

        glColor3ub(0,255,255); //face cyan
        glVertex3d(1,1,-1);
        glVertex3d(1,-1,-1);
        glVertex3d(-1,-1,-1);
        glVertex3d(-1,1,-1);

        glColor3ub(255,0,255); //face magenta
        glVertex3d(1,-1,1);
        glVertex3d(1,1,1);
        glVertex3d(-1,1,1);
        glVertex3d(-1,-1,1);
    glEnd();
}

void MainWindow::animate()
{

}

QString MainWindow::helpString() const
{
    return QString();
}
