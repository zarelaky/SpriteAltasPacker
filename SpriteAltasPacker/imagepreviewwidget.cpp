#include "imagepreviewwidget.h"
#include "zoomableimagewidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
ImagePreviewWidget::ImagePreviewWidget() :
    QDockWidget()
{
    setMinimumSize(200,200);
    setWindowTitle(tr("Image Preview"));

    _img = new ZoomableImageWidget(this);
    this->setWidget(_img);
}


 ImagePreviewWidget::~ImagePreviewWidget()
 {

 }


 void ImagePreviewWidget::setImage(const QString& img) {

     _img->setPixmap(img);

 }
