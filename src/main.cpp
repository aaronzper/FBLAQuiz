#include <QApplication>
#include "mainwindow.h"
#include <iostream>
#include <QMessageBox>

void MessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    QMessageBox* box = new QMessageBox();

    switch(type) {
    case QtDebugMsg:
        box->setIcon(QMessageBox::Icon::Information);
        box->setWindowTitle("Debug");
        break;
    case QtInfoMsg:
        box->setIcon(QMessageBox::Icon::Information);
        box->setWindowTitle("Info");
        break;
    case QtWarningMsg:
        box->setIcon(QMessageBox::Icon::Warning);
        box->setWindowTitle("Warning");
        break;
    case QtCriticalMsg:
        box->setIcon(QMessageBox::Icon::Critical);
        box->setWindowTitle("Error");
        break;
    case QtFatalMsg:
        box->setIcon(QMessageBox::Icon::Critical);
        box->setWindowTitle("Fatal Error");
    }
    box->setText(msg);
    box->show();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(MessageHandler);

    try {
        QApplication a(argc, argv);

        MainWindow win;
        win.show();

        return a.exec();
    }
    catch (std::runtime_error e) {
        std::cerr << "Fatal Error: " << e.what() << std::endl;
        abort();
    }
    catch (std::exception e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        abort();
    }
}
