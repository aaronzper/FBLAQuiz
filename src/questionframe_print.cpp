#include "questionframes.h"

#define INIT_HTML_OUTPUT()												\
	QString htmlOutput = "<h2>" + questionLabel->text() + "</h2>\n";	\

QString TrueFalseFrame::generateReport() {
	INIT_HTML_OUTPUT();

	return htmlOutput;
}

QString MultiChoiceFrame::generateReport() {
	INIT_HTML_OUTPUT();

	return htmlOutput;
}

QString ShortAnswerFrame::generateReport() {
	INIT_HTML_OUTPUT();

	return htmlOutput;
}

QString MultiAnswerFrame::generateReport() {
	INIT_HTML_OUTPUT();

	return htmlOutput;
}
