#ifndef COMMON_TEXT_CUTTER_H
#define COMMON_TEXT_CUTTER_H

#include <QtCore>

namespace common
{
class TextCutter
{
    Q_DECLARE_TR_FUNCTIONS(TextCutter)

public:
    TextCutter();

    QVector<QString> CutText(const QString& text, const std::int32_t num_parts) const;

    QString LoadFile(const QString& path, bool* ok, QString* error) const;

private:
    QTranslator common_translator_;
};
}

#endif // COMMON_TEXT_CUTTER_H