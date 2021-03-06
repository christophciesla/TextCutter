#include <QtCore>
#include <cstdint>

#include "common/text_cutter.h"

namespace
{
    const std::int32_t kMinNumberOfParts{ 2 };
    const std::int32_t kMaxNumberOfParts{ 10 };

    QTextStream qout{ stdout };
    QTextStream qerr{ stderr };

    std::int32_t ExtractNumberOfParts(const QString& num_parts_string)
    {
        bool ok{ false };
        const std::int32_t num_parts{ num_parts_string.toInt(&ok) };
        if (!ok)
        {
            qout << QCoreApplication::tr("Invalid format.") << '\n' <<
                QCoreApplication::tr("Creating %1 text parts which is minimum.").arg(kMinNumberOfParts) << '\n';
            return kMinNumberOfParts;
        }
        if (num_parts < kMinNumberOfParts)
        {
            qout << QCoreApplication::tr("Creating %1 text parts which is minimum.").arg(kMinNumberOfParts) << '\n';
            return kMinNumberOfParts;
        }
        if (num_parts > kMaxNumberOfParts)
        {
            qout << QCoreApplication::tr("Creating %1 text parts which is maximum.").arg(kMaxNumberOfParts) << '\n';
            return kMaxNumberOfParts;
        }
        return num_parts;
    }

    void OutputParts(const QVector<QString>& parts)
    {
        for (std::int32_t i{ 0 }; i < parts.size(); ++i)
        {
            qout << QCoreApplication::tr("Part %1:").arg(i + 1) << '\n';
            qout << parts[i] << "\n\n";
        }
    }
}

int main( int argc, char* argv[] )
{
    QCoreApplication app{ argc, argv };

    QTranslator qt_translator{};
    bool success{ qt_translator.load(QLocale(), "qtbase", "_",
        QLibraryInfo::location(QLibraryInfo::TranslationsPath)) };
    if (success)
    {
        std::ignore = app.installTranslator(&qt_translator);
    }

    QTranslator app_translator{};
    success = app_translator.load(QLocale(), "textcutter", "_", ":/translations");
    if (success)
    {
        std::ignore = app.installTranslator(&app_translator);
    }

    app.setApplicationName(QCoreApplication::tr("Text cutter"));

    common::TextCutter text_cutter{};

    QCommandLineParser command_line_parser{};
    command_line_parser.setApplicationDescription(
        QCoreApplication::tr("Cuts a text char by char into up to 10 parts."));
    command_line_parser.addHelpOption();

    const QCommandLineOption num_parts_option{
        {"n","num-parts"},
        QCoreApplication::tr("Number of parts to be generated.") + " " +
        QCoreApplication::tr("If not specified, the text will be cut into two parts."),
        QCoreApplication::tr("number"),
        "2"};
    command_line_parser.addOption(num_parts_option);

    //const QCommandLineOption output_files_option{
    //    {"o","output-files"},
    //    QCoreApplication::tr("Prefix of output file names.") + " " +
    //    QCoreApplication::tr("Files will be named <prefix>_<part number>.txt.") + " " +
    //    QCoreApplication::tr("If not specified, the text parts will be written to standard output."),
    //    QCoreApplication::tr("file prefix") };
    //command_line_parser.addOption(output_files_option);

    const QCommandLineOption input_file_option{
        {"i","input-file"},
        QCoreApplication::tr("Path to file with the original text.") + " " +
        QCoreApplication::tr("If specified, the \"%1\" command line argument will be ignored.").arg(
            QCoreApplication::tr("text")),
        QCoreApplication::tr("file name") };
    command_line_parser.addOption(input_file_option);

    command_line_parser.addPositionalArgument(QCoreApplication::tr("text"),
        QCoreApplication::tr("The original text to be cut."));

    command_line_parser.process(app);

    const std::int32_t num_parts{ ExtractNumberOfParts(command_line_parser.value(num_parts_option)) };

    QString input_text{};

    const QString input_file{ command_line_parser.value(input_file_option) };
    if (input_file.isEmpty())
    {
        const QStringList input_text_list{ command_line_parser.positionalArguments() };
        if (input_text_list.isEmpty())
        {
            qerr << QCoreApplication::tr("Input text is empty.") << '\n';
            exit(1);
        }
        input_text = input_text_list.front();
    }
    else
    {
        bool ok{false};
        QString error_msg{};
        input_text = text_cutter.LoadFile(input_file, &ok, &error_msg);
        if (!ok)
        {
            qerr << error_msg << '\n';
            exit(1);
        }
    }
    if (input_text.isEmpty())
    {
        qerr << QCoreApplication::tr("Input text is empty.") << '\n';
        exit(1);
    }

    const auto parts{text_cutter.CutText(input_text, num_parts)};
    OutputParts(parts);


    return 0;
}
