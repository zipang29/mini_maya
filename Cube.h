#ifndef CUBE_H
#define CUBE_H


#include "enum.h"

class Cube
{
    public:
        Cube();
        void init();
        void draw();
        void animate();

    private:
        Actions::Mode currentMode;
};

#endif // CUBE_H
