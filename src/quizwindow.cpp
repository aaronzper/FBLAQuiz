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
	for(int i = 1; i <= 10; i++) {
		TrueFalseFrame* frame = new TrueFalseFrame(TrueFalseQuestion("Is this an example question?", true), i, inner);
		layout->addWidget(frame);
	}

	MultiChoiceFrame* mc_frame = new MultiChoiceFrame(MultiChoiceQuestion("Example multi-choice", "Correct Answer", QStringList({"Wrong 1", "Wrong 2"})), 11, inner);
	layout->addWidget(mc_frame);

	ShortAnswerFrame* sa_frame = new ShortAnswerFrame(ShortAnswerQuestion("Example short answer", QStringList{"answer1","answer2"}), 12, inner);
	layout->addWidget(sa_frame);

	setMinimumSize(534, 150);
	resize(534, 550);
}

void QuizWindow::resizeEvent(QResizeEvent* event) {
	// Resize scrollbars to fit the whole window whenever it's size changes
	scrollArea->setFixedSize(geometry().size());
}
