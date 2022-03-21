#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <QtWidgets>
#include <array>
#include <cstdint>

namespace gui
{
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    void ClearPartTabs();
    void Reset();
    void CutText();

    static constexpr std::int32_t kMaxNumberOfParts{ 10 };

    QTabWidget* tab_widget_;
    QSpinBox* num_parts_;
    QPushButton* cut_button_;
    QPushButton* reset_button_;
    QTextEdit* original_;
    std::array<QTextEdit*, kMaxNumberOfParts> part_edits_;
};
}

#endif // GUI_MAIN_WINDOW_H
