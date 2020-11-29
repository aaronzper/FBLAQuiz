#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H
#include <QWidget>
#include "questionset.h"

class QuizWindow : public QWidget
{
        Q_OBJECT
    public:
        explicit QuizWindow(QuestionSet qSet, QWidget *parent = nullptr);

    signals:

};

#endif // QUIZWINDOW_H
