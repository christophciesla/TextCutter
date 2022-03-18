#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <QtWidgets>
#include <cstdint>

namespace gui
{
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    QTabWidget* tab_widget_;
    QSpinBox* num_parts_;
    QPushButton* cut_button_;
    QPushButton* reset_button_;
    QTextEdit* original_;

    void ClearPartTabs();
    void Reset();
    void CutText();
};
}

#endif // GUI_MAIN_WINDOW_H
