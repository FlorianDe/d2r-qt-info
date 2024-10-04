#include "cli_parser.h"

namespace CLIParser {
CommandLineParseResult parseCommandLine(QCommandLineParser& parser) {
	using Status = CommandLineParseResult::Status;
	parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
	const QCommandLineOption helpOption = parser.addHelpOption();
	const QCommandLineOption versionOption = parser.addVersionOption();

	if (!parser.parse(QCoreApplication::arguments()))
		return {Status::Error, parser.errorText()};

	if (parser.isSet(versionOption))
		return {Status::VersionRequested};

	if (parser.isSet(helpOption))
		return {Status::HelpRequested};

	return {Status::Ok};
}
};