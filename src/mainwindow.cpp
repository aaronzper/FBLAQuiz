#include "mainwindow.h"
#include "questionset.h"
#include "quizwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QErrorMessage>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	setFixedSize(400, 155);

	QLabel* title = new QLabel("FBLA Quiz Program", this);
	title->setGeometry(0, 0, width(), 60);
	title->setAlignment(Qt::AlignCenter);
	QFont font;
	font.setPointSize(24);
	title->setFont(font);

	QPushButton* buttonStartQuiz = new QPushButton("Start Quiz",this);
	buttonStartQuiz->setGeometry(20, 60, 360, 40);
	connect(buttonStartQuiz, SIGNAL(clicked()), this, SLOT(buttonStartQuizClicked()));

	QPushButton* buttonAbout = new QPushButton("About",this);
	buttonAbout->setGeometry(20, 105, 177, 30);
	connect(buttonAbout, SIGNAL(clicked()), this, SLOT(buttonAboutClicked()));

	QPushButton* buttonHelp = new QPushButton("Help",this);
	buttonHelp->setGeometry(203, 105, 177, 30);
	connect(buttonHelp, SIGNAL(clicked()), this, SLOT(buttonHelpClicked()));
}

void MainWindow::buttonStartQuizClicked() {
	QString quizPath = QFileDialog::getOpenFileName(this, tr("Open Quiz File"), "", tr("Quiz Files (*.fblaquiz)"));

	try {
		QuestionSet qSet(quizPath);
		QuizWindow* win = new QuizWindow(qSet);
		hide();
		win->show();
	}
	catch(std::runtime_error e) {
		qCritical("%s", e.what());
	}
}

void MainWindow::buttonAboutClicked() {
	throw std::runtime_error("Foo");
}

void MainWindow::buttonHelpClicked() {
	return;
}

