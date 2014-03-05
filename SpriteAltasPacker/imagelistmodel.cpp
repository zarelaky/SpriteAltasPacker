#include "imagelistmodel.h"
#include <QDebug>

ImageListModel::ImageListModel()
    : _imageListChanged(false)
    , _canvasSize(1024,1024)
    , _allowTrimmed(false)
    , _allowRotated(false)
{
}



ImageListModel::~ImageListModel()
{
    ImageMap::Iterator i = _images.begin();
    while (i != _images.end()) {
	    delete i.value();
        ++i;
    }

    _images.clear();
}

void ImageListModel::Add(const QString& s) {
    if (!_images.contains(s)) {
        TrimmedImageInfo* p = new TrimmedImageInfo();
        p->setImage(s);
        _images[s] = p;
        _imageListChanged = true;
    }
}

void ImageListModel::Remove(const QString& s) {
    qDebug() << "remove:" << s;
    ImageMap::Iterator i = _images.find(s);
    Q_ASSERT(i != _images.end());
    if (i != _images.end()) {
        delete i.value();
        _images.remove(s);
        _imageListChanged = true;
    }
}

void ImageListModel::Clear()
{
    ImageMap::Iterator i = _images.begin();
    while (i != _images.end()) {
        delete i.value();
        ++i;
    }

    _images.clear();
}

void ImageListModel::beginEdit()
{
    _imageListChanged = false;
}

void ImageListModel::endEdit()
{
    if (_imageListChanged) {
        emit imageListChanged();
    }
}


int ImageListModel::canvasWidth() const {
    return _canvasSize.width();
}


int ImageListModel::canvasHeight() const {
    return _canvasSize.height();
}

QSize ImageListModel::canvasSize() const {
    return _canvasSize;
}
void ImageListModel::setCanvasSize(const QSize& sz) {
    _canvasSize = sz;
    emit canvasSizeChanged(_canvasSize);
}

void ImageListModel::setCanvasSize(int w, int h) {
    setCanvasSize(QSize(w,h));
}

void ImageListModel::setCanvasWidth(int w) {
    setCanvasSize(QSize(w, _canvasSize.height()));
}

void ImageListModel::setCanvasHeight(int h) {
     setCanvasSize(QSize( _canvasSize.width(),h));
}

void ImageListModel::setAllowTrimmed(bool allowTrimmed) {
    _allowTrimmed = allowTrimmed;
    ImageMapIterator i = Begin();
    // apply trimmed
    while (i!= End()) {
        if (allowTrimmed) {
            (*i)->trimmed();
        } else {
            (*i)->reset();
        }
        ++i;
    }
    emit imageListChanged();
}

void ImageListModel::setAllowRotated(bool allowRotated)
{
    _allowRotated = allowRotated;
}
bool ImageListModel::allowRotated() const {
    return _allowRotated;
}

