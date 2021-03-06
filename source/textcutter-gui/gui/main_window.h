#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <QtWidgets>
#include <array>
#include <cstdint>

#include "common/text_cutter.h"

namespace gui
{
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    void LoadTextFromFile();
    void ClearPartTabs();
    void Reset();
    void CutText();

    static constexpr std::int32_t kMaxNumberOfParts{ 10 };

    common::TextCutter text_cutter_;

    QPushButton* load_from_file_button_;
    QTabWidget* tab_widget_;
    QSpinBox* num_parts_;
    QPushButton* cut_button_;
    QPushButton* reset_button_;
    QTextEdit* original_;
    std::array<QTextEdit*, kMaxNumberOfParts> part_edits_;
};
}

#endif // GUI_MAIN_WINDOW_H
