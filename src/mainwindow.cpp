#include "mainwindow.h"
#include "questionset.h"
#include "quizwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QErrorMessage>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400, 165);

    QLabel* title = new QLabel("FBLA Quiz Program", this);
    title->setGeometry(0, 0, width(), 60);
    title->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPointSize(24);
    title->setFont(font);

    QPushButton* buttonStartQuiz = new QPushButton("Start Quiz",this);
    buttonStartQuiz->setGeometry(20, 60, 360, 40);
    connect(buttonStartQuiz, SIGNAL(clicked()), this, SLOT(buttonStartQuizClicked()));

    QPushButton* buttonCreateQuiz = new QPushButton("Create Quiz",this);
    buttonCreateQuiz->setGeometry(20, 105, 177, 40);
    connect(buttonCreateQuiz, SIGNAL(clicked()), this, SLOT(buttonCreateQuizClicked()));

    QPushButton* buttonEditQuiz = new QPushButton("Edit Quiz",this);
    buttonEditQuiz->setGeometry(203, 105, 177, 40);
    connect(buttonEditQuiz, SIGNAL(clicked()), this, SLOT(buttonEditQuizClicked()));
}

void MainWindow::buttonStartQuizClicked() {
    QString quizPath = QFileDialog::getOpenFileName(this, tr("Open Quiz File"), "", tr("Quiz Files (*.fblaquiz)"));

    try {
        QuestionSet qSet(quizPath);
        QuizWindow* win = new QuizWindow(qSet);
        win->show();
        hide();
    }
    catch(std::runtime_error e) {
        qCritical(e.what());
    }
}

void MainWindow::buttonCreateQuizClicked() {
    throw std::runtime_error("Foo");
}

void MainWindow::buttonEditQuizClicked() {
    return;
}

