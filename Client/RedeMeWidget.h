#ifndef REDEMEWIDGET_H
#define REDEMEWIDGET_H

#include <QWidget>
#include "ui_RedeMeWidget.h"

class RedeMeWidget : public QWidget
{
	Q_OBJECT

public:
	RedeMeWidget(QWidget *parent = 0);
	~RedeMeWidget();

private:
	Ui::RedeMeWidget ui;
};

#endif // REDEMEWIDGET_H
