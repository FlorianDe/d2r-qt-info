#include <QFile>
#include <QMenuBar>
#include <QMessageBox>
#include <QPointer>
#include <QScreen>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>

#include "MainWindow.h"
#include "constants.h"
#include "json/types/types.h"
#include "json/utils.h"
#include "widgets/RunewordDetailWidget.h"
#include <misc/qt_utils.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
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
	m_scrollAreaContent->setStyleSheet("background-color: #000000;");
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
	// 	readJsonFile(":/runeword_item_type_hierarchy.json").get<std::vector<ns::RuneWord>
	// >();

	m_scrollAreaLayout->addStretch();
	QList<QString> runeWordTitles;
	for (const auto& rw : runewords) {
		RunewordDetailWidget::QtRunewordDetailModel runeWordData;

		runeWordData.title = QString::fromStdString(rw.title);
		runeWordTitles << runeWordData.title;

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

	m_filterWidget->populateRuneWords(runeWordTitles);

	this->connect(m_filterWidget, &FilterWidget::runewordSelectionChanged, this, &MainWindow::onRunewordSelectionChange);
	this->connect(m_filterWidget, &FilterWidget::filterChanged, this, &MainWindow::onFilterChanged);

	// setup menu bar
	const QPointer bar = new QMenuBar(this);

	// set about dialog
	const QPointer action_about = new QAction(tr("&About"), this);
	this->connect(action_about, &QAction::triggered, this, [this] {
		QMessageBox::about(this, tr("About"),
											 QCoreApplication::applicationName() + "\n" + QCoreApplication::applicationVersion());
	});

	QMenu* fileMenuBar = menuBar()->addMenu(tr("&File"));
	fileMenuBar->addAction(action_about);

	this->setMenuBar(bar);
	this->setUnifiedTitleAndToolBarOnMac(true); // macos specific settings

	// Set the size of the main window
	this->resize(WIDTH, HEIGHT);
	this->show();
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
