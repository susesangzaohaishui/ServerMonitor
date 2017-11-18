#pragma once

#include <QWidget>

class QSliderButton;
class QStackedWidget;
class QVBoxLayout;

class QAnimalTabWidget : public QWidget
{
	Q_OBJECT
public:
	QAnimalTabWidget(void);
	virtual ~QAnimalTabWidget(void);
	bool addItem(const QString& sName, QWidget* widget);
    void ChangWidget(QWidget* widget);
public slots:
	void OnChgWidget( QWidget* widget);
signals:
private:
	QSliderButton*	mSliderButton;
	QStackedWidget*	mStacked;
	QVBoxLayout*	mMainLayout;
};

