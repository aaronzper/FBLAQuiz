#ifndef QUESTIONSET_H
#define QUESTIONSET_H
#include <vector>
#include <QString>
#include "question.h"
#include "questioncontainer.h"

class QuestionSet {
    public:
        QuestionSet(QString path);
        QuestionContainer operator[](int i);
        QuestionContainer getRandomQuestion();
        int count();
    private:
        std::vector<QuestionContainer> questions;
};

#endif // QUESTIONSET_H
