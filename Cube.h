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
        /*float x_FD_HG, y_FD_HG, z_FD_HG;
        float x_FD_HD, y_FD_HD, z_FD_HD;
        float x_FD_BG, y_FD_BG, z_FD_BG;
        float x_FD_BD, y_FD_BD, z_FD_BD;*/

        // Correspond aux vertex du cube. On part de la face avant dans le sens des aiguilles d'une montre en partant du point en haut à gauche de la
        // face du devant du cube puise on fait pareille pour la face arrière
        float x_A, y_A, z_A;
        float x_B, y_B, z_B;
        float x_C, y_C, z_C;
        float x_D, y_D, z_D;
        float x_E, y_E, z_E;
        float x_F, y_F, z_F;
        float x_G, y_G, z_G;
        float x_H, y_H, z_H;
};

#endif // CUBE_H
