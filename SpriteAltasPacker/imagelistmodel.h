#ifndef IMAGELISTMODEL_H
#define IMAGELISTMODEL_H
#include <QObject>
#include <QImage>
#include <QMap>
#include <QMapIterator>
#include "trimmedimageinfo.h"



class ImageListModel : public QObject
{
    Q_OBJECT
public:
    typedef QMap<QString, TrimmedImageInfo*> ImageMap;
    typedef typename ImageMap::Iterator ImageMapIterator;

    ImageListModel();
    virtual ~ImageListModel();

    void Add(const QString& s);
    void Remove(const QString& s);

    ImageMapIterator Begin(){
        return _images.begin();
    }
    ImageMap::Iterator End() {
        return _images.end();
    }

    void Clear();
    void beginEdit();
    void endEdit();


    int canvasWidth() const;
    int canvasHeight() const;
    QSize canvasSize() const;
    void setCanvasWidth(int w);
    void setCanvasHeight(int h);
    void setCanvasSize(const QSize& sz);
    void setCanvasSize(int w, int h);

    void setAllowTrimmed(bool allowTrimmed);
    bool allowTrimmed() const;

    void setAllowRotated(bool allowRotated);
    bool allowRotated() const;
signals:
    void imageListChanged();
    void canvasSizeChanged(const QSize& sz);
private:
    ImageMap    _images;
    bool        _imageListChanged;
    QSize       _canvasSize;
    bool        _allowTrimmed;
    bool        _allowRotated;

};

#endif // IMAGELISTMODEL_H
