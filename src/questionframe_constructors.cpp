#include "questionframes.h"
#include "questioncontainer.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QRadioButton>
#include <vector>
#include <algorithm>
#include <random>
#include <QCheckBox>

template<class T>
T shuffleList(T list) {
	std::random_device rd;
	std::mt19937 mt(rd());

	std::shuffle(list.begin(), list.end(), mt);
	return list;
}

QuestionFrame::QuestionFrame(QString questionStr, int number, QWidget* parent) : QFrame(parent) {
	setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	setFixedWidth(500);

	QFont font;
	font.setPointSize(12);

	questionLabel = new QLabel(this);
	questionLabel->setFont(font);
	questionLabel->setText(QString("%1. %2").arg(QString::number(number), questionStr)); // Set the label to said formatted string
	questionLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	questionLabel->setWordWrap(true);
	questionLabel->move(5,5);
	questionLabel->setMinimumWidth(495);
	questionLabel->adjustSize();

	questionHeight = questionLabel->height();

	inner = new QWidget(this);
}

TrueFalseFrame::TrueFalseFrame(TrueFalseQuestion q, int number, QWidget* parent) : QuestionFrame(q.getQuestion(), number, parent) {
	buttonTrue = new QRadioButton(inner);
	buttonFalse = new QRadioButton(inner);
	answer = q.getAnswer();

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

	choices = shuffleList<QStringList>(choices);

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
		else {
			wrongAnswers.push_back(button);
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

	allChoices = shuffleList<QStringList>(allChoices);

	unsigned int height = 0;
	for(QString s : allChoices) {
			QCheckBox* checkbox = new QCheckBox(inner);
			checkbox->setText(s);
			layout->addWidget(checkbox);
			height += checkbox->height();

			if(answers.contains(s)) {
				correctAnswers.push_back(checkbox);
			}
			else {
				wrongAnswers.push_back(checkbox);
			}
	}

	inner->setGeometry(5, questionHeight + 5, 495, height); 
	setFixedHeight(childrenRect().height());
}
