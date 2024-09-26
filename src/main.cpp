#include <QApplication>

#include "constants.h"
#include "MainWindow.h"


int main(int argc, char* argv[]) {
	Q_INIT_RESOURCE(resources);
	QApplication app(argc, argv);
	QCoreApplication::setApplicationName(CMAKE_DEF_APP_NAME);
	QCoreApplication::setApplicationVersion(CMAKE_DEF_PROJECT_VERSION);
	QCoreApplication::setOrganizationName(CMAKE_DEF_ORG_COMPANY);
	QCoreApplication::setOrganizationDomain(CMAKE_DEF_ORG_DOMAIN);

	QIcon appIcon;
	appIcon.addFile(QString::fromStdString(Constants::Files::APP_ICON_PATH));
	app.setWindowIcon(appIcon);

	MainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}