#include "questionset.h"
#include <QFile>
#include <QTextStream>
#include <vector>
#include <iostream>
#include "question.h"
#include "questioncontainer.h"

QuestionSet::QuestionSet(QString path)
{
	QFile file(path);
	if(!file.exists())
		throw std::runtime_error("Question file not found");

	file.open(QIODevice::ReadOnly);
	QTextStream txt(&file);

	for(QString line = txt.readLine(); !line.isNull(); line = txt.readLine()) {
		QuestionType type = (QuestionType)line[0].digitValue();
		line.remove(0,1); // remove first char (the question type) since the question constructors dont need that info

		QuestionContainer qc;
		switch(type) {
			case true_false:     // True/false
				qc.init(TrueFalseQuestion(line));
				break;
			case multi_choice:     // Multi-choice
				qc.init(MultiChoiceQuestion(line));
				break;
			case short_answer:     // Short answer
				qc.init(ShortAnswerQuestion(line));
				break;
			case multi_answer:     // Multi-answer
				qc.init(MultiAnswerQuestion(line));
				break;
			default:    // Invalid type (including -1, for when its not even an int)
				throw std::runtime_error("Malformed question file");
				break;
		}

		questions.push_back(qc);
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
