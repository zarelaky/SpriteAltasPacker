#include "ContentWidget.h"
#include <QPainter>


ContentWidget::ContentWidget(QWidget* p)
: QWidget(p)
{

	_canvas = QImage(512,512, QImage::Format_ARGB32);
    _bkgndBrush = new QBrush(QPixmap(":/res/images/thumb_bkgnd1.png"));
	rerender();

}

ContentWidget::~ContentWidget()
{
    if (_bkgndBrush) {
        delete _bkgndBrush;
    }
}

void ContentWidget::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);
	QPainter p(this);
    p.fillRect(rect(), *_bkgndBrush);
    //p.drawImage(QPoint(0,0), _canvas);
}

void ContentWidget::resizeEvent(QResizeEvent* e)
{
    Q_UNUSED(e);
}

void ContentWidget::rerender()
{
	QPainter tp(&_canvas);

	tp.fillRect(QRect(0,0,512,512), QBrush(qRgb(255,0,0)));

}
