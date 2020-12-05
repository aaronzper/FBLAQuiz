#include "quizwindow.h"
#include "questionset.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "questionframes.h"

QuizWindow::QuizWindow(QuestionSet qSet, QWidget *parent) : QWidget(parent)
{
    QWidget* inner = new QWidget(this);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(inner);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout* layout = new QVBoxLayout(inner);
    for(int i = 1; i <= 100; i++) {
        TrueFalseFrame* frame = new TrueFalseFrame(TrueFalseQuestion("Is this an example question?", true), i, this);
        layout->addWidget(frame);
    }
}

void QuizWindow::resizeEvent(QResizeEvent* event) {
    // Resize scrollbars to fit the whole window whenever it's size changes
    scrollArea->setFixedSize(geometry().size());
}
