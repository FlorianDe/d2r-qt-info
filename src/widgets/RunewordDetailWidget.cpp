#include "RunewordDetailWidget.h"

#include "FilterWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>

RunewordDetailWidget::RunewordDetailWidget(const QtRunewordDetailModel& runeWord, QWidget* parent)
		: QWidget(parent), m_runeword(runeWord) {
	setupUI(runeWord);
}

void RunewordDetailWidget::setupUI(const QtRunewordDetailModel& runeWord) {
	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	// Add sections to the main layout
	mainLayout->addWidget(createTitleAndRunesSection(runeWord));
	mainLayout->addWidget(createAttributesSection(runeWord));
	mainLayout->addWidget(createVersionAndCompatibilitySection(runeWord));

	setLayout(mainLayout);
}

QWidget* RunewordDetailWidget::createTitleAndRunesSection(const QtRunewordDetailModel& runeWord) {
	QWidget* section = new QWidget(this);
	section->setStyleSheet("background-color: #45070E;");

	QVBoxLayout* layout = new QVBoxLayout(section);
	layout->setContentsMargins(0, 0, 0, 0);

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
	section->setStyleSheet("background-color: #2E2927;");

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
	// attributesContent->setStyleSheet("border: 1px solid red;");
	attributesLayout->setContentsMargins(0, 0, 0, 0);
	attributesLayout->setSpacing(0);

	// Header label for description
	QLabel* headerLabel = new QLabel("Eigenschaften des Runenworts:", attributesContent);
	headerLabel->setAlignment(Qt::AlignCenter);
	headerLabel->setStyleSheet("font-weight: bold;");
	headerLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
	attributesLayout->addWidget(headerLabel);

	QLabel* attributeLabel = new QLabel(runeWord.attributes.join("\n"), attributesContent);
	attributeLabel->setAlignment(Qt::AlignCenter);
	attributeLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
	// attributeLabel->setWordWrap(true);
	attributesLayout->addWidget(attributeLabel);

	// for (std::size_t i = 0; i < runeWord.attributes.size(); ++i) {
	//     QLabel *attributeLabel = new QLabel(runeWord.attributes[i], attributesContent);
	//     if(i % 2 == 0){
	//         attributeLabel->setStyleSheet("background-color: #2E2927;");
	//     } else {
	//         attributeLabel->setStyleSheet("background-color: #25211F;");
	//     }

	//     attributeLabel->setAlignment(Qt::AlignCenter);
	//     attributeLabel->setWordWrap(true);
	//     attributesLayout->addWidget(attributeLabel);
	// }

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
	section->setStyleSheet("background-color: #2E2927; padding: 0; margin: 0");

	QVBoxLayout* layout = new QVBoxLayout(section);
	layout->setContentsMargins(0, 0, 0, 0);

	// // Create a QTextEdit widget
	// QTextEdit *textEdit = new QTextEdit;

	// // Set the QTextEdit to read-only
	// textEdit->setReadOnly(true);
	// textEdit->setFrameStyle(QFrame::NoFrame);
	// textEdit->setContentsMargins(0, 0, 0, 0);

	// Set multiline formatted text
	const QString templateString = "<b>Available in:</b> %1<br>"
																 "<b>Version:</b> %2<br>"
																 "<b>Sockets:</b> genau %3<br>"
																 "<b>Gegenstand:</b> %4";
	const QString result = templateString.arg(runeWord.isClosedBnetLadder ? "Closed BNet Ladder" : "Non-Ladder")
														 .arg(runeWord.version == "" ? "Since beginning" : runeWord.version)
														 .arg(runeWord.socketsNeeded)
														 .arg(runeWord.itemTypes.join(", "));

	QLabel* footerTextLabel = new QLabel(this);
	footerTextLabel->setText(result);
	footerTextLabel->setAlignment(Qt::AlignCenter);
	footerTextLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

	layout->addWidget(footerTextLabel);

	section->setLayout(layout);

	return section;
}

RunewordDetailWidget::QtRunewordDetailModel RunewordDetailWidget::getRuneWord() const { return this->m_runeword; }