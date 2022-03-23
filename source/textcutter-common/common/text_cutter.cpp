#include "common/text_cutter.h"

namespace common
{
QVector<QString> TextCutter::CutText(const QString& text, const std::int32_t num_parts)
{
    QVector<QString> parts{ num_parts };

    const std::int32_t part_length{ (text.length() + num_parts - 1) / 4 };
    for (QString& part : parts)
    {
        part.reserve(part_length);
    }

    for (std::int32_t i{ 0 }; i < text.length(); ++i)
    {
        const QChar c{ text[i] };
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
