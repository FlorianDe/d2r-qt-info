#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include "RuneCheckBoxGridWidget.h"
#include "SocketAmountCheckBoxGridWidget.h"

#include "json/types/types.h"
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QStringList>


class FilterWidget final : public QWidget {
	Q_OBJECT

public:
	struct FilterState {
		QString itemType;																							 // NOLINT(*-identifier-naming)
		QVector<int> selectedSocketOptions;														 // NOLINT(*-identifier-naming)
		QVector<QString> selectedRunes;																 // NOLINT(*-identifier-naming)
		RuneCheckBoxGridWidget::LogicalRunesOperator logicalRunesOperator; // NOLINT(*-identifier-naming)
	};

	explicit FilterWidget(const std::vector<types::json::Runeword>& runewords,
												const types::json::RunewordItemTypesHierarchy& runewordsItemTypesHierarchy,
												QWidget* parent = nullptr);

	FilterState getFilterState() const;

signals:
	void runewordSelectionChanged(const QString& runeWord);
	void filterChanged(const FilterWidget::FilterState& filterState);

private slots:
	void onSearchClicked();
	void onResetClicked();
	void onRuneWordSelected();

private:
	void populateItemTypes() const;
	void populateRuneWords() const;

	QComboBox* m_runeWordComboBox;
	QComboBox* m_itemTypeComboBox;
	SocketAmountCheckBoxGridWidget* m_socketsSelection;
	RuneCheckBoxGridWidget* m_runeCheckBoxWidget;
	QPushButton* m_searchButton;
	QPushButton* m_resetButton;
	const std::vector<types::json::Runeword>& m_runewords;
	const types::json::RunewordItemTypesHierarchy& m_runewordsItemTypesHierarchy;

};
#endif // FILTERWIDGET_H