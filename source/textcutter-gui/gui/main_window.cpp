#include "gui/main_window.h"

namespace gui
{
namespace
{
    constexpr std::int32_t kMinNumberOfParts{ 2 };
}

MainWindow::MainWindow(QWidget* parent)
    : QWidget{ parent }
    , text_cutter_{}
    , tab_widget_{new QTabWidget{}}
    , num_parts_{new QSpinBox{}}
    , cut_button_{new QPushButton{ tr("Cut") }}
    , reset_button_{new QPushButton{ tr("Reset") }}
    , original_{new QTextEdit{}}
    , part_edits_{}
{
    setWindowTitle(QApplication::applicationName());

    num_parts_->setRange(kMinNumberOfParts, kMaxNumberOfParts);

    QVBoxLayout* layout = new QVBoxLayout{};
    setLayout(layout);

    layout->addWidget(tab_widget_);

    QHBoxLayout* button_layout = new QHBoxLayout{};
    layout->addLayout(button_layout);

    button_layout->addWidget(num_parts_);
    button_layout->addWidget(cut_button_);
    button_layout->addWidget(reset_button_);
    button_layout->addStretch();

    tab_widget_->addTab(original_, tr("Original text"));
    for (std::int32_t i{ 0 }; i < kMaxNumberOfParts; ++i)
    {
        QTextEdit* part_edit{ new QTextEdit{} };
        part_edit->setReadOnly(true);
        part_edits_[i] = part_edit;
    }

    connect(reset_button_, &QPushButton::clicked, this, &MainWindow::Reset);
    connect(cut_button_, &QPushButton::clicked, this, &MainWindow::CutText);

    Reset();
}

MainWindow::~MainWindow()
{
    qDeleteAll(part_edits_);
}

void MainWindow::ClearPartTabs()
{
    for(QTextEdit* part_edit: part_edits_)
    {
        part_edit->clear();
        tab_widget_->removeTab(1);
    }
}

void MainWindow::Reset()
{
    ClearPartTabs();

    original_->clear();
    num_parts_->setValue(kMinNumberOfParts);
}

void MainWindow::CutText()
{
    ClearPartTabs();

    const auto parts{text_cutter_.CutText(
        original_->toPlainText(), std::min(num_parts_->value(), kMaxNumberOfParts))};
    const std::int32_t num_parts{std::min(parts.size(), kMaxNumberOfParts)};

    for (std::int32_t i{ 0 }; i < num_parts; ++i)
    {
        QTextEdit* part_edit{part_edits_[i]};
        part_edit->setText(parts[i]);
        tab_widget_->addTab(part_edit, tr("Part %1").arg(i + 1));
    }
}
}
