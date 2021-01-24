#include "mainwindow.h"
#include "questionset.h"
#include "quizwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QErrorMessage>
#include <QMessageBox>

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
	QMessageBox msgBox;
	msgBox.setText("FBLA Coding and Programming submission by Aaron Perrotta.\n\nThis project makes use of the Qt5 framework, which is licensed under the LGPLv3. For further information, see the LICENSE file in the root directory of the source code.");

	msgBox.exec();
}

void MainWindow::buttonHelpClicked() {
	QMessageBox msgBox;
	msgBox.setText("To begin, click the \"Start Quiz\" button. Then select the fblaquiz file you'd like to use. The program will then display 5 questions randomly chosen from that quiz set.\n\nFor true-false and multi-choice questions (indicated by the radio buttons), only one answer is correct. For multi-answer questions (indicated by the check boxes), multiple answers may be correct. For short-answer questions (indicated by the text input box), one or more answers may be correct. The program will also indicate if the question is case-sensitive.\n\nAfter you finish the quiz, click the \"Submit\" button and the program will show you which questions you got correct, the correct answer for questions you got wrong, and yor final score. Clicking the \"Print\" button after that will open up your system print dialog to print a report on how you did.");

	msgBox.exec();
}

