#include "MainWindow.h"

MainWindow::MainWindow()
{

}

void MainWindow::initializeGL()
{
    this->gl = new QOpenGLFunctions(this->context());
}

void MainWindow::resizeGL()
{

}

void MainWindow::paintGL()
{
    const qreal retinaScale = devicePixelRatio();
    gl->glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    gl->glClear(GL_COLOR_BUFFER_BIT);
}

