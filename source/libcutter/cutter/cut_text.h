#ifndef CUTTER_CUT_TEXT_H
#define CUTTER_CUT_TEXT_H

#include <QtCore>

namespace cutter
{
QVector<QString> CutText(const QString& text, const std::int32_t num_parts);
}

#endif // CUTTER_CUT_TEXT