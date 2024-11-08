QT       += core gui multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boss.cpp \
    enemy.cpp \
    flag.cpp \
    game.cpp \
    gamebossfight.cpp \
    gamewindow.cpp \
    main.cpp \
    platform.cpp \
    player.cpp \
    powerup.cpp \
    trap.cpp

HEADERS += \
    boss.h \
    enemy.h \
    flag.h \
    game.h \
    gamebossfight.h \
    gamewindow.h \
    platform.h \
    player.h \
    powerup.h \
    trap.h \
    typeDef.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
