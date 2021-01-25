#include <QApplication>
#include "mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include "quizgeneration.h"

void MessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
	QMessageBox* box = new QMessageBox();

	// Display an appropriate message box
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
	QString arg_str = argv[1]; // Convert to QString so we can compare it below (also because I couldn't get strcmp() to work)
	if(arg_str == "generate") {
		generateQuiz(); // Go into the CLI fblaquiz generation tool
	}
	else {
		qInstallMessageHandler(MessageHandler); // Sets the message handler to be the function above. (So that function is called whenever Qt's error/warning/etc functions are called)

		try {
			QApplication a(argc, argv);

			MainWindow win;
			win.show(); // Shows the main window

			return a.exec();
		}
		catch (std::runtime_error e) { // If an uncaught std::runtime_error is thrown (which is how I indicate errors in this) print it and abort.
			std::cerr << "Fatal Error: " << e.what() << std::endl;
			abort();
		}
	}

}
