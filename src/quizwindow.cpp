#include <iostream>
#include "quizwindow.h"
#include "questionset.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "questionframes.h"

union frame_ptr {
	TrueFalseFrame* tf;
	MultiChoiceFrame* mc;
	ShortAnswerFrame* sa;
	MultiAnswerFrame* ma;
};

QuizWindow::QuizWindow(QuestionSet qSet, QWidget *parent) : QWidget(parent)
{
	QWidget* inner = new QWidget(this);
	scrollArea = new QScrollArea(this);
	scrollArea->setWidget(inner);
	scrollArea->setWidgetResizable(true);

	QVBoxLayout* layout = new QVBoxLayout(inner);
	
	for(int i = 0; i < qSet.count(); i++) {
		frame_ptr f;	
		switch(qSet[i].getType()) {
			case true_false:
				f.tf = new TrueFalseFrame((TrueFalseQuestion)qSet[i], i + 1, inner);
				qFrames.push_back(f.tf);
				layout->addWidget(f.tf);
				break;
			case multi_choice:
				f.mc = new MultiChoiceFrame((MultiChoiceQuestion)qSet[i], i + 1, inner);
				qFrames.push_back(f.mc);
				layout->addWidget(f.mc);
				break;
			case short_answer:
				f.sa = new ShortAnswerFrame((ShortAnswerQuestion)qSet[i], i + 1, inner);
				qFrames.push_back(f.sa);
				layout->addWidget(f.sa);
				break;
			case multi_answer:
				f.ma = new MultiAnswerFrame((MultiAnswerQuestion)qSet[i], i + 1, inner);
				qFrames.push_back(f.ma);
				layout->addWidget(f.ma);
				break;
			default:
				// This shouldn't happen
				throw std::runtime_error("Invalid question type");
				break;
		}
	}

	button = new QPushButton("Submit", inner);
	button->setFixedWidth(80);
	layout->addWidget(button);
	connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));

	setMinimumSize(534, 150);
	resize(534, 550);
}

void QuizWindow::resizeEvent(QResizeEvent* event) {
	// Resize scrollbars to fit the whole window whenever it's size changes
	scrollArea->setFixedSize(geometry().size());
}

void QuizWindow::buttonClicked() {
	try {
		if(!submitted) {
			submitted = true;
			button->setText("Print");

			for(QuestionFrame* frame : qFrames) {
				frame->showResult();
			}
		}
		else {
			// Print report
		}
	}
	catch(std::runtime_error e) {
		qCritical("%s", e.what());
	}
}
