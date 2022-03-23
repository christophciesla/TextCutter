#ifndef COMMON_TEXT_CUTTER_H
#define COMMON_TEXT_CUTTER_H

#include <QtCore>

namespace common
{
QVector<QString> CutText(const QString& text, const std::int32_t num_parts);
}

#endif // COMMON_TEXT_CUTTER_H