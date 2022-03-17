#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <QtWidgets>

namespace gui
{
class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);

private:
	QTabWidget* _tabWidget;
	QPushButton* _resetBtn;
	QPushButton* _cutBtn;
	QSpinBox* _numParts;
	QTextEdit* _original;

private slots:
	void on_resetBtn_clicked(bool clearOriginal = true);
	void on_cutBtn_clicked();
};
}

#endif // GUI_MAIN_WINDOW_H
