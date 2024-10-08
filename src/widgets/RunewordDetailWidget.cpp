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
	// language=CSS
	section->setStyleSheet(R"(
	#section {
		background-color: #45070E;
		border: 2px solid #212121;
	}
	)");

	QVBoxLayout* layout = new QVBoxLayout(section);
	layout->setContentsMargins(0, 5, 0, 5);

	QLabel* titleLabel = new QLabel(runeWord.title, section);
	titleLabel->setAlignment(Qt::AlignCenter);
	// language=CSS
	titleLabel->setStyleSheet(R"(*{
		font-weight: bold;
		color: #ffe979;
		padding: 0px;
	})");

	QLabel* runesLabel = new QLabel(runeWord.runes.join(", "), section);
	runesLabel->setAlignment(Qt::AlignCenter);
	// language=CSS
	runesLabel->setStyleSheet(R"(*{
		color: #ffffff;
	})");

	layout->addWidget(titleLabel);
	layout->addWidget(runesLabel);

	section->setLayout(layout);

	return section;
}

QString RunewordDetailWidget::getRuneImagePath(const QString& rune) {
	return ":/images/runes/" + rune.toLower() + "_rune.png";
}

QWidget* RunewordDetailWidget::createAttributesSection(const QtRunewordDetailModel& runeWord) {
	constexpr int RUNE_SIZE = 48;
	QWidget* section = new QWidget(this);
	section->setObjectName("section");
	// language=CSS
	section->setStyleSheet(R"(
	#section{
		background-color: #2E2927;
		border: 2px solid #212121;
	}
	* {
		color: #ffffff;
	}
	)");

	QHBoxLayout* mainLayout = new QHBoxLayout(section);
	mainLayout->setContentsMargins(10, 10, RUNE_SIZE+2*10, 10);

	QWidget* runeContent = new QWidget(this);
	runeContent->setFixedWidth(RUNE_SIZE);
	QVBoxLayout* runeContentLayout = new QVBoxLayout(runeContent);
	runeContentLayout->setContentsMargins(0, 0, 0, 0);
	runeContentLayout->setSpacing(0);

	for (const QString& rune : runeWord.runes) {
		const auto runeImagePath = getRuneImagePath(rune);

		QPixmap icon(runeImagePath);
		if (icon.isNull()) {
			qDebug() << "Failed loading pixmap from path: " << runeImagePath;
		} else {
			QLabel* iconLabel = new QLabel(this);
			iconLabel->setFixedSize(RUNE_SIZE, RUNE_SIZE);

			iconLabel->setPixmap(icon.scaled(iconLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
			iconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

			runeContentLayout->addWidget(iconLabel);
		}
	}

	QWidget* attributesContent = new QWidget(this);
	QVBoxLayout* attributesLayout = new QVBoxLayout(attributesContent);
	attributesLayout->setContentsMargins(0, 0, 0, 0);
	attributesLayout->setSpacing(0);

	// Header label for description
	QLabel* headerLabel = new QLabel(tr("Properties of the Runeword:"), attributesContent);
	headerLabel->setAlignment(Qt::AlignCenter);
	headerLabel->setStyleSheet("font-weight: bold;");
	headerLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
	attributesLayout->addWidget(headerLabel);

	QLabel* attributeLabel = new QLabel(runeWord.attributes.join("\n"), attributesContent);
	attributeLabel->setAlignment(Qt::AlignCenter);
	attributeLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
	// attributeLabel->setWordWrap(true);
	attributesLayout->addWidget(attributeLabel);

	const QString templateString = tr("Level Requirements: %1");
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
	// language=CSS
	section->setStyleSheet(R"(
	#section{
		background-color: #2E2927;
		border: 2px solid #212121;
	}
	* {
		color: #ffffff;
	}
)");

	QVBoxLayout* layout = new QVBoxLayout(section);
	layout->setSpacing(5);

	const QString templateString = tr("<b>Available in:</b> %1<br>"
																		"<b>Version:</b> %2<br>"
																		"<b>Sockets:</b> %3<br>"
																		"<b>Item type/s:</b> %4");
	const QString result = templateString.arg(runeWord.isClosedBnetLadder ? tr("Closed BNet Ladder") : tr("Non-Ladder"))
														 .arg(runeWord.version == "" ? tr("Since beginning") : runeWord.version)
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