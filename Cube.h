#ifndef CUBE_H
#define CUBE_H


#include "enum.h"
#include "DataMotion.h"
#include <QVector>

class Cube
{
    public:
        Cube();
        void init();
        void draw();
        void animate();

    private:
        Actions::Mode currentMode;
        int lineNumber;
        DataMotion * data;

        //face droite
        float x_FD_HG, y_FD_HG, z_FD_HG;
        float x_FD_HD, y_FD_HD, z_FD_HD;
        float x_FD_BG, y_FD_BG, z_FD_BG;
        float x_FD_BD, y_FD_BD, z_FD_BD;
};

#endif // CUBE_H
