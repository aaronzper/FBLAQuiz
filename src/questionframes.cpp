#include "questionframes.h"
#include <QLabel>
#include <cstdio>

QuestionFrame::QuestionFrame(QString questionStr, int number, QWidget* parent) : QFrame(parent) {
    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    setFixedWidth(500);

    QFont font;
    font.setPointSize(12);

    QLabel* question = new QLabel(this);
    question->setFont(font);
    question->setText(QString("%1. %2").arg(QString::number(number), questionStr)); // Set the label to said formatted string
    question->setGeometry(5,5,495,50);
    question->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    setFixedHeight(childrenRect().height());
}

TrueFalseFrame::TrueFalseFrame(TrueFalseQuestion q, int number, QWidget* parent) : QuestionFrame(q.getQuestion(), number, parent) {
    return;
}
