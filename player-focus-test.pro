QT += gui qml widgets

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        compass.cpp \
        gamecontrol.cpp \
        global.cpp \
        herd.cpp \
        kdtree.cpp \
        main.cpp \
        mygameview.cpp \
        player.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    compass.h \
    gamecontrol.h \
    global.h \
    herd.h \
    kdtree.h \
    mygameview.h \
    player.h
