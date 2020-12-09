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
		template<class T>
		void init(T question);
		QuestionType getType();

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
