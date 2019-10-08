TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    algofactory.cpp \
    readfile.cpp \
    tsp.cpp \
    tspswarm.cpp \
    tspannealing.cpp \
    particle.cpp

HEADERS += \
    algofactory.h \
    absalgorithm.h \
    readfile.h \
    tsp.h \
    tspswarm.h \
    tspannealing.h \
    particle.h
