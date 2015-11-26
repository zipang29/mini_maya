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
        X = 1,
        Y = 2,
        Z = 0,
        ALL = 3
    };
};

#endif // ENUM

