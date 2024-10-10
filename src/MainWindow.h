#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "widgets/FilterWidget.h"
#include "widgets/RunewordDetailWidget.h"
#include <QLineEdit>
#include <QMainWindow>
#include <QScrollArea>
#include <QSplitter>

class MainWindow final : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(const std::vector<types::json::Runeword>& vector, const types::json::RunewordItemTypesHierarchy& runeword_item_types_hierarchy, QWidget* parent = nullptr);

protected:
	bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
	void updateTheme();
	void onRunewordSelectionChange(const QString& runeWord);
	void onFilterChanged(const FilterWidget::FilterState& filterState);

private:
	QWidget* m_centralWidget;
	QSplitter* m_splitter;
	FilterWidget* m_filterWidget;
	QVector<RunewordDetailWidget*> m_detailWidgets;
	QScrollArea* m_scrollArea;
	QWidget* m_scrollAreaContent;
	QVBoxLayout* m_scrollAreaLayout;

	std::vector<types::json::Runeword> m_runewords;
	types::json::RunewordItemTypesHierarchy m_runewordsItemTypesHierarchy;
};

#endif // MAINWINDOW_H