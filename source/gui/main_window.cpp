#include "main_window.h"

namespace gui
{
namespace
{
    const std::int32_t kMaxNumberOfParts{ 10 };
}

MainWindow::MainWindow(QWidget* parent)
    : QWidget{ parent }
    , tab_widget_(new QTabWidget{})
    , num_parts_(new QSpinBox{})
    , cut_button_(new QPushButton{ "Zerhacken" })
    , reset_button_(new QPushButton{ "Zurücksetzen" })
    , original_(new QTextEdit{})
{
    setWindowTitle("Zerhacker");

    num_parts_->setRange(2, kMaxNumberOfParts);

    QVBoxLayout* layout = new QVBoxLayout{};
    setLayout(layout);

    layout->addWidget(tab_widget_);

    QHBoxLayout* button_layout = new QHBoxLayout{};
    layout->addLayout(button_layout);

    button_layout->addWidget(num_parts_);
    button_layout->addWidget(cut_button_);
    button_layout->addWidget(reset_button_);
    button_layout->addStretch();

    tab_widget_->addTab(original_, "Originaltext");
    for (std::int32_t i{ 1 }; i <= kMaxNumberOfParts; ++i)
    {
        QTextEdit* part_edit{ new QTextEdit{} };
        part_edit->setReadOnly(true);
        tab_widget_->addTab(part_edit, QString("Teil %1").arg(i));
    }

    connect(reset_button_, &QPushButton::clicked, this, &MainWindow::Reset);
    connect(cut_button_, &QPushButton::clicked, this, &MainWindow::CutText);

    Reset();
}

void MainWindow::ClearPartTabs()
{
    for (std::int32_t i{ 1 }; i <= kMaxNumberOfParts; ++i)
    {
        tab_widget_->setTabVisible(i, false);
        QTextEdit* part_edit{ qobject_cast<QTextEdit*>(tab_widget_->widget(i)) };
        if (part_edit != nullptr)
        {
            part_edit->clear();
        }
    }
}

void MainWindow::Reset()
{
    ClearPartTabs();

    original_->clear();
    num_parts_->setValue(2);
}

void MainWindow::CutText()
{
    ClearPartTabs();

    const auto parts{GenerateParts(original_->toPlainText(), num_parts_->value())};

    for (std::int32_t i{ 0 }; i < parts.size(); ++i)
    {
        const std::int32_t tab_index{ i + 1 };
        QTextEdit* part_edit{ qobject_cast<QTextEdit*>(tab_widget_->widget(tab_index)) };
        if (part_edit != nullptr)
        {
            part_edit->setText(parts[i]);
            tab_widget_->setTabVisible(tab_index, true);
        }
    }
}

QVector<QString> MainWindow::GenerateParts(const QString& original, const std::int32_t num_parts)
{
    QVector<QString> parts{std::min(num_parts, kMaxNumberOfParts)};

    const std::int32_t part_length{ (original.length() + num_parts - 1) / 4};
    for (QString& part : parts)
    {
        part.reserve(part_length);
    }

    for (std::int32_t i{ 0 }; i < original.length(); ++i)
    {
        const QChar c{ original[i] };
        if ((c == ' ') || (c == '\n'))
        {
            parts[i % num_parts].append('_');
        }
        else
        {
            parts[i % num_parts].append(c);
        }
    }
    return parts;
}
}
