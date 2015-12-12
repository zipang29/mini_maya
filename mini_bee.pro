include( ../examples.pri )

TEMPLATE = app
TARGET   = mini_bee


HEADERS  = \
    Parser.h \
    MainWindow.h \
    Cube.h \
    DataMotion.h \
    Enum.h \
    Tools.h \
    Face.h
SOURCES  = main.cpp \
    Parser.cpp \
    MainWindow.cpp \
    Cube.cpp \
    DataMotion.cpp \
    Tools.cpp \
    Face.cpp

RESOURCES += \
    ressources.qrc

LIBS += "D:/Programmes/libQGLViewer-2.6.3/examples/mini_maya/qQualisysRT/lib/Release/qQualisysRT.lib"
INCLUDEPATH += "D:/Programmes/libQGLViewer-2.6.3/examples/mini_maya/qQualisysRT/src"
