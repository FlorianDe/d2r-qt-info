#include <QApplication>

#include "MainWindow.h"
#include "constants.h"

#include "misc/cli_parser.h"

int main(int argc, char* argv[]) {
	Q_INIT_RESOURCE(resources);
	QApplication app(argc, argv);
	QCoreApplication::setApplicationName(CMAKE_DEF_APP_NAME);
	QCoreApplication::setApplicationVersion(CMAKE_DEF_PROJECT_VERSION);
	QCoreApplication::setOrganizationName(CMAKE_DEF_ORG_COMPANY);
	QCoreApplication::setOrganizationDomain(CMAKE_DEF_ORG_DOMAIN);

	QCommandLineParser parser;

	const auto [statusCode, errorString] = CLIParser::parseCommandLine(parser);

	using Status = CommandLineParseResult::Status;
	switch (statusCode) {
	case Status::Ok:
		break;
	case Status::Error:
		std::fputs(qPrintable(errorString.value_or("Unknown error occurred")), stderr);
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