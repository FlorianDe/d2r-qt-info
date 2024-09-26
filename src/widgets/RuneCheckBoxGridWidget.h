#ifndef RUNECHECKBOXWIDGET_H
#define RUNECHECKBOXWIDGET_H

#include "CheckBoxImageWidget.h"
#include <QGridLayout>
#include <QVector>

class RuneCheckBoxGridWidget final : public QWidget {
	Q_OBJECT

public:
	enum class LogicalRunesOperator {
		OR,
		AND
	};


	explicit RuneCheckBoxGridWidget(QWidget* parent = nullptr, int columnCount = 4);
	QVector<QString> getSelectedRunes() const;
	LogicalRunesOperator getSelectedRunesOperator() const;

	void reset();

private:
	QVector<CheckBoxImageWidget*> m_checkBoxes;
	QButtonGroup* m_logicalOperatorButtonGroup;
};

#endif // RUNECHECKBOXWIDGET_H