#include "common/text_cutter.h"

struct ResourceInitializer
{
    ResourceInitializer()
    {
        Q_INIT_RESOURCE(translations_common);
    }
};

namespace common
{
namespace
{
    ResourceInitializer resource_initializer{};
}

bool TextCutter::InitializeTranslator(QTranslator& translator)
{
    return translator.load(QLocale(), "textcutter-common",  "_", ":/translations");
}

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

QString TextCutter::LoadFile(const QString& path, bool* ok, QString* error)
{
    bool success{false};
    QString error_str{};
    QString file_content{};

    QFile file{path};
    if (file.exists())
    {
        if(file.open(QIODevice::ReadOnly))
        {
            const QByteArray file_content_raw{file.readAll()};
            file_content = QString::fromUtf8(file_content_raw);
            success = true;
            error_str = QString{};
        }
        else
        {
            success = false;
            error_str = tr("Cannot open file.");
        }
    }
    else
    {
        success = false;
        error_str = tr("File does not exist.");
    }

    if (ok != nullptr)
    {
        *ok = success;
    }
    if (error != nullptr)
    {
        *error = error_str;
    }
    return file_content;
}
}
