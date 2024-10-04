#include <QApplication>
#include <QStyleHints>

#include "qt_utils.h"

namespace QtUtils {
bool isDarkMode() {
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
	const auto scheme = QApplication::styleHints()->colorScheme();
	return scheme == Qt::ColorScheme::Dark;
#else
	const QPalette defaultPalette;
	const auto text = defaultPalette.color(QPalette::WindowText);
	const auto window = defaultPalette.color(QPalette::Window);
	return text.lightness() > window.lightness();
#endif // QT_VERSION
}

}
