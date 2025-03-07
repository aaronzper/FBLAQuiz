#include "questionframes.h"

// Create htmlOutput variable with header + indent
#define INIT_HTML_OUTPUT()									\
	QString qLabelText = questionLabel->text();				\
	qLabelText.remove(qLabelText.size() - 1, 1);			\
	QString htmlOutput = "<h2>" + qLabelText + "</h2>\n";	\
	htmlOutput += "<i>";									\
	if(isCorrect) {										\
		htmlOutput += "Correct";							\
	}														\
	else {													\
		htmlOutput += "Incorrect";							\
	}														\
	htmlOutput += "</i>";									\
	htmlOutput += "<div style=\"margin-left: 40px\">";		\

// End indent and return htmlOutput
#define END_HTML_OUTPUT()	\
	htmlOutput += "</div>"; \
	return htmlOutput;		\

QString TrueFalseFrame::generateReport() {
	INIT_HTML_OUTPUT();

	htmlOutput += "<p>" + buttonTrue->text() + "</p>";
	htmlOutput += "<p>" + buttonFalse->text() + "</p>";

	END_HTML_OUTPUT();
}

QString MultiChoiceFrame::generateReport() {
	INIT_HTML_OUTPUT();

	QList<QRadioButton*> buttons = inner->findChildren<QRadioButton*>(); // Get all the radio buttons
	for(QRadioButton* button : buttons) {
		htmlOutput += "<p>" + button->text() + "</p>";
	}

	END_HTML_OUTPUT();
}

QString ShortAnswerFrame::generateReport() {
	INIT_HTML_OUTPUT();

	QString userAnswer = answerInput->text();
	if(userAnswer == "") userAnswer = "N/A";
	htmlOutput += "<p>Your Answer: " + userAnswer + "</p>";

	bool showAnswers;
	bool multipleAnswers = answers.length() > 1;
	QString correctAnswerLabel = "Correct Answer";

	if(!isCorrect) {
		showAnswers = true;
	}
	else { // isCorrect == true
		if(multipleAnswers) {
			showAnswers = true;
		}
		else {
			if(caseSensitive) {
				showAnswers = true;
			}
			else {
				showAnswers = false;
			}
		}
	}

	if(showAnswers) {
		if(caseSensitive) {
			correctAnswerLabel += " (Case Sensitive)"; 
		}

		QString correctAnswerText = "";
		if(multipleAnswers) {
			correctAnswerLabel = "All Correct Answers";

			correctAnswerText += "</p><ul>";

			for(QString answer : answers) {
				correctAnswerText += "<li>" + answer + "</li>";
			}

			correctAnswerText += "</ul>";
		}
		else {
			correctAnswerText = answers[0] + "</p>";
		}

		// Don't need to worry abou the closing <p> here since its part of correctAnswerText
		correctAnswerLabel = "<p>" + correctAnswerLabel + ": ";

		htmlOutput += correctAnswerLabel + correctAnswerText;
	}

	END_HTML_OUTPUT();
}

QString MultiAnswerFrame::generateReport() {
	INIT_HTML_OUTPUT();

	QList<QCheckBox*> buttons = inner->findChildren<QCheckBox*>(); // Get all the check boxes
	for(QCheckBox* button : buttons) {
		htmlOutput += "<p>" + button->text() + "</p>";
	}

	END_HTML_OUTPUT();
}
