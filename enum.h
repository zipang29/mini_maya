#ifndef ENUM
#define ENUM

struct Actions {
    enum Mode {
        RESIZE = 0,
        ROTATE = 1,
        TWIST = 2,
        SELECT = 3,
        EXTRUDE = 4
    };
};

#endif // ENUM

