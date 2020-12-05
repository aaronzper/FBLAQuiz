#ifndef QUESTIONFRAMES_H
#define QUESTIONFRAMES_H
#include <QFrame>
#include "question.h"

class QuestionFrame : public QFrame {
        Q_OBJECT
    public:
        explicit QuestionFrame(QString questionStr, int number, QWidget* parent = nullptr);
};

class TrueFalseFrame : public QuestionFrame {
        Q_OBJECT
    public:
        explicit TrueFalseFrame(TrueFalseQuestion q, int number, QWidget* parent = nullptr);
};

class MultiChoiceFrame : public QuestionFrame {
        Q_OBJECT
    public:
        explicit MultiChoiceFrame(QWidget* parent = nullptr);
};

class ShortAnswerFrame : public QuestionFrame {
        Q_OBJECT
    public:
        explicit ShortAnswerFrame(QWidget* parent = nullptr);
};

class MultiAnswerFrame : public QuestionFrame {
        Q_OBJECT
    public:
        explicit MultiAnswerFrame(QWidget* parent = nullptr);
};

#endif // QUESTIONFRAMES_H
