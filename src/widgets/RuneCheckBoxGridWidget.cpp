#include "CheckBoxImageWidget.h"
#include "RuneCheckBoxGridWidget.h"

#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>

RuneCheckBoxGridWidget::RuneCheckBoxGridWidget(QWidget* parent, const int columnCount) : QWidget(parent) {

	QGroupBox *groupBox = new QGroupBox("Runes selection", this);
	QVBoxLayout *layout = new QVBoxLayout(groupBox);
	// this->setStyleSheet("border: 1px solid red;");

	QWidget* gridWidget = new QWidget(this);
	QGridLayout* gridLayout = new QGridLayout(gridWidget);
	gridLayout->setContentsMargins(0, 0, 0, 0);
	gridLayout->setSpacing(0);
	gridLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	gridWidget->setLayout(gridLayout);

	QWidget* radioButtonWidget = new QWidget(this);
	QLabel *radioButtonLabel = new QLabel("Select an option:", this);
	QRadioButton *orRadioButton = new QRadioButton("OR", this);
	orRadioButton->setChecked(true);
	QRadioButton *andRadioButton = new QRadioButton("AND", this);
	QHBoxLayout *radioButtonsLayout = new QHBoxLayout(radioButtonWidget);
	radioButtonsLayout->addWidget(radioButtonLabel);
	radioButtonsLayout->addWidget(orRadioButton);
	radioButtonsLayout->addWidget(andRadioButton);
	// Create a QButtonGroup to manage the radio buttons
	m_logicalOperatorButtonGroup = new QButtonGroup(this);

	// Add the radio buttons to the group
	m_logicalOperatorButtonGroup->addButton(orRadioButton, static_cast<int>(LogicalRunesOperator::OR));
	m_logicalOperatorButtonGroup->addButton(andRadioButton, static_cast<int>(LogicalRunesOperator::AND));

	// Array of runes (placeholders for rune names)
	QList<QString> runeNames = {"El",	"Eld",	 "Tir", "Nef", "Eth", "Ith", "Tal", "Ral", "Ort", "Thul", "Amn",
													 "Sol", "Shael", "Dol", "Hel", "Io",	"Lum", "Ko",	"Fal", "Lem", "Pul",	"Um",
													 "Mal", "Ist",	 "Gul", "Vex", "Ohm", "Lo",	 "Sur", "Ber", "Jah", "Cham", "Zod"};

	int row = 0, col = 0;
	for (int i = 0; i < runeNames.size(); ++i) {
		CheckBoxImageWidget* checkBox =
				new CheckBoxImageWidget(":/runes/" + runeNames[i].toLower() + "_rune.png.webp", runeNames[i], this);

		m_checkBoxes.append(checkBox);

		gridLayout->addWidget(checkBox, row, col);

		// Move to the next column or row if necessary
		col++;
		if (col == columnCount) {
			col = 0;
			row++;
		}
	}

	// const int dimensions = 4;
	// // Vertical spacers
	// gridLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 0, 1, dimensions +
	// 2); gridLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), dimensions + 1, 0,
	// 1, dimensions + 2);

	// // Horizontal spacers
	// gridLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 1, 0, dimensions, 1);
	// gridLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 1, dimensions + 1,
	// dimensions, 1); this->setStyleSheet("border: 1px solid red;");

	layout->addWidget(gridWidget);
	layout->addWidget(radioButtonWidget);

	groupBox->setLayout(layout);
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(groupBox);
	setLayout(mainLayout);
}

void RuneCheckBoxGridWidget::reset() {
	for (auto* checkBox : m_checkBoxes) {
		checkBox->setChecked(false);
	}
}

// Get the names of the selected runes (checkboxes that are checked)
QVector<QString> RuneCheckBoxGridWidget::getSelectedRunes() const {
	QVector<QString> selectedRunes;
	for (const auto* checkBox : m_checkBoxes) {
		if (checkBox->isChecked()) {
			selectedRunes.append(checkBox->text());
		}
	}
	return selectedRunes;
}
RuneCheckBoxGridWidget::LogicalRunesOperator RuneCheckBoxGridWidget::getSelectedRunesOperator() const {
	int selectedId = m_logicalOperatorButtonGroup->checkedId();
	return static_cast<LogicalRunesOperator>(selectedId);
}