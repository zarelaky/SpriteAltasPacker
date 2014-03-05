#include "ContentWidget.h"
#include <QPainter>
#include <QMessageBox>
#include <QDebug>


ContentWidget::ContentWidget(QWidget* p)
: QWidget(p)
, _ilm(NULL)
, _heuristic(rbp::MaxRectsBinPack::RectBottomLeftRule)
{
    _bkgndBrush = new QBrush(QPixmap(":/res/images/thumb_bkgnd1.png"));
	rerender();
    _canvas = QImage(512,512, QImage::Format_ARGB32);

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
    p.drawImage(QPoint(0,0), _canvas);
}

void ContentWidget::resizeEvent(QResizeEvent* e)
{
    Q_UNUSED(e);
}

void ContentWidget::rerender()
{
	QPainter tp(&_canvas);

    _canvas.fill(Qt::transparent);


    ImagePlaceInfoMapIterator it(_ipis);
	QPen pen;
	pen.setColor(qRgb(255,0,0));
	pen.setWidth(2);
	tp.setPen(pen);
    while (it.hasNext())
    {
        QRect rc;
		it.next();
        rc.setX(it.value()->rc.x);
        rc.setY(it.value()->rc.y);
        rc.setWidth(it.value()->rc.width);
        rc.setHeight(it.value()->rc.height);
        TrimmedImageInfo* tii = it.value()->tii;
        tp.drawImage(rc.x(),
                     rc.y(),
                     *(tii->img()) ,
                     tii->sourceOrigin().x(),
                     tii->sourceOrigin().y(),
                     tii->width(),
                     tii->height());
    }
    update();

}

void ContentWidget::SetImageListModel(ImageListModel* ilm){
    _ilm = ilm;
}

void ContentWidget::SetCanvasSize(int w, int h)
{
    if (w != _canvas.width() || h != _canvas.height()) {
        _canvas = QImage(w, h, QImage::Format_ARGB32);
        setFixedSize(w, h);
        updateImagePlaceInfos();
    }
}
void ContentWidget::setCanvasSize(const QSize& sz) {
    SetCanvasSize(sz.width(), sz.height());
}



void ContentWidget::updateImagePlaceInfos()
{
    _rbp.Init(_canvas.width(), _canvas.height());
	qDebug() << "canvas:" << _canvas.width() << "," << _canvas.height() ;
    ImagePlaceInfoMapIterator it(_ipis);
    while (it.hasNext()) {
        delete it.next().value();
    }
    _ipis.clear();

    ImageListModel::ImageMapIterator i = _ilm->Begin();
    while (i != _ilm->End()) {
        const QString& key = i.key();
        int w = i.value()->width();
        int h = i.value()->height();

        rbp::Rect r = _rbp.Insert(w,h, _heuristic);
		qDebug() <<"texture:" << w << "," << h << "\n(" 
			<< r.x << "," << r.y << "," << r.width << "," << r.height << ")";
        if (r.width != 0 && r.height != 0) {
            ImagePlaceInfo* ipi = new ImagePlaceInfo;
            ipi->rc = r;
            ipi->rotated = (r.width == w && r.height == h);
            ipi->tii = i.value();
            _ipis[key]= ipi;
        } else {
            QMessageBox::warning(this, tr(""), key);
        }
        ++i;
    }
    rerender();
}

void ContentWidget::SetHeuristic(rbp::MaxRectsBinPack::FreeRectChoiceHeuristic heuristic)
{
    _heuristic = heuristic;

    updateImagePlaceInfos();
}



void ContentWidget::imageListChanged() {
    qDebug() << "imageListChanged " ;
    updateImagePlaceInfos();
}
