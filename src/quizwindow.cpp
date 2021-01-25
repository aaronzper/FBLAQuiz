#include <iostream>
#include "quizwindow.h"
#include "questionset.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "questionframes.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QTextDocument>

union frame_ptr {
	TrueFalseFrame* tf;
	MultiChoiceFrame* mc;
	ShortAnswerFrame* sa;
	MultiAnswerFrame* ma;
};

QuizWindow::QuizWindow(QuestionSet qSet, QWidget *parent) : QWidget(parent) {
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

	// Set up a label to show the final score but dont show it yet
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
	QString finalScore = "";

	try {
		// The button renames itself to say "Print" once it's clicked for the first time, so we need to check which its on (Submit or Print) and act accordingly
		if(!submitted) { // "Submit"
			submitted = true;
			button->setText("Print");

			unsigned int correct = 0;
			for(QuestionFrame* frame : qFrames) {
				if(frame->showResult()) { // showResult() not only displays to the user how the user did, but also returns whether it was correct or not
					correct++;
				}
			}

			unsigned int numQs = qFrames.size();
			finalScore = QString("Final Score: %1/%2").arg(QString::number(correct), QString::number(numQs));
			scoreLabel->setText(finalScore); 
		}
		else { // "Print"
			// Creates a string that to contain HTML code that is later rendered to show the report
			QString htmlOutput = "<h1>FBLA Quiz Results</h1>\n";
			htmlOutput += "<p>" + finalScore + "</p>\n";

			for(QuestionFrame* frame : qFrames) {
				htmlOutput += frame->generateReport();
			}

			QTextDocument printOutput;
			printOutput.setHtml(htmlOutput); // Render the HTML

			QPrinter printer;
			QPrintDialog* dialog = new QPrintDialog(&printer);
			dialog->setWindowTitle("Print Results of Quiz");
			if(dialog->exec() != QDialog::Accepted) return; // Just exit if the user closes out of the print dialog

			QPainter painter;
			painter.begin(&printer);
			printOutput.drawContents(&painter);
			painter.end();
		}
	}
	catch(std::runtime_error e) {
		qCritical("%s", e.what());
	}
}
