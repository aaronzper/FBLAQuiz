#include <iostream>
#include "quizwindow.h"
#include "questionset.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "questionframes.h"

QuizWindow::QuizWindow(QuestionSet qSet, QWidget *parent) : QWidget(parent)
{
	QWidget* inner = new QWidget(this);
	scrollArea = new QScrollArea(this);
	scrollArea->setWidget(inner);
	scrollArea->setWidgetResizable(true);

	QVBoxLayout* layout = new QVBoxLayout(inner);
	
	for(int i = 0; i < qSet.count(); i++) {
		switch(qSet[i].getType()) {
			case true_false:
				layout->addWidget(new TrueFalseFrame((TrueFalseQuestion)qSet[i], i + 1, inner));
				break;
			case multi_choice:
				layout->addWidget(new MultiChoiceFrame((MultiChoiceQuestion)qSet[i], i + 1, inner));
				break;
			case short_answer:
				layout->addWidget(new ShortAnswerFrame((ShortAnswerQuestion)qSet[i], i + 1, inner));
				break;
			case  multi_answer:
				layout->addWidget(new MultiAnswerFrame((MultiAnswerQuestion)qSet[i], i + 1, inner));
				break;
		}
	}

	setMinimumSize(534, 150);
	resize(534, 550);
}

void QuizWindow::resizeEvent(QResizeEvent* event) {
	// Resize scrollbars to fit the whole window whenever it's size changes
	scrollArea->setFixedSize(geometry().size());
}
