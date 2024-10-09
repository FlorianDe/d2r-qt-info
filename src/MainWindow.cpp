#include <QApplication>
#include <QDir>
#include <QMenuBar>
#include <QMessageBox>
#include <QOperatingSystemVersion>
#include <QPointer>
#include <QScreen>
#include <QStyleFactory>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>

#include "MainWindow.h"
#include "constants.h"
#include "misc/debug_utils.h"
#include "widgets/RunewordDetailWidget.h"
#include "json/types/types.h"
#include "json/utils.h"

#include <misc/qt_utils.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	qDebug() << "Default style:" << this->style()->objectName();
	if (QOperatingSystemVersion::currentType() == QOperatingSystemVersion::Windows) {
		const QString styleName = "Windows";
		if (QStyle* style = QStyleFactory::create(styleName)) {
			QApplication::setStyle(style);
		} else {
			qDebug() << "Failed to create and apply" << styleName << "for  OS:" << QOperatingSystemVersion::current().name();
		}
	}
	qDebug() << "Current style:" << this->style()->objectName();

	DebugUtils::printFiles(":/");

	constexpr int WIDTH = 1200;
	constexpr int HEIGHT = 600;

	m_centralWidget = new QWidget(this);
	this->setCentralWidget(m_centralWidget);

	m_splitter = new QSplitter(Qt::Horizontal, this);
	const QPointer mainLayout = new QVBoxLayout(m_centralWidget);
	mainLayout->addWidget(m_splitter);

	m_filterWidget = new FilterWidget(this);
	m_filterWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

	m_scrollArea = new QScrollArea(this);
	m_scrollAreaContent = new QWidget(this);
	m_scrollAreaLayout = new QVBoxLayout(m_scrollAreaContent);

	m_scrollAreaContent->setLayout(m_scrollAreaLayout);
	m_scrollArea->setWidget(m_scrollAreaContent);
	m_scrollArea->setWidgetResizable(true);
	m_scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	m_splitter->addWidget(m_filterWidget);
	m_splitter->addWidget(m_scrollArea);
	m_splitter->setSizes({100, WIDTH - 100}); // Initial size of widgets

	const auto runewords = JsonUtils::readJsonFile(QString::fromStdString(Constants::Files::RUNEWORDS))
														 .get<std::vector<types::json::Runeword>>();
	// auto runewordsHierarchy =
	// 	JsonUtils::readJsonFile(":/runeword_item_type_hierarchy.json").get<std::vector<types::json::Runeword>
	// >();

	m_scrollAreaLayout->addStretch();
	QList<QString> runewordTitles;
	for (const auto& rw : runewords) {
		RunewordDetailWidget::QtRunewordDetailModel runeWordData;

		runeWordData.title = QString::fromStdString(rw.title);
		runewordTitles << runeWordData.title;

		if (rw.version.has_value()) {
			runeWordData.version = QString::fromStdString(rw.version.value());
		}

		for (const auto& str : rw.runes) {
			runeWordData.runes << QString::fromStdString(str);
		}
		for (const auto& desc : rw.description) {
			runeWordData.attributes << QString::fromStdString(desc);
		}
		runeWordData.levelRequirement = rw.level;
		runeWordData.isClosedBnetLadder = rw.ladder;
		runeWordData.socketsNeeded = rw.runes.size();
		if (rw.ttypes.has_value()) {
			for (const auto& str : rw.ttypes.value()) {
				runeWordData.itemTypes.append(QString::fromStdString(str));
			}
		}

		RunewordDetailWidget* detailWidget = new RunewordDetailWidget(runeWordData, this);
		m_detailWidgets.append(detailWidget);
		m_scrollAreaLayout->addWidget(detailWidget);
	}
	m_scrollAreaLayout->addStretch();

	m_filterWidget->populateRuneWords(runewordTitles);

	this->connect(m_filterWidget, &FilterWidget::runewordSelectionChanged, this, &MainWindow::onRunewordSelectionChange);
	this->connect(m_filterWidget, &FilterWidget::filterChanged, this, &MainWindow::onFilterChanged);

	// QMenu *languageMenu = this->menuBar()->addMenu(tr("Language"));
	// QAction *englishAction = new QAction(tr("English"), this);
	// QAction *germanAction = new QAction(tr("German"), this);
	// connect(englishAction, &QAction::triggered, this, [this]() { switchLanguage("en"); });
	// connect(germanAction, &QAction::triggered, this, [this]() { switchLanguage("de"); });
	// languageMenu->addAction(englishAction);
	// languageMenu->addAction(germanAction);

	QMenu* helpMenu = this->menuBar()->addMenu(tr("Help"));
	const QPointer aboutAction = new QAction(tr("&About"), this);
	connect(aboutAction, &QAction::triggered, this, [this] {
		QMessageBox::about(this, tr("About"),
											 QCoreApplication::applicationName() + "\n\nVersion: " + QCoreApplication::applicationVersion() + "\n\nHash: "+CMAKE_DEF_COMMIT_HASH_VERSION);
	});
	helpMenu->addAction(aboutAction);

	// this->setMenuBar(bar);
	this->setUnifiedTitleAndToolBarOnMac(true); // macos specific settings

	this->updateTheme();
	this->installEventFilter(this);

	// Set the size of the main window
	this->resize(WIDTH, HEIGHT);
	this->show();
}

