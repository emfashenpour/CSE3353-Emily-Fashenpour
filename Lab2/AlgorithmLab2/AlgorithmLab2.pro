TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    search.cpp \
    searchalgorithm.cpp \
    adjlist.cpp \
    adjmatrix.cpp \
    node.cpp \
    connect.cpp \
    datacreator.cpp \
    sort.cpp \
    sortalgorithm.cpp

HEADERS += \
    algorithm.h \
    search.h \
    searchalgorithm.h \
    graph.h \
    adjlist.h \
    adjmatrix.h \
    node.h \
    connect.h \
    datacreator.h \
    sort.h \
    sortalgorithm.h
