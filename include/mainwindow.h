#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>

class MainWindow : public QWidget
{
	Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent = nullptr);

	private slots:
		void buttonStartQuizClicked();
		void buttonCreateQuizClicked();
		void buttonEditQuizClicked();
};

#endif // MAINWINDOW_H