void MainWindow::updateTheme() {

	// if (QtUtils::isDarkMode()) {
	// 	this->setStyleSheet(R"(
	//            QWidget {
	//                background-color: #00ff00;
	//            }
	//        )");
	// } else {
	// 	this->setStyleSheet(R"(
	//            QWidget {
	//                background-color: #ff0000;
	//            }
	//        )");
	// }

	// QPalette darkPalette;
	// darkPalette.setColor(QPalette::Window,QColor(53,53,53));
	// darkPalette.setColor(QPalette::WindowText,Qt::white);
	// darkPalette.setColor(QPalette::Disabled,QPalette::WindowText,QColor(127,127,127));
	// darkPalette.setColor(QPalette::Base,QColor(42,42,42));
	// darkPalette.setColor(QPalette::AlternateBase,QColor(66,66,66));
	// darkPalette.setColor(QPalette::ToolTipBase,Qt::white);
	// darkPalette.setColor(QPalette::ToolTipText,Qt::white);
	// darkPalette.setColor(QPalette::Text,Qt::white);
	// darkPalette.setColor(QPalette::Disabled,QPalette::Text,QColor(127,127,127));
	// darkPalette.setColor(QPalette::Dark,QColor(35,35,35));
	// darkPalette.setColor(QPalette::Shadow,QColor(20,20,20));
	// darkPalette.setColor(QPalette::Button,QColor(53,53,53));
	// darkPalette.setColor(QPalette::ButtonText,Qt::white);
	// darkPalette.setColor(QPalette::Disabled,QPalette::ButtonText,QColor(127,127,127));
	// darkPalette.setColor(QPalette::BrightText,Qt::red);
	// darkPalette.setColor(QPalette::Link,QColor(42,130,218));
	// darkPalette.setColor(QPalette::Highlight,QColor(42,130,218));
	// darkPalette.setColor(QPalette::Disabled,QPalette::Highlight,QColor(80,80,80));
	// darkPalette.setColor(QPalette::HighlightedText,Qt::white);
	// darkPalette.setColor(QPalette::Disabled,QPalette::HighlightedText,QColor(127,127,127));
	// this->setPalette(darkPalette);
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
	if (event->type() == QEvent::ThemeChange) {
		qDebug() << "Update theme. To dark mode?:" << QtUtils::isDarkMode();
		updateTheme();
		return true;
	}
	return QMainWindow::eventFilter(obj, event);
}

void MainWindow::onRunewordSelectionChange(const QString& runeWord) {
	qDebug() << "Selected runeWord: " << runeWord;

	for (auto* detailWidget : this->m_detailWidgets) {
		if (auto rw = detailWidget->getRuneWord(); runeWord == nullptr ? true : runeWord == rw.title) {
			detailWidget->show();
		} else {
			detailWidget->hide();
		}
	}
}

void MainWindow::onFilterChanged(const FilterWidget::FilterState& filterState) {
	const auto [itemType, selectedSocketOptions, selectedRunes, logicalRunesOperator] = filterState;

	qDebug() << "\nSelected itemType: " << itemType;
	qDebug() << "Selected selectedSocketOptions: "
					 << std::accumulate(selectedSocketOptions.begin(), selectedSocketOptions.end(), QString(),
															[](const QString& a, int b) {
																return a.isEmpty() ? QString::number(b) : a + ", " + QString::number(b);
															});

	qDebug() << "Selected runes: " << selectedRunes.join(", ");
	qDebug() << "Selected mode: "
					 << (logicalRunesOperator == RuneCheckBoxGridWidget::LogicalRunesOperator::OR ? "OR" : "AND");

	for (auto* detailWidget : this->m_detailWidgets) {
		auto rw = detailWidget->getRuneWord();

		const bool itemTypeMatches = itemType == nullptr ? true : true;
		const bool socketsMatched = selectedSocketOptions.isEmpty()
																		? true
																		: std::find(selectedSocketOptions.begin(), selectedSocketOptions.end(),
																								rw.socketsNeeded) != selectedSocketOptions.end();
		const bool allRunesInsideRw =
				selectedRunes.isEmpty() ? true
																: std::all_of(selectedRunes.begin(), selectedRunes.end(), [&rw](const auto& item) {
																		return std::find(rw.runes.begin(), rw.runes.end(), item) != rw.runes.end();
																	});
		const bool someRunesInsideRw =
				selectedRunes.isEmpty() ? true
																: std::any_of(selectedRunes.begin(), selectedRunes.end(), [&rw](const auto& item) {
																		return std::find(rw.runes.begin(), rw.runes.end(), item) != rw.runes.end();
																	});

		const bool runesFilter =
				logicalRunesOperator == RuneCheckBoxGridWidget::LogicalRunesOperator::OR ? someRunesInsideRw : allRunesInsideRw;

		if (itemTypeMatches && socketsMatched && runesFilter) {
			detailWidget->show();
		} else {
			detailWidget->hide();
		}
	}
}
