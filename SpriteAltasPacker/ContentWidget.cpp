#include "ContentWidget.h"
#include <QPainter>


ContentWidget::ContentWidget(QWidget* p)
: QWidget(p)
{

	_canvas = QImage(512,512, QImage::Format_ARGB32);
	rerender();

}

ContentWidget::~ContentWidget()
{
}

void ContentWidget::paintEvent(QPaintEvent* e)
{
	QPainter p(this);
	p.drawImage(QPoint(0,0), _canvas);
}

void ContentWidget::resizeEvent(QResizeEvent* e)
{
}

void ContentWidget::rerender()
{
	QPainter tp(&_canvas);
	tp.fillRect(QRect(0,0,512,512), QBrush(qRgb(255,0,0)));

}
