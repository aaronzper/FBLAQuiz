#ifndef QUESTIONSET_H
#define QUESTIONSET_H
#include <vector>
#include <QString>
#include <variant>
#include "question.h"

typedef std::variant<std::monostate, TrueFalseQuestion, MultiChoiceQuestion, ShortAnswerQuestion> QuestionContainer;

class QuestionSet
{
    public:
        QuestionSet(QString path);
        QuestionContainer operator[](int i);
        QuestionContainer getRandomQuestion();
        int count();
    private:
        std::vector<QuestionContainer> questions;
};

#endif // QUESTIONSET_H
