#include "SocketAmountCheckBoxGridWidget.h"
#include "RuneCheckBoxGridWidget.h"

#include <QPointer>

SocketAmountCheckBoxGridWidget::SocketAmountCheckBoxGridWidget(QWidget* parent, const int columnCount) : QWidget(parent) {

	const QPointer gridLayout = new QGridLayout(this);
	// gridLayout->setContentsMargins(0, 0, 0, 0);
	// gridLayout->setSpacing(0);
	// gridLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	int row = 0, col = 0;
	for (int i = 2; i <= 6; i++) {
		QPointer checkBox = new QCheckBox(QString::number(i), this);

		m_checkBoxes.append(checkBox);

		gridLayout->addWidget(checkBox, row, col);

		col++;
		if (col == columnCount) {
			col = 0;
			row++;
		}
	}

	this->setLayout(gridLayout);
}

void SocketAmountCheckBoxGridWidget::reset() {
	for (auto* checkBox : m_checkBoxes) {
		checkBox->setChecked(false);
	}
}

// Get the names of the selected runes (checkboxes that are checked)
QVector<int> SocketAmountCheckBoxGridWidget::getSelectedSocketAmounts() const {
	QVector<int> selectedSocketAmounts;
	for (const auto* checkBox : m_checkBoxes) {
		if (checkBox->isChecked()) {
			selectedSocketAmounts.append(checkBox->text().toInt());
		}
	}
	return selectedSocketAmounts;
}