#include "question.h"
#include <QString>
#include <QStringList>

QString Question::getQuestion() {
    return question;
}

TrueFalseQuestion::TrueFalseQuestion(const QString q, const bool a) {
    question = q;
    answer = a;
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
}

bool TrueFalseQuestion::getAnswer() {
    return answer;
}

MultiChoiceQuestion::MultiChoiceQuestion(const QString q, const QString a, const QStringList& c) {
    question = q;
    answer = a;
    choices = c;
}

MultiChoiceQuestion::MultiChoiceQuestion(const QString rawStr) {
    QStringList params = rawStr.split(';', Qt::SkipEmptyParts);
    question = params[0];
    answer = params[1];

    // Remove first two elements (question and correct answer) leaving only the choices
    params.removeFirst();
    params.removeFirst();
    choices = params;
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
}

ShortAnswerQuestion::ShortAnswerQuestion(const QString rawStr) {
    QStringList params = rawStr.split(';', Qt::SkipEmptyParts);
    question = params[0];

    params.removeFirst(); // Remove question and leave everything else (the answers)
    answers = params;
}

const QStringList ShortAnswerQuestion::getAnswers() {
    return answers;
}
