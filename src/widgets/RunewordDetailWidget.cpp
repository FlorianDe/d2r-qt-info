#include "RunewordDetailWidget.h"

#include "FilterWidget.h"

#include <QLabel>
#include <QTextEdit>

RunewordDetailWidget::RunewordDetailWidget(const QtRunewordDetailModel& runeWord, QWidget* parent)
		: QWidget(parent), m_runeword(runeWord) {
	setupUI(runeWord);
}

void RunewordDetailWidget::setupUI(const QtRunewordDetailModel& runeWord) {
	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	mainLayout->addWidget(createTitleAndRunesSection(runeWord));
	mainLayout->addWidget(createAttributesSection(runeWord));
	mainLayout->addWidget(createVersionAndCompatibilitySection(runeWord));
	mainLayout->setSpacing(1);

	setLayout(mainLayout);
}

QWidget* RunewordDetailWidget::createTitleAndRunesSection(const QtRunewordDetailModel& runeWord) {
	QWidget* section = new QWidget(this);
	section->setObjectName("section");
	section->setStyleSheet("#section {background-color: #45070E; color: #FBFF79; border: 2px solid #212121;}");

	QVBoxLayout* layout = new QVBoxLayout(section);
	layout->setContentsMargins(0, 5, 0, 5);

	QLabel* titleLabel = new QLabel(runeWord.title, section);
	titleLabel->setAlignment(Qt::AlignCenter);
	// titleLabel->setStyleSheet("font-weight: bold; color: yellow; padding: 0px;");

	QLabel* runesLabel = new QLabel(runeWord.runes.join(", "), section);
	runesLabel->setAlignment(Qt::AlignCenter);

	layout->addWidget(titleLabel);
	layout->addWidget(runesLabel);

	section->setLayout(layout);

	return section;
}

QWidget* RunewordDetailWidget::createAttributesSection(const QtRunewordDetailModel& runeWord) {
	constexpr int RUNE_SIZE = 48;
	QWidget* section = new QWidget(this);
	section->setObjectName("section");
	section->setStyleSheet("#section{background-color: #2E2927; color: #ffffff; border: 2px solid #212121;}");

	QHBoxLayout* mainLayout = new QHBoxLayout(section);

	QWidget* runeContent = new QWidget(this);
	runeContent->setFixedWidth(RUNE_SIZE);
	QVBoxLayout* runeContentLayout = new QVBoxLayout(runeContent);
	runeContentLayout->setContentsMargins(0, 0, 0, 0);
	runeContentLayout->setSpacing(0);

	for (const QString& rune : runeWord.runes) {
		QPixmap icon(":/runes/" + rune.toLower() + "_rune.png.webp");
		QLabel* iconLabel = new QLabel(this);
		iconLabel->setFixedSize(RUNE_SIZE, RUNE_SIZE);

		iconLabel->setPixmap(icon.scaled(iconLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
		iconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

		runeContentLayout->addWidget(iconLabel);
	}

	QWidget* attributesContent = new QWidget(this);
	QVBoxLayout* attributesLayout = new QVBoxLayout(attributesContent);
	attributesLayout->setContentsMargins(0, 0, 0, 0);
	attributesLayout->setSpacing(0);

	// Header label for description
	QLabel* headerLabel = new QLabel("Properties of the Runeword:", attributesContent);
	headerLabel->setAlignment(Qt::AlignCenter);
	headerLabel->setStyleSheet("font-weight: bold;");
	headerLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
	attributesLayout->addWidget(headerLabel);

	QLabel* attributeLabel = new QLabel(runeWord.attributes.join("\n"), attributesContent);
	attributeLabel->setAlignment(Qt::AlignCenter);
	attributeLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
	// attributeLabel->setWordWrap(true);
	attributesLayout->addWidget(attributeLabel);

	const QString templateString = "Level Requirements: %1";
	QLabel* levelRequirementLabel = new QLabel(templateString.arg(runeWord.levelRequirement), section);
	levelRequirementLabel->setAlignment(Qt::AlignCenter);
	levelRequirementLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
	levelRequirementLabel->setStyleSheet("padding-top: 10px;");
	attributesLayout->addWidget(levelRequirementLabel);

	mainLayout->addWidget(runeContent);
	mainLayout->addWidget(attributesContent);

	section->setLayout(mainLayout);

	return section;
}

QWidget* RunewordDetailWidget::createVersionAndCompatibilitySection(const QtRunewordDetailModel& runeWord) {
	QWidget* section = new QWidget(this);
	section->setObjectName("section");
	section->setStyleSheet("#section{background-color: #2E2927; color: #ffffff; border: 2px solid #212121;}");

	QVBoxLayout* layout = new QVBoxLayout(section);
	layout->setSpacing(5);

	const QString templateString = "<b>Available in:</b> %1<br>"
																 "<b>Version:</b> %2<br>"
																 "<b>Sockets:</b> %3<br>"
																 "<b>Item type/s:</b> %4";
	const QString result = templateString.arg(runeWord.isClosedBnetLadder ? "Closed BNet Ladder" : "Non-Ladder")
														 .arg(runeWord.version == "" ? "Since beginning" : runeWord.version)
														 .arg(runeWord.socketsNeeded)
														 .arg(runeWord.itemTypes.join(", "));

	QLabel* footerTextLabel = new QLabel(this);
	footerTextLabel->setText(result);
	footerTextLabel->setAlignment(Qt::AlignCenter);
	footerTextLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
	footerTextLabel->setStyleSheet("border: 0px;");

	layout->addWidget(footerTextLabel);

	section->setLayout(layout);

	return section;
}

RunewordDetailWidget::QtRunewordDetailModel RunewordDetailWidget::getRuneWord() const { return this->m_runeword; }