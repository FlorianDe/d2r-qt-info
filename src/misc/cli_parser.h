#include <QCommandLineParser>

#ifndef CLI_PARSER_H
#define CLI_PARSER_H

// https://doc.qt.io/qt-6/qcommandlineparser.html#how-to-use-qcommandlineparser-in-complex-applications
struct CommandLineParseResult {
	enum class Status { Ok, Error, VersionRequested, HelpRequested };
	Status statusCode = Status::Ok;										 // NOLINT(*-identifier-naming)
	std::optional<QString> errorString = std::nullopt; // NOLINT(*-identifier-naming)
};

namespace CLIParser {
CommandLineParseResult parseCommandLine(QCommandLineParser& parser);
}

#endif // CLI_PARSER_H
