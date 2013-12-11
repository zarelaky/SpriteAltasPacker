#include "FilesWidget.h"
#include "ui_filesview.h"


FilesWidget::FilesWidget(QWidget* p)
	: QDockWidget(p)
{
    Ui::FilesDockWidget* ui = new Ui::FilesDockWidget();
	ui->setupUi(this);
}

FilesWidget::~FilesWidget()
{
}
