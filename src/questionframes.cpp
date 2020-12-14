#include "questionframes.h"
#include "questioncontainer.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QRadioButton>
#include <vector>
#include <algorithm>
#include <random>
#include <QCheckBox>

QuestionFrame::QuestionFrame(QString questionStr, int number, QWidget* parent) : QFrame(parent) {
	setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	setFixedWidth(500);

	QFont font;
	font.setPointSize(12);

	QLabel* question = new QLabel(this);
	question->setFont(font);
	question->setText(QString("%1. %2").arg(QString::number(number), questionStr)); // Set the label to said formatted string
	question->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	question->setWordWrap(true);
	question->move(5,5);
	question->setMinimumWidth(495);
	question->adjustSize();

	questionHeight = question->height();

	inner = new QWidget(this);
}

TrueFalseFrame::TrueFalseFrame(TrueFalseQuestion q, int number, QWidget* parent) : QuestionFrame(q.getQuestion(), number, parent) {
	QRadioButton* buttonTrue = new QRadioButton(inner);
	QRadioButton* buttonFalse = new QRadioButton(inner);

	buttonTrue->setText("True");
	buttonFalse->setText("False");

	QVBoxLayout* layout = new QVBoxLayout(inner);
	layout->addWidget(buttonTrue);
	layout->addWidget(buttonFalse);

	inner->setGeometry(5, questionHeight + 5, 495, buttonTrue->height() + buttonFalse->height());
	setFixedHeight(childrenRect().height());
}

MultiChoiceFrame::MultiChoiceFrame(MultiChoiceQuestion q, int number, QWidget* parent) : QuestionFrame(q.getQuestion(), number, parent) {
	QStringList choices = q.getChoices();
	choices << q.getAnswer();

	QVBoxLayout* layout = new QVBoxLayout(inner);

	// TODO: Randomize the order of the choices

	unsigned int height = 0;
	for(QString s : choices) {
		QRadioButton* button = new QRadioButton(inner);
		button->setText(s);
		layout->addWidget(button);
		height += button->height();

		// Don't need to worry about duplicates here since the question file parser checks for duplicate correct answers
		if(s == q.getAnswer()) {
			correctAnswer = button;		
		}	
	}

	inner->setGeometry(5, questionHeight + 5, 495, height); 
	setFixedHeight(childrenRect().height());
}

ShortAnswerFrame::ShortAnswerFrame(ShortAnswerQuestion q, int number, QWidget* parent) : QuestionFrame(q.getQuestion(), number, parent) {
	answerInput = new QLineEdit(inner);

	answerInput->setFixedWidth(300);

	inner->setGeometry(5, questionHeight + 5, 495, answerInput->height()); 
	setFixedHeight(childrenRect().height());
}

MultiAnswerFrame::MultiAnswerFrame(MultiAnswerQuestion q, int number, QWidget* parent) : QuestionFrame(q.getQuestion(), number, parent) {
	QStringList allChoices = q.getChoices();
	QStringList answers = q.getAnswers();
	allChoices << answers;

	QVBoxLayout* layout = new QVBoxLayout(inner);

	// TODO: Randomize the order of the choices

	unsigned int height = 0;
	for(QString s : allChoices) {
			QCheckBox* checkbox = new QCheckBox(inner);
			checkbox->setText(s);
			layout->addWidget(checkbox);
			height += checkbox->height();
	}

	inner->setGeometry(5, questionHeight + 5, 495, height); 
	setFixedHeight(childrenRect().height());
}
