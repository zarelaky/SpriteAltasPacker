#include "trimmedimageinfo.h"
#include <QDebug>
TrimmedImageInfo::TrimmedImageInfo()
{

}

TrimmedImageInfo::~TrimmedImageInfo()
{

}

void TrimmedImageInfo::reset() {
    _trimmed = _img.rect();
}

inline bool isTransparent(QRgb pixel) {
    return qAlpha(pixel) == 0;
}

void TrimmedImageInfo::trimmed() {
    if (!_img.hasAlphaChannel()) {
        return;
    }
    int minX = 0;
    bool minXReached(false);

    int minY = 0;
    bool minYReached(false);
    int maxX = _img.width() - 1;
    bool maxXReached(false);
    int maxY = _img.height() - 1;
    bool maxYReached(false);


    while (!maxXReached || !minXReached
            ||!minYReached || !maxYReached)
    {
        if (!minXReached || !maxXReached) {
            for (int y = minY; y <= maxY; ++y) {

                if (!minXReached && !isTransparent(_img.pixel(minX, y))) {
                    minXReached = true;
                }


                if (!maxXReached&& !isTransparent(_img.pixel(maxX, y))) {
                    maxXReached = true;
                }

            }
            if (!maxXReached) {
                --maxX;
            }
            if (!minXReached) {
                ++minX;
            }
        }
        if (!minYReached || !maxYReached) {
            for (int x = minX; x < maxX; ++x) {
                if (!minYReached) {
                    if (!isTransparent(_img.pixel(x, minY))) {
                        minYReached = true;
                    }
                }
                if (!maxYReached) {
                    if (!isTransparent(_img.pixel(x, maxY))) {
                        maxYReached = true;
                    }
                }
            }

            if (!maxYReached) {
                --maxY;
            }
            if (!minYReached) {
                ++minY;
            }
        }

    }
    _trimmed.setTopLeft(QPoint(minX, minY + 1));
    _trimmed.setBottomRight(QPoint(maxX, maxY + 1));
    qDebug() << "trimmed rect:" << _trimmed;
}

int TrimmedImageInfo::width() const {
    return _trimmed.width();
}

int TrimmedImageInfo::sourceWidth() const {
    return _img.width();
}

int TrimmedImageInfo::height() const {
    return _trimmed.height();
}

int TrimmedImageInfo::sourceHeight() const {
    return _img.height();
}

QPoint TrimmedImageInfo::sourceOrigin() const {
    return _trimmed.topLeft();
}

void TrimmedImageInfo::setImage(const QString& path) {
    if (_img.load(path)) {
        _trimmed = _img.rect();
    }
}

const QImage* TrimmedImageInfo::img() const {
    return &_img;
}
