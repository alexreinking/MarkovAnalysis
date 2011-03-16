# -------------------------------------------------
# Project created by QtCreator 2011-03-12T15:57:19
# -------------------------------------------------
QT += core
QT -= gui
TARGET = MarkovAnalyzer
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    tftestgenerator.cpp \
    tfstate.cpp \
    tfreader.cpp \
    randomgenerator.cpp
HEADERS += MarkovGenerator.h \
    State.h \
    StateReader.h \
    tftestgenerator.h \
    tfstate.h \
    tfreader.h \
    randomgenerator.h
