#include <QDebug>
#include <QDir>

namespace DebugUtils {

void printFiles(const QString &path) {
	constexpr auto sortFlags = QDir::DirsFirst | QDir::Name;
	constexpr auto fileFilters = QDir::AllEntries | QDir::NoDotAndDotDot;

	QDir dir(path);
	dir.setSorting(sortFlags);
	QFileInfoList entryList = dir.entryInfoList(fileFilters, dir.sorting());

	QList<QFileInfo> stack;
	for (const QFileInfo &entry : entryList) {
		stack.push_back(entry);
	}

	while (!stack.isEmpty()) {
		QFileInfo current = stack.takeLast();
		QString relativePath = current.absoluteFilePath().remove(0, path.length() + 1);
		const int level = relativePath.count(QDir::separator());  // Determine depth level for indentation

		qDebug().noquote() << QString("%1|__%2").arg(QString(level, ' '), current.fileName());

		if (current.isDir()) {
			QDir subDir(current.absoluteFilePath());
			subDir.setSorting(sortFlags);
			QFileInfoList subDirEntries = subDir.entryInfoList(fileFilters, subDir.sorting());

			for (const QFileInfo &subEntry : subDirEntries) {
				stack.push_back(subEntry);
			}
		}
	}
}
} // namespace DebugUtils