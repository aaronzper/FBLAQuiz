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
		if(line.isEmpty()) continue;

		QuestionType type = (QuestionType)line[0].digitValue();
		line.remove(0,1); // remove first char (the question type) since the question constructors dont need that info

		QuestionContainer qc;
		switch(type) {
			case true_false:     // True-false
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
			default:    // Invalid type (for when its not even an int)
				throw std::runtime_error("Malformed question file");
				break;
		}

		questions.push_back(qc);
	}
}

QuestionContainer QuestionSet::operator[](int i) {
	return questions[i];
}

std::vector<QuestionContainer> QuestionSet::getRandomQuestions(unsigned int count) {
	if(count > questions.size()) throw std::runtime_error("Count of randomly picked questions to return greater than size of QuestionSet");
	std::vector<unsigned int> indexes;
	unsigned int i = 0;
	while(1) {
		unsigned int index = rand() % questions.size();
		
		if(std::count(indexes.begin(), indexes.end(), index)) { // If the number of instances of index in indexes is non-zero
			continue; // Continue to generate another number
		}

		indexes.push_back(index);
		i++;
		if(i == count) break;
	}

	std::vector<QuestionContainer> output;
	for(unsigned int index : indexes) {
		output.push_back(questions[index]);
	}

	return output;
}

int QuestionSet::count() {
	return questions.size();
}
