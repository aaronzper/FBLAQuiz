#include "questionframes.h"

// Macro to update the questionLabel with whether or not the question is correct or not
// These backslashes may not be aligned if your tab-width isn't 4
#define UPDATE_QUESTION_LABEL()						\
	QString questionText = questionLabel->text();	\
	if(isCorrect) { 								\
		questionText += " ✅";						\
	}												\
	else {											\
		questionText += " ❌";						\
	}												\
	questionLabel->setText(questionText);			\

bool TrueFalseFrame::showResult() {
	isCorrect = false;

	QString trueText = buttonTrue->text();
	QString falseText = buttonFalse->text();
	bool clickedTrue = buttonTrue->isChecked();
	bool clickedFalse = buttonFalse->isChecked();		

	if(answer == true) {
		trueText += " (Correct Answer";
		if(clickedTrue) {
			trueText += ", Your Answer";
			isCorrect = true;
		}
		else if(clickedFalse) {
			falseText += " (Your Answer)";
		}
		trueText += ")";
	}
	else {
		falseText += " (Correct Answer";
		if(clickedFalse) {
			falseText += ", Your Answer";
			isCorrect = true;
		}
		else if(clickedTrue) {
			trueText += " (Your Answer)";
		}
		falseText += ")";
	}

	UPDATE_QUESTION_LABEL();	

	buttonTrue->setText(trueText);
	buttonFalse->setText(falseText);
	
	return isCorrect;
}

bool MultiChoiceFrame::showResult() {
	isCorrect = false;

	QString correctAnswerText = correctAnswer->text();
	correctAnswerText += " (Correct Answer";

	if(correctAnswer->isChecked()) {
		isCorrect = true;
		correctAnswerText += ", Your Answer";
	}
	else {
		for(QRadioButton* button : wrongAnswers) {
			if(button->isChecked()) {
				QString buttonText = button->text();
				buttonText += " (Your Answer)";
				button->setText(buttonText);

				break;
			}
		}
	}

	correctAnswerText += ")";
	correctAnswer->setText(correctAnswerText);

	UPDATE_QUESTION_LABEL();

	return isCorrect;
}

bool ShortAnswerFrame::showResult() {
	QString answer = answerInput->text();
	QStringList _answers = answers;

	if(!caseSensitive) {
		answer = answer.toLower();

		for(int i = 0; i < _answers.length(); i++) {
			_answers[i] = _answers[i].toLower();
		}
	}

	isCorrect = _answers.contains(answer);

	UPDATE_QUESTION_LABEL();

	if(!isCorrect) {
		int innerHeight = inner->height();
		innerHeight += correctAnswerLabelHeight;
		inner->setFixedHeight(innerHeight);
	}
	setFixedHeight(childrenRect().height());

	return isCorrect;
}

bool MultiAnswerFrame::showResult() {
	bool allCorrectAreChecked = true;
	for(QCheckBox* check : correctAnswers) {
		QString checkText = check->text();
		checkText += " (Correct Answer";

		if(!check->isChecked()) {
			allCorrectAreChecked = false;
		}
		else {
			checkText += ", Your Answer";
		}

		checkText += ")";
		check->setText(checkText);
	}

	bool allIncorrectArentChecked = true;
	for(QCheckBox* check : wrongAnswers) {
		if(check->isChecked()) {
			allIncorrectArentChecked = false;

			QString checkText = check->text();
			checkText += " (Your Answer)";
			check->setText(checkText);
		}
	}

	isCorrect = allCorrectAreChecked && allIncorrectArentChecked;

	UPDATE_QUESTION_LABEL();

	return isCorrect;	
}
