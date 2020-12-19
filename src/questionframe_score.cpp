#include "questionframes.h"

bool TrueFalseFrame::showResult() {
	QString questionText = questionLabel->text();
	QString trueText = buttonTrue->text();
	QString falseText = buttonFalse->text();
	bool clickedTrue = buttonTrue->isChecked();
	bool clickedFalse = buttonFalse->isChecked();		
	bool correct = false;

	if(answer == true) {
		trueText += " (Correct Answer";
		if(clickedTrue) {
			trueText += ", Your Answer";
			correct = true;
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
			correct = true;
		}
		else if(clickedTrue) {
			trueText += " (Your Answer)";
		}
		falseText += ")";
	}

	if(correct) {
		questionText += " ✅";
	}
	else {
		questionText += " ❌";
	}

	questionLabel->setText(questionText);
	buttonTrue->setText(trueText);
	buttonFalse->setText(falseText);
	
	return correct;
}

bool MultiChoiceFrame::showResult() {
	return false;
}

bool ShortAnswerFrame::showResult() {
	return false;
}

bool MultiAnswerFrame::showResult() {
	return false;
}
