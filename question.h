#ifndef QUESTION_H
#define QUESTION_H
#include "questionanswer.h"
#include <QStringList>

class QString;

enum QuestionType { true_false, multi_choice, short_answer };

class Question
{
    public:
        QString getQuestion();
        QuestionType getType();
    protected:
        QString question;
        QuestionType type;
};

class TrueFalseQuestion : public Question {
    public:
        TrueFalseQuestion(const QString question, const bool answer);
        TrueFalseQuestion(const QString rawStr);
        bool getAnswer();
    private:
        bool answer;
};

class MultiChoiceQuestion : public Question {
    public:
        MultiChoiceQuestion(const QString question, const QString answer, const QStringList& choices);
        MultiChoiceQuestion(const QString rawStr);
        const QString getAnswer();
        const QStringList getChoices();
    private:
        QString answer;
        QStringList choices;
};

class ShortAnswerQuestion : public Question {
    public:
        ShortAnswerQuestion(const QString question, const QStringList& answers);
        ShortAnswerQuestion(const QString rawStr);
        const QStringList getAnswers();
    private:
        QStringList answers;
};

#endif // QUESTION_H
