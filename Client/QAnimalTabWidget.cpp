#include "QAnimalTabWidget.h"

#include "QSliderButton.h"
#include <QStackedWidget.h>
#include <QVBoxLayout>


QAnimalTabWidget::QAnimalTabWidget(void)
{
	mSliderButton	= new QSliderButton(this);
	mStacked		= new QStackedWidget(this);
	mMainLayout		= new QVBoxLayout;

	mMainLayout->addWidget(mSliderButton);
	mMainLayout->addWidget(mStacked);
	this->setLayout(mMainLayout);
	mMainLayout->setContentsMargins(0, 0 ,0 ,0);
	mMainLayout->setSpacing(0);


    bool ret = connect(mSliderButton, SIGNAL(sig_itemClicked( QWidget*)), this, SLOT(OnChgWidget( QWidget*)));   
}


QAnimalTabWidget::~QAnimalTabWidget(void)
{
	delete mSliderButton;
	delete mStacked;
	delete mMainLayout;
}

bool QAnimalTabWidget::addItem( const QString& sName, QWidget* widget )
{
	//如果窗口已经增加
	if (-1 != mStacked->indexOf(widget))
	{
		return false;
	}

	//增加界面
	if (mSliderButton->addItem(sName, widget))
	{
		mStacked->addWidget(widget);
		return true;
	}
	return false;
}

void QAnimalTabWidget::OnChgWidget( QWidget* widget )
{
    //mSliderButton->ChangePage(widget);
	mStacked->setCurrentWidget(widget);
}

void QAnimalTabWidget::ChangWidget( QWidget* widget )
{
  mSliderButton->ChangePage(widget);
}
