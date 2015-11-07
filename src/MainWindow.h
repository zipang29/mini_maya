#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGLViewer/qglviewer.h>

using namespace qglviewer;

class MainWindow : public QGLViewer
{
    protected:
      virtual void draw();
      virtual void init();
      virtual void animate();
      virtual QString helpString() const;
};

#endif // MAINWINDOW_H
