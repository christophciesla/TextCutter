#ifndef COMMON_TEXT_CUTTER_H
#define COMMON_TEXT_CUTTER_H

#include <QtCore>

namespace common
{
class TextCutter
{
    Q_DECLARE_TR_FUNCTIONS(TextCutter)

public:
    static bool InitializeTranslator(QTranslator& translator);

    static QVector<QString> CutText(const QString& text, const std::int32_t num_parts);

    static QString LoadFile(const QString& path, bool* ok, QString* error);
};
}

#endif // COMMON_TEXT_CUTTER_H