#ifndef CHECKBOXIMAGEWIDGET_H
#define CHECKBOXIMAGEWIDGET_H

#include <QCheckBox>
#include <QGraphicsDropShadowEffect>
#include <QLabel>

class CheckBoxImageWidget final : public QWidget {
	Q_OBJECT

public:
	explicit CheckBoxImageWidget(const QString& imagePath, const QString& text, QWidget* parent = nullptr);

	// CheckBoxInterface implementation
	bool isChecked() const;
	void setChecked(bool checked) const;
	QString text() const;

protected:
	void mousePressEvent(QMouseEvent* event) override;

private slots:
	void toggleCheckboxState() const;
	void updateImageGlow() const;

private:
	QCheckBox* m_checkbox;
	QLabel* m_imageLabel;
	QLabel* m_textLabel;
	QGraphicsDropShadowEffect* m_glowEffect;
};

#endif // CHECKBOXIMAGEWIDGET_H