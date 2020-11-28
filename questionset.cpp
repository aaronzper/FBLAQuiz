#include "questionset.h"
#include <QFile>
#include <QTextStream>
#include <vector>
#include <iostream>
#include "question.h"
#include <stdlib.h>
#include <variant>

QuestionSet::QuestionSet(QString path)
{
    QFile file(path);
    if(!file.exists())
        throw std::runtime_error("Question file not found");

    file.open(QIODevice::ReadOnly);
    QTextStream txt(&file);

    for(QString line = txt.readLine(); !line.isNull(); line = txt.readLine()) {
        int type = line[0].digitValue();
        line.remove(0,1); // remove first char (the question type) since the question constructors dont need that info
        QuestionContainer q;

        // Heap-allocate pointers to each question for the array, so I can cast them from the base Question class to the type-specific question classes (TrueFalseQuestion, etc)
        switch(type) {
            case 0:     // True/false
                q = TrueFalseQuestion(line);
                break;
            case 1:     // Multi-choice
                q = MultiChoiceQuestion(line);
                break;
            case 2:     // Short answer
                q = ShortAnswerQuestion(line);
                break;
            default:    // Invalid type (including -1, for when its not even an int)
                throw std::runtime_error("Malformed question file");
                break;
        }

        questions.push_back(q);
    }
}

QuestionContainer QuestionSet::operator[](int i) {
    return questions[i];
}

QuestionContainer QuestionSet::getRandomQuestion() {
    return questions[rand() % questions.size()];
}

int QuestionSet::count() {
    return questions.size();
}
