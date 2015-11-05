#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>

class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

    public:
        explicit MainWindow();
        void initializeGL();
        void resizeGL();
        void paintGL();

    private:
        QOpenGLFunctions * gl;
};

#endif // MAINWINDOW_H
