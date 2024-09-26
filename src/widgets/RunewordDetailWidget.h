#ifndef RUNEWORDDETAILWIDGET_H
#define RUNEWORDDETAILWIDGET_H

#include <QLabel>
#include <QStringList>

class RunewordDetailWidget final : public QWidget {
	Q_OBJECT

public:
	struct QtRunewordDetailModel {
		QString title;					 // NOLINT(*-identifier-naming)
		QString version;				 // NOLINT(*-identifier-naming)
		QStringList runes;			 // NOLINT(*-identifier-naming)
		QStringList attributes;	 // NOLINT(*-identifier-naming)
		int levelRequirement;		 // NOLINT(*-identifier-naming)
		bool isClosedBnetLadder; // NOLINT(*-identifier-naming)
		int socketsNeeded;			 // NOLINT(*-identifier-naming)
		QStringList itemTypes;	 // NOLINT(*-identifier-naming)
	};
	explicit RunewordDetailWidget(const QtRunewordDetailModel& runeWord, QWidget* parent = nullptr);

	QtRunewordDetailModel getRuneWord() const;

private:
	QtRunewordDetailModel m_runeword;
	void setupUI(const QtRunewordDetailModel& runeWord);

	QWidget* createTitleAndRunesSection(const QtRunewordDetailModel& runeWord);
	QWidget* createAttributesSection(const QtRunewordDetailModel& runeWord);
	QWidget* createVersionAndCompatibilitySection(const QtRunewordDetailModel& runeWord);
};

#endif // RUNEWORDDETAILWIDGET_H