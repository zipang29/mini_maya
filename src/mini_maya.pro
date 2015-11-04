# The <code>animate()</code> function illustrated by a water particle simulation.

# When animation is activated (the Return key toggles animation), the <code>animate()</code> and
# then the <code>draw()</code> functions are called in an infinite loop.

# You can tune the frequency of your animation (default is 25Hz) using
# <code>setAnimationInterval()</code>. The frame rate will then be fixed, provided that your
# animation loop function is fast enough.

TEMPLATE = app
QT += opengl xml

HEADERS  = \
    Parser.h


SOURCES  = \
    main.cpp \
    Parser.cpp

#include(D:\Programmes\libQGLViewer-2.6.3\examples\examples.pri )

win32:LIBS += "D:\Programmes\libQGLViewer-2.6.3\QGLViewer\QGLViewer2.lib"
win32:LIBS += "D:\Programmes\libQGLViewer-2.6.3\QGLViewer\QGLViewerd2.lib"

INCLUDEPATH += "D:\Programmes\libQGLViewer-2.6.3\QGLViewer"
DEPENDPATH += "D:\Programmes\libQGLViewer-2.6.3\QGLViewer"

win32:INCLUDEPATH += "D:/Programmes/glew-1.13.0/include"
win32:LIBS += -L"D:/Programmes/glew-1.13.0/lib/Release/Win32" -lglew32
