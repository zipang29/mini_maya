#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T16:00:53
#
#-------------------------------------------------

TARGET = mini_maya
CONFIG *= qt opengl release
QT *= opengl xml

SOURCES += main.cpp\
    Parser.cpp \
    MainWindow.cpp

HEADERS  += \
    Constantes.h \
    Parser.h \
    MainWindow.h

# Windows
INCLUDEPATH *= D:/Programmes/libQGLViewer-2.6.3
LIBS *= -LD:/Programmes/libQGLViewer-2.6.3/QGLViewer -lQGLViewer2

INCLUDEPATH += "D:/Programmes/glew-1.13.0/include"
LIBS += -L"D:/Programmes/glew-1.13.0/lib/Release/Win32" -lglew32
