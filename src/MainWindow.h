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
	explicit MainWindow(QWidget* parent = nullptr);

private slots:
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
};

#endif // MAINWINDOW_H