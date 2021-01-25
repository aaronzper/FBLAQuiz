// Contains class declarations for all the different types of question
// Each question class inherits the base Question class (that just has basic question functionality, specifically containing the question text itself)
// Each question class has two constructors: one with a stirng param to parse into that question (from the fblaquiz file)

#ifndef QUESTION_H
#define QUESTION_H
#include <QStringList>

class QString;

enum QuestionType { true_false = 0, multi_choice = 1, short_answer = 2, multi_answer = 3};

class Question {
	public:
		QString getQuestion();
	protected:
		QString question;
};

class TrueFalseQuestion : public Question {
	public:
		TrueFalseQuestion(const QString question, const bool answer);
		TrueFalseQuestion(const QString rawStr);
		bool getAnswer();
	private:
		bool answer;
};

class MultiChoiceQuestion : public Question {
	public:
		MultiChoiceQuestion(const QString question, const QString answer, const QStringList& choices);
		MultiChoiceQuestion(const QString rawStr);
		const QString getAnswer();
		const QStringList getChoices();
	private:
		QString answer;
		QStringList choices;
};

class ShortAnswerQuestion : public Question {
	public:
		ShortAnswerQuestion(const QString question, const QStringList& answers);
		ShortAnswerQuestion(const QString rawStr);
		const QStringList getAnswers();
		bool isCaseSenstitive();
	private:
		QStringList answers;
		bool caseSensitive;
};

class MultiAnswerQuestion : public Question {
	public:
		MultiAnswerQuestion(const QString question, const QStringList& answers, const QStringList& choices);
		MultiAnswerQuestion(const QString rawStr);
		const QStringList getAnswers();
		const QStringList getChoices();
	private:
		QStringList answers;
		QStringList choices;
};

#endif // QUESTION_H
