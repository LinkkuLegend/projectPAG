SOURCES += \
    main.cpp \
    mainwindow.cpp \
    viewer.cpp \
    ball.cpp \
    boundingbox.cpp \
    maths.cpp \
    mesh.cpp \
    meshloader.cpp \
    octree.cpp



QT *= xml opengl widgets gui


win32 {

    INCLUDEPATH += C:/Qt/libQGLViewer-2.5.2

    CONFIG(debug, debug|release){
        LIBS += -LC:/Qt/libQGLViewer-2.5.2/QGLViewer/debug \
            -lQGLViewerd2
    }

    CONFIG(release, debug|release){
        LIBS += -LC:/Qt/libQGLViewer-2.5.2/QGLViewer/release \
            -lQGLViewer2
    }
}



macx|darwin-g++ {

    INCLUDEPATH *= /Users/dsdg/Library/Frameworks/QGLViewer.framework/Versions/2/Headers

    LIBS *= -F/Users/dsdg/Library/Frameworks/ -framework QGLViewer
}

HEADERS += \
    mainwindow.h \
    viewer.h \
    ball.h \
    boundingbox.h \
    maths.h \
    mesh.h \
    meshloader.h \
    octree.h

FORMS += \
    mainwindow.ui
