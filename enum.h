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
        X = 2,
        Y = 0,
        Z = 1,
        ALL = 3
    };
};

#endif // ENUM

