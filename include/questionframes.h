// Contains the declarations for the different QuestionFrame classes that make up each visible question in the quiz window. All the classes derive from the QuestionFrame calss that provides base functionality.
#ifndef QUESTIONFRAMES_H
#define QUESTIONFRAMES_H
#include <QFrame>
#include <QRadioButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include "question.h"

class QuestionFrame : public QFrame {
	Q_OBJECT
	public:
		explicit QuestionFrame(QString str, int number, QWidget* parent = nullptr);
		virtual bool showResult() = 0;
		virtual QString generateReport() = 0;
	protected:
		QLabel* questionLabel;
		unsigned int questionHeight;
		QWidget* inner;
		bool isCorrect;
};

class TrueFalseFrame : public QuestionFrame {
	Q_OBJECT
	public:
		explicit TrueFalseFrame(TrueFalseQuestion q, int number, QWidget* parent = nullptr);
		bool showResult();
		QString generateReport();
	private:
		bool answer;
		QRadioButton* buttonTrue;
		QRadioButton* buttonFalse;
};

class MultiChoiceFrame : public QuestionFrame {
	Q_OBJECT
	public:
		explicit MultiChoiceFrame(MultiChoiceQuestion q, int number, QWidget* parent = nullptr);
		bool showResult();
		QString generateReport();
	private:
		QRadioButton* correctAnswer;
		std::vector<QRadioButton*> wrongAnswers;
};

class ShortAnswerFrame : public QuestionFrame {
	Q_OBJECT
	public:
		explicit ShortAnswerFrame(ShortAnswerQuestion q, int number, QWidget* parent = nullptr);
		bool showResult();
		QString generateReport();
	private:
		QLineEdit* answerInput;
		int correctAnswerLabelHeight;
		QStringList answers;
		bool caseSensitive;
};

class MultiAnswerFrame : public QuestionFrame {
	Q_OBJECT
	public:
		explicit MultiAnswerFrame(MultiAnswerQuestion q, int number, QWidget* parent = nullptr);
		bool showResult();
		QString generateReport();
	private:
		std::vector<QCheckBox*> correctAnswers;
		std::vector<QCheckBox*> wrongAnswers;
};

#endif // QUESTIONFRAMES_H
