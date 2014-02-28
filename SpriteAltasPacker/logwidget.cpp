#include "logwidget.h"
#include "ui_logview.h"
LogWidget::LogWidget()
{
    Ui::LogWidgetUI* ui = new Ui::LogWidgetUI();

    QWidget* w = new QWidget();
    ui->setupUi(w);
    setWidget(w);
    setWindowTitle(tr("LogView"));
}
