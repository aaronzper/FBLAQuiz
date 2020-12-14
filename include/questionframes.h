#ifndef QUESTIONFRAMES_H
#define QUESTIONFRAMES_H
#include <QFrame>
#include <QRadioButton>
#include <QLineEdit>
#include <QCheckBox>
#include "question.h"

class QuestionFrame : public QFrame {
	Q_OBJECT
	public:
		explicit QuestionFrame(QString questionStr, int number, QWidget* parent = nullptr);
	protected:
		unsigned int questionHeight;
		QWidget* inner;
};

class TrueFalseFrame : public QuestionFrame {
	Q_OBJECT
	public:
		explicit TrueFalseFrame(TrueFalseQuestion q, int number, QWidget* parent = nullptr);
};

class MultiChoiceFrame : public QuestionFrame {
	Q_OBJECT
	public:
		explicit MultiChoiceFrame(MultiChoiceQuestion q, int number, QWidget* parent = nullptr);
	private:
		QRadioButton* correctAnswer;
};

class ShortAnswerFrame : public QuestionFrame {
	Q_OBJECT
	public:
		explicit ShortAnswerFrame(ShortAnswerQuestion q, int number, QWidget* parent = nullptr);
	private:
		QLineEdit* answerInput;
};

class MultiAnswerFrame : public QuestionFrame {
	Q_OBJECT
	public:
		explicit MultiAnswerFrame(MultiAnswerQuestion q, int number, QWidget* parent = nullptr);
	private:
		std::vector<QCheckBox*> correctAnswers;
		std::vector<QCheckBox*> wrongAnswers;
};

#endif // QUESTIONFRAMES_H
