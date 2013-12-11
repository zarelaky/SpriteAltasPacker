#include "PropertiesWidget.h"
#include "ui_propertiesview.h"

PropertiesWidget::PropertiesWidget(QWidget* p)
	: QDockWidget(p)
{
    Ui::PropertiesDockWidget* ui = new Ui::PropertiesDockWidget();
	ui->setupUi(this);
}

PropertiesWidget::~PropertiesWidget()
{
}
