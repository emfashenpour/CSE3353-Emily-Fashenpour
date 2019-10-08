TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    algofactory.cpp \
    tsp.cpp \
    readfile.cpp \
    tspgenetic.cpp \
    tsptabu.cpp

HEADERS += \
    algofactory.h \
    absalgorithm.h \
    tsp.h \
    readfile.h \
    tspgenetic.h \
    tsptabu.h
