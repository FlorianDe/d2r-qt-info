#include <QApplication>
#include <QCommandLineParser>

#include "MainWindow.h"
#include "constants.h"

// https://doc.qt.io/qt-6/qcommandlineparser.html#how-to-use-qcommandlineparser-in-complex-applications
struct CommandLineParseResult {
	enum class Status { Ok, Error, VersionRequested, HelpRequested };
	Status statusCode = Status::Ok;
	std::optional<QString> errorString = std::nullopt;
};

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

int main(int argc, char* argv[]) {
	Q_INIT_RESOURCE(resources);
	QApplication app(argc, argv);
	QCoreApplication::setApplicationName(CMAKE_DEF_APP_NAME);
	QCoreApplication::setApplicationVersion(CMAKE_DEF_PROJECT_VERSION);
	QCoreApplication::setOrganizationName(CMAKE_DEF_ORG_COMPANY);
	QCoreApplication::setOrganizationDomain(CMAKE_DEF_ORG_DOMAIN);

	QCommandLineParser parser;

	using Status = CommandLineParseResult::Status;
	CommandLineParseResult parseResult = parseCommandLine(parser);
	switch (parseResult.statusCode) {
	case Status::Ok:
		break;
	case Status::Error:
		std::fputs(qPrintable(parseResult.errorString.value_or("Unknown error occurred")), stderr);
		std::fputs("\n\n", stderr);
		std::fputs(qPrintable(parser.helpText()), stderr);
		return 1;
	case Status::VersionRequested:
		parser.showVersion();
		Q_UNREACHABLE_RETURN(0);
	case Status::HelpRequested:
		parser.showHelp();
		Q_UNREACHABLE_RETURN(0);
	}

	QIcon appIcon;
	appIcon.addFile(QString::fromStdString(Constants::Files::APP_ICON_PATH));
	app.setWindowIcon(appIcon);

	MainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}