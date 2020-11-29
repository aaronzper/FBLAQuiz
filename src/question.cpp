#include "question.h"
#include <QString>
#include <QStringList>

QString Question::getQuestion() {
    return question;
}

QuestionType Question::getType() {
    return type;
}

TrueFalseQuestion::TrueFalseQuestion(const QString q, const bool a) {
    question = q;
    answer = a;
    type = QuestionType::true_false;
}

TrueFalseQuestion::TrueFalseQuestion(const QString rawStr) {
    QStringList params = rawStr.split(';', Qt::SkipEmptyParts);

    question = params[0];
    if(params[1].toLower() == "1")
        answer = true;
    else if (params[1].toLower() == "0")
        answer = false;
    else
        throw std::runtime_error("Malformed question file");

    type = QuestionType::true_false;
}

bool TrueFalseQuestion::getAnswer() {
    return answer;
}

MultiChoiceQuestion::MultiChoiceQuestion(const QString q, const QString a, const QStringList& c) {
    question = q;
    answer = a;
    choices = c;
    type = QuestionType::multi_choice;
}

MultiChoiceQuestion::MultiChoiceQuestion(const QString rawStr) {
    QStringList params = rawStr.split(';', Qt::SkipEmptyParts);
    question = params[0];
    answer = params[1];

    // Remove first two elements (question and correct answer) leaving only the choices
    params.removeFirst();
    params.removeFirst();
    choices = params;

    type = QuestionType::multi_choice;
}

const QString MultiChoiceQuestion::getAnswer() {
    return answer;
}

const QStringList MultiChoiceQuestion::getChoices() {
    return choices;
}

ShortAnswerQuestion::ShortAnswerQuestion(const QString q, const QStringList& a) {
    question = q;
    answers = a;
    type = QuestionType::short_answer;
}

ShortAnswerQuestion::ShortAnswerQuestion(const QString rawStr) {
    QStringList params = rawStr.split(';', Qt::SkipEmptyParts);
    question = params[0];

    params.removeFirst(); // Remove question and leave everything else (the answers)
    answers = params;

    type = QuestionType::short_answer;
}

const QStringList ShortAnswerQuestion::getAnswers() {
    return answers;
}
