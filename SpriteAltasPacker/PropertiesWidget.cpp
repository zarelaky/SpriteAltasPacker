#include "PropertiesWidget.h"
#include "imagelistmodel.h"
#include "ui_propertiesview.h"


static int geometry_wx []= { 128,
                          256,
                          512,
                          1024,
                          2048,
                          4096,
                          8192,
                          16384,
                        -1};

PropertiesWidget::PropertiesWidget(QWidget* p, ImageListModel* ilm)
	: QDockWidget(p)
    , _ilm(ilm)
{
    _ui = new Ui::PropertiesDockWidget();
    _ui->setupUi(this);


    for (int i = 0; geometry_wx[i] != -1; ++i) {
        _ui->cmbMaxH->addItem(QString("%1").arg(geometry_wx[i]));
        _ui->cmbMaxW->addItem(QString("%1").arg(geometry_wx[i]));
    }
    _ui->cmbMaxH->setCurrentIndex(_ui->cmbMaxH->findText(QString("%1").arg(_ilm->canvasHeight())));
    _ui->cmbMaxW->setCurrentIndex(_ui->cmbMaxW->findText(QString("%1").arg(_ilm->canvasHeight())));

}

PropertiesWidget::~PropertiesWidget()
{

}

void PropertiesWidget::formatIndexChange(int)
{

}

void PropertiesWidget::trimedChanged(int checkState)
{
    _ilm->setAllowTrimmed(Qt::Checked == checkState);
}

void PropertiesWidget::rotatedChanged(int checkState)
{

    _ilm->setAllowRotated(Qt::Checked == checkState);

}
void PropertiesWidget::interSpaceChanged(int)
{

}

void PropertiesWidget::widthTextChange(QString width)
{
    bool ok(false);
    int v = width.toInt(&ok);
    if (ok) {
        _ilm->setCanvasWidth(v);
    }
}

void PropertiesWidget::heightTextChange(QString height)
{
    bool ok(false);
    int v = height.toInt(&ok);
    if (ok) {
        _ilm->setCanvasHeight(v);
    }
}

void PropertiesWidget::savePath()
{

}
