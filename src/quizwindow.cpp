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

	scoreLabel = new QLabel(inner);
	QFont scoreFont;
	scoreFont.setBold(true);
	scoreFont.setPointSize(12);
	scoreLabel->setFont(scoreFont);
	layout->addWidget(scoreLabel);

	button = new QPushButton("Submit", inner);
	button->setFixedWidth(80);
	connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
	layout->addWidget(button);

	setMinimumSize(534, 150);
	resize(534, 550);
}

void QuizWindow::resizeEvent(QResizeEvent* event) {
	// Resize scrollbars to fit the whole window whenever it's size changes
	scrollArea->setFixedSize(geometry().size());
}

void QuizWindow::buttonClicked() {
	try {
		// "Submit"
		if(!submitted) {
			submitted = true;
			button->setText("Print");

			unsigned int correct = 0;
			for(QuestionFrame* frame : qFrames) {
				if(frame->showResult()) {
					correct++;
				}
			}

			unsigned int numQs = qFrames.size();
			scoreLabel->setText(QString("Final Score: %1/%2").arg(QString::number(correct), QString::number(numQs))); 
		}
		// "Print"
		else {
			// TODO: Print report
		}
	}
	catch(std::runtime_error e) {
		qCritical("%s", e.what());
	}
}
