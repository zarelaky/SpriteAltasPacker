#include "zoomableimagewidget.h"
#include <QPainter>

ZoomableImageWidget::ZoomableImageWidget(QWidget *parent) :
    QWidget(parent)
{
}

void ZoomableImageWidget::setPixmap(const QString &imagePath)
{
    if (imagePath.isEmpty()|| !_img.load(imagePath)) {
        _img = QPixmap();
    }
    update();

}

void ZoomableImageWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    if (!_img.isNull()) {
        QRect rc = rect();
        float k = (float)_img.width()/(float)_img.height();
        float h = rc.width()/k;
        float w = rc.height()*k;
        if (h > rc.height()) {
            h = rc.height();
        } else {
            w = rc.width();
        }
        rc.setWidth(w);
        rc.setHeight(h);
        p.drawPixmap(rc, _img);
    }
}
