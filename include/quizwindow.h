// Contains the class for the window that actually displays the quizthe window that actually displays the quiz.

#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H
#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <vector>
#include "questionframes.h"
#include "questionset.h"

class QuizWindow : public QWidget
{
	Q_OBJECT
	public:
		explicit QuizWindow(QuestionSet qSet, QWidget *parent = nullptr);

	private:
		void resizeEvent(QResizeEvent* event);

		QScrollArea* scrollArea;
		std::vector<QuestionFrame*> qFrames;
		QPushButton* button; // Button object that starts out as "Submit" but then is changed to "Print"
		QLabel* scoreLabel;
		bool submitted = false;

	private slots:
		void buttonClicked();
};

#endif // QUIZWINDOW_H
