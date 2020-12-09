#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H
#include <QWidget>
#include <QScrollArea>
#include "questionset.h"

class QuizWindow : public QWidget
{
	Q_OBJECT
	public:
		explicit QuizWindow(QuestionSet qSet, QWidget *parent = nullptr);

	private:
		void resizeEvent(QResizeEvent* event);
		QScrollArea* scrollArea;

};

#endif // QUIZWINDOW_H
