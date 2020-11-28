TEMPLATE = app
TARGET = fbla_quiz
QT = core gui printsupport
CONFIG += c++17
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    question.cpp \
    questionset.cpp \
    quizwindow.cpp

#HEADERS += \

HEADERS += \
    mainwindow.h \
    question.h \
    questionset.h \
    quizwindow.h
