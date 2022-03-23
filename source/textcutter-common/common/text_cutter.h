#ifndef COMMON_TEXT_CUTTER_H
#define COMMON_TEXT_CUTTER_H

#include <QtCore>

namespace common
{
class TextCutter
{
    Q_DECLARE_TR_FUNCTIONS(TextCutter)

public:
    static QVector<QString> CutText(const QString& text, const std::int32_t num_parts);
};
}

#endif // COMMON_TEXT_CUTTER_H