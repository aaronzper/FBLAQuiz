#include "questionframes.h"
#include "questioncontainer.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QRadioButton>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

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
	std::vector<QString> choices;
	choices.push_back(q.getAnswer());

	for(QString s : q.getChoices()) {
		choices.push_back(s);
	}

	QVBoxLayout* layout = new QVBoxLayout(inner);

	// Randomize the order of the answers
	std::shuffle(std::begin(choices), std::end(choices), std::default_random_engine());

	unsigned int height = 0;
	for(QString s : choices) {
		QRadioButton* button = new QRadioButton(inner);
		button->setText(s);
		layout->addWidget(button);
		height += button->height();

		if(s == q.getAnswer()) {
			correctAnswer = button;		
		}	
	}

	inner->setGeometry(5, questionHeight + 5, 495, height); 
	setFixedHeight(childrenRect().height());
}
