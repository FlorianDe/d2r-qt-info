#include "FilterWidget.h"
#include "RuneCheckBoxGridWidget.h"
#include "SocketAmountCheckBoxGridWidget.h"

#include <QApplication>
#include <QComboBox>
#include <QPainter>
#include <QStandardItem>
#include <QStyledItemDelegate>

#include <QGroupBox>
#include <QPointer>

struct BaseItemTypeComboBoxModel {
	QIcon image;		 // NOLINT(*-identifier-naming)
	int indentation; // NOLINT(*-identifier-naming)
};
class BaseItemTypeComboBoxDelegate : public QStyledItemDelegate {
public:
	BaseItemTypeComboBoxDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
		painter->save();

		const auto extraDataVariant = index.data(Qt::UserRole);
		const auto extraData = qvariant_cast<BaseItemTypeComboBoxModel>(extraDataVariant);
		QString text = index.data(Qt::DisplayRole).toString();

		// Draw the background
		painter->fillRect(option.rect,
											option.state & QStyle::State_Selected ? option.palette.highlight() : option.palette.window());

		// Draw the icon
		if (!extraDataVariant.isValid()) {
			qDebug() << "QVariant data is invalid";
		} else {
			if (!extraData.image.isNull()) {
				QPixmap pixmap = extraData.image.pixmap(12, 12);
				QRect iconRect(option.rect.x() + 5 + extraData.indentation * 20,
											 option.rect.y() + (option.rect.height() - pixmap.height()) / 2, pixmap.width(), pixmap.height());
				painter->drawPixmap(iconRect, pixmap);
			} else {
				qDebug() << "Icon not found for QCombobox:" << text;
			}
		}

		// Calculate the indentation for the text
		QRect textRect(option.rect.x() + 35 + extraData.indentation * 20, option.rect.y(), option.rect.width() - 25,
									 option.rect.height());
		painter->drawText(textRect, Qt::AlignVCenter | Qt::TextWordWrap, text);

		painter->restore();
	}

	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override {
		return QSize(option.rect.width(), 32);
	}
};

FilterWidget::FilterWidget(QWidget* parent) : QWidget(parent) { setupUI(); }

void FilterWidget::setupUI() {
	const QPointer mainLayout = new QVBoxLayout();

	QLabel* runeWordLabel = new QLabel(tr("Select runeword") + ":", this);
	m_runeWordComboBox = new QComboBox(this);
	this->connect(m_runeWordComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
								&FilterWidget::onRuneWordSelected);

	// Create a horizontal line as a divider
	QFrame* line = new QFrame(this);
	line->setFrameShape(QFrame::HLine);		// Horizontal line
	line->setFrameShadow(QFrame::Sunken); // Sunken style

	QLabel* itemTypeLabel = new QLabel(tr("Select item type") + ":", this);

	m_itemTypeComboBox = new QComboBox(this);
	m_itemTypeComboBox->setItemDelegate(new BaseItemTypeComboBoxDelegate(this));
	QStringList items = {"Weapons", "Armors", "Shields", "Axes"};
	for (int i = 0; i < items.size(); ++i) {
		const auto iconPath = ":/images/item_base_types/" + items[i].toLower() + ".png";
		auto image = QIcon(iconPath);
		BaseItemTypeComboBoxModel extraData{image, 0};
		m_itemTypeComboBox->addItem(items[i], QVariant::fromValue(extraData));
	}
	// populateItemTypes();

	QVBoxLayout* socketSelectionLayout = new QVBoxLayout();
	QLabel* socketsSelectionLabel = new QLabel(tr("Sockets"));
	m_socketsSelection = new SocketAmountCheckBoxGridWidget(this, 5);
	socketSelectionLayout->addWidget(socketsSelectionLabel);
	socketSelectionLayout->addWidget(m_socketsSelection);

	m_runeCheckBoxWidget = new RuneCheckBoxGridWidget(this);

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	m_searchButton = new QPushButton(tr("Search"), this);
	this->connect(m_searchButton, &QPushButton::clicked, this, &FilterWidget::onSearchClicked);
	m_resetButton = new QPushButton(tr("Reset"), this);
	this->connect(m_resetButton, &QPushButton::clicked, this, &FilterWidget::onResetClicked);
	buttonLayout->addWidget(m_searchButton);
	buttonLayout->addWidget(m_resetButton);

	mainLayout->addWidget(runeWordLabel);
	mainLayout->addWidget(m_runeWordComboBox);
	mainLayout->addWidget(line);
	mainLayout->addWidget(itemTypeLabel);
	mainLayout->addWidget(m_itemTypeComboBox);
	mainLayout->addLayout(socketSelectionLayout);
	mainLayout->addWidget(m_runeCheckBoxWidget);

	mainLayout->addLayout(buttonLayout);

	this->setLayout(mainLayout);
}

void FilterWidget::onRuneWordSelected() {
	const QString runeWord = m_runeWordComboBox->currentIndex() == -1 ? nullptr : m_runeWordComboBox->currentText();
	emit runewordSelectionChanged(runeWord);
}

void FilterWidget::populateItemTypes() const {
	// TODO: initialize
	const QList<QString> baseTypes = {"Weapon", "Armor", "Shield", "Accessory"};
	m_itemTypeComboBox->addItems(baseTypes);
	m_itemTypeComboBox->setCurrentIndex(-1);
}

void FilterWidget::populateRuneWords(const QList<QString>& runewords) const {
	auto rws = runewords;
	rws.sort();
	m_runeWordComboBox->addItems(rws);
	m_runeWordComboBox->setCurrentIndex(-1);
}
FilterWidget::FilterState FilterWidget::getFilterState() const {
	const QString itemType = m_itemTypeComboBox->currentIndex() == -1 ? nullptr : m_itemTypeComboBox->currentText();
	const QVector<int> selectedSocketOptions = m_socketsSelection->getSelectedSocketAmounts();
	const QVector<QString> selectedRunes = m_runeCheckBoxWidget->getSelectedRunes();
	const RuneCheckBoxGridWidget::LogicalRunesOperator logicalRunesOperator =
			m_runeCheckBoxWidget->getSelectedRunesOperator();

	return {
			itemType,
			selectedSocketOptions,
			selectedRunes,
			logicalRunesOperator,
	};
}

void FilterWidget::onSearchClicked() { emit filterChanged(this->getFilterState()); }

void FilterWidget::onResetClicked() {
	m_runeWordComboBox->setCurrentIndex(-1);
	m_itemTypeComboBox->setCurrentIndex(-1);
	m_socketsSelection->reset();
	m_runeCheckBoxWidget->reset();

	emit filterChanged(
			{nullptr, m_socketsSelection->getSelectedSocketAmounts(), m_runeCheckBoxWidget->getSelectedRunes()});
}