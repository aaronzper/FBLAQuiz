#include "questionframes.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QRadioButton>

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
}

TrueFalseFrame::TrueFalseFrame(TrueFalseQuestion q, int number, QWidget* parent) : QuestionFrame(q.getQuestion(), number, parent) {
	QWidget* inner = new QWidget(this);

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
