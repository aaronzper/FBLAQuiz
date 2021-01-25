// Contains the declaration for a helper class that contains one of the 4 question types. It also defines explicit casts from this class to the differ question classes.

#ifndef QUESTIONCONTAINER_H
#define QUESTIONCONTAINER_H
#include <variant>
#include "question.h"

class QuestionContainer
{
	public:
		QuestionContainer();
		
		template<class T>
		QuestionContainer(T question);

		// Init function that has the same functionality as the second constructor, in case one declares an empty QuestionContainer
		template<class T>
		void init(T question);

		QuestionType getType();

		// Explicit casts from this class to the different question type classes
		explicit operator TrueFalseQuestion() const;
		explicit operator MultiChoiceQuestion() const;
		explicit operator ShortAnswerQuestion() const;
		explicit operator MultiAnswerQuestion() const;
	private:
		bool _init;
		QuestionType type;
		std::variant<std::monostate, TrueFalseQuestion, MultiChoiceQuestion, ShortAnswerQuestion, MultiAnswerQuestion> container;
};

#endif // QUESTIONCONTAINER_H
