#include "main_window.h"

namespace gui
{
MainWindow::MainWindow(QWidget* parent)
	: QWidget(parent)
	, _tabWidget(new QTabWidget)
	, _numParts(new QSpinBox)
	, _cutBtn(new QPushButton("Zerhacken"))
	, _resetBtn(new QPushButton("Zurücksetzen"))
	, _original(new QTextEdit)
{
	setWindowTitle("Zerhacker");

	_numParts->setRange(2, 10);

	QVBoxLayout* layout = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(_tabWidget);

	QHBoxLayout* btnLayout = new QHBoxLayout;
	layout->addLayout(btnLayout);

	btnLayout->addWidget(_numParts);
	btnLayout->addWidget(_cutBtn);
	btnLayout->addWidget(_resetBtn);
	btnLayout->addStretch();

	_tabWidget->addTab(_original, "Originaltext");

	connect(_resetBtn, SIGNAL(clicked()), SLOT(on_resetBtn_clicked()));
	connect(_cutBtn, SIGNAL(clicked()), SLOT(on_cutBtn_clicked()));

	on_resetBtn_clicked();
}

void MainWindow::on_resetBtn_clicked(bool clearOriginal)
{
	for (int i = 1; i < _tabWidget->count(); )
	{
		delete _tabWidget->widget(i);
	}
	if (clearOriginal)
	{
		_original->clear();
		_numParts->setValue(2);
	}
}

void MainWindow::on_cutBtn_clicked()
{
	on_resetBtn_clicked(false);
	QStringList parts;
	int num = _numParts->value();
	for (int i = 0; i < num; i++)
	{
		parts.append(QString());
	}

	QString original = _original->toPlainText();

	for (int i = 0; i < original.length(); i++)
	{
		QChar c = original[i];
		if (c == ' ' || c == '\n')
			parts[i % num].append('_');
		else
			parts[i % num].append(c);
	}

	int counter = 1;
	foreach(const QString & part, parts)
	{
		QTextEdit* pEdit = new QTextEdit(part);
		pEdit->setReadOnly(true);
		_tabWidget->addTab(pEdit, QString("Teil %1").arg(counter++));
	}
}
}