#ifndef ENUM
#define ENUM

struct ETools {
    enum ETool {
        RESIZE = 0,
        ROTATE = 1,
        TWIST = 2,
        SELECT = 3,
        EXTRUDE = 4
    };
};

struct Modes {
    enum Mode {
        RESIZE = 0,
        ROTATE = 1,
        TWIST = 2,
        SELECT = 3,
        EXTRUDE = 4,
        CHANGE_TOOL = 5,
        PAUSE = 6
    };
};

// L'énumération doit être mappée de façon à ce que les axes correspondent à ceux de la motion capture
struct Axes {
    enum Axe {
        UNDEFINED = -1,
        X = 1,
        Y = 0,
        Z = 2,
        ALL = 3
    };
};

struct Coordonnees {
    enum Coordonnee {
        X = 0,
        Y = 1,
        Z = 2
    };
};

#endif // ENUM

