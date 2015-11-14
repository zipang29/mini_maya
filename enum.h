#ifndef ENUM
#define ENUM

struct Modes {
    enum Mode {
        RESIZE = 0,
        ROTATE = 1,
        TWIST = 2,
        SELECT = 3,
        EXTRUDE = 4
    };
};

struct Axes {
    enum Axe {
        UNDEFINED = -1,
        X = 0,
        Y = 1,
        Z = 2
    };
};

#endif // ENUM

