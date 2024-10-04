#include "CheckBoxImageWidget.h"

#include <QHBoxLayout>
#include <QMouseEvent>

CheckBoxImageWidget::CheckBoxImageWidget(const QString& imagePath, const QString& text, QWidget* parent)
		: QWidget(parent), m_checkbox(new QCheckBox(text, this)), m_imageLabel(new QLabel(this)),
			m_glowEffect(new QGraphicsDropShadowEffect(this)) // Initialize glowEffect here
{
	m_checkbox->setContentsMargins(0, 0, 0, 0);
	m_checkbox->setFixedHeight(32);

	// Set the image in the QLabel
	if (const QPixmap imagePixmap(imagePath); imagePixmap.isNull()) {
		qDebug() << "Failed to load image:" << imagePath;
	} else {
		m_imageLabel->setPixmap(imagePixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		m_imageLabel->setScaledContents(true);
	}
	m_imageLabel->setSizePolicy(QSizePolicy::Fixed,
														QSizePolicy::Preferred); // Fixed width, preferred height
	m_imageLabel->setContentsMargins(0, 0, 0, 0);

	// Configure the glow effect
	m_glowEffect->setBlurRadius(16);
	m_glowEffect->setColor(Qt::white);
	m_glowEffect->setOffset(0, 0);
	m_glowEffect->setEnabled(m_checkbox->isChecked());

	m_imageLabel->setGraphicsEffect(m_glowEffect); // No glow by default

	// Set up the layout
	auto* layout = new QHBoxLayout(this);
	layout->addWidget(m_imageLabel);
	layout->addWidget(m_checkbox);
	layout->setSpacing(2);

	this->setContentsMargins(0, 0, 0, 0);

	setLayout(layout);

	// Connect the checkbox toggle
	this->connect(m_checkbox, &QCheckBox::toggled, this, &CheckBoxImageWidget::updateImageGlow);
}

bool CheckBoxImageWidget::isChecked() const { return m_checkbox->isChecked(); }

void CheckBoxImageWidget::setChecked(bool checked) const {
	m_checkbox->setChecked(checked);
	updateImageGlow();
}

QString CheckBoxImageWidget::text() const { return m_checkbox->text(); }

void CheckBoxImageWidget::mousePressEvent(QMouseEvent* event) {
	// Debug information
	// qDebug() << "Mouse pressed at:" << event->pos();
	// Ensure the widget's geometry is valid and handle clicks on the image, checkbox, and text
	if (m_imageLabel->geometry().contains(event->pos()) || m_checkbox->geometry().contains(event->pos())) {
		// qDebug() << "Widget area clicked.";
		toggleCheckboxState();
	} else {
		QWidget::mousePressEvent(event); // Call the base class implementation if needed
	}
}

void CheckBoxImageWidget::toggleCheckboxState() const { m_checkbox->setChecked(!m_checkbox->isChecked()); }

void CheckBoxImageWidget::updateImageGlow() const {
	if (m_imageLabel && m_glowEffect) {
		m_glowEffect->setEnabled(m_checkbox->isChecked());
	} else {
		qDebug() << "imageLabel or glowEffect is null.";
	}
}