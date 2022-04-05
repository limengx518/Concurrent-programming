TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        chesspiece.cpp \
        gamepiece.cpp \
        grid.cpp \
        main.cpp

HEADERS += \
    chesspiece.h \
    gamepiece.h \
    grid.h
