#include "questionframes.h"

#define UPDATE_QUESTION_LABEL() 					\
	QString questionText = questionLabel->text(); 	\
	if(isCorrect) { 								\
		questionText += " ✅";						\
	}												\
	else {											\
		questionText += " ❌";						\
	}												\
	questionLabel->setText(questionText);			\

bool TrueFalseFrame::showResult() {
	bool isCorrect = false;

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
	bool isCorrect = false;

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
	return false;
}

bool MultiAnswerFrame::showResult() {
	return false;
}
