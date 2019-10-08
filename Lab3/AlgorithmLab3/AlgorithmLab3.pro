TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    tspalgorithm.cpp \
    readfile.cpp \
    tsp.cpp \
    algofactory.cpp

HEADERS += \
    tspalgorithm.h \
    readfile.h \
    absalgorithm.h \
    tsp.h \
    algofactory.h
