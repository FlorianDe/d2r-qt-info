#ifndef SOCKETAMOUNTCHECKBOXGRIDWIDGET_H
#define SOCKETAMOUNTCHECKBOXGRIDWIDGET_H

#include <QCheckBox>

class SocketAmountCheckBoxGridWidget final : public QWidget {
	Q_OBJECT

public:
	explicit SocketAmountCheckBoxGridWidget(QWidget* parent = nullptr, int columnCount = 5);
	QVector<int> getSelectedSocketAmounts() const;

	void reset();

private:
	QVector<QCheckBox*> m_checkBoxes;
};

#endif // SOCKETAMOUNTCHECKBOXGRIDWIDGET_H