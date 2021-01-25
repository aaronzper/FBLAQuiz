// Contains the declaration for a class that represents a set of questions. Essentially an in-memory version of an fblaquiz file. Makes use of the QuestionContainer class.

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
