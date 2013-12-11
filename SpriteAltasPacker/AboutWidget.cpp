#include "AboutWidget.h"
#include "ui_about.h"

AboutWidget::AboutWidget(QWidget* p /*=NULL*/)
	: QDialog(p)
{
    _ui = new Ui::About();
    _ui->setupUi(this);

}
AboutWidget::~AboutWidget()
{
}
