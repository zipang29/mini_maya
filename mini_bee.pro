# The <code>animate()</code> function illustrated by a water particle simulation.

# When animation is activated (the Return key toggles animation), the <code>animate()</code> and
# then the <code>draw()</code> functions are called in an infinite loop.

# You can tune the frequency of your animation (default is 25Hz) using
# <code>setAnimationInterval()</code>. The frame rate will then be fixed, provided that your
# animation loop function is fast enough.

TEMPLATE = app
TARGET   = mini_bee

HEADERS  = \
    Parser.h \
    MainWindow.h \
    Cube.h \
    DataMotion.h \
    Enum.h
SOURCES  = main.cpp \
    Parser.cpp \
    MainWindow.cpp \
    Cube.cpp \
    DataMotion.cpp

include( ../examples.pri )
