#include "questionframes.h"

// Create htmlOutput variable with header + indent
#define INIT_HTML_OUTPUT()												\
	QString htmlOutput = "<h2>" + questionLabel->text() + "</h2>\n";	\
	htmlOutput += "<div style=\"margin-left: 40px\">";					\

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

	QList<QRadioButton*> buttons = inner->findChildren<QRadioButton*>();
	for(QRadioButton* button : buttons) {
		htmlOutput += "<p>" + button->text() + "</p>";
	}

	END_HTML_OUTPUT();
}

QString ShortAnswerFrame::generateReport() {
	INIT_HTML_OUTPUT();

	htmlOutput += "<p>Your Answer: " + answerInput->text() + "</p>";

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

	QList<QCheckBox*> buttons = inner->findChildren<QCheckBox*>();
	for(QCheckBox* button : buttons) {
		htmlOutput += "<p>" + button->text() + "</p>";
	}

	END_HTML_OUTPUT();
}
