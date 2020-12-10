#include "question.h"
#include <QString>
#include <QStringList>
#include <stdexcept>

void malformedFile(const std::string& msg = "") {
	std::string errorMsg = "Malformed quiz file";
	
	if(msg != "") {
		errorMsg += ": " + msg;	
	}
	
	throw std::runtime_error(errorMsg);
}

QStringList getParams(QString s) {
	return s.split(';', Qt::SkipEmptyParts);
}

QString Question::getQuestion() {
	return question;
}

TrueFalseQuestion::TrueFalseQuestion(const QString q, const bool a) {
	question = q;
	answer = a;
}

TrueFalseQuestion::TrueFalseQuestion(const QString rawStr) {
	QStringList params = getParams(rawStr);
	if(!(params.size() >= 2))
		malformedFile("Incorrect length of question entry");

	question = params[0];
	if(params[1].toLower() == "1")
		answer = true;
	else if (params[1].toLower() == "0")
		answer = false;
	else
		malformedFile("Invalid answer for true/false question");

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
	QStringList params = getParams(rawStr);
	if(!(params.size() >= 2))
		malformedFile("Incorrect length of question entry");

	question = params[0];
	answer = params[1];

	// Remove first two elements (question and correct answer) leaving only the choices
	params.removeFirst();
	params.removeFirst();
	choices = params;

	if(choices.contains(answer)) {
		malformedFile("Multiple choice question cannot have the correct answer also be an incorrect choice");
	}
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
	QStringList params = getParams(rawStr);
	if(!(params.size() >= 2))
		malformedFile("Incorrect length of question entry");

	question = params[0];

	params.removeFirst(); // Remove question and leave everything else (the answers)
	answers = params;
}

const QStringList ShortAnswerQuestion::getAnswers() {
	return answers;
}

MultiAnswerQuestion::MultiAnswerQuestion(const QString q, const QStringList& a, const QStringList& c) {
	question = q;
	answers = a;
	choices = c;
}

MultiAnswerQuestion::MultiAnswerQuestion(const QString rawStr) {
	QStringList params = getParams(rawStr);
	if(!(params.size() >= 3))
		malformedFile("Incorrect length of question entry");

	question = params[0];

	int numAnswers = params[1].toInt();

	// Remove first two elements (question and num of answers) leaving only answers & choices choices
	params.removeFirst();
	params.removeFirst();

	int recordedAnswers = 0;
	for(QString entry : params) {
		if(recordedAnswers >= numAnswers) {
			choices.push_back(entry);
		}
		else {
			answers.push_back(entry);
			recordedAnswers++;
		}
	}
}

const QStringList MultiAnswerQuestion::getAnswers() {
	return answers;
}

const QStringList MultiAnswerQuestion::getChoices() {
	return choices;
}
