TEMPLATE = app
TARGET = fbla_quiz
QT = core gui printsupport
CONFIG += c++17
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/question.cpp \
    src/questionset.cpp \
    src/quizwindow.cpp

#HEADERS += \

HEADERS += \
    include/mainwindow.h \
    include/question.h \
    include/questionset.h \
    include/quizwindow.h
