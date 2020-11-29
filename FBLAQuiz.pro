TEMPLATE = app
TARGET = fbla_quiz
QT = core gui printsupport
CONFIG += c++17
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += src/*

HEADERS += include/*
INCLUDEPATH += include/
