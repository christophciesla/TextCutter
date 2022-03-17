#include "main_window.h"

namespace gui
{
MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , tab_widget_(new QTabWidget{})
    , num_parts_(new QSpinBox{})
    , cut_button_(new QPushButton{ "Zerhacken" })
    , reset_button_(new QPushButton{ "Zurücksetzen" })
    , original_(new QTextEdit{})
{
    setWindowTitle("Zerhacker");

    num_parts_->setRange(2, 10);

    QVBoxLayout* layout = new QVBoxLayout{};
    setLayout(layout);

    layout->addWidget(tab_widget_);

    QHBoxLayout* btnLayout = new QHBoxLayout{};
    layout->addLayout(btnLayout);

    btnLayout->addWidget(num_parts_);
    btnLayout->addWidget(cut_button_);
    btnLayout->addWidget(reset_button_);
    btnLayout->addStretch();

    tab_widget_->addTab(original_, "Originaltext");

    connect(reset_button_, &QPushButton::clicked, this, &MainWindow::Reset);
    connect(cut_button_, &QPushButton::clicked, this, &MainWindow::CutText);

    Reset();
}

void MainWindow::Reset()
{
    while (tab_widget_->count() > 1)
    {
        delete tab_widget_->widget(1);
    }

    original_->clear();
    num_parts_->setValue(2);
}

void MainWindow::CutText()
{
    while (tab_widget_->count() > 1)
    {
        delete tab_widget_->widget(1);
    }

    QStringList parts;
    int num = num_parts_->value();
    for (int i = 0; i < num; i++)
    {
        parts.append(QString());
    }

    QString original = original_->toPlainText();

    for (int i = 0; i < original.length(); i++)
    {
        QChar c = original[i];
        if (c == ' ' || c == '\n')
        {
            parts[i % num].append('_');
        }
        else
        {
            parts[i % num].append(c);
        }
    }

    int counter = 1;
    foreach(const QString & part, parts)
    {
        QTextEdit* pEdit = new QTextEdit(part);
        pEdit->setReadOnly(true);
        tab_widget_->addTab(pEdit, QString("Teil %1").arg(counter++));
    }
}
}
