#include "question.h"
#include <QString>
#include <QStringList>
#include <stdexcept>

// Helper function any errors in parsing the fblaquiz file
void malformedFile(const QString& msg = "", const QString& rawStr = "") {
	QString errorMsg = "Malformed quiz file";
	
	if(msg != "") {
		errorMsg += ": " + msg;
	}

	if(rawStr != "") {
		errorMsg += "\n\nMalformed line in question: " + rawStr;
	}
	
	throw std::runtime_error(errorMsg.toStdString());
}

// Helper function to split a line in the fblaquiz file into a list
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

// Parser for true-false question
TrueFalseQuestion::TrueFalseQuestion(const QString rawStr) {
	QStringList params = getParams(rawStr);
	if(!(params.size() >= 2))
		malformedFile("Incorrect length of question entry", rawStr);

	question = params[0];
	if(params[1] == "1")
		answer = true;
	else if (params[1] == "0")
		answer = false;
	else
		malformedFile("Invalid answer for true/false question", rawStr);

}

bool TrueFalseQuestion::getAnswer() {
	return answer;
}

MultiChoiceQuestion::MultiChoiceQuestion(const QString q, const QString a, const QStringList& c) {
	question = q;
	answer = a;
	choices = c;
}

// Parser for multi-choice question
MultiChoiceQuestion::MultiChoiceQuestion(const QString rawStr) {
	QStringList params = getParams(rawStr);
	if(!(params.size() >= 2))
		malformedFile("Incorrect length of question entry", rawStr);

	question = params[0];
	answer = params[1];

	// Remove first two elements (question and correct answer) leaving only the choices
	params.removeFirst();
	params.removeFirst();
	choices = params;

	if(choices.contains(answer)) {
		malformedFile("Multiple choice question cannot have the correct answer also be an incorrect choice", rawStr);
	}
}

const QString MultiChoiceQuestion::getAnswer() {
	return answer;
}

const QStringList MultiChoiceQuestion::getChoices() {
	return choices;
}

ShortAnswerQuestion::ShortAnswerQuestion(const QString q, const QStringList& a, bool case_sensitive) {
	question = q;
	answers = a;
	caseSensitive = case_sensitive;
}

// Parser for short-answer question
ShortAnswerQuestion::ShortAnswerQuestion(const QString rawStr) {
	QStringList params = getParams(rawStr);
	if(!(params.size() >= 2))
		malformedFile("Incorrect length of question entry", rawStr);

	question = params[0];
	
	if(params[1] == "1")
		caseSensitive = true;
	else if (params[1] == "0")
		caseSensitive = false;	
	else 
		malformedFile("Invalid case-sensitivity value", rawStr);

	params.removeFirst(); // Remove first two params (question and case sensitivity)
	params.removeFirst(); 

	answers = params; // All remaining params all the answers)
}

const QStringList ShortAnswerQuestion::getAnswers() {
	return answers;
}

bool ShortAnswerQuestion::isCaseSenstitive() {
	return caseSensitive;
}

MultiAnswerQuestion::MultiAnswerQuestion(const QString q, const QStringList& a, const QStringList& c) {
	question = q;
	answers = a;
	choices = c;
}

// Parser for multi-answer question
MultiAnswerQuestion::MultiAnswerQuestion(const QString rawStr) {
	QStringList params = getParams(rawStr);
	if(!(params.size() >= 3))
		malformedFile("Incorrect length of question entry", rawStr);

	question = params[0];

	int numAnswers = params[1].toInt();

	// Remove first two elements (question and num of answers) leaving only answers & choices choices
	params.removeFirst();
	params.removeFirst();

	int recordedAnswers = 0;
	for(QString entry : params) { // Goes down the list of answers, and puts them all into the correct answers list until we've pushed the number of correct answers there are, then starts pushing to the choices (incorrect answers) list.
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
